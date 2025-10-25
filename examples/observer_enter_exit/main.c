/**
 * @file main_state_example.c
 * @author niwciu (niwciu@gmail.com)
 * @brief Entry point for mock state machine demonstration.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This program demonstrates the observer_enter_exit API in a pure C environment.
 * The mock state machine alternates between ENTER and EXIT states.
 * The display observer reacts to each state transition.
 *
 * @note
 * Deterministic execution with static memory allocation only.
 * Suitable for safety-critical demonstration (ISO 26262, MISRA C:2012).
 *
 * @copyright Copyright (c) 2025
 */

#include "mock_state_machine.h"
#include "mock_display.h"
#include <stdio.h>
#include <unistd.h> /* Non-MISRA: host-side delay for simulation */

/* ===================== Static Function Declarations ===================== */
/**
 * @brief Print example usage information.
 * @note Purely informational; does not affect program logic.
 */
static void print_example_info(void);

/* ===================== Main Entry Point ================================= */
/**
 * @brief Program entry point.
 * Initializes modules, prints example info, and runs main state loop.
 * @return Returns 0 on normal exit.
 */
int main(void)
{
    print_example_info();

    init_mock_state_machine();
    init_mock_display();

    /* Main loop: alternate between ENTER and EXIT states */
    for (;;)
    {
        update_mock_state_machine();
        usleep(1000000U); /* 1 second delay for demonstration */
    }

    /* Normal exit (unreachable in current design) */
    return 0;
}

/* ===================== Static Helper Functions ========================= */
static void print_example_info(void)
{
    (void)printf("\r\n=================================================================\r\n");
    (void)printf(" observer_enter_exit Example: Mock State Machine\r\n");
    (void)printf("=================================================================\r\n");
    (void)printf(" The state machine alternates between ENTER and EXIT states.\r\n");
    (void)printf(" Observers (Display) react to each state transition independently.\r\n\r\n");
    (void)printf(" Demonstrates deterministic, MISRA-compliant observer_enter_exit pattern.\r\n\r\n");
    (void)printf("=================================================================\r\n");
    (void)printf(" Each second triggers a state transition.\r\n");
    (void)printf(" To stop, press Ctrl + Z\r\n\r\n");
}
