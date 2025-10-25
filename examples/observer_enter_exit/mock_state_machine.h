/**
 * @file mock_state_machine.h
 * @brief Mock module generating ENTER/EXIT state events.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This module alternates between ENTER and EXIT states
 * and notifies all subscribed observers with an event_state_e argument.
 */

#ifndef MOCK_STATE_MACHINE_H
#define MOCK_STATE_MACHINE_H

#include "observer.h"

void init_mock_state_machine(void);
void subscribe_state_event(observer_cb_arg_t callback);
void update_mock_state_machine(void);

#endif /* MOCK_STATE_MACHINE_H */
