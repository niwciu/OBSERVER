/**
 * @file observer.h
 * @author niwciu (niwciu@gmail.com)
 * @brief Observer pattern API for deterministic, safety-critical systems.
 * 
 * @details
 * This header provides a deterministic, static memory implementation of
 * the Observer design pattern suitable for safety-critical embedded software.
 * 
 * Features:
 *  - No dynamic memory allocation.
 *  - Deterministic behavior: table-based subscription management.
 *  - Support for callbacks with void, uint8_t, or event_state_e arguments.
 *  - Single-point return style in unsubscribe functions for MISRA C / ISO 26262 compliance.
 *  - Full Doxygen documentation for automated generation and safety review.
 * 
 * Thread Safety:
 *  - None of the API functions are reentrant or thread-safe.
 *  - Caller must provide synchronization (mutex, critical section, or interrupt disabling)
 *    if concurrent access from multiple tasks or ISRs is possible.
 * 
 * Version: 1.0.0
 * Date: 2025-10-25
 * 
 * @copyright Copyright (c) 2025
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
 * @brief Register a callback in the subscription table.
 *
 * @details
 * This function registers a callback function in the provided subscription table.
 * If the callback is already present, it will not be added again, and
 * CALLBACK_SUBSCR_OK will be returned.
 *
 * @param[in,out] subscription_table Pointer to an array of observer_cb_t with subscription slots.
 * @param[in] cb_2_register Callback function to register.
 * @param[in] subscription_table_size Number of slots in subscription_table (must be > 0).
 *
 * @return CALLBACK_SUBSCR_OK if callback successfully registered or already present.
 * @return CALLBACK_ERROR_INVALID_ARGUMENT if subscription_table is NULL, cb_2_register is NULL, or subscription_table_size == 0.
 * @return CALLBACK_ERROR_TABLE_FULL if no free slot is available in the table.
 *
 * @pre subscription_table points to a valid array of size subscription_table_size.
 * @post If successful, cb_2_register is stored in subscription_table.
 * @safety Not reentrant or thread-safe. Caller must ensure synchronization if used concurrently.
 */
subscr_status_e subscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size);

/**
 * @brief Unregister a callback from the subscription table.
 *
 * @details
 * Removes a previously registered callback from the subscription table.
 * The table is compacted by shifting subsequent entries left.
 *
 * @param[in,out] subscription_table Pointer to an array of observer_cb_t.
 * @param[in] cb_2_register Callback function to unregister.
 * @param[in] subscription_table_size Number of slots in subscription_table.
 *
 * @return CALLBACK_SUBSCR_OK if callback successfully removed.
 * @return CALLBACK_ERROR_NOT_FOUND if callback was not found in the table.
 * @return CALLBACK_ERROR_INVALID_ARGUMENT if subscription_table is NULL, cb_2_register is NULL, or subscription_table_size == 0.
 *
 * @pre subscription_table points to a valid array of size subscription_table_size.
 * @post If successful, cb_2_register is removed and table is compacted.
 * @safety Not reentrant or thread-safe. Caller must ensure synchronization if used concurrently.
 */
subscr_status_e unsubscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size);

/**
 * @brief Notify all registered callbacks (no argument).
 *
 * @details
 * Calls all non-NULL callback pointers in the subscription table in index order.
 *
 * @param[in] subscription_table Pointer to an array of observer_cb_t.
 * @param[in] subscription_table_size Number of slots in subscription_table.
 *
 * @pre subscription_table points to a valid array of size subscription_table_size.
 * @post All registered callbacks are invoked.
 * @safety Not reentrant or thread-safe. Concurrent subscribe/unsubscribe may cause missed callbacks.
 */
void notify(observer_cb_t *subscription_table, uint8_t subscription_table_size);

/* =========================================================================
 * API for callbacks with event_state_e argument
 * ========================================================================= */

/**
 * @brief Register a callback with event_state_e argument.
 *
 * @param[in,out] subscription_table Pointer to an array of observer_cb_state_t.
 * @param[in] cb_2_register Callback function to register.
 * @param[in] subscription_table_size Number of slots in subscription_table (must be > 0).
 *
 * @return CALLBACK_SUBSCR_OK if callback successfully registered or already present.
 * @return CALLBACK_ERROR_INVALID_ARGUMENT if subscription_table is NULL, cb_2_register is NULL, or subscription_table_size == 0.
 * @return CALLBACK_ERROR_TABLE_FULL if no free slot is available in the table.
 *
 * @pre subscription_table points to a valid array of size subscription_table_size.
 * @post If successful, cb_2_register is stored in subscription_table.
 * @safety Not reentrant or thread-safe. Caller must ensure synchronization if used concurrently.
 */
