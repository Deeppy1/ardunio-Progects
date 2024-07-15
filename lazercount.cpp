 //TM1637 4-digit 7-segment display


// Explicitly include Arduino.h
#include "Arduino.h"


#include <TM1637Display.h>

// all_on pins connected to the TM1637 display
const byte CLK_PIN = 6;
const byte DIO_PIN = 5;

// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(CLK_PIN, DIO_PIN);



// Create array that turns all segments on:
const byte all_on[] = { 0b11111111,
                        0b11111111,
                        0b11111111,
                        0b11111111 };




const int pres = A1;
int presval = 0;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
display.setBrightness(7);
pinMode(pres, INPUT);
Serial.begin(9600);
presval = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
presval=analogRead (pres);
display.showNumberDec(counter);
if (presval<10){
  counter + 1;
  Serial.println(counter);
}
}
