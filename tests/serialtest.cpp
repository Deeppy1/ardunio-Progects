int counter;
void setup(){
    serial.begin(9600)
}
void loop() {
    counter++;
    serial.println(counter);
    delay(1000);
}