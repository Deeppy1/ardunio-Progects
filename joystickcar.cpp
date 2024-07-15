#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
const int x = A0;
const int y = A1;
const int but = 2;
const int irin = 3;
int irval = 0;
int xval;
int yval;
int butval;
int estop = 0;
const int irleft = 6;
const int irright = 7;
int sleepmode = 1;
int irleftval;
int irrightval;
const int red = 8;
const int yellow = 5;
const int green = 4;


void setup() {

  servo1.attach(9);
  servo2.attach(10);
  servo4.attach(11);
  servo3.attach(12);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(but, INPUT);
  pinMode(irin, INPUT);
  pinMode(irleft, INPUT);
  pinMode(irright, INPUT);
  Serial.begin(9600);
}
void Fred() {
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
}
void Fyellow() {
  digitalWrite(yellow, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
}
void Fgreen() {
  digitalWrite(green, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
}
void forward() {
  Fgreen();
  servo1.write(180);
  servo2.write(0);
  servo3.write(0);
  servo4.write(180);
  Serial.println("forward");
}
void back() {
  Fgreen();
  servo1.write(0);
  servo2.write(180);
  servo3.write(180);
  servo4.write(0);
  Serial.println("back");
}
void left() {
  Fgreen();
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  Serial.println("left");
}
void right() {
  Fgreen();
  servo1.write(180);
  servo2.write(180);
  servo3.write(180);
  servo4.write(180);
  Serial.println("right");
}
void stop() {
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  Serial.println("stop");
}

void sleep() {
  Fred();
  Serial.println("sleep");
  irleftval = digitalRead(irleft);
  irrightval = digitalRead(irright);
  if (irrightval == 1) {
    //insert left and right motors here
    servo3.write(180);
    servo4.write(0);
    delay(100);
    stop();
  }
  if (irleftval == 1) {
    //insert left and right motors here
    servo1.write(180);
    servo2.write(0);
    delay(100);
    stop();
  }
  if (irrightval == 0 && irleftval == 0) {
    sleepmode = 1;
    Serial.println("sleep sucsess");
  } else {
    delay(100);
    sleep();
  }
}

void stand() {
  Fyellow();

  Serial.println("stand");
  irleftval = digitalRead(irleft);
  irrightval = digitalRead(irright);
  if (irrightval == 0) {
    //insert left and right motors here
    servo3.write(180);
    servo4.write(0);
    delay(100);
    stop();
  }
  if (irleftval == 0) {
    //insert left and right motors here
    servo1.write(180);
    servo2.write(0);
    delay(100);
    stop();
  }
  if (irrightval == 1 && irleftval == 1) {
    sleepmode = 0;
    Serial.println("stand sucsess");
  } else {
    delay(100);
    stand();
  }
}

void loop() {
  butval = digitalRead(but);
  if (butval == 1) {
    if (sleepmode == 0) {
      sleep();
    } else {
      stand();
    }
  }

  irval = digitalRead(irin);
  if (irval == 1) {
    estop = 1;

  } else {
    estop = 0;
    Serial.println("estop");
  }


  if (estop == 1) {
    yval = analogRead(y);
    xval = analogRead(x);

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
    /*
  Serial.print("X val: ");
  Serial.println(xval);
  Serial.print("Y val: ");
  Serial.println(yval);
  //*/
  }
}
