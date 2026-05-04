#ifndef SCAN_I2C_H
#define SCAN_I2C_H

#include <Arduino.h>
#include <Wire.h>

// Function to scan I2C bus at specified interval
// period: scan interval in milliseconds
// Returns device count if scan was performed, -1 if scan was skipped (too soon)
int scanI2C(unsigned long period);

#endif