//http://192.168.4.1/        → page utama
//http://192.168.4.1/page2  → page kedua
//http://192.168.4.1/status → data JSON

/*IPAddress ip(192,168,1,17);
IPAddress gateway(192,168,1,17);
IPAddress subnet(255,255,255,0);

WiFi.softAPConfig(ip, gateway, subnet);*/


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "NodeMCU_AP";
const char* password = "12345678";

ESP8266WebServer server(80);

// ====== PAGE 1 ======
void handleRoot() {
  server.send(200, "text/html",
    "<h1>Page 1</h1>"
    "<p>Ini halaman utama</p>"
    "<a href='/page2'>Ke Page 2</a>"
  );
}

// ====== PAGE 2 ======
void handlePage2() {
  server.send(200, "text/html",
    "<h1>Page 2</h1>"
    "<p>Ini halaman kedua</p>"
    "<a href='/'>Kembali ke Home</a>"
  );
}

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/page2", handlePage2);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}

