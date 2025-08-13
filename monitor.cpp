#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// Pure function to check temperature
bool isTemperatureOk(float temperature) {
    return temperature >= 95 && temperature <= 102;
}

// Pure function to check pulse rate
bool isPulseRateOk(float pulseRate) {
    return pulseRate >= 60 && pulseRate <= 100;
}

// Pure function to check oxygen saturation
bool isSpo2Ok(float spo2) {
    return spo2 >= 90;
}

// Function to display critical alert animation
void displayCriticalAlert(const std::string& message) {
    cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
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
