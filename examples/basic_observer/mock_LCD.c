/**
 * @file mock_LCD.c
 * @author niwciu (niwciu@gmail.com)
 * @brief Implementation of mock LCD observer reacting to pushbutton events.
 * @version 1.0.0
 * @date 2025-10-25
 * 
 * @copyright Copyright (c) 2025
 */

#include "mock_LCD.h"
#include "mock_pushbutton.h"
#include <stdio.h>

/* ===================== Static Function Declarations ===================== */
/**
 * @brief Callback function executed when 'C' key is pressed.
 */
static void print_push_C_event_info(void);

/* ===================== Public API Implementation ======================== */
void init_mock_LCD(void)
{
    /* No hardware initialization needed in mock environment */
}

void set_mock_LCD_subscriptions(void)
{
    subscribe_C_push_event(print_push_C_event_info);
}

/* ===================== Static Helper Functions ========================== */
static void print_push_C_event_info(void)
{
    (void)printf("[MOCK_LCD]: Key 'C' has been pressed\r\n");
}
