#include "nonblocking_blink.h"

void blink(uint8_t pin, unsigned long period, uint8_t duty) {
  static unsigned long lastToggle = 0;
  static bool state = HIGH;
  static uint8_t lastPin = 255;
  
  // Initialize pin on first call
  if (lastPin != pin) {
    lastPin = pin;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, state);
    lastToggle = millis();
    return;
  }
  
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - lastToggle;
  
  // Clamp duty to 0-100
  duty = (duty > 100) ? 100 : duty;
  
  if (state == HIGH) {
    unsigned long onTime = (period * duty) / 100;
    if (elapsedTime >= onTime) {
      state = LOW;
      digitalWrite(pin, state);
      lastToggle = currentTime;
    }
  } else {
    unsigned long offTime = period - ((period * duty) / 100);
    if (elapsedTime >= offTime) {
      state = HIGH;
      digitalWrite(pin, state);
      lastToggle = currentTime;
    }
  }
}