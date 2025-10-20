/**
 * @file observer.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2025-06-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "observer_public_types.h"
#include <stdint.h>

/** API dla callbacków bezargumentowych */
subscr_status_e subscribe(observer_cb_t *subscription_table,
                          observer_cb_t cb_2_register,
                          uint8_t subscription_table_size);
void unsubscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register,
                 uint8_t subscription_table_size);
void notify(observer_cb_t *subscription_table, uint8_t subscription_table_size);

/** API dla callbacków z argumentem `bool` */
subscr_status_e subscribe_with_arg(observer_cb_arg_t *subscription_table,
                                   observer_cb_arg_t cb_2_register,
                                   uint8_t subscription_table_size);
void unsubscribe_with_arg(observer_cb_arg_t *subscription_table,
                          observer_cb_arg_t cb_2_register,
                          uint8_t subscription_table_size);
void notify_with_arg(observer_cb_arg_t *subscription_table,
                     uint8_t subscription_table_size, event_state_e state);

/** API dla callbacków z argumentem uint8_t */
subscr_status_e subscribe_with_u8_arg(observer_cb_u8_arg_t *subscription_table,
                                      observer_cb_u8_arg_t cb_2_register,
                                      uint8_t subscription_table_size);
void unsubscribe_with_u8_arg(observer_cb_u8_arg_t *subscription_table,
                             observer_cb_u8_arg_t cb_2_register,
                             uint8_t subscription_table_size);
void notify_with_u8_arg(observer_cb_u8_arg_t *subscription_table,
                        uint8_t subscription_table_size, uint8_t data);

#ifdef __cplusplus
}
#endif
#endif /* _OBSERVER_H_ */
