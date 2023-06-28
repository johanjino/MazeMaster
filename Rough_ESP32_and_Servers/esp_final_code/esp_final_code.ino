////////////////////////////   INCLUDES   /////////////////////////////////
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <AccelStepper.h>
#include <cmath>

////////////////////////////  INITIALIZATIONS  //////////////////////////// 
const char* ssid = "johan";
const char* password = "password";
const char* serverURL = "http://192.168.43.199:8080/process";

const int stepsPerRevolution = 100;
double F = 0;
int dir1 = 14;
int dir2 = 26;
int step1 = 12;
int step2 = 27;

#define SAMPLES 4
#define DATA_ELEMENTS 7 // R_area, Y_area, B_area, offset, R_turn, L_turn, F_turn
#define ABSOLUTE_ERROR 10

#define DECLINATION 0.72 
unsigned char CMPS2_address = 0x30; 
float Max[2], Mid[2], Min[2], X, Y;

int32_t Image[4] = {0};
int32_t Cam_Data[DATA_ELEMENTS] = {0};
int32_t Curr_Data[DATA_ELEMENTS] = {0};
int32_t Node_Data[4][4] = {0};
static int32_t Cam_Data_Buff[SAMPLES][DATA_ELEMENTS] = {0};
int image_number = 0;
bool register_new_image = false;
String response = "";
int curr_angle = 0;

enum possible_states {taking_images, done_taking_images, go_forward, at_junction, take_turn};
possible_states bot_state;

#define RX_PIN 16
#define TX_PIN 17
#define DATA_SIZE 4 //bytes

TaskHandle_t core0Task;
portMUX_TYPE core0Mutex = portMUX_INITIALIZER_UNLOCKED;

// Memory addresses to write to
volatile uint32_t* memAddress1 = reinterpret_cast<uint32_t*>(0x3FFFC000);
volatile uint32_t* memAddress2 = reinterpret_cast<uint32_t*>(0x3FFFC004);
volatile uint32_t* memAddress3 = reinterpret_cast<uint32_t*>(0x3FFFC008);
volatile uint32_t* memAddress4 = reinterpret_cast<uint32_t*>(0x3FFFC00C);
volatile uint32_t* memAddress5 = reinterpret_cast<uint32_t*>(0x3FFFC010);
volatile uint32_t* memAddress6 = reinterpret_cast<uint32_t*>(0x3FFFC014);
volatile uint32_t* memAddress7 = reinterpret_cast<uint32_t*>(0x3FFFC018);


////////////////////////////   FUNCTIONS   ////////////////////////////
int32_t get_compass_angle() {
  float measured_angle = CMPS2_getHeading();
  measured_angle = measured_angle - 135;
  measured_angle = measured_angle * 100;
  int result = static_cast<int>(measured_angle);
  return result;
}

float CMPS2_getHeading(void) {
  float components[2];
  CMPS2_set(false);   
  CMPS2_read_XYZ(); 
  components[0] = X;  
  components[1] = Y;
  CMPS2_set(true);  
  CMPS2_read_XYZ();  

  components[0] = (components[0] - X) / 2.0;
  components[1] = (components[1] - Y) / 2.0;

  float temp0 = 0;
  float temp1 = 0;
  float deg = 0;

  if (components[0] < Mid[0])
  {
    if (components[1] > Mid[1])
    {
      //Quadrant 1
      temp0 = components[1] - Mid[1];
      temp1 = Mid[0] - components[0];
      deg = 90 - atan(temp0 / temp1) * (180 / 3.14159);
    }
    else
    {
      //Quadrant 2
      temp0 = Mid[1] - components[1];
      temp1 = Mid[0] - components[0];
      deg = 90 + atan(temp0 / temp1) * (180 / 3.14159);
    }
  }
  else {
    if (components[1] < Mid[1])
    {
      //Quadrant 3
      temp0 = Mid[1] - components[1];
      temp1 = components[0] - Mid[0];
      deg = 270 - atan(temp0 / temp1) * (180 / 3.14159);
    }
    else
    {
      //Quadrant 4
      temp0 = components[1] - Mid[1];
      temp1 = components[0] - Mid[0];
      deg = 270 + atan(temp0 / temp1) * (180 / 3.14159);
    }
  }

  //correct heading
  deg += DECLINATION;
  if (DECLINATION > 0)
  {
    if (deg > 360) {
      deg -= 360;
    }
  }
  else
  {
    if (deg < 0) {
      deg += 360;
    }
  }

  return deg;
}

