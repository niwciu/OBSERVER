/**
 * @file mock_pushbutton.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2025-10-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "observer.h"

void init_mock_pushbutton(void);
void subscribe_C_push_event(observer_cb_t callback);
void update_mock_pushbutton(void);