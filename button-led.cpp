


const int buttonPin = 2;  
const int ledPin = 11; 
const int buttonPin_1 = 1;  
const int ledPin_1 = 10;     

int buttonState = 0;  
int buttonState_1 = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
    // initialize the LED pin as an output:
  pinMode(ledPin_1, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin_1, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
   // read the state of the pushbutton value:
  buttonState_1 = digitalRead(buttonPin_1);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState_1 == HIGH) {
    // turn LED on:
    digitalWrite(ledPin_1, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin_1, LOW);
  }
}
