#include <TM1637Display.h>
const byte CLK_PIN = 26;
const byte DIO_PIN = 27;
TM1637Display display1 = TM1637Display(CLK_PIN, DIO_PIN);

#include <Keypad.h>
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', '4'},
  {'5','6','7', '8'},
  {'9','10','11', '12'},
  {'13','14','15', '16'}
};
byte pin_rows[ROW_NUM] = {28, 29, 30, 31}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {35, 34, 33, 32}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
const int r1 = 36;
const int g1 = 37;
const int b1 = 38;

const int r2 = 39;
const int g2 = 40;
const int b2 = 41;


const int a1 = 2;
const int a2 = 3;
const int b1 = 4;
const int b2 = 5;
const int TRIG_PIN1 = 11; 
const int ECHO_PIN1 = 12; 

const int TRIG_PIN2 = 10; 
const int ECHO_PIN2 = 9;  

const int TRIG_PIN3 = 8; 
const int ECHO_PIN3 = 7;  

bool turn;

const int ir1 = 22;
const int ir2 = 23;
const int ir3 = 24;
const int ir4 = 25;

int irval1;
int irval2;
int irval3;
int irval4;

const int x = 42;
const int y = 43;
const int xybut = 44;
int xval;
int yval;
int xybutval;

int mode = 1;

int dist1far;
int divdist1far;

void setup() {
  pinMode(a1 ,OUTPUT);
  pinMode(a2 ,OUTPUT);
  pinMode(b1 ,OUTPUT);
  pinMode(b2 ,OUTPUT);
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(xybut, INPUT);
  display.setBrightness(7);
  display.clear();
  Serial.begin(9600);
}
void forward() {
  analogWrite(a1, 1023);
  analogWrite(a2, 0);
  analogWrite(b1, 1023);
  analogWrite(b2, 0);
  digitalWrite(r1, LOW);
  digitalWrite(g1, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(g2, HIGH);
  digitalWrite(b2, LOW);
}
void back() {
  analogWrite(a1, 0);
  analogWrite(a2, 1023);
  analogWrite(b1, 0);
  analogWrite(b2, 1023);
  digitalWrite(r1, HIGH);
  digitalWrite(g1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(r2, HIGH);
  digitalWrite(g2, LOW);
  digitalWrite(b2, LOW);
}
void left() {
  analogWrite(a1, 0);
  analogWrite(a2, 1023);
  analogWrite(b1, 1023);
  analogWrite(b2, 0);
  digitalWrite(r1, HIGH);
  digitalWrite(g1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(g2, HIGH);
  digitalWrite(b2, LOW);
}
void right() {
  analogWrite(a1, 1023);
  analogWrite(a2, 0);
  analogWrite(b1, 0);
  analogWrite(b2, 1023);
  digitalWrite(r1, LOW);
  digitalWrite(g1, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(r2, HIGH);
  digitalWrite(g2, LOW);
  digitalWrite(b2, LOW);
}
void stop() {
  analogWrite(a1, 0);
  analogWrite(a2, 0);
  analogWrite(b1, 0);
  analogWrite(b2, 0);
  digitalWrite(r1, LOW);
  digitalWrite(g1, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(r2, LOW);
  digitalWrite(g2, LOW);
  digitalWrite(b2, HIGH);
}
void turn180() {
  turn = TRUE;
  back();
  delay(1500);
  right();
  delay(3000);
  turn = FALSE;

}
void getdist1() {
  digitalWrite(TRIG_PIN1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);
  
  long duration1 = pulseIn(ECHO_PIN1, HIGH);
  long distance1 = duration1 * 0.034 / 2;
}
void getdist2() {
  digitalWrite(TRIG_PIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  
  long duration2 = pulseIn(ECHO_PIN2, HIGH);
  long distance2 = duration2 * 0.034 / 2;
}
void getdist3() {
  digitalWrite(TRIG_PIN3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN3, LOW);
  
  long duration3 = pulseIn(ECHO_PIN3, HIGH);
  long distance3 = duration3 * 0.034 / 2;
}
void getDistance() {
  getdist1();
  getdist2();
  getdist3();
  Serial.print("D1: ");
  Serial.println(distance1);
  Serial.print("D2: ");
  Serial.println(distance2);
  Serial.print("D3: ");
  Serial.println(distance3);
  delay(100);
}
void distavoid() {
  getDistance();
  if (distance1 > 10){
    turn180();
    Serial.println("dist1 trigger");
  }
  else{
    turn = FALSE;
  }
  if (distance2 > 10){
    turn180();
    Serial.println("dist2 trigger");
  }
  else{
    turn = FALSE;
  }
  if (distance3 > 10){
    turn180();
    Serial.println("dist3 trigger");
  }
  else{
    turn = FALSE;
  }
}
void irread() {
  irval1 = digitalRead(ir1);
  irval2 = digitalRead(ir2);
  irval3 = digitalRead(ir3);
  irval4 = digitalRead(ir4);

}
void iravoid() {
  irread();
  if (irval1 == 0) {
    turn180();
  }
  else{
    turn = FALSE;
  }
  if (irval2 == 0) {
    turn180();
  }
  else{
    turn = FALSE;
  }
  if (irval3 == 0) {
    turn180();
  }
  else{
    turn = FALSE;
  }
  if (irval4 == 0) {
    turn180();
  }
  else{
    turn = FALSE;
  }
}
void avoid() {
  distavoid();
  iravoid();
  if (turn == TRUE){
    turn180();
  }
  else{
    forward();
  }
}
void getkey() {
  char key = keypad.getKey();
  Serial.println("getting key")
  if (key){
    Serial.println(key);
  }
}
void joystickdrive() {
 
    yval = analogRead(y);
    xval = analogRead(x);
    Serial.print("xval: ");
    Serial.ntln
    if (yval > 600) {
      back();
    } else if (yval < 400) {
      forward();
    }

    else if (xval > 600) {
      right();
    } else if (xval < 400) {
      left();
    }

    else {
      stop();
    }
}
void modechange() {
  xybutval = digitalRead(xybut)
  if (xybutval == 1){
  getkey();
  if (key == 1){
    mode = 1;
  }
  else if (key == 2){
    mode = 2;
  }
}
}
void scanonce(){
  getDistance();
  left();
  delay(300);
  stop();
  if (distance1 < dist1far) {
    dist1far = distance1;
  }
}


void scan(){
  for (int i = 0; i < 15; i++) {
    scanonce();
  if (distance1 > dist1far) {
    dist1far = distance1;
  }
  }
  divdist1far = dist1far / 3;
  getDistance();
  if (distance1 == divdist1far)
    stop();
  }





void loop() {
  modechange();
  if (mode == 1) {
    joystickdrive();
  }
  else if (mode == 2) {
    avoid(); 
  }
}