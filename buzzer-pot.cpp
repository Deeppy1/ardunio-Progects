#include <TM1637Display.h>
//#include "KETM1650.h"
#define CLK1 2
#define DIO1 3
#define CLK2 4
#define DIO2 5

TM1637Display display1(CLK1, DIO1); // First display
//KETM1650 tm_4display(CLK2, DIO2);

const int potPin = A0; // analog pin for potentiometer input
const int pot2 = A1;
int val2;
int val3;
const int buzzerPin = 9; // digital pin for buzzer output
int nil = 0;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(pot2, INPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  display1.setBrightness(0x0f);
  nil = 0;
  //tm_4display.init(); //initialize
  //tm_4display.setBrightness(3); //set brightness to 3，in the range of 1~8
}

void loop() {
  int potValue = analogRead(potPin); // read the potentiometer value
  val2 = analogRead(pot2); // read the potentiometer value
  Serial.print("Potentiometer Reading: ");
  Serial.println(potValue); // Print potentiometer reading to Serial Monitor
  //Serial.println(val2);
  
  // If potentiometer value is not zero, generate tone
  if (potValue > 100) {
    val3 = map(val2, 0, 1023, 50, 2500); // map potentiometer value to frequency range (adjust as needed)
    int frequency = map(potValue, 0, 1023, 50, 800); // map potentiometer value to frequency range (adjust as needed)
    tone(buzzerPin, frequency); // generate tone on buzzer pin
    Serial.print("Buzzer Frequency: ");
    Serial.println(frequency); // Print buzzer frequency to Serial Monitor
    //Serial.println(val3);
    display1.showNumberDec(frequency);
    
  } else {
    noTone(buzzerPin); // If potentiometer value is zero, turn off the buzzer
    Serial.println("Buzzer Off");
    display1.showNumberDec(nil);
    
  }
  //tm_4display.displayString(val3);//the 4-digit tube display will show item value
  delay(500); // delay for stability
}
