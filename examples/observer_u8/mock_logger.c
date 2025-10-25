/**
 * @file mock_logger.c
 * @brief Mock observer logging sensor data updates.
 */

#include "mock_sensor.h"
#include <stdio.h>

static void log_sensor_value(uint8_t value);

void init_mock_logger(void)
{
    subscribe_sensor_data(log_sensor_value);
}

static void log_sensor_value(uint8_t value)
{
    (void)printf("[LOGGER] Sensor value = %u\r\n", value);
}
