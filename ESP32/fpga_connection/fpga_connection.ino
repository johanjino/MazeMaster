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

// void get_Cam_Data(uint32_t Cam_Data[DATA_ELEMENTS]){
//   //returns Cam_Data(R_area, B_area, Y_area, offset, R_turn, F_turn, L_turn)
//   portENTER_CRITICAL(&core0Mutex);
  
//   uint32_t Red = *memAddress1;
//   uint32_t Yellow = *memAddress2;
//   uint32_t Blue = *memAddress3;
//   uint32_t Offset = *memAddress4;
//   uint32_t Right = *memAddress5;
//   uint32_t Left = *memAddress6;
//   uint32_t Forward = *memAddress6;

//   portEXIT_CRITICAL(&core0Mutex);

//   Cam_Data[0] = Red;
//   Cam_Data[1] = Yellow;
//   Cam_Data[2] = Blue;
//   Cam_Data[3] = Offset;
//   Cam_Data[4] = Right;
//   Cam_Data[5] = Left;
//   Cam_Data[6] = Forward;


// }

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

void setup() {
  Serial.begin(115200);

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
}

void loop() {
  if (Serial.available()) {
    if (Serial.read() == '1') {
      read_data();
    }
  }
}
