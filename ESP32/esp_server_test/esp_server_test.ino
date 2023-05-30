#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "NOWEARIH";
const char* password = "IR1W7GzkXv4I";
int port = 90;

AsyncWebServer server(port);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Port Number: ");
  Serial.println(port);

  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
    int params = request->params();
    String message;
    for(int i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
      if(p->isPost()){
        message += p->value();
      }
    }
    if (message){
      Serial.println(message);
    }
    request->send(200, "text/plain", String(message.length()));
  });

  server.begin();
}

void loop() {}
