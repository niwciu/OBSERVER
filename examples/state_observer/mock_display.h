/**
 * @file mock_display.h
 * @author niwciu (niwciu@gmail.com)
 * @brief Mock display observer module for state transitions.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * Provides initialization of display observer which subscribes
 * to ENTER/EXIT state changes from the mock state machine.
 *
 * @note Deterministic, static memory; suitable for safety-critical simulation.
 *
 * @copyright Copyright (c) 2025
 */

#ifndef MOCK_DISPLAY_H
#define MOCK_DISPLAY_H

#include "observer.h"

/**
 * @brief Initialize the mock display observer.
 */
void init_mock_display(void);

#endif /* MOCK_DISPLAY_H */
