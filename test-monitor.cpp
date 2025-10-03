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
    ASSERT_EQ(vitalsOk(0, 0, 0), 0);        // All extremely low
    ASSERT_EQ(vitalsOk(200, 200, 50), 0);   // Temperature and pulse extremely high, spo2 low
}

// Extension 1: Early Warning System Tests
TEST(WarningTest, TemperatureWarnings) {
    // Hypothermia warning range: 95.0 to 96.53
    ASSERT_TRUE(isTemperatureWarning(95.5f));   // Low warning  
    ASSERT_TRUE(isTemperatureWarning(96.5f));   // High warning

    // Hyperthermia warning range: 100.47 to 102.0
    ASSERT_TRUE(isTemperatureWarning(100.5f));  // Low warning
    ASSERT_TRUE(isTemperatureWarning(101.0f));  // Mid warning
    ASSERT_TRUE(isTemperatureWarning(101.5f));  // High warning

    // No warning ranges
    ASSERT_FALSE(isTemperatureWarning(98.0f));  // Normal temp
    ASSERT_FALSE(isTemperatureWarning(99.0f));  // Normal temp
}

TEST(WarningTest, PulseRateWarnings) {    // Low pulse warning range: 60.0 to 61.5
    ASSERT_TRUE(isPulseRateWarning(60.5f));     // Low warning
    ASSERT_TRUE(isPulseRateWarning(61.0f));     // Mid warning

    // High pulse warning range: 98.5 to 100.0
    ASSERT_TRUE(isPulseRateWarning(99.0f));     // High warning
    ASSERT_TRUE(isPulseRateWarning(99.5f));     // High warning

    // No warning range
    ASSERT_FALSE(isPulseRateWarning(75.0f));    // Normal pulse
    ASSERT_FALSE(isPulseRateWarning(85.0f));    // Normal pulse
}

TEST(WarningTest, Spo2Warnings) {
    // Low SpO2 warning range: 90.0 to 91.35
    ASSERT_TRUE(isSpo2Warning(90.5f));          // Low warning
    ASSERT_TRUE(isSpo2Warning(91.0f));          // Mid warning

    // No warning range
    ASSERT_FALSE(isSpo2Warning(95.0f));         // Normal SpO2
    ASSERT_FALSE(isSpo2Warning(98.0f));         // Normal SpO2
}

TEST(VitalsWithWarningTest, SingleWarnings) {
    // These should return 1 (pass) but generate warning messages
    ASSERT_EQ(vitalsOk(95.5f, 70, 95), 1);     // Temperature warning
    ASSERT_EQ(vitalsOk(98.6f, 60.5f, 95), 1);  // Pulse rate warning
    ASSERT_EQ(vitalsOk(98.6f, 70, 90.5f), 1);  // SpO2 warning
}

TEST(VitalsWithWarningTest, MultipleWarnings) {
    // Multiple warnings but still within acceptable range
    ASSERT_EQ(vitalsOk(95.5f, 60.5f, 90.5f), 1);  // All three warnings
    ASSERT_EQ(vitalsOk(101.0f, 99.0f, 95), 1);     // Temp and pulse warnings
}
