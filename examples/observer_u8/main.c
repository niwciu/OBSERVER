/**
 * @file main_sensor_example.c
 * @author niwciu (niwciu@gmail.com)
 * @brief Entry point for mock sensor demonstration using observer_u8 API.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This program demonstrates the observer_u8 API in a pure C environment.
 * The mock sensor periodically increments a uint8_t value and notifies
 * subscribed observers (e.g., logger) with the new value.
 *
 * @note Deterministic execution with static memory allocation only.
 * Uses usleep for host-side simulation (non-MISRA for embedded systems).
 *
 * @copyright Copyright (c) 2025
 */

#include "mock_sensor.h"
#include "mock_logger.h"
#include <stdio.h>
#include <unistd.h> /* Non-MISRA: host-side delay for simulation */

/* ===================== Static Function Declarations ===================== */
/**
 * @brief Print example usage information.
 */
static void print_example_info(void);

/* ===================== Main Entry Point ================================= */
/**
 * @brief Program entry point.
 * Initializes modules, prints example info, and runs main sensor loop.
 * @return Returns 0 on normal exit.
 */
int main(void)
{
    print_example_info();

    init_mock_sensor();
    init_mock_logger();

    /* Main loop: periodically update sensor and notify observers */
    for (;;)
    {
        update_mock_sensor();
        usleep(500000U); /* 500 ms delay for demonstration */
    }

    /* Normal exit (unreachable in current design) */
    return 0;
}

/* ===================== Static Helper Functions ========================= */
static void print_example_info(void)
{
    (void)printf("\r\n=================================================================\r\n");
    (void)printf(" observer_u8 Example: Mock Sensor\r\n");
    (void)printf("=================================================================\r\n");
    (void)printf(" Sensor value is incremented periodically and sent to observers.\r\n");
    (void)printf(" Observers (Logger) print the sensor value independently.\r\n\r\n");
    (void)printf(" Demonstrates deterministic, MISRA-compliant observer_u8 pattern.\r\n\r\n");
    (void)printf("=================================================================\r\n");
    (void)printf(" Each 500 ms triggers a sensor update.\r\n");
    (void)printf(" To stop, press Ctrl + Z\r\n\r\n");
}
