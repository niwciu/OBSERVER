/**
 * @file main.c
 * @brief Entry point for mock observer demonstration.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This program demonstrates the observer pattern implemented in pure C.
 * The pushbutton module notifies all subscribers (LED, LCD) when the 'c'
 * key is pressed in the terminal.
 *
 * The program operates deterministically with static memory only.
 * Exiting restores the terminal configuration.
 */

#include "mock_LCD.h"
#include "mock_LED.h"
#include "mock_pushbutton.h"
#include <stdio.h>

/* ===================== Static Function Declarations ===================== */
static void init_mock_modules(void);
static void set_all_subscriptions(void);
static void print_example_info(void);

/* ===================== Main Entry Point ================================= */

int main(void)
{
    init_mock_modules();
    set_all_subscriptions();
    print_example_info();

    for (;;)
    {
        update_mock_pushbutton();
    }

    /* Graceful shutdown — normally unreachable, but safe for analysis */
    deinit_mock_pushbutton();
    return 0;
}

/* ===================== Static Helper Functions ========================= */

static void init_mock_modules(void)
{
    init_mock_LCD();
    init_mock_LED();
    init_mock_pushbutton();
}

static void set_all_subscriptions(void)
{
    set_mock_LCD_subscriptions();
    set_mock_LED_subscriptions();
}

static void print_example_info(void)
{
    (void)printf("\r\n============================================================\r\n");
    (void)printf("                     Basic Observer Example\r\n");
    (void)printf("============================================================\r\n");
    (void)printf(" Each press of 'c' key triggers a notification event.\r\n");
    (void)printf(" Observers (LCD and LED) react independently.\r\n\r\n");
    (void)printf(" Demonstrates deterministic, MISRA-compliant observer pattern.\r\n");
    (void)printf("============================================================\r\n");
    (void)printf(" To stop, press Ctrl + Z\r\n");
    (void)printf("============================================================\r\n");
}
