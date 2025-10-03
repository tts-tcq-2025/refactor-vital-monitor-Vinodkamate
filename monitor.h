
#pragma once
#include <string>
int vitalsOk(float temperature, float pulseRate, float spo2);
bool isInRange(float value, float min, float max);
bool isTemperatureOk(float temperature);
bool isPulseRateOk(float pulseRate);
bool isSpo2Ok(float spo2);
void displayCriticalAlert(const std::string& message);
void testVitals();




