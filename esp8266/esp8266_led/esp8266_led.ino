#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>

const char *ssid = "___";        // your wi-fi name
const char *password = "___";    // your wi-fi password

#define PIN_RED 16
#define PIN_GREEN 14
#define PIN_BLUE 12

#define MAX_BRIGHT 200
#define MIN_BRIGHT 1023

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void turnOn() {
  analogWrite(PIN_RED, 200);
  analogWrite(PIN_GREEN, 200);
  analogWrite(PIN_BLUE, 200);
  server.send(200, "text/html", "");
}

void turnOff() {
  analogWrite(PIN_RED, MIN_BRIGHT);
  analogWrite(PIN_GREEN, MIN_BRIGHT);
  analogWrite(PIN_BLUE, MIN_BRIGHT);
  server.send(200, "text/html", "");
}

void setColor() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(server.arg("plain"));
  
  analogWrite(PIN_RED, getLedValue(root["red"]));
  analogWrite(PIN_GREEN, getLedValue(root["green"]));
  analogWrite(PIN_BLUE, getLedValue(root["blue"]));
  server.send(200, "text/html", "");
}

int getLedValue(int led){
  return MIN_BRIGHT - led*4;
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  analogWrite(PIN_RED, MIN_BRIGHT);
  analogWrite(PIN_GREEN, MIN_BRIGHT);
  analogWrite(PIN_BLUE, MIN_BRIGHT);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  for(int i = 0; i< 3; ++i){
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);                      
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }

  server.on( "/", HTTP_GET, handleRoot);
  server.on("/turnOn", HTTP_POST, turnOn);
  server.on("/turnOff", HTTP_POST, turnOff);
  server.on("/setColor", HTTP_POST, setColor);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