//reads measurements in mG
void CMPS2_read_XYZ(void) {
  //command internal control register 0 bit 0 (measure)
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(8);

  //wait for measurement to be completed
  bool flag = false;
  while (!flag) {
    //jump to status register
    Wire.beginTransmission(CMPS2_address);
    Wire.write(0x06);
    Wire.endTransmission();

    //read its value
    Wire.requestFrom(CMPS2_address, (uint8_t)1);
    int temporal = 0;
    if (Wire.available()) {
      temporal = Wire.read();
    }

    //if the last bit is 1, data is ready
    temporal &= 1;
    if (temporal != 0) {
      flag = true;
    }
  }

  //move address pointer to first address
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x00);
  Wire.endTransmission();

  //save data
  Wire.requestFrom(CMPS2_address, (uint8_t)6);
  byte tmp[6] = {0, 0, 0, 0, 0, 0}; //array for raw data
  if (Wire.available()) {
    for (int i = 0; i < 6; i++) {
      tmp[i] = Wire.read(); //save it
    }
  }

  //initialize array for data
  float measured_data[2];

  //reconstruct raw data
  measured_data[0] = 1.0 * (int)(tmp[1] << 8 | tmp[0]); //x
  measured_data[1] = 1.0 * (int)(tmp[3] << 8 | tmp[2]); //y

  //convert raw data to mG
  for (int i = 0; i < 2; i++) {
    measured_data[i] = 0.48828125 * (float)measured_data[i];
  }

  X = measured_data[0];
  Y = measured_data[1];

  //correct minimum, mid and maximum values
  if (measured_data[0] > Max[0]) { //x max
    Max[0] = measured_data[0];
  }
  if (measured_data[0] < Min[0]) { //x min
    Min[0] = measured_data[0];
  }
  if (measured_data[1] > Max[1]) { //y max
    Max[1] = measured_data[1];
  }
  if (measured_data[1] < Min[1]) { //y min
    Min[1] = measured_data[1];
  }
  for (int i = 0; i < 2; i++) { //mid
    Mid[i] = (Max[i] + Min[i]) / 2;
  }

  return;
}

//initialize the compass
void CMPS2_init(void) {
  Wire.begin(); // initialization of I2C bus

  //command internal control register 0 for set operation
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x20);
  Wire.endTransmission();
  delay(10);

  //command internal control register 1 to 16 bit resolution, 8ms measurement time
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x08);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);

  //initialize minimum, mid and maximum values
  for (int i = 0; i < 2; i++) {
    Max[i] = -32768;  //smallest int on 16 bits
    Min[i] = 32767;  //largest int on 16 bits
    Mid[i] = 0;
  }
}

//sets/resets the sensor, changing the magnetic polarity of the sensing element
void CMPS2_set(bool reset) {
  //command internal control register 0 bit 7 (capacitor recharge)
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x80);
  Wire.endTransmission();
  delay(50);

  if (reset) {
    //command internal control register 0 bit 6 (reset)
    Wire.beginTransmission(CMPS2_address);
    Wire.write(0x07);
    Wire.write(0x40);
    Wire.endTransmission();
    delay(10);
  }
  else {
    //command internal control register 0 bit 5 (set)
    Wire.beginTransmission(CMPS2_address);
    Wire.write(0x07);
    Wire.write(0x20);
    Wire.endTransmission();
    delay(10);
  }
  return;
}

