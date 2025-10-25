/**
 * @file mock_sensor.h
 * @author niwciu (niwciu@gmail.com)
 * @brief Mock sensor module generating uint8_t data notifications.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This module periodically generates simulated sensor readings
 * and notifies all subscribed observers with a uint8_t argument.
 * Demonstrates use of the observer_u8 API.
 *
 * @note Deterministic execution, static memory only.
 *
 * @copyright Copyright (c) 2025
 */

#ifndef MOCK_SENSOR_H
#define MOCK_SENSOR_H

#include "observer.h"

/**
 * @brief Initialize the mock sensor module.
 */
void init_mock_sensor(void);

/**
 * @brief Subscribe callback for sensor data updates.
 * @param callback Callback function taking uint8_t argument.
 */
void subscribe_sensor_data(observer_cb_u8_arg_t callback);

/**
 * @brief Simulate sensor data update (e.g. called periodically).
 */
void update_mock_sensor(void);

#endif /* MOCK_SENSOR_H */
