#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "johan";
const char* password = "password";

const char* serverURL = "http://192.168.43.199:8080/process";

////////////////////////////   INITIALIZATIONS   //////////////////////////// 
float Node_Data[4][4];


float test_array[4][4] = {
  {0, 2.2, 3.3, 4.4},
  {5.5, 6.6, 7.7, 8.8},
  {9.9, 10.1, 11.2, 12.3},
  {13.4, 14.5, 15.6, 16}
};

void connect_WiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void send_and_receive(float Node_Data[4][4]) {
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
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    String response = http.getString();
    Serial.print("Server response: ");
    Serial.println(response);
  } else {
    Serial.print("Error occurred during HTTP request. Error code: ");
    Serial.println(httpResponseCode);
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
    send_and_receive(test_array);
    }
  }

}
