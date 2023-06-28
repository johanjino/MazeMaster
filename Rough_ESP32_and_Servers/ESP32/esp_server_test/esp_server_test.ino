////////////////////////////   INCLUDES   /////////////////////////////////
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

////////////////////////////  INITIALIZATIONS  //////////////////////////// 
const char* ssid = "Alvi";
const char* password = "alvi12345";
const char* serverURL = "http://172.20.10.2:8080/process";

float test_array[4][4] = {
  {NULL, 2.2, 3.3, 4.4},
  {5.5, 6.6, 7.7, 8.8},
  {9.9, 10.1, 11.2, 12.3},
  {13.4, 14.5, NULL, 16}
};

#define SAMPLES 4
#define DATA_ELEMENTS 7
#define ACCEPTABLE_ERROR_PERCENTAGE 10

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





void setup() {
  Serial.begin(9600);
  delay(100);
  connect_WiFi();
}

void loop() {

  if (Serial.available() > 0) {
    if (Serial.read() == '1') {
    response = send_and_receive(test_array);
    Serial.print(response);
    }
  }

}
