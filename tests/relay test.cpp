#define RELAY_PIN  4 // Define the pin connected to the relay

void setup() {
  pinMode(RELAY_PIN, OUTPUT); // Set the relay pin as an output
}

void loop() {
  // Turn on the relay
  digitalWrite(RELAY_PIN, HIGH);
  delay(1000); // Wait for 1 second

  // Turn off the relay
  digitalWrite(RELAY_PIN, LOW);
  delay(1000); // Wait for 1 second
}
