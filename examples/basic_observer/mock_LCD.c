/**
 * @file mock_LCD.c
 * @brief Implementation of mock LCD observer reacting to pushbutton events.
 * @version 1.0.0
 * @date 2025-10-25
 */

#include "mock_LCD.h"
#include "mock_pushbutton.h"
#include <stdio.h>

static void print_push_C_event_info(void);

void init_mock_LCD(void)
{
    /* No hardware initialization needed in mock environment */
}

void set_mock_LCD_subscriptions(void)
{
    subscribe_C_push_event(print_push_C_event_info);
}

static void print_push_C_event_info(void)
{
    (void)printf("[MOCK_LCD]: Key 'C' has been pressed\r\n");
}
