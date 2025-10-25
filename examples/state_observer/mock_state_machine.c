/**
 * @file mock_state_machine.c
 * @author niwciu (niwciu@gmail.com)
 * @brief Mock state machine generating ENTER/EXIT events.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This module alternates between ENTER and EXIT states,
 * notifying all subscribed observers via observer_enter_exit API.
 *
 * @note Deterministic execution; static array for subscriptions.
 *
 * @copyright Copyright (c) 2025
 */

#include "mock_state_machine.h"
#include "observer.h"
#include <stdint.h>
#include <stdio.h>

/* ===================== Local Variables ================================= */
#define STATE_TABLE_SIZE (4U) /**< Maximum number of observers */

static observer_cb_state_t state_subscriptions[STATE_TABLE_SIZE];
static event_state_e current_state = EVENT_STATE_EXIT;

/* ===================== Public API Implementation ======================== */
void init_mock_state_machine(void)
{
    uint8_t i;

    for (i = 0U; i < STATE_TABLE_SIZE; ++i)
    {
        state_subscriptions[i] = NULL;
    }

    current_state = EVENT_STATE_EXIT;
}

void subscribe_state_event(observer_cb_state_t callback)
{
    (void)subscribe_state_change(state_subscriptions, callback, STATE_TABLE_SIZE);
}

void update_mock_state_machine(void)
{
    /* Toggle state deterministically */
    if (current_state == EVENT_STATE_EXIT)
    {
        current_state = EVENT_STATE_ENTER;
    }
    else
    {
        current_state = EVENT_STATE_EXIT;
    }

    notify_state_change(state_subscriptions, STATE_TABLE_SIZE, current_state);
}