uint32_t get_data() {
  byte buffer[DATA_SIZE];

  // Read the incoming bytes into the buffer
  for (int i = 0; i < DATA_SIZE; i++) {
    buffer[i] = Serial2.read();
  }

  std::swap(buffer[0], buffer[3]);
  std::swap(buffer[1], buffer[2]);

  uint32_t value = (static_cast<uint32_t>(buffer[0]) << 24) |
                   (static_cast<uint32_t>(buffer[1]) << 16) |
                   (static_cast<uint32_t>(buffer[2]) << 8) |
                   (static_cast<uint32_t>(buffer[3]));

  return value;
}

void read_data() {
  portENTER_CRITICAL(&core0Mutex);
  
  uint32_t readData1 = *memAddress1;
  uint32_t readData2 = *memAddress2;
  uint32_t readData3 = *memAddress3;
  uint32_t readData4 = *memAddress4;
  uint32_t readData5 = *memAddress5;
  uint32_t readData6 = *memAddress6;
  uint32_t readData7 = *memAddress7;

  portEXIT_CRITICAL(&core0Mutex);

  if (readData1 == 304964){
    readData1 = 0;
  }
  if (readData2 == 304964){
    readData2 = 0;
  }
  if (readData3 == 304964){
    readData3 = 0;
  }
  int32_t signedData4 = static_cast<int32_t>(readData4);

  Serial.println("Full Data obtained: ");
  Serial.print(readData1);
  Serial.print("  ");
  Serial.print(readData2);
  Serial.print("  ");
  Serial.print(readData3);
  Serial.print("  ");
  Serial.print(signedData4);
  Serial.print("  ");
  Serial.print(readData5);
  Serial.print("  ");
  Serial.print(readData6);
  Serial.print("  ");
  Serial.print(readData7);
  Serial.println(" "); 
}

void get_Cam_Data(int32_t Cam_Data[DATA_ELEMENTS]){
  //returns Cam_Data(R_area, B_area, Y_area, offset, R_turn, F_turn, L_turn)
  portENTER_CRITICAL(&core0Mutex);
  
  uint32_t Red = *memAddress1;
  uint32_t Yellow = *memAddress2;
  uint32_t Blue = *memAddress3;
  uint32_t Offset_raw = *memAddress4;
  uint32_t Right = *memAddress5;
  uint32_t Left = *memAddress6;
  uint32_t Forward = *memAddress7;

  portEXIT_CRITICAL(&core0Mutex);

  if (Red == 304964){
    Red = 0;
  }
  if (Yellow == 304964){
    Yellow = 0;
  }
  if (Blue == 304964){
    Blue = 0;
  }
  int32_t Offset = static_cast<int32_t>(Offset_raw);


  Cam_Data[0] = Red;
  Cam_Data[1] = Yellow;
  Cam_Data[2] = Blue;
  Cam_Data[3] = Offset;
  Cam_Data[4] = Right;
  Cam_Data[5] = Left;
  Cam_Data[6] = Forward;


}

void Core0Task(void* parameter) {
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);

  while (true) {
    if (Serial2.available() >= DATA_SIZE) {
      uint32_t value = get_data();
      uint32_t data;
      if (value == 0x00524242) {
        data = get_data();
        portENTER_CRITICAL(&core0Mutex);
        memcpy((void*)memAddress1, &data, sizeof(data));
        data = get_data();
        memcpy((void*)memAddress2, &data, sizeof(data));
        data = get_data();
        memcpy((void*)memAddress3, &data, sizeof(data));
        data = get_data();
        memcpy((void*)memAddress4, &data, sizeof(data));
        data = get_data();
        memcpy((void*)memAddress5, &data, sizeof(data));
        data = get_data();
        memcpy((void*)memAddress6, &data, sizeof(data));
        data = get_data();
        memcpy((void*)memAddress7, &data, sizeof(data));
        portEXIT_CRITICAL(&core0Mutex);
      }
    //   } else if (value == 0x00594242) {
    //     data = get_data();
    //     portENTER_CRITICAL(&core0Mutex);
    //     memcpy((void*)memAddress3, &data, sizeof(data));
    //     data = get_data();
    //     memcpy((void*)memAddress4, &data, sizeof(data));
    //     portEXIT_CRITICAL(&core0Mutex);
    //   } else if (value == 0x00424242) {
    //     data = get_data();
    //     portENTER_CRITICAL(&core0Mutex);
    //     memcpy((void*)memAddress5, &data, sizeof(data));
    //     data = get_data();
    //     memcpy((void*)memAddress6, &data, sizeof(data));
    //     portEXIT_CRITICAL(&core0Mutex);
    //   }
    // }
    }
    delay(1);  // Add a small delay to allow other tasks to run
  }
}

