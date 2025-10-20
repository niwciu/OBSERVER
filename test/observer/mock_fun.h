

#pragma once

#include <stdint.h>
#define MOCK_COUNTER_QTY 5

extern uint8_t mock_fun_counter[MOCK_COUNTER_QTY];

void mock_fun_1(void);
void mock_fun_2(void);
void mock_fun_3(void);
void mock_fun_4(void);
void mock_fun_5(void);
void mock_dirty_fun(void);
void mock_reset_mock_fun_counters(void);
