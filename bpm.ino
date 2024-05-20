#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MAX30100_PulseOximeter.h"
#include <ArduinoJson.h>

// Endereço I2C do LCD
#define LCD_ADDRESS 0x27

// Definições do LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define REPORTING_PERIOD_MS 2000
#define MOVING_AVERAGE_SIZE 4

PulseOximeter pox;
uint32_t tsLastReport = 0;

float heartRateReadings[MOVING_AVERAGE_SIZE] = {0};
float spO2Readings[MOVING_AVERAGE_SIZE] = {0};
int currentIndex = 0;

void setup()
{
    Serial.begin(74880);
    Serial.print("Inicalizando oxímetro...");

    if (!pox.begin()) {
        for (;;);
    } else {
    }
    pox.setIRLedCurrent(MAX30100_LED_CURR_11MA);

    lcd.begin(16, 2);
    lcd.setBacklight(HIGH);
}

float calculateMovingAverage(float *array, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

float calculateWeightedAverage(float *array, int size) {
    float sum = 0;
    int weightSum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i] * (i + 1);
        weightSum += (i + 1);
    }
    return sum / weightSum;
}

void sendJson(float heartRate, float spO2) {
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["heart_rate"] = heartRate;
    jsonDoc["spo2"] = spO2;
    String jsonString;
    serializeJson(jsonDoc, jsonString);
    Serial.println(jsonString);
}

void loop()
{
    pox.update();

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        heartRateReadings[currentIndex] = pox.getHeartRate();
        spO2Readings[currentIndex] = pox.getSpO2();
        currentIndex = (currentIndex + 1) % MOVING_AVERAGE_SIZE;

        float avgHeartRate = calculateWeightedAverage(heartRateReadings, MOVING_AVERAGE_SIZE);
        float avgSpO2 = calculateWeightedAverage(spO2Readings, MOVING_AVERAGE_SIZE);

        if (avgHeartRate > 30 && avgHeartRate < 200 && avgSpO2 > 70 && avgSpO2 < 100) {
            Serial.print("Heart rate:");
            Serial.print(avgHeartRate);
            Serial.print(" bpm / SpO2:");
            Serial.print(avgSpO2);
            Serial.println(" %");

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("HR: ");
            lcd.print(avgHeartRate);
            lcd.print(" bpm");
            lcd.setCursor(0, 1);
            lcd.print("SpO2: ");
            lcd.print(avgSpO2);
            lcd.print(" %");

            sendJson(avgHeartRate, avgSpO2);
        } else {

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Leitura fora");
            lcd.setCursor(0, 1);
            lcd.print("do intervalo");
        }

        tsLastReport = millis();
    }
}
