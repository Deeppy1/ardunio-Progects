
#include <Bluepad32.h>

ControllerPtr myControllers[BP32_MAX_CONTROLLERS];

// Pin definitions for the LEDs
const int brakeLedPin = 2;
const int throttleLedPin = 15;
const int brakeLedPin2 = 4;
const int throttleLedPin2 = 16;

// Arduino setup function. Runs in CPU 1
void setup() {
  // Initialize serial
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  String fv = BP32.firmwareVersion();
  Serial.print("Firmware version installed: ");
  Serial.println(fv);

  const uint8_t* addr = BP32.localBdAddress();
  Serial.print("BD Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(addr[i], HEX);
    if (i < 5)
      Serial.print(":");
    else
      Serial.println();
  }

  // Set up LED pins
  pinMode(brakeLedPin, OUTPUT);
  pinMode(throttleLedPin, OUTPUT);

  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.forgetBluetoothKeys();
}

// This callback gets called any time a new gamepad is connected.
void onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      Serial.print("CALLBACK: Controller is connected, index=");
      Serial.println(i);
      myControllers[i] = ctl;
      foundEmptySlot = true;

      ControllerProperties properties = ctl->getProperties();
      char buf[80];
      sprintf(buf,
              "BTAddr: %02x:%02x:%02x:%02x:%02x:%02x, VID/PID: %04x:%04x, "
              "flags: 0x%02x",
              properties.btaddr[0], properties.btaddr[1], properties.btaddr[2],
              properties.btaddr[3], properties.btaddr[4], properties.btaddr[5],
              properties.vendor_id, properties.product_id, properties.flags);
      Serial.println(buf);
      break;
    }
  }
  if (!foundEmptySlot) {
    Serial.println(
        "CALLBACK: Controller connected, but could not found empty slot");
  }
}

void onDisconnectedController(ControllerPtr ctl) {
  bool foundGamepad = false;

  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      Serial.print("CALLBACK: Controller is disconnected from index=");
      Serial.println(i);
      myControllers[i] = nullptr;
      foundGamepad = true;
      break;
    }
  }

  if (!foundGamepad) {
    Serial.println(
        "CALLBACK: Controller disconnected, but not found in myControllers");
  }
}

void processGamepad(ControllerPtr gamepad) {
  if (gamepad->a()) {
    static int colorIdx = 0;
    switch (colorIdx % 3) {
      case 0:
        gamepad->setColorLED(255, 0, 0);
        break;
      case 1:
        gamepad->setColorLED(0, 255, 0);
        break;
      case 2:
        gamepad->setColorLED(0, 0, 255);
        break;
    }
    colorIdx++;
  }

  

  // Get the brake and throttle values
  int brakeValue = gamepad->brake();      // (0 - 1023)
  int throttleValue = gamepad->throttle(); // (0 - 1023)

  // Map these values to the LED brightness range (0 - 255)
  int brakeBrightness = map(brakeValue, 0, 1023, 0, 255);
  int throttleBrightness = map(throttleValue, 0, 1023, 0, 255);
  
  int Xval = gamepad->axisX();
  int Yval = gamepad->axisY();

  // Set the LED brightness
  analogWrite(brakeLedPin, brakeBrightness);
  analogWrite(throttleLedPin, throttleBrightness);
  analogWrite(brakeLedPin2, brakeBrightness);
  analogWrite(throttleLedPin2, throttleBrightness);

  if (Yval > 100){
    analogWrite(brakeLedPin, 1023);
    analogWrite(throttleLedPin2, 1023)
  }
  if (Yval < -100){
    analogWrite(brakeLedPin2, 1023);
    analogWrite(throttleLedPin, 1023)
  }
  char buf[256];
  snprintf(buf, sizeof(buf) - 1,
           "idx=%d, dpad: 0x%02x, buttons: 0x%04x, "
           "axis L: %4li, %4li, axis R: %4li, %4li, "
           "brake: %4ld, throttle: %4li, misc: 0x%02x, "
           "gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d, "
           "battery: %d",
           gamepad->index(),        // Gamepad Index
           gamepad->dpad(),         // DPad
           gamepad->buttons(),      // bitmask of pressed buttons
           gamepad->axisX(),        // (-511 - 512) left X Axis
           gamepad->axisY(),        // (-511 - 512) left Y axis
           gamepad->axisRX(),       // (-511 - 512) right X axis
           gamepad->axisRY(),       // (-511 - 512) right Y axis
           gamepad->brake(),        // (0 - 1023): brake button
           gamepad->throttle(),     // (0 - 1023): throttle (AKA gas) button
           gamepad->miscButtons(),  // bitmask of pressed "misc" buttons
           gamepad->gyroX(),        // Gyro X
           gamepad->gyroY(),        // Gyro Y
           gamepad->gyroZ(),        // Gyro Z
           gamepad->accelX(),       // Accelerometer X
           gamepad->accelY(),       // Accelerometer Y
           gamepad->accelZ(),       // Accelerometer Z
           gamepad->battery()       // 0=Unknown, 1=empty, 255=full
  );
  Serial.println(buf);
}

void processMouse(ControllerPtr mouse) {
  char buf[160];
  sprintf(buf,
          "idx=%d, deltaX:%4li, deltaY:%4li, buttons: 0x%04x, misc: 0x%02x, "
          "scrollWheel: %d, battery=%d",
          mouse->index(),        // Controller Index
          mouse->deltaX(),       // Mouse delta X
          mouse->deltaY(),       // Mouse delta Y
          mouse->buttons(),      // bitmask of pressed buttons
          mouse->miscButtons(),  // bitmask of pressed "misc" buttons
          mouse->scrollWheel(),  // Direction: 1=up, -1=down, 0=no movement
          mouse->battery()       // 0=Unk, 1=Empty, 255=full
  );
  Serial.println(buf);
}

void processBalanceBoard(ControllerPtr balance) {
  char buf[160];
  sprintf(buf,
          "idx=%d, tl:%4i, tr:%4i, bl: %4i, br: %4i, temperature=%d, "
          "battery=%d",
          balance->index(),  // Controller Index
          balance->topLeft(), balance->topRight(), balance->bottomLeft(),
          balance->bottomRight(), balance->temperature(),
          balance->battery()  // 0=Unk, 1=Empty, 255=full
  );
  Serial.println(buf);
}

// Arduino loop function. Runs in CPU 1
void loop() {
  BP32.update();

  for (int i = 0; i < BP32_MAX_CONTROLLERS; i++) {
    ControllerPtr myController = myControllers[i];

    if (myController && myController->isConnected()) {
      if (myController->isGamepad())
        processGamepad(myController);
      else if (myController->isMouse())
        processMouse(myController);
      else if (myController->isBalanceBoard())
        processBalanceBoard(myController);
    }
  }
  delay(150);
}
