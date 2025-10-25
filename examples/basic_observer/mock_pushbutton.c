/**
 * @file mock_pushbutton.c
 * @author niwciu
 * @brief symulacja przycisku "C" reagująca bez Entera
 * @version 1.0.1
 * @date 2025-10-25
 */

#include "mock_pushbutton.h"

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

#define SUBSCR_TABLE_SIZE 4

observer_cb_t key_c_push_subscr_table[SUBSCR_TABLE_SIZE];

static struct termios oldt, newt;

static void clear_subscr_tables(void);
static int kbhit(void);
static int getch(void);

void init_mock_pushbutton(void)
{
    clear_subscr_tables();

    // 🔧 Ustaw terminal w tryb RAW (bez Entera)
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // bez kanonicznego trybu i echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void deinit_mock_pushbutton(void)
{
    // 🔧 Przywróć normalny tryb terminala
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void subscribe_C_push_event(observer_cb_t callback)
{
    subscribe(key_c_push_subscr_table, callback, SUBSCR_TABLE_SIZE);
}

void update_mock_pushbutton(void)
{
    if (kbhit())
    {
        int c = getch();
        if (c == 'c')
        {
            notify(key_c_push_subscr_table, SUBSCR_TABLE_SIZE);
        }
    }
}

static void clear_subscr_tables(void)
{
    for (int i = 0; i < SUBSCR_TABLE_SIZE; i++)
    {
        key_c_push_subscr_table[i] = NULL;
    }
}

static int kbhit(void)
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

static int getch(void)
{
    return getchar(); // nie trzeba już modyfikować terminala w każdej iteracji
}
