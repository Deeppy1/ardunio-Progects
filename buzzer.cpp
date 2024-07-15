void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  for(unsigned int i = 0; i < 20000; i += 500) {
      tone(9, i);
      Serial.print("debug: frequency: ");
      Serial.println(i);
  }
  delay(500);
  Serial.println("debug: finished sleeping");
}
