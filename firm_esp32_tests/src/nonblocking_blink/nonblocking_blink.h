#ifndef NONBLOCKING_BLINK_H
#define NONBLOCKING_BLINK_H

#include <Arduino.h>

// Simple non-blocking blink function
// Just call this repeatedly in your loop()
// pin: GPIO pin number
// period: total cycle time in milliseconds
// duty: duty cycle 0-100 (percentage of time ON)
void blink(uint8_t pin, unsigned long period, uint8_t duty);

#endif