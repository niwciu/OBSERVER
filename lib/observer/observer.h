/* observer.h
 * Author: niwciu (niwciu@gmail.com)
 * Date: 2025-10-20 (updated)
 *
 * Observer pattern API (deterministic, safety-critical oriented).
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
     * Preconditions:
     *  - subscription_table must point to a buffer of subscription_table_size entries.
     *  - subscription_table_size must be > 0.
     *
     * Threading:
     *  - This API is NOT guaranteed to be reentrant or thread-safe.
     *    Caller must protect concurrent access (e.g., mutex or disabling interrupts)
     *    if subscribe/unsubscribe/notify may be called concurrently or from ISRs.
     *
     * @param subscription_table Pointer to array of observer_cb_t with subscription slots.
     * @param cb_2_register Callback to register.
     * @param subscription_table_size Number of slots in subscription_table (must be > 0).
     * @return CALLBACK_SUBSCR_OK on success,
     *         CALLBACK_ERROR_INVALID_ARGUMENT on NULL/invalid args,
     *         CALLBACK_ERROR_TABLE_FULL when table full.
     */
    subscr_status_e subscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Unregister callback from the given subscription table.
     *
     * If callback is found, subsequent entries are shifted left to keep table compact.
     * If callback not found, function returns without side effects.
     *
     * Preconditions:
     *  - subscription_table must point to a buffer of subscription_table_size entries.
     *
     * Threading:
     *  - Not thread-safe; caller must ensure synchronization if necessary.
     *
     * @param subscription_table Pointer to array of observer_cb_t.
     * @param cb_2_register Callback to unregister.
     * @param subscription_table_size Number of slots in subscription_table.
     */
    void unsubscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Notify all registered callbacks (no argument).
     *
     * Callbacks are invoked in table order (index increasing).
     * If a callback pointer is NULL it is skipped.
     *
     * Preconditions:
     *  - subscription_table must point to a buffer of subscription_table_size entries.
     *
     * Threading:
     *  - Not thread-safe; invoking notify concurrently with subscribe/unsubscribe
     *    may lead to undefined observer ordering or missed callbacks.
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
