#include "scan_i2c.h"

int scanI2C(unsigned long period) {
  static unsigned long lastScan = 0;
  
  unsigned long currentTime = millis();
  if (currentTime - lastScan < period) {
    return -1;  // Scan skipped, not enough time elapsed
  }
  
  lastScan = currentTime;
  int deviceCount = 0;
  
  Serial.println("\n\nI2C Scanner");
  Serial.println("Scanning I2C bus for devices...\n");
  
  Wire.begin(19, 21); // Use GPIO 21 for SDA and GPIO 22 for SCL
  
  for (byte i = 8; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device found at address 0x");
      if (i < 16) Serial.print("0");
      Serial.print(i, HEX);
      Serial.println(" !");
      deviceCount++;
    }
  }
  
  Serial.print("\nScan complete. Found ");
  Serial.print(deviceCount);
  Serial.println(" device(s).\n");
  
  return deviceCount;
}