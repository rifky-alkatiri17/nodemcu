//http://192.168.4.1/control?led=1


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void handleControl() {
  String led = server.arg("led"); //ini untuk menangkap data dg key "led"

  Serial.print("Data diterima: ");
  Serial.println(led);

  server.send(200, "text/plain", "OK");
}

void setup() {
  WiFi.softAP("NodeMCU_AP", "12345678");
  server.on("/control", handleControl);
  server.begin();
}

void loop() {
  server.handleClient();
}
