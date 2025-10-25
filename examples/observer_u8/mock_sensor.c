/**
 * @file mock_sensor.c
 * @brief Implementation of mock sensor data generator.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This module simulates sensor data updates by incrementing a counter
 * and notifying observers with the new value.
 */

#include "mock_sensor.h"
#include <stdio.h>
#include <stdint.h>

#define SENSOR_TABLE_SIZE (4U)

static observer_cb_u8_arg_t sensor_subscriptions[SENSOR_TABLE_SIZE];
static uint8_t sensor_value = 0U;

void init_mock_sensor(void)
{
    uint8_t i;
    for (i = 0U; i < SENSOR_TABLE_SIZE; ++i)
    {
        sensor_subscriptions[i] = NULL;
    }
    sensor_value = 0U;
}

void subscribe_sensor_data(observer_cb_u8_arg_t callback)
{
    (void)subscribe_u8(sensor_subscriptions, callback, SENSOR_TABLE_SIZE);
}

void update_mock_sensor(void)
{
    sensor_value++;
    notify_u8(sensor_subscriptions, SENSOR_TABLE_SIZE, sensor_value);
}
