/**
 * @file observer.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2025-10-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "observer_public_types.h"
#include <stdint.h>

    /* =========================================================================
     * API for callbacks without argument
     * ========================================================================= */

    /**
     * @brief Register callback in the given subscription table.
     *
     * If the callback is already present, function returns CALLBACK_SUBSCR_OK
     * without adding a duplicate entry.
     *
     * @param subscription_table Pointer to array of observer_cb_t with subscription slots.
     * @param cb_2_register Callback to register.
     * @param subscription_table_size Number of slots in subscription_table (must be > 0).
     * @return CALLBACK_SUBSCR_OK on success or CALLBACK_TABLE_FULL_ERROR when table full.
     */
    subscr_status_e subscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Unregister callback from the given subscription table.
     *
     * If callback is found, subsequent entries are shifted left to keep table compact.
     *
     * @param subscription_table Pointer to array of observer_cb_t.
     * @param cb_2_register Callback to unregister.
     * @param subscription_table_size Number of slots in subscription_table.
     */
    void unsubscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Notify all registered callbacks (no argument).
     *
     * @param subscription_table Pointer to array of observer_cb_t.
     * @param subscription_table_size Number of slots in subscription_table.
     */
    void notify(observer_cb_t *subscription_table, uint8_t subscription_table_size);

    /* =========================================================================
     * API for callbacks with event_state_e argument
     * ========================================================================= */

    subscr_status_e subscribe_enter_exit(observer_cb_arg_t *subscription_table, observer_cb_arg_t cb_2_register, uint8_t subscription_table_size);
    void unsubscribe_enter_exit(observer_cb_arg_t *subscription_table, observer_cb_arg_t cb_2_register, uint8_t subscription_table_size);
    void notify_enter_exit(observer_cb_arg_t *subscription_table, uint8_t subscription_table_size, event_state_e state);

    /* =========================================================================
     * API for callbacks with uint8_t argument
     * ========================================================================= */

    subscr_status_e subscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_register, uint8_t subscription_table_size);
    void unsubscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_register, uint8_t subscription_table_size);
    void notify_u8(observer_cb_u8_arg_t *subscription_table, uint8_t subscription_table_size, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* OBSERVER_H_ */
