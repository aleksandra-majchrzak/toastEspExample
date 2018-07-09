#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

const char *ssid = "___";        // your wi-fi name
const char *password = "___";    // your wi-fi password

#define PIN 12

ESP8266WebServer server(80);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void turnOn() {
  for (int i = 0; i < 8; ++i){
    strip.setPixelColor(i, strip.Color(100, 100, 50));
  }
  strip.show();
  server.send(200, "text/html", "");
}

void turnOff() {
  for (auto i = 0; i < 8; ++i){
    strip.setPixelColor(i, 0);
  }
  strip.show();
  server.send(200, "text/html", "");
}

void setColor() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(server.arg("plain"));

  int r = root["red"];
  int g = root["green"];
  int b = root["blue"];

  for (auto i = 0; i < 8; ++i) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
  server.send(200, "text/html", "");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  strip.begin();
  // turn off all the LEDs
  for (auto i = 0; i < 8; ++i){
    strip.setPixelColor(i, 0);
  }
  strip.show();
  
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

  if(MDNS.begin("esp8266")) {
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
