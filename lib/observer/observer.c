/**
 * @file observer.c
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2025-06-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "observer.h"
#include <stdio.h>
subscr_status_e subscribe(observer_cb_t *subscription_table,
                          observer_cb_t cb_2_register,
                          uint8_t subscription_table_size) {
  return subscribe_with_arg((observer_cb_arg_t *)subscription_table,
                            (observer_cb_arg_t)cb_2_register,
                            subscription_table_size);
}

void unsubscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register,
                 uint8_t subscription_table_size) {
  unsubscribe_with_arg((observer_cb_arg_t *)subscription_table,
                       (observer_cb_arg_t)cb_2_register,
                       subscription_table_size);
}

void notify(observer_cb_t *subscription_table,
            uint8_t subscription_table_size) {
  for (uint8_t i = 0; i < subscription_table_size; i++) {
    if (subscription_table[i])
      subscription_table[i]();
  }
}

subscr_status_e subscribe_with_arg(observer_cb_arg_t *subscription_table,
                                   observer_cb_arg_t cb_2_register,
                                   uint8_t subscription_table_size) {
  for (uint8_t i = 0; i < subscription_table_size; i++) {
    if (subscription_table[i] == cb_2_register)
      return CALLBACK_SUBSCR_OK;

    if (subscription_table[i] == NULL) {
      subscription_table[i] = cb_2_register;
      return CALLBACK_SUBSCR_OK;
    }
  }
  return CALLBACK_TABLE_FULL_ERROR;
}

void unsubscribe_with_arg(observer_cb_arg_t *subscription_table,
                          observer_cb_arg_t cb_2_register,
                          uint8_t subscription_table_size) {
  for (uint8_t i = 0; i < subscription_table_size; i++) {
    if (subscription_table[i] == cb_2_register) {
      for (uint8_t j = i; j < subscription_table_size - 1; j++) {
        subscription_table[j] = subscription_table[j + 1];
      }
      subscription_table[subscription_table_size - 1] = NULL;
      break;
    }
  }
}

void notify_with_arg(observer_cb_arg_t *subscription_table,
                     uint8_t subscription_table_size, event_state_e state) {
  for (uint8_t i = 0; i < subscription_table_size; i++) {
    if (subscription_table[i])
      subscription_table[i](state);
  }
}

/** API dla callbacków z argumentem uint8_t */
subscr_status_e subscribe_with_u8_arg(observer_cb_u8_arg_t *subscription_table,
                                      observer_cb_u8_arg_t cb_2_register,
                                      uint8_t subscription_table_size) {
  for (uint8_t i = 0; i < subscription_table_size; i++) {
    if (subscription_table[i] == cb_2_register)
      return CALLBACK_SUBSCR_OK;

    if (subscription_table[i] == NULL) {
      subscription_table[i] = cb_2_register;
      return CALLBACK_SUBSCR_OK;
    }
  }
  return CALLBACK_TABLE_FULL_ERROR;
}

void unsubscribe_with_u8_arg(observer_cb_u8_arg_t *subscription_table,
                             observer_cb_u8_arg_t cb_2_register,
                             uint8_t subscription_table_size) {
  for (uint8_t i = 0; i < subscription_table_size; i++) {
    if (subscription_table[i] == cb_2_register) {
      for (uint8_t j = i; j < subscription_table_size - 1; j++) {
        subscription_table[j] = subscription_table[j + 1];
      }
      subscription_table[subscription_table_size - 1] = NULL;
      break;
    }
  }
}

void notify_with_u8_arg(observer_cb_u8_arg_t *subscription_table,
                        uint8_t subscription_table_size, uint8_t data) {
  for (uint8_t i = 0; i < subscription_table_size; i++) {
    if (subscription_table[i])
      subscription_table[i](data);
  }
}
