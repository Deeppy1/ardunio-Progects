#include <Wire.h>
#include "Adafruit_VL6180X.h"

// Create a sensor object
Adafruit_VL6180X vl = Adafruit_VL6180X();

void setup() {
  Serial.begin(9600);
  // Initialize the sensor
  if (!vl.begin()) {
    Serial.println("Failed to find VL6180X sensor!");
    while (1);
  }
  Serial.println("VL6180X sensor ready!");
}

void loop() {
  // Get the range in millimeters
  uint8_t range = vl.readRange();
  uint8_t status = vl.readRangeStatus();
  
  if (status == VL6180X_ERROR_NONE) {
    Serial.print("Range: ");
    Serial.print(range);
    Serial.println(" mm");
  } else {
    Serial.println("Error reading range!");
  }
  
  // Small delay between readings
  delay(500);
}
