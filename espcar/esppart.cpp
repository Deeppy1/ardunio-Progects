#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "*********"; // Your network SSID
const char* password = "********"; // Your network password

const int relay1Pin = 4; // GPIO pin connected to Relay 1 (D4)
const int relay2Pin = 16; // GPIO pin connected to Relay 2 (D16)
const int relay3Pin = 17; // GPIO pin connected to Relay 3 (D17)
const int relay4Pin = 5; // GPIO pin connected to Relay 4 (D5)
const int relay5Pin = 18;

WebServer server(80);

bool relay1State = false;
bool relay2State = false;
bool relay3State = false;
bool relay4State = false;

void setup() {
  Serial.begin(115200);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);
  pinMode(relay5Pin, OUTPUT);

  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, LOW);
  digitalWrite(relay3Pin, LOW);
  digitalWrite(relay4Pin, LOW);
  digitalWrite(relay5Pin, LOW);

  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html",
                "<html><body>"
                "<h1>Robot Control Panel</h1>"
                "<p><a href=\"/go_forwards\">Go Forwards</a></p>"
                "<p><a href=\"/go_back\">Go Back</a></p>"
                "<p><a href=\"/go_left\">Go Left</a></p>"
                "<p><a href=\"/go_right\">Go Right</a></p>"
                "<p><a href=\"/stop\">Stop</a></p>"
                "</body></html>");
  });

  server.on("/go_forwards", HTTP_GET, []() {
    relay1State = !relay1State;
    digitalWrite(relay1Pin, relay1State ? HIGH : LOW);
    if (relay1State) {
      relay2State = false;
      relay3State = false;
      relay4State = false;
      digitalWrite(relay2Pin, LOW);
      digitalWrite(relay3Pin, LOW);
      digitalWrite(relay4Pin, LOW);
      digitalWrite(relay5Pin, LOW);
    }
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/go_back", HTTP_GET, []() {
    relay2State = !relay2State;
    digitalWrite(relay2Pin, relay2State ? HIGH : LOW);
    if (relay2State) {
      relay1State = false;
      relay3State = false;
      relay4State = false;
      digitalWrite(relay1Pin, LOW);
      digitalWrite(relay3Pin, LOW);
      digitalWrite(relay4Pin, LOW);
      digitalWrite(relay5Pin, LOW);
    }
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/go_left", HTTP_GET, []() {
    relay3State = !relay3State;
    digitalWrite(relay3Pin, relay3State ? HIGH : LOW);
    if (relay3State) {
      relay1State = false;
      relay2State = false;
      relay4State = false;
      digitalWrite(relay1Pin, LOW);
      digitalWrite(relay2Pin, LOW);
      digitalWrite(relay4Pin, LOW);
      digitalWrite(relay5Pin, LOW);
    }
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/go_right", HTTP_GET, []() {
    relay4State = !relay4State;
    digitalWrite(relay4Pin, relay4State ? HIGH : LOW);
    if (relay4State) {
      relay1State = false;
      relay2State = false;
      relay3State = false;
      digitalWrite(relay1Pin, LOW);
      digitalWrite(relay2Pin, LOW);
      digitalWrite(relay3Pin, LOW);
      digitalWrite(relay5Pin, LOW);
    }
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/stop", HTTP_GET, []() {
    relay1State = !relay1State; // Toggle the relay state
    digitalWrite(relay1Pin, LOW);
    digitalWrite(relay2Pin, LOW);
    digitalWrite(relay3Pin, LOW);
    digitalWrite(relay4Pin, LOW);
    digitalWrite(relay5Pin, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
  });



  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
