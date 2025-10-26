/**
 * @file observer.h
 * @brief Public API for the deterministic Observer library.
 *
 * @details
 *   Provides declarations for a static-memory, deterministic implementation
 *   of the Observer design pattern for safety-critical embedded systems.
 *   Designed in compliance with MISRA C and ISO 26262 software safety
 *   requirements.
 *
 * @features
 *   - No dynamic memory allocation.
 *   - Deterministic table-based subscription management.
 *   - Supports callback variants: `void`, `uint8_t`, and `event_state_e`.
 *   - Single-point return style (MISRA C Rule 15.5).
 *   - Complete Doxygen documentation for automated traceability.
 *
 * @thread_safety
 *   None of the API functions are reentrant or thread-safe.
 *   Caller must ensure synchronization (e.g., mutex, critical section, or interrupt masking)
 *   if concurrent access is possible.
 *
 * @version 1.0.0
 * @date 2025-10-25
 * @ingroup observer
 * @author
 *   niwciu (niwciu@gmail.com)
 *
 * @copyright
 *   Copyright (c) 2025
 *
 * @safety
 *   Deterministic, static allocation only.
 *   All pointer arguments validated before use.
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
     * @brief Register a callback in the subscription table (void callbacks).
     *
     * @details
     *   Registers a callback function in the provided subscription table.
     *   If the callback is already present, it is not added again.
     *
     * @param[in,out] subscription_table Pointer to an array of observer_cb_t.
     * @param[in] cb_2_register Callback function to register.
     * @param[in] subscription_table_size Number of entries in the table (must be > 0).
     *
     * @return OBSERVER_OK                    Callback registered or already present.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_FULL_ERROR       No free slot available.
     *
     * @pre  `subscription_table` points to a valid array of given size.
     * @post On success, `cb_2_register` is stored in the table.
     * @safety Not reentrant; caller must ensure synchronization.
     * @traceability OBSR-FUNC-001
     */
    subscr_status_e subscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Unregister a callback from the subscription table (void callbacks).
     *
     * @details
     *   Removes a registered callback and compacts the table
     *   by shifting subsequent entries left.
     *
     * @param[in,out] subscription_table Pointer to an array of observer_cb_t.
     * @param[in] cb_2_register Callback function to remove.
     * @param[in] subscription_table_size Table length.
     *
     * @return OBSERVER_OK                    Callback successfully removed.
     * @return OBSERVER_TABLE_EMPTY_ERROR      Callback not found.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     *
     * @pre  Valid table pointer of given size.
     * @post Table compacted after removal.
     * @safety Not reentrant; caller must ensure synchronization.
     * @traceability OBSR-FUNC-002
     */
    subscr_status_e unsubscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_remove, uint8_t subscription_table_size);

    /**
     * @brief Notify all registered callbacks (no argument).
     *
     * @details
     *   Invokes all non-NULL callbacks in ascending index order.
     *
     * @param[in] subscription_table Pointer to an array of observer_cb_t.
     * @param[in] subscription_table_size Table length.
     *
     * @return OBSERVER_OK                    At least one callback invoked.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_EMPTY_ERROR      No callbacks registered.
     *
     * @pre  Valid table pointer of given size.
     * @post All active callbacks are executed once.
     * @safety Not reentrant; caller must ensure synchronization.
     * @traceability OBSR-FUNC-003
     */
    subscr_status_e notify(observer_cb_t *subscription_table, uint8_t subscription_table_size);

    /* =========================================================================
     *  Callbacks with event_state_e argument
     * ========================================================================= */

    /**
     * @brief Register a callback with event_state_e argument.
     *
     * @details
     *   Registers a state-change callback in the given subscription table.
     *   Prevents duplicate registrations.
     *
     * @param[in,out] subscription_table Pointer to array of observer_cb_state_t.
     * @param[in] cb_2_register Callback function to register.
     * @param[in] subscription_table_size Table length (must be > 0).
     *
     * @return OBSERVER_OK                    Callback registered or already present.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_FULL_ERROR       No free slot available.
     *
     * @pre  Valid table pointer of given size.
     * @post Callback stored on success.
     * @safety Not reentrant; caller must ensure synchronization.
     * @traceability OBSR-FUNC-004
     */
    subscr_status_e subscribe_state_change(observer_cb_state_t *subscription_table, observer_cb_state_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Unregister a callback with event_state_e argument.
     *
     * @details
     *   Removes a previously registered callback from the table and compacts it.
     *
     * @param[in,out] subscription_table Pointer to array of observer_cb_state_t.
     * @param[in] cb_2_register Callback function to remove.
     * @param[in] subscription_table_size Table length.
     *
     * @return OBSERVER_OK                    Callback removed.
     * @return OBSERVER_TABLE_EMPTY_ERROR      Callback not found.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     *
     * @pre  Valid table pointer of given size.
     * @post Table compacted after removal.
     * @safety Not reentrant; caller must ensure synchronization.
     * @traceability OBSR-FUNC-005
     */
    subscr_status_e unsubscribe_state_change(observer_cb_state_t *subscription_table, observer_cb_state_t cb_2_remove, uint8_t subscription_table_size);

    /**
     * @brief Notify all registered callbacks with event_state_e argument.
     *
     * @details
     *   Calls all valid (non-NULL) callbacks, passing the given event state.
     *
     * @param[in] subscription_table Pointer to array of observer_cb_state_t.
     * @param[in] subscription_table_size Table length.
     * @param[in] state Event state passed to callbacks.
     *
     * @return OBSERVER_OK                    At least one callback invoked.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_EMPTY_ERROR      No callbacks registered.
     *
     * @pre  Valid table pointer of given size.
     * @post All registered callbacks called with `state`.
     * @safety Not reentrant; caller must ensure synchronization.
     * @traceability OBSR-FUNC-006
     */
    subscr_status_e notify_state_change(observer_cb_state_t *subscription_table, uint8_t subscription_table_size, event_state_e state);

    /* =========================================================================
     *  Callbacks with uint8_t argument
     * ========================================================================= */

    /**
     * @brief Register a callback with uint8_t argument.
     *
     * @details
     *   Registers a callback in the given table if not already present.
     *
     * @param[in,out] subscription_table Pointer to array of observer_cb_u8_arg_t.
     * @param[in] cb_2_register Callback to register.
     * @param[in] subscription_table_size Table length (must be > 0).
     *
     * @return OBSERVER_OK                    Callback registered or already present.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_FULL_ERROR       No free slot.
     *
     * @pre  Valid table pointer of given size.
     * @post Callback stored on success.
     * @safety Not reentrant; caller must ensure synchronization.
     * @traceability OBSR-FUNC-007
     */
    subscr_status_e subscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_register, uint8_t subscription_table_size);

    /**
     * @brief Unregister a callback with uint8_t argument.
     *
     * @details
     *   Removes a callback from the table and shifts subsequent entries left.
     *
     * @param[in,out] subscription_table Pointer to array of observer_cb_u8_arg_t.
     * @param[in] cb_2_register Callback to remove.
     * @param[in] subscription_table_size Table length.
     *
     * @return OBSERVER_OK                    Callback removed.
     * @return OBSERVER_TABLE_EMPTY_ERROR      Callback not found.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     *
     * @pre  Valid table pointer of given size.
     * @post Table compacted after removal.
     * @safety Not reentrant; caller must ensure synchronization.
     * @traceability OBSR-FUNC-008
     */
    subscr_status_e unsubscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_remove, uint8_t subscription_table_size);

    /**
     * @brief Notify all registered callbacks with uint8_t argument.
     *
     * @details
     *   Invokes all registered callbacks, passing a uint8_t data value.
     *
     * @param[in] subscription_table Pointer to array of observer_cb_u8_arg_t.
     * @param[in] subscription_table_size Table length.
     * @param[in] data Data argument passed to each callback.
     *
     * @return OBSERVER_OK                    At least one callback invoked.
     * @return OBSERVER_INVALID_ARGUMENT_ERROR Null pointer or zero size.
     * @return OBSERVER_TABLE_EMPTY_ERROR      No callbacks registered.
     *
     * @pre  Valid table pointer of given size.
     * @post All registered callbacks called with `data`.
     * @safety Not reentrant; caller must ensure synchronization.
     * @traceability OBSR-FUNC-009
     */
    subscr_status_e notify_u8(observer_cb_u8_arg_t *subscription_table, uint8_t subscription_table_size, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* OBSERVER_H_ */

/** @} */ /* end of observer group */
