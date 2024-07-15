const int but = 2;
int butval;
const int led1 = 8;
const int led2 = 10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  butval = digitalRead(but);
  if (butval == 1) {
    analogWrite(led1, 1023);
    analogWrite(led2, 1023);
  }
  if (butval == 0) { 
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

Serial.println(butval);
delay(10);
}
