/**
 * @file main_sensor_example.c
 * @brief Demonstration of observer_u8 (uint8_t argument) API.
 */

#include "mock_sensor.h"
#include "mock_logger.h"
#include <stdio.h>
#include <unistd.h> /* for usleep (simulation only) */

extern void init_mock_logger(void);

int main(void)
{
    (void)printf("\r\n=== observer_u8 Example: Mock Sensor ===\r\n");

    init_mock_sensor();
    init_mock_logger();

    for (;;)
    {
        update_mock_sensor();
        usleep(500000); /* 500 ms delay for readability */
    }

    return 0;
}
