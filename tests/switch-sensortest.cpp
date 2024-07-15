  const int irin = 13;
  
  int value = LOW;
  void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(irin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
value = digitalRead (irin);
Serial.println(value);
delay(100);


}
