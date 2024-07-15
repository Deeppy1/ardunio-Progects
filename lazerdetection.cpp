const int buzz = 3;  // Declare the constant outside of any function
const int red = 9;    
const int pres = A0;
const int pot = A1;
const int green = 10;
const int blue = 11;



int presval = 0;
int trigger = false;
int live = false;
int potval = 0;


void setup() {
  pinMode(buzz, OUTPUT);  // Set the pin mode for the buzzer
  pinMode(pres, INPUT);
  pinMode(pot, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
  live = false;
}

void loop() {

  presval = analogRead(pres);  // Corrected the pin name to "pres"
  potval = analogRead(pot);
  Serial.println(presval);  // Added a semicolon

  if (potval < 511) {
    live = true;
    Serial.println("live!");
    analogWrite(red, 1000);
    analogWrite(green,0);
  }
  if (potval > 511) {
    live = false;
    analogWrite(green,1000);
    analogWrite(red,0);
    trigger = false;

  }
  if (live = true) {
    if (presval < 20) {
      trigger = true;
  }
  }

  if (trigger == true) {
    analogWrite(buzz, 100);
    analogWrite(blue, 1000);
    analogWrite(red, 0);
    analogWrite(green, 0);
    delay(300);
    analogWrite(buzz, 500);
    analogWrite(red, 1000);
    analogWrite(blue, 0);
    analogWrite(green, 0);
    delay(300);
    Serial.println("trigger");

  }
  else{
    analogWrite(buzz, 0);
  }
}
