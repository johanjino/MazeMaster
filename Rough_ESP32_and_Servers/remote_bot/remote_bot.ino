#include <Wire.h>
#include "SmoothStepper.h"
#include <Arduino.h>
#include <AccelStepper.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const int stepsPerRevolution = 100;

double F = 0;

int dir1 = 14;
int dir2 = 26;
int step1 = 12;
int step2 = 27;


const char* ssid = "johan";
const char* password = "password";

const char* serverURL = "http://192.168.43.199:8080/process";

float test_array[4][4] = {0};

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
    return "Sending to server is unsuccessful :(\n";
  }

  http.end();
}
  

void setup() {
  Serial.begin(9600);
  delay(100);
  connect_WiFi();
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(step1, OUTPUT);
  pinMode(step2, OUTPUT);
}

void loop() { 

  int a = 800;

  String roverState = send_and_receive(test_array);
  Serial.print(roverState);

      if(roverState.equals("1\n")){ //Forward
        Serial.print("F");
        digitalWrite(dir1, HIGH);
        digitalWrite(dir2, LOW);
          for(int i=0; i<25; i++){
            digitalWrite(step1, HIGH);
            digitalWrite(step2, HIGH);
            delay(20);
            digitalWrite(step1, LOW);
            digitalWrite(step2, LOW);
            delay(20);

          }
      }

      else if (roverState.equals("4\n")){ //Backward
        Serial.print("B");
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, HIGH);
        for(int i=0; i<25; i++){
            digitalWrite(step1, HIGH);
            digitalWrite(step2, HIGH);
            delay(20);
            digitalWrite(step1, LOW);
            digitalWrite(step2, LOW);
            delay(20);
          }
      }

      else if (roverState.equals("3\n")){ //Left
        Serial.print("L");
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, LOW);
        for(int i=0; i<25; i++){
            digitalWrite(step1, HIGH);
            digitalWrite(step2, HIGH);
            delay(20);
            digitalWrite(step1, LOW);
            digitalWrite(step2, LOW);
            delay(20);
          }
      }

      else if (roverState.equals("2\n")){ //Right
        Serial.print("R");
        digitalWrite(dir1, HIGH);
        digitalWrite(dir2, HIGH);
        for(int i=0; i<25; i++){
            digitalWrite(step1, HIGH);
            digitalWrite(step2, HIGH);
            delay(20);
            digitalWrite(step1, LOW);
            digitalWrite(step2, LOW);
            delay(20);
          }
      }




}