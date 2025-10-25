/**
 * @file mock_display.c
 * @brief Mock observer printing state transitions.
 */

#include "mock_state_machine.h"
#include <stdio.h>

static void display_state_change(event_state_e state);

void init_mock_display(void)
{
    subscribe_state_event(display_state_change);
}

static void display_state_change(event_state_e state)
{
    if (state == EVENT_STATE_ENTER)
    {
        (void)printf("[DISPLAY] State entered\r\n");
    }
    else
    {
        (void)printf("[DISPLAY] State exited\r\n");
    }
}
