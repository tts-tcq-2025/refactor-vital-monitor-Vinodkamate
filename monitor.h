// Copyright 2025 Health Monitor System
#ifndef MONITOR_H_
#define MONITOR_H_

#include <string>

int vitalsOk(const float temperature, const float pulseRate, const float spo2);
bool isInRange(const float value, const float min, const float max);
bool isTemperatureOk(const float temperature);
bool isPulseRateOk(const float pulseRate);
bool isSpo2Ok(const float spo2);

// Extension 1: Early Warning System
bool isInLowWarningRange(const float value, const float min, const float tolerance);
bool isInHighWarningRange(const float value, const float max, const float tolerance);
bool isTemperatureWarning(const float temperature);
bool isPulseRateWarning(const float pulseRate);
bool isSpo2Warning(const float spo2);
void displayWarningAlert(const std::string& message);
void runTestCase(const std::string& testName, const float temp,
                const float pulse, const float spo2, const bool expected);

// Helper functions
bool checkVital(const bool isOk, const std::string& alertMessage);
bool checkVitalWithWarning(const bool isOk, const bool isWarning,
                          const std::string& criticalMsg,
                          const std::string& warningMsg);
bool checkAllVitals(const float temperature, const float pulseRate,
                    const float spo2);
bool checkAllVitalsWithWarnings(const float temperature,
                               const float pulseRate, const float spo2);
void displayCriticalAlert(const std::string& message);
void testVitals();

#endif  // MONITOR_H_

