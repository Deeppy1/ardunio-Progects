#include <Adafruit_NeoPixel.h>

#define LED_PIN      6
#define LED_COUNT    64  // Change this to match the number of NeoPixels you have
#define BUTTON_PIN_1 2   // Change this to the pin where your first button is connected
#define BUTTON_PIN_2 8   // Add this line for the new button on pin 8
#define STATUS_LED   13  // Change this to the pin where your status LED is connected

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
bool cycleColors = true; // Flag to indicate whether to cycle colors or not
bool buttonState1 = false; // Variable to track first button state
bool buttonState2 = false; // Variable to track second button state
bool lastButtonState1 = false; // Variable to track last first button state
bool lastButtonState2 = false; // Variable to track last second button state
unsigned long lastDebounceTime1 = 0; // Variable to track the last time a first button state change was detected
unsigned long lastDebounceTime2 = 0; // Variable to track the last time a second button state change was detected
unsigned long debounceDelay = 10; // Debounce delay to prevent button bouncing

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(BUTTON_PIN_1, INPUT_PULLUP); // Set first button pin as input with internal pull-up resistor
  pinMode(BUTTON_PIN_2, INPUT_PULLUP); // Set second button pin as input with internal pull-up resistor
  pinMode(STATUS_LED, OUTPUT); // Set status LED pin as output
}

void loop() {
  // Read the current state of the first button
  int reading1 = digitalRead(BUTTON_PIN_1);
  // Read the current state of the second button
  int reading2 = digitalRead(BUTTON_PIN_2);

  // Check if the first button state has changed and debounce it
  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = millis();
  }

  // If a debounce delay has passed since the last first button state change, update the first button state
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    // If the first button state has changed, update it and handle it
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      // If the first button is pressed, toggle the color cycling
      if (buttonState1 == LOW) {
        cycleColors = !cycleColors;
      }
    }
  }

  lastButtonState1 = reading1;

  // Check if the second button state has changed and debounce it
  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis();
  }

  // If a debounce delay has passed since the last second button state change, update the second button state
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    // If the second button state has changed, update it and handle it
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      // If the second button is pressed, toggle the color cycling
      if (buttonState2 == LOW) {
        cycleColors = !cycleColors;
        Serial.println("button 2");
      }
    }
  }

  lastButtonState2 = reading2;

  // Update the status LED based on the cycleColors flag
  digitalWrite(STATUS_LED, cycleColors ? HIGH : LOW);

  // If color cycling is enabled, perform color cycling
  if (cycleColors) {
    static uint16_t hue = 0;
    
    for (int i = 0; i < strip.numPixels(); i++) {
      // Set each pixel to a color corresponding to the current hue, with full saturation and value
      strip.setPixelColor(i, strip.ColorHSV(hue, 255, 255));
    }
    
    strip.show();
    
    // Increment the hue for the next loop iteration, ensuring it stays within range
    hue = (hue + 1) % 65536; // 65536 is the maximum value for hue in HSV
    
    delay(0.005); // Adjust the delay to change the speed of color cycling
  } else {
    // If color cycling is disabled, turn off all LEDs
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    
    strip.show();
  }
}
