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

// Constants for warning tolerance (1.5% of upper limits)
const float WARNING_TOLERANCE = 0.015f;  // 1.5%
const float TEMP_WARNING_TOLERANCE = TEMP_MAX * WARNING_TOLERANCE;  // 1.53
const float PULSE_WARNING_TOLERANCE = PULSE_MAX * WARNING_TOLERANCE; // 1.5
const float SPO2_WARNING_TOLERANCE = SPO2_MIN * WARNING_TOLERANCE;  // 1.35

// Generic range checking function to avoid duplication
bool isInRange(const float value, const float min, const float max) {
    return value >= min && value <= max;
}

// Pure function to check temperature
bool isTemperatureOk(const float temperature) {
    return isInRange(temperature, TEMP_MIN, TEMP_MAX);
}

// Pure function to check pulse rate
bool isPulseRateOk(const float pulseRate) {
    return isInRange(pulseRate, PULSE_MIN, PULSE_MAX);
}

// Pure function to check oxygen saturation (only has minimum limit)
bool isSpo2Ok(const float spo2) {
    return spo2 >= SPO2_MIN;
}

// Extension 1: Warning detection functions
bool isTemperatureWarning(const float temperature) {
    return (temperature >= TEMP_MIN && 
            temperature <= TEMP_MIN + TEMP_WARNING_TOLERANCE) ||
           (temperature >= TEMP_MAX - TEMP_WARNING_TOLERANCE && 
            temperature <= TEMP_MAX);
}

bool isPulseRateWarning(const float pulseRate) {
    return (pulseRate >= PULSE_MIN && 
            pulseRate <= PULSE_MIN + PULSE_WARNING_TOLERANCE) ||
           (pulseRate >= PULSE_MAX - PULSE_WARNING_TOLERANCE && 
            pulseRate <= PULSE_MAX);
}

bool isSpo2Warning(const float spo2) {
    return (spo2 >= SPO2_MIN && 
            spo2 <= SPO2_MIN + SPO2_WARNING_TOLERANCE);
}

// Function to display warning alert
void displayWarningAlert(const std::string& message) {
    std::cout << "WARNING: " << message << std::endl;
}

// Function to display critical alert
void displayCriticalAlert(const std::string& message) {
    std::cout << message << std::endl;
}

// Helper function to check and alert for a single vital with warnings
bool checkVitalWithWarning(const bool isOk, const bool isWarning, 
                          const std::string& criticalMsg, 
                          const std::string& warningMsg) {
    if (!isOk) {
        displayCriticalAlert(criticalMsg);
        return false;
    }
    if (isWarning) {
        displayWarningAlert(warningMsg);
    }
    return true;
}

// Helper function to check and alert for a single vital (legacy support)
bool checkVital(const bool isOk, const std::string& alertMessage) {
    if (!isOk) {
        displayCriticalAlert(alertMessage);
        return false;
    }
    return true;
}

// Helper function to check all vitals with warnings (Extension 1)
bool checkAllVitalsWithWarnings(const float temperature, 
                               const float pulseRate, const float spo2) {
    bool tempOk = checkVitalWithWarning(
        isTemperatureOk(temperature), isTemperatureWarning(temperature),
        "Temperature is critical!", "Approaching temperature limits!");
    bool pulseOk = checkVitalWithWarning(
        isPulseRateOk(pulseRate), isPulseRateWarning(pulseRate),
        "Pulse Rate is out of range!", "Approaching pulse rate limits!");
    bool spo2Ok = checkVitalWithWarning(
        isSpo2Ok(spo2), isSpo2Warning(spo2),
        "Oxygen Saturation out of range!", "Approaching oxygen saturation limits!");
    return tempOk && pulseOk && spo2Ok;
}

// Helper function to check all vitals sequentially (legacy)
bool checkAllVitals(const float temperature, const float pulseRate,
                    const float spo2) {
    return checkVital(isTemperatureOk(temperature), "Temperature is critical!")
        && checkVital(isPulseRateOk(pulseRate), "Pulse Rate is out of range!")
        && checkVital(isSpo2Ok(spo2), "Oxygen Saturation out of range!");
}

// Main function to check vitals with early warning system (CCN = 1)
int vitalsOk(const float temperature, const float pulseRate, const float spo2) {
    return checkAllVitalsWithWarnings(temperature, pulseRate, spo2) ? 1 : 0;
}

// Test function for manual verification including Extension 1
void testVitals() {
    std::cout << "=== Testing Early Warning System (Extension 1) ===" << std::endl;
    
    // Test normal case
    std::cout << "\n1. Normal vitals test:" << std::endl;
    int result1 = vitalsOk(98.6f, 70.0f, 95.0f);
    std::cout << "Result: " << (result1 ? "PASS" : "FAIL") << std::endl;

    // Test warning case - approaching hypothermia
    std::cout << "\n2. Warning case - approaching hypothermia:" << std::endl;
    int result2 = vitalsOk(95.5f, 70.0f, 95.0f);  // Within warning range
    std::cout << "Result: " << (result2 ? "PASS with warning" : "FAIL")
              << std::endl;

    // Test warning case - approaching hyperthermia  
    std::cout << "\n3. Warning case - approaching hyperthermia:" << std::endl;
    int result3 = vitalsOk(101.0f, 70.0f, 95.0f);  // Within warning range
    std::cout << "Result: " << (result3 ? "PASS with warning" : "FAIL")
              << std::endl;

    // Test critical case
    std::cout << "\n4. Critical case:" << std::endl;
    int result4 = vitalsOk(103.0f, 110.0f, 85.0f);
    std::cout << "Result: " << (result4 == 0 ? "FAIL (as expected)" : "PASS")
              << std::endl;
}