void connect_WiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

String send_and_receive(int32_t Node_Data[4][4]) {
  HTTPClient http;

  http.begin(serverURL);
  http.addHeader("Content-Type", "application/json");

  const int rows = 4;
  const int cols = 4;
  StaticJsonDocument<1024> jsonDocument;
  JsonArray jsonArray = jsonDocument.to<JsonArray>();

  for (int i = 0; i < rows; i++) {
    JsonArray rowArray = jsonArray.createNestedArray();
    for (int j = 0; j < cols; j++) {
      rowArray.add(Node_Data[i][j]);
    }
  }

  String payload;
  serializeJson(jsonArray, payload);

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    String response = http.getString();
    return response;
  }
  else{
    return "Sending to server is unsuccessful :(";
  }

  http.end();
}

void add_image(int32_t Node_Data[4][4], int32_t Image[4], int image_index){
  for (int i = 0; i < 4; i++) {
    Node_Data[image_index][i] = Image[i];
  }
}

void make_image(int32_t Curr_Data[DATA_ELEMENTS], int32_t Image[4]) {
  float R_area = Curr_Data[0];
  float Y_area = Curr_Data[1];
  float B_area = Curr_Data[2];

  int32_t compass_angle = get_compass_angle();

  Image[0] = R_area;
  Image[1] = Y_area;
  Image[2] = B_area;
  Image[3] = compass_angle;
}

void get_Curr_Data(int32_t Curr_Data[DATA_ELEMENTS]) {
  get_Cam_Data(Cam_Data);

  for (int i = 0; i < SAMPLES - 1; i++) {
    for (int j = 0; j < DATA_ELEMENTS; j++) {
      Cam_Data_Buff[i][j] = Cam_Data_Buff[i + 1][j];
      delay(50);
    }
  }

  for (int i = 0; i < DATA_ELEMENTS; i++) {
    Cam_Data_Buff[SAMPLES - 1][i] = Cam_Data[i];
  }
  for (int i = 0; i < DATA_ELEMENTS; i++) {
    float sum = 0;
    for (int j = 0; j < SAMPLES; j++) {
      sum += Cam_Data_Buff[j][i];
    }
    Curr_Data[i] = round(sum / SAMPLES);
  }
}

void init_buffer(){
  for (int i = 0; i < SAMPLES; i++){
    get_Curr_Data(Curr_Data);
  }
}

bool is_same(int32_t first_image[4], int32_t curr_image[4]) {
  for (int i = 0; i < 4; i++) {
    if (  abs(first_image[i]-curr_image[i]) > ABSOLUTE_ERROR  ) { 
      return false;
    }
  }
  return true; 
}

void reset_Node_Data(int32_t Node_Data[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            Node_Data[i][j] = 0;
        }
    }
}

