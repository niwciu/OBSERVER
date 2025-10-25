/**
 * @file mock_LED.h
 * @author niwciu (niwciu@gmail.com)
 * @brief Mock LED module demonstrating observer reaction to pushbutton events.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This module registers to the "C key pressed" observer event and toggles
 * its internal LED state accordingly. The LED state change is printed
 * to standard output for demonstration purposes.
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef MOCK_LED_H
#define MOCK_LED_H

/**
 * @brief Initialize the mock LED module.
 */
void init_mock_LED(void);

/**
 * @brief Register the LED observer callback for the "C key pressed" event.
 */
void set_mock_LED_subscriptions(void);

#endif /* MOCK_LED_H */
