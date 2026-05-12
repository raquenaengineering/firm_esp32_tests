#include "rtc_set_read.h"
#include <Arduino.h>

// Global variables for non-blocking print
static unsigned long lastPrintTime = 0;
static unsigned long printIntervalMs = 0;
static DS3231 rtc;

void setupRTC() {
    Wire.begin(SDA_PIN, SCL_PIN);
    Serial.println("RTC initialized.");
}

void setRTCOnce(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
    // Set the time using the DS3231 library's methods
    rtc.setYear(year - 2000); // Store year as offset from 2000
    rtc.setMonth(month);
    rtc.setDate(day);
    rtc.setHour(hour);
    rtc.setMinute(minute);
    rtc.setSecond(second);
    Serial.println("RTC time set!");
}

void printRTCNonBlocking(unsigned long intervalMs) {
    printIntervalMs = intervalMs;
}

void loopRTC() {
    if (printIntervalMs == 0) return;

    unsigned long currentTime = millis();
    if (currentTime - lastPrintTime >= printIntervalMs) {
        lastPrintTime = currentTime;

        // Read the current time from the RTC
        uint16_t year = rtc.getYear() + 2000; // Add 2000 to get the full year
        bool century = false;
        uint8_t month = rtc.getMonth(century);
        uint8_t day = rtc.getDate();
        bool h12 = false, PM_time = false;
        uint8_t hour = rtc.getHour(h12, PM_time);
        uint8_t minute = rtc.getMinute();
        uint8_t second = rtc.getSecond();

        // Convert to 24-hour format if needed
        if (h12 && PM_time && hour != 12) {
            hour += 12;
        } else if (h12 && !PM_time && hour == 12) {
            hour = 0;
        }

        Serial.print(year); Serial.print('/');
        Serial.print(month); Serial.print('/');
        Serial.print(day); Serial.print(" ");
        Serial.print(hour); Serial.print(':');
        Serial.print(minute); Serial.print(':');
        Serial.println(second);
    }
}