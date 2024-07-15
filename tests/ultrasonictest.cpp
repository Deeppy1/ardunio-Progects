#define TRIG_PIN 11 // Define TRIG pin
#define ECHO_PIN 12 // Define ECHO pin

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(TRIG_PIN, OUTPUT); // Set TRIG pin as output
  pinMode(ECHO_PIN, INPUT); // Set ECHO pin as input
}

void loop() {
  long duration, distance;
  
  // Send a 10us pulse to trigger the sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Measure the duration of the pulse from the echo pin
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate distance in centimeters
  distance = duration * 0.034 / 2;
  
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(500); // Wait for a second before taking the next measurement
}
