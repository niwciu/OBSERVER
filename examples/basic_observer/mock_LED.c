/**
 * @file mock_LED.c
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "mock_LED.h"
#include "mock_pushbutton.h"

#include <stdio.h>

typedef enum
{
    MOCK_LED_OFF = 0U,
    MOCK_LED_ON = 1U,

} e_LED_state_t;

e_LED_state_t mock_LED_1;

static void toogle_mock_led_state(void);

void init_mock_LED(void)
{
    mock_LED_1 = MOCK_LED_OFF;
}

void set_mock_LED_subscriptions(void)
{
    subscribe_C_push_event(toogle_mock_led_state);
}

static void toogle_mock_led_state(void)
{
    if (MOCK_LED_OFF == mock_LED_1)
    {
        mock_LED_1 = MOCK_LED_ON;
        printf("LED_STATE IS ON\r\n");
    }
    else
    {
        mock_LED_1 = MOCK_LED_OFF;
        printf("LED_STATE IS OFF\r\n");
    }
}