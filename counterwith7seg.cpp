#include <TM1637Display.h>

const byte CLK_PIN = 4;
const byte DIO_PIN = 5;
const int but = 6;
int butval;
int counter = 0

TM1637Display display = TM1637Display(CLK_PIN, DIO_PIN);

void setup() {
  display.setBrightness(7);  // Configure the display brightness (0-7):
  Serial.begin(9600);
}
void loop() {
Serial.println(counter);
butval = digitalRead(but);
if (butval == 1){
counter++;
display.showNumberDec(counter);
}
}