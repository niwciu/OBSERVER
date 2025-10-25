/**
 * @file mock_pushbutton.c
 * @author niwciu (niwciu@gmail.com)
 * @brief Implementation of mock pushbutton "C" event generator.
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @details
 * This module simulates a pushbutton input using terminal keyboard input.
 * Each time the 'c' key is detected, the observer notification mechanism
 * from observer_lib is invoked.
 *
 * @note POSIX system calls (select, termios) are used solely for simulation.
 *       These calls are not part of MISRA-C safe subset but are acceptable
 *       for host-side testing and demonstration.
 * 
 * @copyright Copyright (c) 2025
 */
 */

#include "mock_pushbutton.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

#define SUBSCR_TABLE_SIZE (4U)

static observer_cb_t key_c_push_subscr_table[SUBSCR_TABLE_SIZE];
static struct termios oldt;
static struct termios newt;

/* ===================== Static Function Declarations ====================== */
static void clear_subscr_tables(void);
static int kbhit(void); /* Non-MISRA: POSIX API for simulation */
static int getch(void); /* Non-MISRA: POSIX API for simulation */

/* ===================== Public API Implementation ========================= */
void init_mock_pushbutton(void)
{
    clear_subscr_tables();
    (void)tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    (void)tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void deinit_mock_pushbutton(void)
{
    (void)tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void subscribe_C_push_event(observer_cb_t callback)
{
    (void)subscribe(key_c_push_subscr_table, callback, SUBSCR_TABLE_SIZE);
}

void update_mock_pushbutton(void)
{
    if (kbhit() != 0)
    {
        const int c = getch();
        if (c == 'c')
        {
            notify(key_c_push_subscr_table, SUBSCR_TABLE_SIZE);
        }
    }
}

/* ===================== Static Helper Functions ========================== */
static void clear_subscr_tables(void)
{
    uint8_t i;
    for (i = 0U; i < SUBSCR_TABLE_SIZE; ++i)
    {
        key_c_push_subscr_table[i] = NULL;
    }
}

/**
 * @brief Check if a key was pressed (non-blocking).
 * @return Non-zero if key available, zero otherwise.
 * @note Non-MISRA: uses select() from POSIX for simulation.
 */
static int kbhit(void)
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

/**
 * @brief Read character from stdin without waiting for newline.
 * @return Character code read from stdin.
 */
static int getch(void)
{
    return getchar();
}
