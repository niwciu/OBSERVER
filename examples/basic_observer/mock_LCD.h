/**
 * @file mock_LCD.h
 * @brief Mock LCD observer module for displaying pushbutton event information.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This module prints informational text whenever the "C" key is pressed,
 * showing how multiple observers can react independently to the same event.
 */

#ifndef MOCK_LCD_H
#define MOCK_LCD_H

void init_mock_LCD(void);
void set_mock_LCD_subscriptions(void);

#endif /* MOCK_LCD_H */
