/**
 * @file main_state_example.c
 * @brief Demonstration of observer_enter_exit (state change) API.
 */

#include "mock_state_machine.h"
#include "mock_display.h"
#include <stdio.h>
#include <unistd.h>

extern void init_mock_display(void);

int main(void)
{
    (void)printf("\r\n=== observer_enter_exit Example: Mock State Machine ===\r\n");

    init_mock_state_machine();
    init_mock_display();

    for (;;)
    {
        update_mock_state_machine();
        usleep(1000000); /* 1 second between transitions */
    }

    return 0;
}
