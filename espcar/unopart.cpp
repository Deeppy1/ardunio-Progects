#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define the pins for relays
int relay1 = 2;
int relay2 = 3;
int relay3 = 4;
int relay4 = 5;
int relay5 = 6;

// Define the relay values
int rval1 = 0;
int rval2 = 0;
int rval3 = 0;
int rval4 = 0;
int rval5 = 0;

// Define the pins for servos
int servoPin1 = 7;
int servoPin2 = 8;
int servoPin3 = 9;
int servoPin4 = 10;

int but = 13;
int x = A0;
int y = A1;

bool butval;
int xval;
int yval;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

bool autonomous = false;

int lastxstate; // Missing semicolon
int lastystate; // Missing semicolon

int mode = 1;

void forward();
void backward();
void left(); // Added function declaration for left() and right()
void right();

void setup() {
  Serial.begin(9600);

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);

  pinMode(relay1, INPUT);
  pinMode(relay2, INPUT);
  pinMode(relay3, INPUT);
  pinMode(relay4, INPUT);
  pinMode(relay5, INPUT);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(1000);  // Pause for 1 second
  display.clearDisplay();

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Welcome!");
  display.display();
  delay(1000);
  display.clearDisplay();
  
  xval = analogRead(x);
  yval = analogRead(y);
  lastystate = yval;
  lastxstate = xval;

}

void loop() {
  Serial.print("mode: ");
  Serial.println(mode);

  butval = digitalRead(but);

  Serial.print("but val: ");
  Serial.println(butval);

  if (butval == 1) {
    Serial.println("but is true");

    if (mode == 0) {
      mode = 1; // Increment mode by 1
    } else {
      mode = 0; // Set mode to 0
    }
  }

  if (mode == 1) {
    xval = analogRead(x);
    yval = analogRead(y);

    Serial.print("x: ");
    Serial.println(xval);
    Serial.print("y: ");
    Serial.println(yval);
    stop();
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Stopped");
    display.setCursor(0, 16);
    display.print("Mode: ");
    display.print(mode);
    display.display();

    if (yval < 250) {
      if (xval == lastxstate) { // Keep yval as it is
        forward();
        Serial.println("forwards");
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print("Forwards");
        display.setCursor(0, 16);
        display.print("Mode: ");
        display.print(mode);
        display.display();
        lastxstate = xval; // Update lastxstate
      }
    }
    else if (yval > 750) {
      if (xval == lastxstate) { // Keep yval as it is
        backward();
        Serial.println("backwards");
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print("Backwards");
        display.setCursor(0, 16); 
        display.print("Mode: ");
        display.print(mode);
        display.display();
        lastxstate = xval; // Update lastxstate
      }
    }
    else if (xval < 250) {
      if (yval == lastystate) { // Keep yval as it is
        left();
        Serial.println("left");
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print("Left");
        display.setCursor(0, 16);
        display.print("Mode: ");
        display.print(mode);
        display.display();
        lastxstate = xval; // Update lastxstate
      }
    }
    else if (xval > 750) {
      if (yval == lastystate) { // Keep yval as it is
        right();
        Serial.println("right");
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print("Right");
        display.setCursor(0, 16);
        display.print("Mode: ");
        display.print(mode);
        display.display();
        lastxstate = xval; // Update lastxstate
      }
    }
    else {
      Serial.println("Stopped");
      stop();
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print("Stopped");
      display.setCursor(0, 16);
      display.print("Mode: ");
      display.print(mode);
      display.display();
    }
  }

  if (mode == 0) {
    rval1 = digitalRead(relay1);
    rval2 = digitalRead(relay2);
    rval3 = digitalRead(relay3);
    rval4 = digitalRead(relay4);
    rval5 = digitalRead(relay5);

    if (rval1 == 1) {
      forward();
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print("Forwards");
      display.setCursor(0, 16);
      display.print("Mode: ");
      display.print(mode);
      display.display();
    } else if (rval2 == 1) {
      backward();
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print("Backwards");
      display.setCursor(0, 16);
      display.print("Mode: ");
      display.print(mode);
      display.display();
    } else if (rval3 == 1) {
      left();
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print("Left");
      display.setCursor(0, 16);
      display.print("Mode: ");
      display.print(mode);
      display.display();
    } else if (rval4 == 1) {
      right();
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print("Right");
      display.setCursor(0, 16);
      display.print("Mode: ");
      display.print(mode);
      display.display();
    } else if (rval5 == 1) {
      stop();
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print("Stopped");
      display.setCursor(0, 16);
      display.print("Mode: ");
      display.print(mode);
      display.display();
    } else {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print("No Web Signal");
      display.display();
    }
  }
  delay(1000);
}

void forward() {
  servo1.write(180);
  servo2.write(0);
  servo3.write(180);
  servo4.write(0);
}

void backward() {
  servo1.write(0);
  servo2.write(180);
  servo3.write(0);
  servo4.write(180);
}

void stop() {
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}

void left() {
  servo1.write(0);
  servo2.write(180);
  servo3.write(0);
  servo4.write(180);
}

void right() {
  servo1.write(180);
  servo2.write(0);
  servo3.write(180);
  servo4.write(0);
}
