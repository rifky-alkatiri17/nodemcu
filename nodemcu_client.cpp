// 1. url
//http://192.168.4.1/        → page utama
//http://192.168.4.1/page2  → page kedua
//http://192.168.4.1/status → data JSON
//http://192.168.4.1/control?led=1

// 2. js - data biasa
/*fetch("/control", {
  method: "POST",
  headers: { "Content-Type": "application/x-www-form-urlencoded" },
  body: "x=120&y=200"
});*/


//3. js - json
/*fetch("/data", {
  method: "POST",
  headers: { "Content-Type": "application/json" },
  body: JSON.stringify({
    x: 0.5,
    y: -0.3,
    btn: true
  })
});*/
