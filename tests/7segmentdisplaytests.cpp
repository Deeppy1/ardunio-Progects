// Declare constant pins
const int DATA_PIN = 2;
const int CLK_PIN = 3;

// Segment patterns for digits 0-9 (may need adjustment)
byte segmentPatterns[] = {
  0b1111110, // 0
  0b0110000, // 1
  0b1101101, // 2
  0b1111001, // 3
  0b0110011, // 4
  0b1011011, // 5
  0b1011111, // 6
  0b1110000, // 7
  0b1111111, // 8
  0b1111011, // 9
};

int count = 0;

void setup() {
  // Set data and clock pins as outputs
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
}

void loop() {
  count++;

  // Send the current digit pattern
  sendDigitPattern(segmentPatterns[count % 10]); // modulo 10 to keep count between 0 and 9

  // Delay to slow down the count
  delay(1000);
}

void sendDigitPattern(byte pattern) {
  // Send one bit at a time using data and clock pins
  for (int i = 0; i < 8; i++) {
    digitalWrite(DATA_PIN, bitRead(pattern, i));
    digitalWrite(CLK_PIN, HIGH);
    digitalWrite(CLK_PIN, LOW);
  }
}
