/**
 * @file observer.c
 * @author niwciu
 * @date 2025-10-25
 * @brief Observer pattern implementation (deterministic, safety-critical oriented)
 *
 * @details
 * This source file implements a deterministic, static memory Observer pattern.
 * All API functions validate input parameters and return clear error codes.
 * 
 * Features:
 *  - No dynamic memory allocation.
 *  - Deterministic table-based subscription management.
 *  - Supports callbacks with void, uint8_t, or event_state_e arguments.
 *  - Single-point return style in unsubscribe functions for MISRA C / ISO 26262 compliance.
 *
 * Thread Safety:
 *  - API functions are NOT reentrant or thread-safe.
 *  - Caller must provide synchronization if concurrent access from multiple tasks/ISRs is possible.
 */

#include "observer.h"
#include "observer_public_types.h"
#include <stddef.h>
#include <stdint.h>

/* =========================================================================
 * CALLBACKS WITHOUT ARGUMENT (void)
 * ========================================================================= */

subscr_status_e subscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size)
{
    subscr_status_e status = OBSERVER_INVALID_ARGUMENT_ERROR;

    if ((subscription_table != NULL) && (cb_2_register != NULL) && (subscription_table_size != 0u))
    {
        uint8_t i;
        uint8_t free_index = subscription_table_size; /* invalid by default */
        status = OBSERVER_TABLE_FULL_ERROR;

        for (i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] == cb_2_register)
            {
                status = OBSERVER_OK; /* already registered */
                break;
            }

            if ((subscription_table[i] == NULL) && (free_index == subscription_table_size))
            {
                free_index = i; /* first free slot */
            }
        }

        if ((status != OBSERVER_OK) && (free_index < subscription_table_size))
        {
            subscription_table[free_index] = cb_2_register;
            status = OBSERVER_OK;
        }
    }

    return status;
}

subscr_status_e unsubscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size)
{
    subscr_status_e status = OBSERVER_INVALID_ARGUMENT_ERROR;
    uint8_t i, j;
    uint8_t found = 0u;

    if ((subscription_table != NULL) && (cb_2_register != NULL) && (subscription_table_size != 0u))
    {
        status = OBSERVER_TABLE_EMPTY_ERROR;

        for (i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] == cb_2_register)
            {
                found = 1u;
                for (j = i; j < (uint8_t)(subscription_table_size - 1u); ++j)
                {
                    subscription_table[j] = subscription_table[j + 1u];
                }
                subscription_table[subscription_table_size - 1u] = NULL;
                status = OBSERVER_OK;
                break;
            }
        }
    }

    return status;
}

subscr_status_e notify(observer_cb_t *subscription_table, uint8_t subscription_table_size)
{
    subscr_status_e status = OBSERVER_INVALID_ARGUMENT_ERROR;

    if ((subscription_table != NULL) && (subscription_table_size != 0u))
    {
        status = OBSERVER_TABLE_EMPTY_ERROR;

        for (uint8_t i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] != NULL)
            {
                subscription_table[i]();
                status = OBSERVER_OK;
            }
        }
    }

    return status;
}

/* =========================================================================
 * CALLBACKS WITH event_state_e ARGUMENT
 * ========================================================================= */

subscr_status_e subscribe_state_change(observer_cb_state_t *subscription_table, observer_cb_state_t cb_2_register, uint8_t subscription_table_size)
{
    subscr_status_e status = OBSERVER_INVALID_ARGUMENT_ERROR;

    if ((subscription_table != NULL) && (cb_2_register != NULL) && (subscription_table_size != 0u))
    {
        uint8_t free_index = subscription_table_size;
        uint8_t i;
        status = OBSERVER_TABLE_FULL_ERROR;

        for (i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] == cb_2_register)
            {
                status = OBSERVER_OK;
                break;
            }

            if ((subscription_table[i] == NULL) && (free_index == subscription_table_size))
            {
                free_index = i;
            }
        }

        if ((status != OBSERVER_OK) && (free_index < subscription_table_size))
        {
            subscription_table[free_index] = cb_2_register;
            status = OBSERVER_OK;
        }
    }

    return status;
}


