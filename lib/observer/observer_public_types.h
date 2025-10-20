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

#ifndef _OBSERVER_PUBLIC_TYPES_H_
#define _OBSERVER_PUBLIC_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
typedef enum {
  CALLBACK_SUBSCR_OK,
  CALLBACK_TABLE_FULL_ERROR,
  CALLBACK_TABLE_IDX_TO_HIGH,
} subscr_status_e;

typedef enum { EVENT_STATE_EXIT = 0, EVENT_STATE_ENTER = 1 } event_state_e;

typedef void (*observer_cb_t)(void);
typedef void (*observer_cb_arg_t)(event_state_e state);
typedef void (*observer_cb_u8_arg_t)(uint8_t data);

#ifdef __cplusplus
}
#endif
#endif /* _OBSERVER_PUBLIC_TYPES_H_ */