subscr_status_e subscribe_state_change(observer_cb_state_t *subscription_table, observer_cb_state_t cb_2_register, uint8_t subscription_table_size);

/**
 * @brief Unregister a callback with event_state_e argument.
 *
 * @param[in,out] subscription_table Pointer to an array of observer_cb_arg_t.
 * @param[in] cb_2_register Callback function to unregister.
 * @param[in] subscription_table_size Number of slots in subscription_table.
 *
 * @return CALLBACK_SUBSCR_OK if callback successfully removed.
 * @return CALLBACK_ERROR_NOT_FOUND if callback was not found in the table.
 * @return CALLBACK_ERROR_INVALID_ARGUMENT if subscription_table is NULL, cb_2_register is NULL, or subscription_table_size == 0.
 *
 * @pre subscription_table points to a valid array of size subscription_table_size.
 * @post If successful, cb_2_register is removed and table is compacted.
 * @safety Not reentrant or thread-safe. Caller must ensure synchronization if used concurrently.
 */
subscr_status_e unsubscribe_state_change(observer_cb_state_t *subscription_table, observer_cb_state_t cb_2_register, uint8_t subscription_table_size);

/**
 * @brief Notify all registered callbacks with event_state_e argument.
 *
 * @param[in] subscription_table Pointer to an array of observer_cb_arg_t.
 * @param[in] subscription_table_size Number of slots in subscription_table.
 * @param[in] state Event state passed to callbacks.
 *
 * @pre subscription_table points to a valid array of size subscription_table_size.
 * @post All registered callbacks are invoked with state argument.
 * @safety Not reentrant or thread-safe. Concurrent subscribe/unsubscribe may cause missed callbacks.
 */
void notify_enter_exit(observer_cb_state_t *subscription_table, uint8_t subscription_table_size, event_state_e state);

/* =========================================================================
 * API for callbacks with uint8_t argument
 * ========================================================================= */

/**
 * @brief Register a callback with uint8_t argument.
 *
 * @param[in,out] subscription_table Pointer to an array of observer_cb_u8_arg_t.
 * @param[in] cb_2_register Callback function to register.
 * @param[in] subscription_table_size Number of slots in subscription_table (must be > 0).
 *
 * @return CALLBACK_SUBSCR_OK if callback successfully registered or already present.
 * @return CALLBACK_ERROR_INVALID_ARGUMENT if subscription_table is NULL, cb_2_register is NULL, or subscription_table_size == 0.
 * @return CALLBACK_ERROR_TABLE_FULL if no free slot is available in the table.
 *
 * @pre subscription_table points to a valid array of size subscription_table_size.
 * @post If successful, cb_2_register is stored in subscription_table.
 * @safety Not reentrant or thread-safe. Caller must ensure synchronization if used concurrently.
 */
subscr_status_e subscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_register, uint8_t subscription_table_size);

/**
 * @brief Unregister a callback with uint8_t argument.
 *
 * @param[in,out] subscription_table Pointer to an array of observer_cb_u8_arg_t.
 * @param[in] cb_2_register Callback function to unregister.
 * @param[in] subscription_table_size Number of slots in subscription_table.
 *
 * @return CALLBACK_SUBSCR_OK if callback successfully removed.
 * @return CALLBACK_ERROR_NOT_FOUND if callback was not found in the table.
 * @return CALLBACK_ERROR_INVALID_ARGUMENT if subscription_table is NULL, cb_2_register is NULL, or subscription_table_size == 0.
 *
 * @pre subscription_table points to a valid array of size subscription_table_size.
 * @post If successful, cb_2_register is removed and table is compacted.
 * @safety Not reentrant or thread-safe. Caller must ensure synchronization if used concurrently.
 */
subscr_status_e unsubscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_register, uint8_t subscription_table_size);

/**
 * @brief Notify all registered callbacks with uint8_t argument.
 *
 * @param[in] subscription_table Pointer to an array of observer_cb_u8_arg_t.
 * @param[in] subscription_table_size Number of slots in subscription_table.
 * @param[in] data Data argument passed to callbacks.
 *
 * @pre subscription_table points to a valid array of size subscription_table_size.
 * @post All registered callbacks are invoked with data argument.
 * @safety Not reentrant or thread-safe. Concurrent subscribe/unsubscribe may cause missed callbacks.
 */
void notify_u8(observer_cb_u8_arg_t *subscription_table, uint8_t subscription_table_size, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* OBSERVER_H_ */
