/**
 * @file mock_LED.h
 * @brief Mock LED module demonstrating observer reaction to pushbutton events.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This module registers to the "C key pressed" observer event and toggles
 * its internal LED state accordingly. The LED state change is printed
 * to standard output for demonstration.
 */

#ifndef MOCK_LED_H
#define MOCK_LED_H

void init_mock_LED(void);
void set_mock_LED_subscriptions(void);

#endif /* MOCK_LED_H */
