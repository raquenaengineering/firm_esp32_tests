#ifndef RTC_SET_READ_H
#define RTC_SET_READ_H

#include <Wire.h>
#include <DS3231.h>

// Custom I2C pins
#define SDA_PIN 19
#define SCL_PIN 21

// Function declarations
void setupRTC();
void setRTCOnce(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
void printRTCNonBlocking(unsigned long intervalMs);
void loopRTC();

#endif // RTC_SET_READ_H