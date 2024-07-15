#include <NimBLEDevice.h>

NimBLEScan* pScan;
NimBLEClient* pClient;

class MyCallbacks : public NimBLEAdvertisedDeviceCallbacks {
  void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
    Serial.print("Advertised Device found: ");
    Serial.println(advertisedDevice->toString().c_str());

    // Check if the advertised device is an Xbox controller
    if (advertisedDevice->getName() == "Xbox Wireless Controller") {
      Serial.println("Found an Xbox Wireless Controller!");
      pScan->stop(); // Stop scanning

      // Create a new client and connect to the device
      pClient = NimBLEDevice::createClient();
      pClient->connect(advertisedDevice); // Connect to the controller

      Serial.println("Connected to Xbox Wireless Controller");
    }
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  NimBLEDevice::init("");
  NimBLEDevice::setPower(ESP_PWR_LVL_P 7); // +7db

  pScan = NimBLEDevice::getScan();
  pScan->setAdvertisedDeviceCallbacks(new MyCallbacks());
  pScan->setActiveScan(true); // Active scan to get more data
  pScan->start(120, false); // Start scanning for 30 seconds
}

void loop() {
  // Do nothing in the loop
}
