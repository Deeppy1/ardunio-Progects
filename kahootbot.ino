#include <Keyboard.h>

const int triggerPin = 2;   // Pin that triggers the sequence

void setup() {
  pinMode(triggerPin, INPUT);  // Set pin 2 as an input
  Serial.begin(9600);          // Start serial communication
  Keyboard.begin();            // Start keyboard control
}

void loop() {
  // Check if pin 2 is HIGH
  if (digitalRead(triggerPin) == HIGH) {
    // Open a new tab (Ctrl + T)
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('t');
    delay(100);
    Keyboard.releaseAll();
    
    delay(500);  // Small delay to ensure the new tab is open

    // Type 'kahoot.it'
    Keyboard.print("kahoot.it");
    delay(500);

    // Press Tab 3 times
    for (int i = 0; i < 3; i++) {
      Keyboard.press(KEY_TAB);
      delay(100);
      Keyboard.release(KEY_TAB);
      delay(200);
      Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('v');
    delay(100);
    Keyboard.releaseAll();
    delay(500);
    }

    // Press Ctrl + V (paste from clipboard)
 

    // Press Enter
    Keyboard.press(KEY_RETURN);
    delay(100);
    Keyboard.release(KEY_RETURN);

    // Wait 3 seconds
    delay(3000);

    // Press Tab 2 times
    for (int i = 0; i < 2; i++) {
      Keyboard.press(KEY_TAB);
      delay(100);
      Keyboard.release(KEY_TAB);
      delay(200);
    }

    // Type a random string of letters
    String randomStr = randomString(10);  // Generate 10 random characters
    Serial.println(randomStr);            // Print random string to Serial Monitor
    Keyboard.print(randomStr);            // Also type the string via the keyboard

    // Press Enter
    Keyboard.press(KEY_RETURN);
    delay(100);
    Keyboard.release(KEY_RETURN);
    
    // Optional: Delay after execution to avoid multiple triggers
    delay(5000);
  }
}

// Function to generate a random string of letters
String randomString(int length) {
  String str = "";
  for (int i = 0; i < length; i++) {
    char randomChar = 'a' + random(26);  // Random lowercase letter
    str += randomChar;
  }
  return str;
}
