/**
 * @file mock_display.c
 * @author niwciu (niwciu@gmail.com)
 * @brief Mock observer printing state transitions.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This module subscribes to state change events (ENTER/EXIT) from the
 * mock state machine and prints corresponding messages to stdout.
 *
 * @note Deterministic observer: static memory, no dynamic allocation.
 * Safe for demonstration in safety-critical context.
 *
 * @copyright Copyright (c) 2025
 */

#include "mock_display.h"
#include "mock_state_machine.h"
#include <stdio.h>

/* ===================== Static Function Declarations ===================== */
static void display_state_change(event_state_e state);

/* ===================== Public API Implementation ======================== */
void init_mock_display(void)
{
    subscribe_state_event(display_state_change);
}

/* ===================== Static Helper Functions ========================== */
static void display_state_change(event_state_e state)
{
    if (state == EVENT_STATE_ENTER)
    {
        (void)printf("[DISPLAY]: State ENTER\r\n");
    }
    else
    {
        (void)printf("[DISPLAY]: State EXIT\r\n");
    }
}
