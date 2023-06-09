#define RX_PIN 16
#define TX_PIN 17
#define DATA_SIZE 4

TaskHandle_t core0Task;
portMUX_TYPE core0Mutex = portMUX_INITIALIZER_UNLOCKED;

// Memory addresses to write to
volatile uint32_t* memAddress1 = reinterpret_cast<uint32_t*>(0x3FFFC000);
volatile uint32_t* memAddress2 = reinterpret_cast<uint32_t*>(0x3FFFC004);
volatile uint32_t* memAddress3 = reinterpret_cast<uint32_t*>(0x3FFFC008);
volatile uint32_t* memAddress4 = reinterpret_cast<uint32_t*>(0x3FFFC00C);
volatile uint32_t* memAddress5 = reinterpret_cast<uint32_t*>(0x3FFFC010);
volatile uint32_t* memAddress6 = reinterpret_cast<uint32_t*>(0x3FFFC014);

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

  portEXIT_CRITICAL(&core0Mutex);

  Serial.println("Full Data obtained: ");
  Serial.print(readData1, HEX);
  Serial.print("  ");
  Serial.print(readData2, HEX);
  Serial.print("\t");
  Serial.print(readData3, HEX);
  Serial.print("  ");
  Serial.print(readData4, HEX);
  Serial.print("\t");
  Serial.print(readData5, HEX);
  Serial.print("  ");
  Serial.print(readData6, HEX);
  Serial.println(" ");
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
        portEXIT_CRITICAL(&core0Mutex);
      } else if (value == 0x00594242) {
        data = get_data();
        portENTER_CRITICAL(&core0Mutex);
        memcpy((void*)memAddress3, &data, sizeof(data));
        data = get_data();
        memcpy((void*)memAddress4, &data, sizeof(data));
        portEXIT_CRITICAL(&core0Mutex);
      } else if (value == 0x00424242) {
        data = get_data();
        portENTER_CRITICAL(&core0Mutex);
        memcpy((void*)memAddress5, &data, sizeof(data));
        data = get_data();
        memcpy((void*)memAddress6, &data, sizeof(data));
        portEXIT_CRITICAL(&core0Mutex);
      }
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
