/**
 * @file mock_LCD.c
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "mock_LCD.h"
#include "mock_pushbutton.h"

#include <stdio.h>

static void print_push_C_event_info(void);

void init_mock_LCD(void)
{
}
void set_mock_LCD_subscriptions(void)
{
    subscribe_C_push_event(print_push_C_event_info);
}

static void print_push_C_event_info(void)
{
    printf("MOCK_LCD info: Key C has been pushed\r\n");
}