/**
 * @file mock_state_machine.h
 * @author niwciu (niwciu@gmail.com)
 * @brief Mock module generating ENTER/EXIT state events.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * Alternates between ENTER and EXIT states and notifies all observers
 * registered via observer_enter_exit pattern.
 *
 * @note Deterministic execution, static memory only.
 *
 * @copyright Copyright (c) 2025
 */

#ifndef MOCK_STATE_MACHINE_H
#define MOCK_STATE_MACHINE_H

#include "observer.h"

/**
 * @brief Initialize the mock state machine.
 */
void init_mock_state_machine(void);

/**
 * @brief Subscribe a callback to ENTER/EXIT state events.
 *
 * @param callback Pointer to observer function taking event_state_e argument.
 */
void subscribe_state_event(observer_cb_state_t callback);

/**
 * @brief Update the state machine, toggling state and notifying observers.
 */
void update_mock_state_machine(void);

#endif /* MOCK_STATE_MACHINE_H */
