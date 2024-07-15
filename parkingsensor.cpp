#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int r = 13; // Red LED pin
const int y = 3;  // Yellow LED pin
const int g = 4;  // Green LED pin
const int buzzerPin = 5; // Buzzer pin
const int TRIG_PIN = 11;  // Ultrasonic sensor trigger pin
const int ECHO_PIN = 12;  // Ultrasonic sensor echo pin

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16x2 display

void setup() {
  pinMode(r , OUTPUT);
  pinMode(y , OUTPUT);
  pinMode(g , OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");
  
  if (distance < 10) {
    digitalWrite(r, HIGH);
    digitalWrite(y, LOW);
    digitalWrite(g, LOW);
    tone(buzzerPin, 1000);
    delay(200);
  } else if (distance < 20) {
    digitalWrite(r, LOW);
    digitalWrite(y, HIGH);
    digitalWrite(g, LOW);
    for (int i = 0; i < 3; i++) {
      tone(buzzerPin, 1000);
      delay(250);
      noTone(buzzerPin);
      delay(250);
    }
  } else {
    digitalWrite(r, LOW);
    digitalWrite(y, LOW);
    digitalWrite(g, HIGH);
    noTone(buzzerPin);
  }
  
  delay(500);
}
