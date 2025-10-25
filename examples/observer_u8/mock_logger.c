/**
 * @file mock_logger.c
 * @author niwciu (niwciu@gmail.com)
 * @brief Mock observer logging sensor data updates.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This module subscribes to sensor data updates from the mock sensor
 * and prints the uint8_t value to stdout.
 *
 * @note Deterministic observer: static memory, no dynamic allocation.
 *
 * @copyright Copyright (c) 2025
 */

#include "mock_logger.h"
#include "mock_sensor.h"
#include <stdio.h>

/* ===================== Static Function Declarations ===================== */
static void log_sensor_value(uint8_t value);

/* ===================== Public API Implementation ======================== */
void init_mock_logger(void)
{
    subscribe_sensor_data(log_sensor_value);
}

/* ===================== Static Helper Functions ========================== */
static void log_sensor_value(uint8_t value)
{
    (void)printf("[LOGGER]: Sensor value = %u\r\n", value);
}
