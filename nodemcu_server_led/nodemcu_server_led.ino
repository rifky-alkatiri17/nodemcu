#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Pin LED
const int ledPin = LED_BUILTIN;
int sensorValue = 1;

// const char* ssid = "OPPO F5";
// const char* password = "trikora18";

const char* ssid = "NodeMCU_AP";
const char* password = "12345678";

IPAddress localIP(192,168,1,17);
IPAddress gateway(192,168,1,17);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Web Server NodeMCU</title>
      <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet">
      <script>
        setInterval(function(){
          fetch('/sensor')
            .then(response => response.text())
            .then(data => {
              document.getElementById('sensor').innerHTML = data;
            });
        }, 100); // Update setiap 1 detik
      </script>
    </head>
    <body class="text-center">       
      <div class="container mt-5">
        <h1 class="display-4">Halo dari NodeMCU!</h1>
        <p class="lead">Ini tampilan web dengan Bootstrap</p>
        <h1 class="display-4">Kontrol LED</h1>
        <p class="lead">Tekan tombol untuk mengontrol LED built-in</p>
        <a href="" class="btn btn-success m-2 on">LED ON</a>
        <a href="" class="btn btn-danger m-3 off">LED OFF</a>
        <h1 class="display-4">Kontrol LED & Baca Sensor</h1>
        <p class="lead">Sensor Value: <span id="sensor">Loading...</span></p>
      </div>
      <script>
        const btn = document.querySelectorAll('a');
        btn.forEach(item=>{
          item.addEventListener('click', e=>{
          e.preventDefault();
          console.log('preventDefault berhasil');
          const myfunc = async function(){
            if(e.target.classList.contains('on')){
              await fetch('/on');
            }elseif(e.target.classList.contains('off')){
              await fetch('/off');
            }
          };
          myfunc();
        });
        })
      </script>
    </body>
    </html>
  )rawliteral");
}

void handleLEDon() {
  digitalWrite(ledPin, LOW); // LED BUILTIN menyala dengan logika LOW
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleLEDoff() {
  digitalWrite(ledPin, HIGH); // LED BUILTIN mati dengan logika HIGH
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleSensor() {
  sensorValue++;
  server.send(200, "text/plain", String(sensorValue));
}

void setup() {
  Serial.begin(115200);
  // WiFi.begin(ssid, password);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password);
  WiFi.softAPConfig(localIP, gateway, subnet);
  Serial.println(WiFi.softAPIP());
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // Matikan LED saat awal

  server.on("/", handleRoot);
  server.on("/on", handleLEDon);
  server.on("/off", handleLEDoff);
  server.on("/sensor", handleSensor); // Tambahan endpoint /sensor
  server.begin();
}

void loop() {
  server.handleClient(); //menghandle permintaan client/browser dll
}


