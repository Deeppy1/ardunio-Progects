#include <Keypad.h>
#include <Keyboard.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // Connect to the column pinouts of the keypad
const int buttonPin = 10; // Connect the button to pin 10
int buttonState = 0; // variable for reading the button status
bool isMacMode = true; // flag to indicate the current mode (start in Mac mode)

const int redPin = 15; // Red pin of the RGB LED
const int greenPin = 14; // Green pin of the RGB LED
const int bluePin = 16; // Blue pin of the RGB LED
int mode = 1;
const int com = 10;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as input
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Keyboard.begin();
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.println("Key Pressed: " + String(key)); // Print the pressed key
    switch(key) {
      case 'A':
        if (isMacMode) {
          Keyboard.press(KEY_LEFT_GUI);
          delay(50);
          Keyboard.press('a'); // Cmd + A for select all
          delay(50);
          Keyboard.releaseAll();
        }
        break;
      case 'B':
        if (isMacMode) {
          Keyboard.press(KEY_LEFT_GUI);
          delay(50);
          Keyboard.press('c'); // Cmd + B
          delay(50);
          Keyboard.releaseAll();
        }
        break;
      case '8':
        if (isMacMode) {
          Keyboard.press(KEY_LEFT_GUI);
          delay(50);
          Keyboard.press('c'); // Cmd + B
          delay(50);
          Keyboard.releaseAll();
        }
        break;
      case '5':
        if (isMacMode) {
          Keyboard.press(KEY_LEFT_GUI);
          delay(50);
          Keyboard.press('c'); // Cmd + B
          delay(50);
          Keyboard.releaseAll();
        }
        break;
      case 'C':
        if (isMacMode) {
          Keyboard.press(KEY_LEFT_GUI);
          delay(50);
          Keyboard.press('v'); // Cmd + C for copy
          delay(50);
          Keyboard.releaseAll();
        }
        break;
      case 'D':
        if (isMacMode) {
          Keyboard.press(KEY_LEFT_GUI);
          delay(50);
          Keyboard.press('x'); // Cmd + V for paste
          delay(50);
          Keyboard.releaseAll();
        } else {
          Keyboard.press(KEY_LEFT_CTRL);
          delay(50);
          Keyboard.press('r'); // Ctrl + R to refresh the browser in Windows mode
          delay(50);
          Keyboard.releaseAll();
        }
        break;
      case '9':
        if (isMacMode) {
          // Simulate opening Safari using Spotlight search
          Keyboard.press(KEY_LEFT_GUI); // Press Cmd key
          Keyboard.press(' '); // Press Space key
          //delay(500); // Delay to give time for Spotlight to appear
          Keyboard.releaseAll(); // Release all keys
          delay(250); // Additional delay for Spotlight to open
          // Type the name of the application ("Safari") using individual key presses
          Keyboard.press(KEY_BACKSPACE); // Press Backspace to clear any existing text
          delay(100); // Delay before typing
          Keyboard.release(KEY_BACKSPACE); // Release Backspace
          delay(100); // Additional delay before typing
          Keyboard.print("Safari");
          // Press Enter to open the application
          delay(50);
          Keyboard.press(KEY_RETURN);
          delay(100); // Delay before releasing the Enter key
          Keyboard.release(KEY_RETURN);
        }
        break;

      case '3':
        if (isMacMode) {
          // Simulate opening Safari using Spotlight search
          Keyboard.press(KEY_LEFT_GUI); // Press Cmd key
          Keyboard.press(' '); // Press Space key
          //delay(500); // Delay to give time for Spotlight to appear
          Keyboard.releaseAll(); // Release all keys
          delay(250); // Additional delay for Spotlight to open
          // Type the name of the application ("Safari") using individual key presses
          Keyboard.press(KEY_BACKSPACE); // Press Backspace to clear any existing text
          delay(100); // Delay before typing
          Keyboard.release(KEY_BACKSPACE); // Release Backspace
          delay(100); // Additional delay before typing
          Keyboard.print("Spotify");
          // Press Enter to open the application
          delay(50);
          Keyboard.press(KEY_RETURN);
          delay(100); // Delay before releasing the Enter key
          Keyboard.release(KEY_RETURN);
        }
        break;
      case '6':
        if (isMacMode) {
          // Simulate opening Safari using Spotlight search
          Keyboard.press(KEY_LEFT_GUI); // Press Cmd key
          Keyboard.press(' '); // Press Space key
          //delay(500); // Delay to give time for Spotlight to appear
          Keyboard.releaseAll(); // Release all keys
          delay(250); // Additional delay for Spotlight to open
          // Type the name of the application ("Safari") using individual key presses
          Keyboard.press(KEY_BACKSPACE); // Press Backspace to clear any existing text
          delay(100); // Delay before typing
          Keyboard.release(KEY_BACKSPACE); // Release Backspace
          delay(100); // Additional delay before typing
          Keyboard.print("Arduino IDE");
          // Press Enter to open the application
          delay(100);
          Keyboard.press(KEY_RETURN);
          delay(100); // Delay before releasing the Enter key
          Keyboard.release(KEY_RETURN);
        }
        break;
      case '#':
        if (isMacMode) {
          // Simulate opening Safari using Spotlight search
          Keyboard.press(KEY_LEFT_GUI); // Press Cmd key
          Keyboard.press(' '); // Press Space key
          //delay(500); // Delay to give time for Spotlight to appear
          Keyboard.releaseAll(); // Release all keys
          delay(250); // Additional delay for Spotlight to open
          // Type the name of the application ("Safari") using individual key presses
          Keyboard.press(KEY_BACKSPACE); // Press Backspace to clear any existing text
          delay(100); // Delay before typing
          Keyboard.release(KEY_BACKSPACE); // Release Backspace
          delay(100); // Additional delay before typing
          Keyboard.print("Chrome");
          // Press Enter to open the application
          delay(50);
          Keyboard.press(KEY_RETURN);
          delay(100); // Delay before releasing the Enter key
          Keyboard.release(KEY_RETURN);
        }
        break;
      case '*':
        if (isMacMode) {
          digitalWrite(com, HIGH);
          delay(1000);
          digitalWrite(com, LOW);
        }
        break;


        break;
      case '1':
        if (isMacMode) {
          Keyboard.press(KEY_LEFT_GUI);
          delay(50);
          Keyboard.press('u'); // Cmd + U for uploading in Arduino IDE
          delay(50);
          Keyboard.releaseAll();
        }
      case '4':
        if (isMacMode) {
          Keyboard.press(KEY_LEFT_GUI);
          delay(50);
          Keyboard.press('r'); // Cmd + U for uploading in Arduino IDE
          delay(50);
          Keyboard.releaseAll();
        }
        break;
      case '7':
        if (isMacMode) {
          Keyboard.press(KEY_LEFT_GUI); // Press Cmd key
          delay(50); // Delay to ensure Cmd key is registered
          Keyboard.press(KEY_TAB); // Press Tab key
          delay(50); // Delay to ensure Tab key is registered
          Keyboard.releaseAll(); // Release all keys
}
        break; 

        break;

        case '0':
        if (isMacMode) {
          Keyboard.releaseAll(); // Release all keys
          delay(250); // Additional delay for Spotlight to open
          // Type the name of the application ("Safari") using individual key presses
          Keyboard.press(KEY_BACKSPACE); // Press Backspace to clear any existing text
          delay(100); // Delay before typing
          Keyboard.release(KEY_BACKSPACE); // Release Backspace
          delay(100); // Additional delay before typing
          Keyboard.print("D33pJet462");
          // Press Enter to open the application
          delay(50);
          Keyboard.press(KEY_RETURN);
          delay(100); // Delay before releasing the Enter key
          Keyboard.release(KEY_RETURN);
        }
        break;


        case '2':
        if (isMacMode) {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.press('q');
          delay(100);
          Keyboard.releaseAll();
        }
        break;
      default:
        break;
    }
  }
  
  // Check the button state
  buttonState = digitalRead(buttonPin);

  // If the button is pressed, toggle the mode
  if (buttonState == LOW) {
    isMacMode = !isMacMode; // Toggle the mode
    delay(500); // Debounce delay
    Serial.println("Mode Changed: " + String(isMacMode ? "Mac" : "Windows")); // Print the mode change
  }
  
  // Update the LED based on the mode
  if (isMacMode) {
    // Mac mode (Green)
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  } else {
    // Windows mode (Blue)
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }
}
