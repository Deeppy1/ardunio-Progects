#include <Arduino.h>

// Define the pins connected to the relays
const int relayPins[] = {2, 3, 4, 5};

// Define the pin connected to the melody speaker
const int melodySpeakerPin = 6;

// Define the pin connected to the bass speaker
const int bassSpeakerPin = 9; // PWM pin for bass speaker

// Define the pin connected to the toggle button
const int toggleButtonPin = 7;

// Define the duration for each note in milliseconds
const int quarterNote = 530; // Approx. 113 BPM

// Define the musical notes and their corresponding frequencies for the melody
const int MELODY_NOTE_C4 = 262;
const int MELODY_NOTE_D4 = 294;
const int MELODY_NOTE_E4 = 330;
const int MELODY_NOTE_F4 = 349;
const int MELODY_NOTE_G4 = 392;
const int MELODY_NOTE_A4 = 440;
const int MELODY_NOTE_B4 = 494;
const int MELODY_NOTE_C5 = 523;

// Define states for the state machine
enum State {
  PLAYING,
  PAUSED
};

// State variables
State state = PLAYING;
bool buttonWasPressed = false;

void setup() {
  // Set the relay pins as outputs and turn them off
  for (int i = 0; i < 4; ++i) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }

  // Set the melody speaker pin as an output
  pinMode(melodySpeakerPin, OUTPUT);

  // Set the bass speaker pin as an output
  pinMode(bassSpeakerPin, OUTPUT);

  // Set the toggle button pin as an input with pull-up resistor enabled
  pinMode(toggleButtonPin, INPUT_PULLUP);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the state of the toggle button
  bool toggleButtonState = digitalRead(toggleButtonPin);

  // Handle button press
  if (toggleButtonState == LOW && !buttonWasPressed) {
    buttonWasPressed = true;

    if (state == PLAYING) {
      state = PAUSED;
      Serial.println("Music paused");
      stopMusic();
    } else {
      state = PLAYING;
      Serial.println("Playing music");
    }
  } else if (toggleButtonState == HIGH) {
    buttonWasPressed = false;
  }

  // If in the playing state, continuously play the music
  if (state == PLAYING) {
    playMusic();
  }
}

void playMusic() {
  // Define the rhythm pattern
  int rhythm[] = {0, 0, 1, 1, 2, 0, 0, 3}; // Adjust as needed

  // Define the melody notes
  int melody[] = {MELODY_NOTE_E4, MELODY_NOTE_G4, MELODY_NOTE_A4, MELODY_NOTE_A4, MELODY_NOTE_A4, MELODY_NOTE_B4, MELODY_NOTE_A4, MELODY_NOTE_G4};

  // Define the note durations (quarter notes)
  int noteDurations[] = {4, 8, 4, 4, 2, 4, 4, 2};

  // Play the rhythm, melody, and bass simultaneously
  for (int i = 0; i < sizeof(rhythm) / sizeof(rhythm[0]); ++i) {
    // Turn on the relay corresponding to the current beat
    digitalWrite(relayPins[rhythm[i]], HIGH);

    // Play the melody note
    tone(melodySpeakerPin, melody[i], quarterNote / noteDurations[i]);
    analogWrite(bassSpeakerPin, map(melody[i], 100, 10000, 0, 255)); // Map melody frequency to PWM value for bass speaker

    // Delay for the duration of the note
    delay(quarterNote);

    // Turn off the relay and stop the sound
    digitalWrite(relayPins[rhythm[i]], LOW);
    noTone(melodySpeakerPin);
    analogWrite(bassSpeakerPin, 0); // Turn off bass speaker

    // Add a small delay between notes to improve sound quality
    delay(10);
  }
}

void stopMusic() {
  // Turn off all relays
  for (int i = 0; i < 4; ++i) {
    digitalWrite(relayPins[i], LOW);
  }
  // Stop melody playback
  noTone(melodySpeakerPin);
}
