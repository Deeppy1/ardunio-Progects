#include "Arduino.h"
#include <TM1637Display.h>  // Ensure this library is installed

// Pin assignments
const byte PHOTORESISTOR_PIN = A0;
const byte LED_BUILTIN_PIN = LED_BUILTIN;  // Define for clarity
const byte pin5 = 5;
const byte pin6 = 6;
const byte pin9 = 9;
const byte CLK_PIN = 2;
const byte DIO_PIN = 3;

// Delay constants
const unsigned int MIN_DELAY = 50;
const unsigned int MAX_DELAY = 500;

TM1637Display display(CLK_PIN, DIO_PIN);

void setup() {
  pinMode(LED_BUILTIN_PIN, OUTPUT);
  pinMode(PHOTORESISTOR_PIN, INPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DIO_PIN, OUTPUT);
  display.setBrightness(0x0f);
  Serial.begin(9600);
}

void loop() {
  unsigned int light_value = analogRead(PHOTORESISTOR_PIN);
  Serial.print("Light value: ");
  Serial.print(light_value);

  static unsigned int darkest_light = light_value;
  static unsigned int brightest_light = light_value;

  if (light_value < darkest_light) {
    darkest_light = light_value;
  }
  if (light_value > brightest_light) {
    brightest_light = light_value;
  }

  unsigned int delay_value = map(light_value, darkest_light, brightest_light, MAX_DELAY, MIN_DELAY);
  Serial.print(", Delay value: ");
  Serial.println(delay_value);

  digitalWrite(LED_BUILTIN_PIN, HIGH);
  delay(delay_value);
  digitalWrite(LED_BUILTIN_PIN, LOW);
  delay(delay_value);

if (light_value < 50) {
  analogWrite(pin6, 1000);  // Set LED to full brightness (adjust if needed)
}
if (light_value > 50) {
  analogWrite(pin6,0);  // Set LED to full brightness (adjust if needed)
}
if (light_value > 90) {
  analogWrite(pin5,1000);  // Set LED to full brightness (adjust if needed)
}
if (light_value < 90) {
  analogWrite(pin5,0);  // Set LED to full brightness (adjust if needed)
}
if (light_value > 150) {
  analogWrite(pin5,0);  // Set LED to full brightness (adjust if needed)
}
if (light_value > 150) {
  analogWrite(pin9,1000);  // Set LED to full brightness (adjust if needed)
}
if (light_value < 150) {
  analogWrite(pin9,0);  // Set LED to full brightness (adjust if needed)
}
if (light_value > 250) {
  analogWrite(pin9,1000);  // Set LED to full brightness (adjust if needed)
}
if (light_value > 500) {
  analogWrite(pin9,1000);  // Set LED to full brightness (adjust if needed)
  analogWrite(pin5,1000);  // Set LED to full brightness (adjust if needed)
  analogWrite(pin6,1000);  // Set LED to full brightness (adjust if needed)

}

  display.showNumberDec(light_value);  // Uncomment to use the display
}
