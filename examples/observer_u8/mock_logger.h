/**
 * @file mock_logger.h
 * @author niwciu (niwciu@gmail.com)
 * @brief Mock logger observer module for sensor data updates.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * Provides initialization of logger observer which subscribes
 * to uint8_t sensor data updates from the mock sensor.
 *
 * @note Deterministic, static memory; suitable for safety-critical simulation.
 *
 * @copyright Copyright (c) 2025
 */

#ifndef MOCK_LOGGER_H
#define MOCK_LOGGER_H

#include "observer.h"

/**
 * @brief Initialize the mock logger observer.
 */
void init_mock_logger(void);

#endif /* MOCK_LOGGER_H */
