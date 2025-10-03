#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

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

// Function to display critical alert animation
// Function to display critical alert
void displayCriticalAlert(const std::string& message) {
    std::cout << message << std::endl;
}

// Main function to check vitals
int vitalsOk(float temperature, float pulseRate, float spo2) {
    if (!isTemperatureOk(temperature)) {
        displayCriticalAlert("Temperature is critical!");
        return 0;
    }
    if (!isPulseRateOk(pulseRate)) {
        displayCriticalAlert("Pulse Rate is out of range!");
        return 0;
    }
    if (!isSpo2Ok(spo2)) {
        displayCriticalAlert("Oxygen Saturation out of range!");
        return 0;
    }
    return 1;
}
