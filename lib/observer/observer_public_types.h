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
     *  - OBSERVER_OK == 0 (success)
     *  - OBSERVER_INVALID_ARGUMENT_ERROR indicates invalid input parameters (NULL pointers, zero size).
     *  - OBSERVER_TABLE_FULL_ERROR indicates there were no free slots in the subscription table.
     */
    typedef enum
    {
        OBSERVER_OK = 0u,
        OBSERVER_INVALID_ARGUMENT_ERROR = 1u,
        OBSERVER_TABLE_FULL_ERROR = 2u,
        OBSERVER_TABLE_EMPTY_ERROR = 3u
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
    typedef void (*observer_cb_state_t)(event_state_e state);

    /**
     * @brief Callback taking uint8_t argument.
     */
    typedef void (*observer_cb_u8_arg_t)(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* OBSERVER_PUBLIC_TYPES_H_ */
