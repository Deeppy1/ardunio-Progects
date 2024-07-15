

// Explicitly include Arduino.h
#include "Arduino.h"


const byte RED_PIN = 11;    // PWM pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // PWM pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // PWM pin ccontrolling the blue leg of our RGB LED


 
const byte OFF = 0;                 // Selected color is OFF
const byte DIM = 64;                // Selected color is 1/4 intensity
const byte BRIGHTER = DIM + 64;     // Selected color is 1/2 intensity
const byte BRIGHT = BRIGHTER + 64;  // Selected color is 3/4 intensity
const byte BRIGHTEST = 255;         // Selected color is maximum intensity (255)

// We can change this constant here, in one place, to change how long each color is displayed.
const unsigned int COLOR_DELAY = 500;  // show each color for 500 milliseconds

void setup() {
  // Set each of our PWM pins as OUTPUT pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

// Each time through loop() we display some of the color variations available
// using an RGB LED.
void loop() {
  // First demonstrate our different PWM levels by slowly brightening our red LED
  displayColor(OFF, OFF, OFF);  // OFF!
  delay(COLOR_DELAY);
  displayColor(DIM, OFF, OFF);  // Display red LED at 1/4 intensity
  delay(COLOR_DELAY);
  displayColor(BRIGHTER, OFF, OFF);  // Display red LED at 1/2 intensity
  delay(COLOR_DELAY);
  displayColor(BRIGHT, OFF, OFF);  // Display red LED at 3/4 intensity
  delay(COLOR_DELAY);
  displayColor(BRIGHTEST, OFF, OFF);  // Display red LED at FULL intensity
  delay(COLOR_DELAY);


}


void displayColor(
  byte red_intensity,    // red LED intensity (0-255)
  byte green_intensity,  // green LED intensity (0-255)
  byte blue_intensity    // blue LED intensity (0-255)
) {
  analogWrite(RED_PIN, red_intensity);      // Set red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // Set green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // Set blue LED intensity using PWM
}
