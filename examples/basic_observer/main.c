/**
 * @file main.c
 * @author niwciu (niwciu@gmail.com)
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
 * 
 * @copyright Copyright (c) 2025
 */

#include "mock_LCD.h"
#include "mock_LED.h"
#include "mock_pushbutton.h"
#include <stdio.h>

/* ===================== Static Function Declarations ===================== */
/**
 * @brief Initialize all mock modules.
 */
static void init_mock_modules(void);

/**
 * @brief Register all observers to the pushbutton event.
 */
static void set_all_subscriptions(void);

/**
 * @brief Print information about example usage.
 */
static void print_example_info(void);

/* ===================== Main Entry Point ================================= */
/**
 * @brief Program entry point.
 * Initializes modules, sets up subscriptions and runs the main loop.
 * @return Returns 0 on normal exit.
 */
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
    (void)printf("\r\n=================================================================\r\n");
    (void)printf("                     Basic Observer Example\r\n");
    (void)printf("=================================================================\r\n");
    (void)printf(" Each press of 'c' key triggers a notification event.\r\n");
    (void)printf(" Observers (LCD and LED) react independently.\r\n\r\n");
    (void)printf(" Demonstrates deterministic, MISRA-compliant observer pattern.\r\n\r\n");
    (void)printf("=================================================================\r\n");
    (void)printf(" To check how example works press 'c' key\r\n");
    (void)printf(" To stop, press Ctrl + Z\r\n\r\n");
}
