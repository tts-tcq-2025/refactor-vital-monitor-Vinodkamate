// Copyright 2025 Health Monitor System
#include <gtest/gtest.h>
#include "./monitor.h"

// Test the generic range checking function
TEST(RangeTest, ValueInRange) {
    ASSERT_TRUE(isInRange(50, 0, 100));
    ASSERT_TRUE(isInRange(0, 0, 100));    // Boundary: minimum
    ASSERT_TRUE(isInRange(100, 0, 100));  // Boundary: maximum
}

TEST(RangeTest, ValueOutOfRange) {
    ASSERT_FALSE(isInRange(-1, 0, 100));   // Below minimum
    ASSERT_FALSE(isInRange(101, 0, 100));  // Above maximum
}

// Test individual vital sign functions
TEST(TemperatureTest, NormalTemperature) {
    ASSERT_TRUE(isTemperatureOk(98.6));
    ASSERT_TRUE(isTemperatureOk(99.0));
}

TEST(TemperatureTest, BoundaryTemperature) {
    ASSERT_TRUE(isTemperatureOk(95.0));   // Minimum boundary
    ASSERT_TRUE(isTemperatureOk(102.0));  // Maximum boundary
}

TEST(TemperatureTest, OutOfRangeTemperature) {
    ASSERT_FALSE(isTemperatureOk(94.9));   // Just below minimum
    ASSERT_FALSE(isTemperatureOk(102.1));  // Just above maximum
    ASSERT_FALSE(isTemperatureOk(103.0));  // High temperature
    ASSERT_FALSE(isTemperatureOk(90.0));   // Very low temperature
}

TEST(PulseRateTest, NormalPulseRate) {
    ASSERT_TRUE(isPulseRateOk(70));
    ASSERT_TRUE(isPulseRateOk(80));
}

TEST(PulseRateTest, BoundaryPulseRate) {
    ASSERT_TRUE(isPulseRateOk(60.0));   // Minimum boundary
    ASSERT_TRUE(isPulseRateOk(100.0));  // Maximum boundary
}

TEST(PulseRateTest, OutOfRangePulseRate) {
    ASSERT_FALSE(isPulseRateOk(59.9));   // Just below minimum
    ASSERT_FALSE(isPulseRateOk(100.1));  // Just above maximum
    ASSERT_FALSE(isPulseRateOk(110));    // High pulse rate
    ASSERT_FALSE(isPulseRateOk(50));     // Low pulse rate
}

TEST(Spo2Test, NormalSpo2) {
    ASSERT_TRUE(isSpo2Ok(95));
    ASSERT_TRUE(isSpo2Ok(98));
    ASSERT_TRUE(isSpo2Ok(100));
}

TEST(Spo2Test, BoundarySpo2) {
    ASSERT_TRUE(isSpo2Ok(90.0));  // Minimum boundary
}

TEST(Spo2Test, OutOfRangeSpo2) {
    ASSERT_FALSE(isSpo2Ok(89.9));  // Just below minimum
    ASSERT_FALSE(isSpo2Ok(85));    // Low oxygen saturation
    ASSERT_FALSE(isSpo2Ok(80));    // Very low oxygen saturation
}

// Test complete vital signs monitoring
TEST(VitalsTest, AllNormalVitals) {
    ASSERT_EQ(vitalsOk(98.6, 70, 95), 1);  // All normal
    ASSERT_EQ(vitalsOk(99.0, 80, 98), 1);  // All normal variation
}

TEST(VitalsTest, AllBoundaryVitals) {
    ASSERT_EQ(vitalsOk(95.0, 60.0, 90.0), 1);    // All at minimum boundaries
    ASSERT_EQ(vitalsOk(102.0, 100.0, 100.0), 1);  // Temperature and pulse at max, spo2 high
}

TEST(VitalsTest, SingleVitalOutOfRange) {
    ASSERT_EQ(vitalsOk(103, 70, 95), 0);    // Only temperature high
    ASSERT_EQ(vitalsOk(94, 70, 95), 0);     // Only temperature low
    ASSERT_EQ(vitalsOk(98.6, 50, 95), 0);   // Only pulse rate low
    ASSERT_EQ(vitalsOk(98.6, 110, 95), 0);  // Only pulse rate high
    ASSERT_EQ(vitalsOk(98.6, 70, 85), 0);   // Only oxygen saturation low
}

TEST(VitalsTest, MultipleVitalsOutOfRange) {
    ASSERT_EQ(vitalsOk(103, 110, 85), 0);  // All vitals out of range
    ASSERT_EQ(vitalsOk(94, 50, 85), 0);    // All vitals low
    ASSERT_EQ(vitalsOk(103, 110, 95), 0);  // Temperature and pulse high
    ASSERT_EQ(vitalsOk(94, 70, 85), 0);    // Temperature and spo2 low
}

TEST(VitalsTest, ExtremeCases) {
    ASSERT_EQ(vitalsOk(0, 0, 0), 0);       // All extremely low
    ASSERT_EQ(vitalsOk(200, 200, 50), 0);  // Temperature and pulse extremely high, spo2 low
}
