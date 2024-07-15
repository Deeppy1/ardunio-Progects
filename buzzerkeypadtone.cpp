

// Explicitly include Arduino.h
#include "Arduino.h"

// Include Keypad library
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 12 };

char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // 1st row
  { '4', '5', '6', 'B' },  // 2nd row
  { '7', '8', '9', 'C' },  // 3rd row
  { '*', '0', '#', 'D' }   // 4th row
};

Keypad keypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

const unsigned int TONES[ROWS][COLS] = {
  // a frequency tone for each button
  { 10, 50, 100, 200 },
  { 250, 300, 350, 400 },
  { 450, 500, 550, 600 },
  { 700, 750, 900, 1000 }  // Use frequency of 0 for bottom right key to end tone.
};



void setup() {
  Serial.begin(9600);  // Begin monitoring via the serial monitor
}


void loop() {
  char button_character = keypad.waitForKey();  // Wait for a button to be pressed

  unsigned int tone_frequency = 0;  // Frequency to use for tone (default to 0, no tone)
  for (byte i = 0; i < ROWS; i++) {
    for (byte j = 0; j < COLS; j++) {
      if (button_character == BUTTONS[i][j]) {  // found it, get the corresponding tone
        tone_frequency = TONES[i][j];
      }

    }  // end j loop
  }    // end i loop

  Serial.print("Key: ");  //   send the button_character to serial monitor...
  Serial.print(button_character);
  Serial.print("   Freq: ");
  Serial.println(tone_frequency);

  /*
   * The tone() function plays a tone until stopped.  The code continues to run as the tone plays.
   */
  if (tone_frequency > 0) {                // If tone frequency greater than 0...
  } else {
    Serial.println("Stop tone");
  }
}
