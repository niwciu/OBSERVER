/**
 * @file observer_public_types.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2025-10-20
 *
 * @copyright Copyright (c) 2025
 *
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
     */
    typedef enum
    {
        CALLBACK_SUBSCR_OK = 0u,
        CALLBACK_TABLE_FULL_ERROR = 1u,
        CALLBACK_TABLE_IDX_TO_HIGH = 2u
    } subscr_status_e;

    /**
     * @brief Event state passed to state callbacks.
     */
    typedef enum
    {
        EVENT_STATE_EXIT = 0u,
        EVENT_STATE_ENTER = 1u
    } event_state_e;

    /* Callback types */

    /**
     * @brief Callback without arguments.
     */
    typedef void (*observer_cb_t)(void);

    /**
     * @brief Callback taking event_state_e argument.
     */
    typedef void (*observer_cb_arg_t)(event_state_e state);

    /**
     * @brief Callback taking uint8_t argument.
     */
    typedef void (*observer_cb_u8_arg_t)(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* OBSERVER_PUBLIC_TYPES_H_ */
