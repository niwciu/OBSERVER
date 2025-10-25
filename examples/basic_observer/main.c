/**
 * @file main.c
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "mock_LCD.h"
#include "mock_LED.h"
#include "mock_pushbutton.h"

#include <stdio.h>

static void init_mock_modules(void);
static void set_all_subscriptions(void);
static void print_example_info(void);

int main(void)
{
    init_mock_modules();
    set_all_subscriptions();
    print_example_info();

    while (1)
    {
        update_mock_pushbutton();
    }

    deinit_mock_pushbutton(); // 🔧 Przywraca terminal po Ctrl+Z
    return 0;
}

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
    printf("\r\n======================================================================================\r\n");
    printf("                      basic observer example\r\n");
    printf("======================================================================================\r\n");
    printf(" After running this example each press of \"c\" key (send through terminal)\r\n");
    printf(" will couse notify action of this event to mock_LCD and mock_LED module and \r\n");
    printf(" will run registered specific callback action for each module\r\n\r\n");
    printf(" This simple example shows how to use observer library to implement \r\n");
    printf(" observer coding pattern\r\n");
    printf("======================================================================================\r\n");
    printf(" to stop the example press Ctr + Z \r\n");
    printf("======================================================================================\r\n");
}
