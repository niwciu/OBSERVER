/**
 * @file mock_sensor.c
 * @author niwciu (niwciu@gmail.com)
 * @brief Implementation of mock sensor data generator using observer_u8 API.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This module simulates sensor data updates by incrementing a uint8_t counter
 * and notifying all subscribed observers with the new value.
 *
 * @note Deterministic execution with static subscription table.
 * Safe for demonstration in ISO 26262 context.
 *
 * @copyright Copyright (c) 2025
 */

#include "mock_sensor.h"
#include "observer.h"
#include <stdint.h>
#include <stdio.h>

/* ===================== Local Variables ================================= */
#define SENSOR_TABLE_SIZE (4U) /**< Maximum number of sensor observers */

static observer_cb_u8_arg_t sensor_subscriptions[SENSOR_TABLE_SIZE];
static uint8_t sensor_value = 0U;

/* ===================== Public API Implementation ======================== */
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
    sensor_value++; /* Increment sensor value deterministically */
    notify_u8(sensor_subscriptions, SENSOR_TABLE_SIZE, sensor_value);
}
