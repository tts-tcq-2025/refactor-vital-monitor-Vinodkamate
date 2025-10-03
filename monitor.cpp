// Copyright 2025 Health Monitor System
#include "./monitor.h"
#include <iostream>
#include <string>

// Constants for vital sign thresholds
const float TEMP_MIN = 95.0f;
const float TEMP_MAX = 102.0f;
const float PULSE_MIN = 60.0f;
const float PULSE_MAX = 100.0f;
const float SPO2_MIN = 90.0f;

// Generic range checking function to avoid duplication
bool isInRange(float value, float min, float max) {
    return value >= min && value <= max;
}

// Pure function to check temperature
bool isTemperatureOk(float temperature) {
    return isInRange(temperature, TEMP_MIN, TEMP_MAX);
}

// Pure function to check pulse rate
bool isPulseRateOk(float pulseRate) {
    return isInRange(pulseRate, PULSE_MIN, PULSE_MAX);
}

// Pure function to check oxygen saturation (only has minimum limit)
bool isSpo2Ok(float spo2) {
    return spo2 >= SPO2_MIN;
}

// Function to display critical alert
void displayCriticalAlert(const std::string& message) {
    std::cout << message << std::endl;
}

// Helper function to check and alert for a single vital
bool checkVital(bool isOk, const std::string& alertMessage) {
    if (!isOk) {
        displayCriticalAlert(alertMessage);
        return false;
    }
    return true;
}

// Main function to check vitals (CCN = 1)
int vitalsOk(float temperature, float pulseRate, float spo2) {
    return checkVital(isTemperatureOk(temperature), "Temperature is critical!") &&
           checkVital(isPulseRateOk(pulseRate), "Pulse Rate is out of range!") &&
           checkVital(isSpo2Ok(spo2), "Oxygen Saturation out of range!") ? 1 : 0;
}

// Test function for manual verification
void testVitals() {
    // Test normal case
    int result1 = vitalsOk(98.6f, 70.0f, 95.0f);
    std::cout << "Normal vitals test: " << (result1 ? "PASS" : "FAIL") << std::endl;
    
    // Test abnormal case
    int result2 = vitalsOk(103.0f, 110.0f, 85.0f);
    std::cout << "Abnormal vitals test: " << (result2 == 0 ? "PASS" : "FAIL") << std::endl;
}
