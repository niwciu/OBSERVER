/**
 *
 */

#include "mock_fun.h"

uint8_t mock_fun_counter[MOCK_COUNTER_QTY];

void mock_fun_1(void)
{
    mock_fun_counter[0]++;
}
void mock_fun_2(void)
{
    mock_fun_counter[1]++;
}
void mock_fun_3(void)
{
    mock_fun_counter[2]++;
}
void mock_fun_4(void)
{
    mock_fun_counter[3]++;
}
void mock_fun_5(void)
{
    mock_fun_counter[4]++;
}
void mock_dirty_fun(void)
{
}

void mock_reset_mock_fun_counters(void)
{
    for (uint8_t i = 0; i < MOCK_COUNTER_QTY; i++)
    {
        mock_fun_counter[i] = 0;
    }
}