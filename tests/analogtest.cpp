const int in = 9;  
int val2;

void setup() {
 Serial.begin(9600);
 pinMode(in, INPUT);

}

void loop() {
val2 = analogRead (in);
Serial.println(val2);
delay(100);
}