subscr_status_e unsubscribe_state_change(observer_cb_state_t *subscription_table, observer_cb_state_t cb_2_register, uint8_t subscription_table_size)
{
    subscr_status_e status = OBSERVER_INVALID_ARGUMENT_ERROR;
    uint8_t i, j;
    uint8_t found = 0u;

    if ((subscription_table != NULL) && (cb_2_register != NULL) && (subscription_table_size != 0u))
    {
        status = OBSERVER_TABLE_EMPTY_ERROR;

        for (i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] == cb_2_register)
            {
                found = 1u;
                for (j = i; j < (uint8_t)(subscription_table_size - 1u); ++j)
                {
                    subscription_table[j] = subscription_table[j + 1u];
                }
                subscription_table[subscription_table_size - 1u] = NULL;
                status = OBSERVER_OK;
                break;
            }
        }
    }

    return status;
}

subscr_status_e notify_enter_exit(observer_cb_state_t *subscription_table, uint8_t subscription_table_size, event_state_e state)
{
    subscr_status_e status = OBSERVER_INVALID_ARGUMENT_ERROR;

    if ((subscription_table != NULL) && (subscription_table_size != 0u))
    {
        status = OBSERVER_TABLE_EMPTY_ERROR;

        for (uint8_t i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] != NULL)
            {
                subscription_table[i](state);
                status = OBSERVER_OK;
            }
        }
    }

    return status;
}

/* =========================================================================
 * CALLBACKS WITH UINT8 ARGUMENT
 * ========================================================================= */

subscr_status_e subscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_register, uint8_t subscription_table_size)
{
    subscr_status_e status = OBSERVER_INVALID_ARGUMENT_ERROR;

    if ((subscription_table != NULL) && (cb_2_register != NULL) && (subscription_table_size != 0u))
    {
        uint8_t i;
        uint8_t free_index = subscription_table_size;
        status = OBSERVER_TABLE_FULL_ERROR;

        for (i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] == cb_2_register)
            {
                status = OBSERVER_OK;
                break;
            }

            if ((subscription_table[i] == NULL) && (free_index == subscription_table_size))
            {
                free_index = i;
            }
        }

        if ((status != OBSERVER_OK) && (free_index < subscription_table_size))
        {
            subscription_table[free_index] = cb_2_register;
            status = OBSERVER_OK;
        }
    }

    return status;
}

subscr_status_e unsubscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_register, uint8_t subscription_table_size)
{
    subscr_status_e status = OBSERVER_INVALID_ARGUMENT_ERROR;
    uint8_t i, j;
    uint8_t found = 0u;

    if ((subscription_table != NULL) && (cb_2_register != NULL) && (subscription_table_size != 0u))
    {
        status = OBSERVER_TABLE_EMPTY_ERROR;

        for (i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] == cb_2_register)
            {
                found = 1u;
                for (j = i; j < (uint8_t)(subscription_table_size - 1u); ++j)
                {
                    subscription_table[j] = subscription_table[j + 1u];
                }
                subscription_table[subscription_table_size - 1u] = NULL;
                status = OBSERVER_OK;
                break;
            }
        }
    }

    return status;
}

subscr_status_e notify_u8(observer_cb_u8_arg_t *subscription_table, uint8_t subscription_table_size, uint8_t data)
{
    subscr_status_e status = OBSERVER_INVALID_ARGUMENT_ERROR;

    if ((subscription_table != NULL) && (subscription_table_size != 0u))
    {
        status = OBSERVER_TABLE_EMPTY_ERROR;

        for (uint8_t i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] != NULL)
            {
                subscription_table[i](data);
                status = OBSERVER_OK;
            }
        }
    }

    return status;
}

