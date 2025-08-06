#include <gtest/gtest.h>
#include "./monitor.h"

void testVitals() {
    assert(vitalsOk(98.6, 70, 95) == 1);  // Normal case
    assert(vitalsOk(103, 70, 95) == 0);   // High temperature
    assert(vitalsOk(98.6, 50, 95) == 0);  // Low pulse rate
    assert(vitalsOk(98.6, 70, 85) == 0);  // Low oxygen saturation
    assert(vitalsOk(94, 70, 95) == 0);    // Low temperature
    cout << "All tests passed!\n";
}

