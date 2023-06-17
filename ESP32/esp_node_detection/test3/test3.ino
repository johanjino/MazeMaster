////////////////////////////   INCLUDES   /////////////////////////////////
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


////////////////////////////  INITIALIZATIONS  //////////////////////////// 
const char* ssid = "NOWEARIH";
const char* password = "IR1W7GzkXv4I";
const char* serverURL = "http://192.168.0.22:8080/process";

float test_array[4][4] = {
  {NULL, 2.2, 3.3, 4.4},
  {5.5, 6.6, 7.7, 8.8},
  {9.9, 10.1, 11.2, 12.3},
  {13.4, 14.5, NULL, 16}
};

#define SAMPLES 4
#define DATA_ELEMENTS 7 // R_area, B_area, Y_area, offset, R_turn, F_turn, L_turn
#define ABSOLUTE_ERROR 10

float Image[4] = {};
float Cam_Data[DATA_ELEMENTS] = {};
float Curr_Data[DATA_ELEMENTS] = {};
float Node_Data[4][4];
static float Cam_Data_Buff[SAMPLES][DATA_ELEMENTS] = {};
int image_number = 0;
bool register_new_image = false;
String response = "";

enum possible_states {taking_images, done_taking_images, go_forward, at_junction, take_turn};
possible_states bot_state;


////////////////////////////   FUNCTIONS   ////////////////////////////
void get_Cam_Data(float Cam_Data[DATA_ELEMENTS]){
  //retrns Cam_Data(R_area, B_area, Y_area, offset, R_turn, F_turn, L_turn)
}

float get_compass_angle() {
  //retuns the heading angle
}

void connect_WiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

String send_and_receive(float Node_Data[4][4]) {
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

void make_image(float Curr_Data[DATA_ELEMENTS], float Image[4]) {
  float R_area = Curr_Data[0];
  float B_area = Curr_Data[1];
  float Y_area = Curr_Data[2];

  float compass_angle = get_compass_angle();

  Image[0] = R_area;
  Image[1] = B_area;
  Image[2] = Y_area;
  Image[3] = compass_angle;
}

void init_buffer(){
  for (int i = 0; i < SAMPLES; i++){
    get_Curr_Data(Curr_Data);
  }
}

void get_Curr_Data(float Curr_Data[DATA_ELEMENTS]) {
  get_Cam_Data(Cam_Data);

  for (int i = 0; i < SAMPLES - 1; i++) {
    for (int j = 0; j < DATA_ELEMENTS; j++) {
      Cam_Data_Buff[i][j] = Cam_Data_Buff[i + 1][j];
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
    Curr_Data[i] = sum / SAMPLES;
  }
}

bool is_same(float first_image[4], float curr_image[4]) {
  for (int i = 0; i < 4; i++) {
    if (  abs(first_image[i]-curr_image[i]) > ABSOLUTE_ERROR  ) { 
      return false;
    }
  }
  return true; 
}

void reset_Node_Data(float Node_Data[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            Node_Data[i][j] = 0;
        }
    }
}


////////////////////////////   SETUP   //////////////////////////// 
void setup() {

  init_buffer();
  reset_Node_Data(Node_Data);

  bot_state = go_forward;

  connect_WiFi();

}


////////////////////////////   LOOP   //////////////////////////// 
void loop() {
  
  get_Curr_Data(Curr_Data);

  switch(bot_state){
    case go_forward:
      if (Curr_Data[4]==0 && Curr_Data[5]==1 && Curr_Data[6]==0){
        //make bot go few steps ahead
        break;
      }
      else if (Curr_Data[4]==1 || Curr_Data[6]==1){
        //make bot go few steps ahead to junction/node/turning point centre
        bot_state = at_junction;
        break;
      }
      else {
        break;
      }

    case at_junction:
        bot_state = taking_images;
        break;

    case taking_images:
      make_image(Curr_Data, Image);
      Node_Data[0][image_number] = Image;
      //make bot turn a few steps right
      //make bot turn a few steps right
      get_Curr_Data(Curr_Data)
      make_image(Curr_Data, Image);

      while( ! is_same(Node_Data[0], Image) ){
        get_Curr_Data(Curr_Data)
        if (Curr_Data[5] == 0){
          register_new_image = true;
        }

        if (register_new_image == true && Curr_Data[5] == 1 && image_number < 3){
          image_number++;
          make_image(Curr_Data, Image);
          Node_Data[0] = Image;
          register_new_image = false;
        }
        else if (register_new_image == true && Curr_Data[5] == 1 && image_number == 3){
          make_image(Curr_Data, Image);
        }
        //make the bot trun right 
      }

      bot_state = done_taking_images;
      break;

    case done_taking_images:
      send_and_receive(Node_Data);
      reset_Node_Data(Node_Data);
      image_number = 0;
      register_new_image = false;
      bot_state = take_turn;
      break;

    case take_turn:
      if (Curr_Data[4]==1){
        //make bot turn a few steps right
      }
      else{
        //make bot turn a few steps left
      }
    
      bot_state = go_forward;
      break;
  
    default:
      bot_state = go_forward;
      break;

  }


}