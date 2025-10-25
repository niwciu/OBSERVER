/**
 * @file mock_state_machine.c
 * @brief Implementation of state change event generator using observer_enter_exit API.
 */

#include "mock_state_machine.h"
#include <stdio.h>

#define STATE_TABLE_SIZE (4U)

static observer_cb_arg_t state_subscriptions[STATE_TABLE_SIZE];
static event_state_e current_state = EVENT_STATE_EXIT;

void init_mock_state_machine(void)
{
    uint8_t i;
    for (i = 0U; i < STATE_TABLE_SIZE; ++i)
    {
        state_subscriptions[i] = NULL;
    }
    current_state = EVENT_STATE_EXIT;
}

void subscribe_state_event(observer_cb_arg_t callback)
{
    (void)subscribe_enter_exit(state_subscriptions, callback, STATE_TABLE_SIZE);
}

void update_mock_state_machine(void)
{
    /* Toggle between ENTER and EXIT */
    if (current_state == EVENT_STATE_EXIT)
    {
        current_state = EVENT_STATE_ENTER;
    }
    else
    {
        current_state = EVENT_STATE_EXIT;
    }

    notify_enter_exit(state_subscriptions, STATE_TABLE_SIZE, current_state);
}
