/**
 * @file mock_LED.c
 * @author niwciu (niwciu@gmail.com)
 * @brief Implementation of mock LED observer reacting to pushbutton "C" event.
 * @version 1.0.1
 * @date 2025-10-25
 *
 * @details
 * The LED module subscribes to pushbutton events and toggles its state.
 * Demonstrates the observer pattern in a deterministic, MISRA-compliant style.
* 
 * @copyright Copyright (c) 2025
 */

#include "mock_LED.h"
#include "mock_pushbutton.h"
#include <stdio.h>

/** @brief Enumeration representing LED state */
typedef enum
{
    MOCK_LED_OFF = 0U, /**< LED OFF state */
    MOCK_LED_ON  = 1U  /**< LED ON state */
} e_LED_state_t;

static e_LED_state_t mock_LED_1;

/* ===================== Static Function Declaration ====================== */
/**
 * @brief Toggle the mock LED state and print it to stdout.
 */
static void toggle_mock_led_state(void);

/* ===================== Public API Implementation ======================== */
void init_mock_LED(void)
{
    mock_LED_1 = MOCK_LED_OFF;
}

void set_mock_LED_subscriptions(void)
{
    subscribe_C_push_event(toggle_mock_led_state);
}

/* ===================== Static Helper Functions ========================== */
static void toggle_mock_led_state(void)
{
    if (MOCK_LED_OFF == mock_LED_1)
    {
        mock_LED_1 = MOCK_LED_ON;
        (void)printf("[MOCK_LED]: LED IS ON\r\n");
    }
    else
    {
        mock_LED_1 = MOCK_LED_OFF;
        (void)printf("[MOCK_LED]: LED IS OFF\r\n");
    }
}
