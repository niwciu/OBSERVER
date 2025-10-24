/* observer_public_types.h
 * Author: niwciu (niwciu@gmail.com)
 * Date: 2025-10-20 (updated)
 *
 * Public types for observer module.
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
     * Note:
     *  - CALLBACK_SUBSCR_OK == 0 (success)
     *  - CALLBACK_ERROR_INVALID_ARGUMENT indicates invalid input parameters (NULL pointers, zero size).
     *  - CALLBACK_ERROR_TABLE_FULL indicates there were no free slots in the subscription table.
     */
    typedef enum
    {
        CALLBACK_SUBSCR_OK = 0u,
        CALLBACK_ERROR_INVALID_ARGUMENT = 1u,
        CALLBACK_ERROR_TABLE_FULL = 2u
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
