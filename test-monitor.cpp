#include <gtest/gtest.h>
#include "./monitor.h"

void testVitals() {
    ASSERT_EQ(vitalsOk(98.6, 70, 95) == 1);  // Normal case
    ASSERT_EQ(vitalsOk(103, 70, 95) == 0);   // High temperature
    ASSERT_EQ(vitalsOk(98.6, 50, 95) == 0);  // Low pulse rate
    ASSERT_EQ(vitalsOk(98.6, 70, 85) == 0);  // Low oxygen saturation
    ASSERT_EQ(vitalsOk(94, 70, 95) == 0);    // Low temperature
    cout << "All tests passed!\n";
}


