#include "SD_CARD_RW_SPI.h"
#include <SPI.h>
#include <SD.h>

// Pin definitions (ESP32)
static const int SD_CS   = 13; // IO13 = CS (SD_DAT3)
static const int SD_MOSI = 14; // IO14 = MOSI (SD_CMD)
static const int SD_SCK  = 27; // IO27 = SCK  (SD_CLK)
static const int SD_MISO = 26; // IO26 = MISO (SD_DAT0)

// Timing control
static unsigned long lastTestTime = 0;

// Initialization flag
static bool sdInitialized = false;

// Internal helper: initialize SD card once
static bool initSD()
{
    if (sdInitialized) return true;

    SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

    if (!SD.begin(SD_CS, SPI)) {
        Serial.println("SD init failed");
        return false;
    }

    Serial.println("SD init OK");
    sdInitialized = true;
    return true;
}

int testSDCard(unsigned long period)
{
    unsigned long now = millis();

    // Too soon to run test
    if (now - lastTestTime < period) {
        return -1;
    }

    lastTestTime = now;

    if (!initSD()) {
        return 0;
    }

    const char* filename = "/test_2.txt";
    const char* testData = "SD_TEST_OK_123456789";

    // ---- WRITE TEST ----
    File file = SD.open(filename, FILE_WRITE);
    if (!file) {
        Serial.println("Failed to open file for writing");
        return 0;
    }

    file.print(testData);
    file.close();

    // ---- READ TEST ----
    file = SD.open(filename, FILE_READ);
    if (!file) {
        Serial.println("Failed to open file for reading");
        return 0;
    }

    String readBack = "";
    while (file.available()) {
        readBack += (char)file.read();
    }
    file.close();

    // ---- VERIFY ----
    if (readBack == testData) {
        Serial.println("SD test PASSED");
        return 1;
    } else {
        Serial.println("SD test FAILED (data mismatch)");
        return 0;
    }
}