#include <gtest/gtest.h>
#include "./monitor.h"

TEST(VitalsTest, NormalCase) {
    ASSERT_EQ(vitalsOk(98.6, 70, 95), 1);  // Normal case
}

TEST(VitalsTest, HighTemperature) {
    ASSERT_EQ(vitalsOk(103, 70, 95), 0);   // High temperature
}

TEST(VitalsTest, LowPulseRate) {
    ASSERT_EQ(vitalsOk(98.6, 50, 95), 0);  // Low pulse rate
}

TEST(VitalsTest, LowOxygenSaturation) {
    ASSERT_EQ(vitalsOk(98.6, 70, 85), 0);  // Low oxygen saturation
}

TEST(VitalsTest, LowTemperature) {
    ASSERT_EQ(vitalsOk(94, 70, 95), 0);    // Low temperature
}
