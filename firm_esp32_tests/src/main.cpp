#include <Arduino.h>
#include "scan_i2c/scan_i2c.h"
#include "nonblocking_blink/nonblocking_blink.h"
#include "sd_card_rw_spi/sd_card_rw_spi.h"
#include <SPI.h>

// Safe GPIO pins to test
int testPins[] = {13, 18};
int numPins = sizeof(testPins) / sizeof(testPins[0]);

// SD test period (ms)
unsigned long sdTestPeriod = 2000;

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("\n\nSystem starting...\n");

  // Initialize GPIO test pins
  for (int i = 0; i < numPins; i++) {
    pinMode(testPins[i], OUTPUT);
    digitalWrite(testPins[i], LOW);
  }

  Serial.println("GPIO test pins initialized");

  // IMPORTANT: Do NOT call SPI.end()
  // SD library needs SPI active
}

void loop() {

  // // -----------------------------
  // // GPIO TOGGLE TEST
  // // -----------------------------
  // static bool state = false;
  // state = !state;

  // for (int i = 0; i < numPins; i++) {
  //   digitalWrite(testPins[i], state);
  // }

  // Serial.println(state ? "GPIO -> HIGH" : "GPIO -> LOW");

  // // -----------------------------
  // // SD CARD TEST (NON-BLOCKING)
  // // -----------------------------
  // int sdResult = testSDCard(sdTestPeriod);

  // if (sdResult == 1) {
  //   Serial.println("SD Test: PASS");
  // } 
  // else if (sdResult == 0) {
  //   Serial.println("SD Test: FAIL");
  // }
  // // -1 = skipped (too soon)

  scanI2C(1000);

}