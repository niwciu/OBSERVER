/**
 * @file observer_public_types.h
 * @brief Public type definitions for the Observer library.
 *
 * @details
 *   This header provides common type definitions, enumerations, and callback
 *   function pointer declarations used by the Observer library. It is designed
 *   for deterministic, safety-critical embedded applications conforming to
 *   MISRA C and ISO 26262 guidelines.
 *
 * @version 1.0.0
 * @date 2025-10-25
 * @author
 *   niwciu (niwciu@gmail.com)
 *
 * @copyright
 *   Copyright (c) 2025
 *
 * @defgroup observer Observer Library
 * @brief Deterministic observer pattern for embedded systems.
 * @{
 *
 * @safety
 *   This header defines types only; no runtime behavior is implemented.
 */

#ifndef OBSERVER_PUBLIC_TYPES_H_
#define OBSERVER_PUBLIC_TYPES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    /**
     * @brief Subscription operation status codes.
     *
     * @note
     *   - OBSERVER_OK == 0 (success)
     *   - OBSERVER_INVALID_ARGUMENT_ERROR indicates invalid input parameters.
     *   - OBSERVER_TABLE_FULL_ERROR indicates no free slots available.
     *   - OBSERVER_TABLE_EMPTY_ERROR indicates table has no valid entries.
     */
    typedef enum
    {
        OBSERVER_OK = 0u,
        OBSERVER_INVALID_ARGUMENT_ERROR = 1u,
        OBSERVER_TABLE_FULL_ERROR = 2u,
        OBSERVER_TABLE_EMPTY_ERROR = 3u
    } subscr_status_e;

    /**
     * @brief Event state passed to event_state_e callbacks.
     */
    typedef enum
    {
        EVENT_STATE_EXIT = 0u,
        EVENT_STATE_ENTER = 1u
    } event_state_e;

    /* =========================================================================
     * Callback type definitions
     * ========================================================================= */

    /**
     * @brief Callback without arguments.
     */
    typedef void (*observer_cb_t)(void);

    /**
     * @brief Callback taking event_state_e argument.
     */
    typedef void (*observer_cb_state_t)(event_state_e state);

    /**
     * @brief Callback taking uint8_t argument.
     */
    typedef void (*observer_cb_u8_arg_t)(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* OBSERVER_PUBLIC_TYPES_H_ */

/** @} */ /* end of observer group */
