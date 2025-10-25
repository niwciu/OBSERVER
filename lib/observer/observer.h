/**
 * @file observer.h
 * @author
 *   niwciu (niwciu@gmail.com)
 * @brief
 *   Observer pattern API for deterministic, safety-critical systems.
 *
 * @details
 *   This header defines a deterministic, static-memory implementation
 *   of the Observer design pattern suitable for safety-critical
 *   embedded software (MISRA C / ISO 26262 compliant).
 *
 *   **Features**
 *   - No dynamic memory allocation
 *   - Deterministic behavior: table-based subscription management
 *   - Support for callbacks with `void`, `uint8_t`, or `event_state_e` arguments
 *   - Single-point return style (Rule 15.5 – MISRA C)
 *   - Complete Doxygen documentation for automated safety review
 *
 * **Thread Safety**
 *   None of the API functions are reentrant or thread-safe.
 *   The caller must provide synchronization (e.g. mutex, critical
 *   section, or interrupt masking) if concurrent access is possible.
 *
 * @version 1.0.0
 * @date 2025-10-25
 * @copyright
 *   Copyright (c) 2025
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
     *  Callbacks without argument
     * ========================================================================= */

    /**
     * @brief Register a callback in the subscription table.
     *
     * @details
     *   Registers a callback function in the provided subscription table.
     *   If the callback is already present, no duplicate entry is added.
     *
     * @param[in,out] subscription_table Pointer to an array of observer_cb_t.
     * @param[in] cb_2_register Callback function to register.
     * @param[in] subscription_table_size Number of entries in the table (must > 0).
     *
     * @return OBSERVER_OK             Callback registered or already present.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_FULL_ERROR      No free slot available.
     *
     * @pre  `subscription_table` points to a valid array of given size.
     * @post On success, `cb_2_register` is stored in the table.
     * @safety Not reentrant; caller must ensure synchronization.
     */
    subscr_status_e subscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Unregister a callback from the subscription table.
     *
     * @details
     *   Removes a registered callback and compacts the table
     *   by shifting subsequent entries left.
     *
     * @param[in,out] subscription_table Pointer to an array of observer_cb_t.
     * @param[in] cb_2_register Callback function to remove.
     * @param[in] subscription_table_size Table length.
     *
     * @return OBSERVER_OK             Callback successfully removed.
     * @return OBSERVER_TABLE_EMPTY_ERROR       Callback not found.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     *
     * @pre  Valid table pointer of given size.
     * @post Table compacted after removal.
     * @safety Not reentrant; caller must ensure synchronization.
     */
    subscr_status_e unsubscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Notify all registered callbacks (no argument).
     *
     * @details
     *   Invokes all non-NULL callbacks in ascending index order.
     *
     * @param[in] subscription_table Pointer to an array of observer_cb_t.
     * @param[in] subscription_table_size Table length.
     *
     * @return OBSERVER_OK             At least one callback invoked.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_EMPTY_ERROR       No callbacks registered.
     *
     * @pre  Valid table pointer of given size.
     * @post All active callbacks are executed once.
     * @safety Not reentrant; caller must ensure synchronization.
     */
    subscr_status_e notify(observer_cb_t *subscription_table,
                           uint8_t subscription_table_size);

    /* =========================================================================
     *  Callbacks with event_state_e argument
     * ========================================================================= */

    /**
     * @brief Register a callback with event_state_e argument.
     *
     * @param[in,out] subscription_table Pointer to array of observer_cb_state_t.
     * @param[in] cb_2_register Callback to register.
     * @param[in] subscription_table_size Table length.
     *
     * @return OBSERVER_OK             Callback registered or already present.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_FULL_ERROR      No free slot.
     *
     * @pre  Valid table pointer of given size.
     * @post Callback stored on success.
     * @safety Not reentrant; caller must ensure synchronization.
     */
    subscr_status_e subscribe_state_change(observer_cb_state_t *subscription_table, observer_cb_state_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Unregister a callback with event_state_e argument.
     *
     * @param[in,out] subscription_table Pointer to array of observer_cb_state_t.
     * @param[in] cb_2_register Callback to remove.
     * @param[in] subscription_table_size Table length.
     *
     * @return OBSERVER_OK             Callback removed.
     * @return OBSERVER_TABLE_EMPTY_ERROR       Callback not found.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     *
     * @pre  Valid table pointer of given size.
     * @post Table compacted after removal.
     * @safety Not reentrant; caller must ensure synchronization.
     */
    subscr_status_e unsubscribe_state_change(observer_cb_state_t *subscription_table, observer_cb_state_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Notify all registered callbacks with event_state_e argument.
     *
     * @param[in] subscription_table Pointer to array of observer_cb_state_t.
     * @param[in] subscription_table_size Table length.
     * @param[in] state Event state passed to callbacks.
     *
     * @return OBSERVER_OK             At least one callback invoked.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_EMPTY_ERROR       No callbacks registered.
     *
     * @pre  Valid table pointer of given size.
     * @post All registered callbacks called with `state`.
     * @safety Not reentrant; caller must ensure synchronization.
     */
    subscr_status_e notify_state_change(observer_cb_state_t *subscription_table, uint8_t subscription_table_size, event_state_e state);

    /* =========================================================================
     *  Callbacks with uint8_t argument
     * ========================================================================= */

    /**
     * @brief Register a callback with uint8_t argument.
     *
     * @param[in,out] subscription_table Pointer to array of observer_cb_u8_arg_t.
     * @param[in] cb_2_register Callback to register.
     * @param[in] subscription_table_size Table length.
     *
     * @return OBSERVER_OK             Callback registered or already present.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_FULL_ERROR      No free slot.
     *
     * @pre  Valid table pointer of given size.
     * @post Callback stored on success.
     * @safety Not reentrant; caller must ensure synchronization.
     */
    subscr_status_e subscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Unregister a callback with uint8_t argument.
     *
     * @param[in,out] subscription_table Pointer to array of observer_cb_u8_arg_t.
     * @param[in] cb_2_register Callback to remove.
     * @param[in] subscription_table_size Table length.
     *
     * @return OBSERVER_OK             Callback removed.
     * @return OBSERVER_TABLE_EMPTY_ERROR       Callback not found.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     *
     * @pre  Valid table pointer of given size.
     * @post Table compacted after removal.
     * @safety Not reentrant; caller must ensure synchronization.
     */
    subscr_status_e unsubscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Notify all registered callbacks with uint8_t argument.
     *
     * @param[in] subscription_table Pointer to array of observer_cb_u8_arg_t.
     * @param[in] subscription_table_size Table length.
     * @param[in] data Data argument passed to each callback.
     *
     * @return OBSERVER_OK             At least one callback invoked.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_EMPTY_ERROR       No callbacks registered.
     *
     * @pre  Valid table pointer of given size.
     * @post All registered callbacks called with `data`.
     * @safety Not reentrant; caller must ensure synchronization.
     */
    subscr_status_e notify_u8(observer_cb_u8_arg_t *subscription_table, uint8_t subscription_table_size, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* OBSERVER_H_ */
