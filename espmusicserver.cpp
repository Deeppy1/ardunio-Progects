#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "*********";
const char *password = "************";

WebServer server(80);

const int speakerPin = 25; // Choose a PWM-capable pin

void handleRoot() {
  server.send(200, "text/html", "<h1>Welcome to ESP32 Music Player</h1><p><a href='/play_mario'>Play Mario Theme Song</a></p><p><a href='/play_never_gonna_give_you_up'>Play Never Gonna Give You Up</a></p>");
}

void playMarioThemeSong() {
  // Mario theme song notes and durations
  int melody[] = {659, 659, 0, 659, 0, 523, 659, 0, 784, 0, 0, 0, 392, 0, 0, 0};
  int noteDurations[] = {250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250};

  // Play the melody
  for (int i = 0; i < sizeof(melody) / sizeof(int); i++) {
    tone(speakerPin, melody[i], noteDurations[i]);
    delay(noteDurations[i] + 50);
  }
  noTone(speakerPin);

  server.send(200, "text/plain", "Playing Mario Theme Song");
}

void playNeverGonnaGiveYouUp() {
  // "Never Gonna Give You Up" notes and durations
  int melody[] = {494, 523, 494, 440, 0, 440, 0, 440, 523, 494, 0, 494, 0, 494, 523, 587, 587, 587, 587, 587, 523, 494, 0, 440, 0, 440, 0, 440, 0, 440, 494, 523, 587, 587, 587, 587, 587, 523, 494, 0, 440, 0, 440, 0, 440, 0, 440, 0, 494, 523, 587, 587, 587, 587, 587, 523, 494, 0, 440, 0, 440, 0, 440, 0, 440, 0, 494, 523, 587, 587, 587, 587, 587, 523, 494, 0, 440, 0, 440, 0, 440, 0, 440, 0, 494, 523, 587, 587, 587, 587, 587, 523, 494, 0, 440, 0, 440, 0, 440, 0, 440, 0, 494, 523, 587, 587, 587, 587, 587, 523, 494, 0, 440, 0, 440, 0, 440, 0, 440, 0, 494, 523, 587, 587, 587, 587, 587, 523, 494, 0, 440, 0, 440, 0, 440, 0, 440, 0};
  int noteDurations[] = {250, 250, 500, 250, 500, 250, 500, 250, 250, 500, 250, 500, 250, 500, 250, 125, 125, 250, 250, 250, 125, 125, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 125, 125, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 125, 125, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 125, 125, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 125, 125, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 125, 125, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 125, 125, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 125, 125, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 125, 125, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 125, 125, 250, 250, 250, 250, 250, 250, 250, 250};

  // Play the melody
  for (int i = 0; i < sizeof(melody) / sizeof(int); i++) {
    tone(speakerPin, melody[i], noteDurations[i]);
    delay(noteDurations[i] + 50);
  }
  noTone(speakerPin);

  server.send(200, "text/plain", "Playing Never Gonna Give You Up");
}

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to WiFi");

  server.on("/", handleRoot);
  server.on("/play_mario", playMarioThemeSong);
  server.on("/play_never_gonna_give_you_up", playNeverGonnaGiveYouUp);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
