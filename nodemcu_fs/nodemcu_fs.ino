#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

// instance here...
IPAddress localIP(192,168,1,17);
IPAddress gateway(192,168,1,17);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

// declaration variables here
const char* ssid = "NodeMCU_AP";
const char* password = "12345678";

// const char index_html[] PROGMEM = ...; 

/*void handleRoot(){ //ini jika tanpa fs
  server.send(200, "text/html", "Hello World..") 
  server.send(200, "text/html", PROGMEM)
  server.send(200, "text/html", R"rawliteral())
}*/


void setup() {
  // config here....
  Serial.begin(115200);
  // WiFi.config(localIP,gateway,subnet);// <-- ini mode STA: konek ke wifi lain 
  // WiFi.begin(ssid, password); // 

  WiFi.mode(WIFI_AP);  //default WIFI_AP_STA

  WiFi.softAPConfig(localIP, gateway, subnet); // <-- ini mode AP 
  WiFi.softAP(ssid,password); //  
  Serial.println(WiFi.softAPIP());

  LittleFS.begin();

  server.on("/", []() {
    File f = LittleFS.open("/index.html", "r");
    server.streamFile(f, "text/html");
    f.close();
  });

  server.on("/script.js", []() {
    File f = LittleFS.open("/script.js", "r");
    server.streamFile(f, "application/javascript");
    f.close();
  });

  server.on("/style.css", []() {
    File f = LittleFS.open("/style.css", "r");
    server.streamFile(f, "text/css");
    f.close();
  });
}
