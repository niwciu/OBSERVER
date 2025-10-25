/**
 * @file mock_pushbutton.h
 * @author 
 * @brief Mock module simulating a hardware pushbutton ("C") in terminal environment.
 * @version 1.0.1
 * @date 2025-10-25
 *
 * @details
 * This module emulates a pushbutton event source using terminal input.
 * Pressing the 'c' key triggers a notify action to all subscribed observers.
 *
 * The implementation is designed for demonstration and testing purposes
 * and does not perform any dynamic memory allocation.
 * All timing and I/O operations are deterministic and bounded.
 *
 * @note Terminal mode configuration uses POSIX system calls
 *       (non-MISRA compliant, justified for simulation only).
 *
 * @copyright
 * Copyright (c) 2025
 */

#ifndef MOCK_PUSHBUTTON_H
#define MOCK_PUSHBUTTON_H

#include "observer.h"

/**
 * @brief Initialize the mock pushbutton module.
 * Configures terminal to raw mode (non-canonical, no echo).
 */
void init_mock_pushbutton(void);

/**
 * @brief Deinitialize the mock pushbutton module.
 * Restores terminal to normal operation mode.
 */
void deinit_mock_pushbutton(void);

/**
 * @brief Subscribe a callback to "C key pressed" event.
 * @param callback Pointer to callback function to be registered.
 */
void subscribe_C_push_event(observer_cb_t callback);

/**
 * @brief Update mock pushbutton state.
 * Checks if the 'c' key was pressed and triggers notifications.
 */
void update_mock_pushbutton(void);

#endif /* MOCK_PUSHBUTTON_H */