void move_bot(int roverState){

     if(roverState == 1){ //Forward
        Serial.print("F");
        digitalWrite(dir1, HIGH);
        digitalWrite(dir2, LOW);
          for(int i=0; i<100; i++){
            digitalWrite(step1, HIGH);
            digitalWrite(step2, HIGH);
            delay(10);
            digitalWrite(step1, LOW);
            digitalWrite(step2, LOW);
            delay(10);

          }
      }

      else if (roverState == 4){ //Backward
        Serial.print("B");
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, HIGH);
        for(int i=0; i<100; i++){
            digitalWrite(step1, HIGH);
            digitalWrite(step2, HIGH);
            delay(10);
            digitalWrite(step1, LOW);
            digitalWrite(step2, LOW);
            delay(10);
          }
      }

      else if (roverState == 2){ //Right
        Serial.print("R");
        digitalWrite(dir1, HIGH);
        digitalWrite(dir2, HIGH);
        for(int i=0; i<100; i++){
            digitalWrite(step1, HIGH);
            digitalWrite(step2, HIGH);
            delay(10);
            digitalWrite(step1, LOW);
            digitalWrite(step2, LOW);
            delay(10);
          }
      }

      else if (roverState == 3){ //Left
        Serial.print("L");
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, LOW);
        for(int i=0; i<100; i++){
            digitalWrite(step1, HIGH);
            digitalWrite(step2, HIGH);
            delay(10);
            digitalWrite(step1, LOW);
            digitalWrite(step2, LOW);
            delay(10);
          }
      }

}


////////////////////////////   SETUP   //////////////////////////// 
void setup() {
   move_bot(1);

  Serial.begin(9600);
  delay(100);
  connect_WiFi();

  // Create Core 0 task
  xTaskCreatePinnedToCore(
      Core0Task,    // Task function
      "Core0Task",  // Task name (optional)
      10000,        // Stack size (bytes)
      NULL,         // Task parameters (optional)
      1,            // Task priority
      &core0Task,   // Task handle
      0             // Core to run the task on (Core 0)
  );

  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(step1, OUTPUT);
  pinMode(step2, OUTPUT);

  init_buffer();
  reset_Node_Data(Node_Data);

  bot_state = go_forward;

  delay(10);
  CMPS2_init(); 
  delay(500);
  move_bot(1);
}


////////////////////////////   LOOP   //////////////////////////// 
void loop() {
  
  get_Curr_Data(Curr_Data);  // R_area, Y_area, B_area, offset, R_turn, L_turn, F_turn

  switch(bot_state){
    case go_forward:
      // if (Curr_Data[4]==0 && Curr_Data[5]==0 && Curr_Data[6]==0){
      //   move_bot(1);
      //   break;
      // }
      // else if (Curr_Data[4]==1 || Curr_Data[6]==1){
      //   move_bot(1);
      //   bot_state = at_junction;
      //   break;
      // }
      // else {
      //   break;
      // }
      move_bot(1);
      break;

    case at_junction:
        bot_state = taking_images;
        break;

    case taking_images:
      make_image(Curr_Data, Image);
      add_image(Node_Data, Image, image_number);
      move_bot(2);
      get_Curr_Data(Curr_Data);
      make_image(Curr_Data, Image);

      while( ! is_same(Node_Data[0], Image) ){
        get_Curr_Data(Curr_Data);
        if (Curr_Data[6] == 1){
          register_new_image = true;
        }
        if (register_new_image == true && Curr_Data[6] == 0 && image_number < 3){
          image_number++;
          make_image(Curr_Data, Image);
          add_image(Node_Data, Image, image_number);
          register_new_image = false;
        }
        else if (register_new_image == true && Curr_Data[6] == 0 && image_number == 3){
          break;
        }
        move_bot(2);
      }
      bot_state = done_taking_images;
      break;

    case done_taking_images:
      int response;
      response = send_and_receive(Node_Data).toInt();
      reset_Node_Data(Node_Data);
      image_number = 0;
      register_new_image = false;
      int angle_max;
      angle_max = response * 1.2;
      int angle_min;
      angle_min = response * 0.8;
      curr_angle = get_compass_angle();
      while( !(curr_angle>angle_min && curr_angle<angle_max)){
        move_bot(2);
        curr_angle = get_compass_angle();
      }
      bot_state = go_forward;
      break;

    default:
      bot_state = go_forward;
      break;
  }

}