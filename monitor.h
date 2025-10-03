// Copyright 2025 Health Monitor System
#ifndef MONITOR_H_
#define MONITOR_H_

#include <string>
int vitalsOk(float temperature, float pulseRate, float spo2);
bool isInRange(float value, float min, float max);
bool isTemperatureOk(float temperature);
bool isPulseRateOk(float pulseRate);
bool isSpo2Ok(float spo2);
bool checkVital(bool isOk, const std::string& alertMessage);
void displayCriticalAlert(const std::string& message);
void testVitals();

#endif  // MONITOR_H_

