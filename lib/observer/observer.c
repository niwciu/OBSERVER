/**
 * @file observer.c
 * @author niwciu
 * @date 2025-10-20
 * @brief Observer pattern implementation (deterministic, safety-critical oriented)
 *
 * Implementation notes:
 *  - No dynamic memory allocation.
 *  - Minimal and deterministic control flow.
 *  - All functions validate input parameters and return clear error codes when applicable.
 *  - API functions are not inherently reentrant or thread-safe — caller must provide synchronization
 *    if concurrent access from multiple tasks/ISRs is possible.
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
    subscr_status_e status = CALLBACK_ERROR_INVALID_ARGUMENT;
    uint8_t i;
    uint8_t free_index = subscription_table_size; /* invalid by default */

    if ((subscription_table != NULL) && (cb_2_register != NULL) && (subscription_table_size != 0u))
    {
        status = CALLBACK_ERROR_TABLE_FULL;

        for (i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] == cb_2_register)
            {
                status = CALLBACK_SUBSCR_OK; /* already registered */
                break;
            }

            if ((subscription_table[i] == NULL) && (free_index == subscription_table_size))
            {
                free_index = i; /* first free slot */
            }
        }

        if ((status != CALLBACK_SUBSCR_OK) && (free_index < subscription_table_size))
        {
            subscription_table[free_index] = cb_2_register;
            status = CALLBACK_SUBSCR_OK;
        }
    }

    return status;
}

void unsubscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size)
{
    uint8_t i, j;

    if ((subscription_table == NULL) || (cb_2_register == NULL) || (subscription_table_size == 0u))
    {
        return;
    }

    for (i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] == cb_2_register)
        {
            for (j = i; j < (uint8_t)(subscription_table_size - 1u); ++j)
            {
                subscription_table[j] = subscription_table[j + 1u];
            }
            subscription_table[subscription_table_size - 1u] = NULL;
            break;
        }
    }
}

void notify(observer_cb_t *subscription_table, uint8_t subscription_table_size)
{
    uint8_t i;

    if ((subscription_table == NULL) || (subscription_table_size == 0u))
    {
        return;
    }

    for (i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] != NULL)
        {
            subscription_table[i]();
        }
    }
}

/* =========================================================================
 * CALLBACKS WITH event_state_e ARGUMENT
 * ========================================================================= */

subscr_status_e subscribe_enter_exit(observer_cb_arg_t *subscription_table, observer_cb_arg_t cb_2_register, uint8_t subscription_table_size)
{
    subscr_status_e status = CALLBACK_ERROR_INVALID_ARGUMENT;
    uint8_t i;
    uint8_t free_index = subscription_table_size;

    if ((subscription_table != NULL) && (cb_2_register != NULL) && (subscription_table_size != 0u))
    {
        status = CALLBACK_ERROR_TABLE_FULL;

        for (i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] == cb_2_register)
            {
                status = CALLBACK_SUBSCR_OK;
                break;
            }

            if ((subscription_table[i] == NULL) && (free_index == subscription_table_size))
            {
                free_index = i;
            }
        }

        if ((status != CALLBACK_SUBSCR_OK) && (free_index < subscription_table_size))
        {
            subscription_table[free_index] = cb_2_register;
            status = CALLBACK_SUBSCR_OK;
        }
    }

    return status;
}

void unsubscribe_enter_exit(observer_cb_arg_t *subscription_table, observer_cb_arg_t cb_2_register, uint8_t subscription_table_size)
{
    uint8_t i, j;

    if ((subscription_table == NULL) || (cb_2_register == NULL) || (subscription_table_size == 0u))
    {
        return;
    }

    for (i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] == cb_2_register)
        {
            for (j = i; j < (uint8_t)(subscription_table_size - 1u); ++j)
            {
                subscription_table[j] = subscription_table[j + 1u];
            }
            subscription_table[subscription_table_size - 1u] = NULL;
            break;
        }
    }
}

void notify_enter_exit(observer_cb_arg_t *subscription_table, uint8_t subscription_table_size, event_state_e state)
{
    uint8_t i;

    if ((subscription_table == NULL) || (subscription_table_size == 0u))
    {
        return;
    }

    for (i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] != NULL)
        {
            subscription_table[i](state);
        }
    }
}

/* =========================================================================
 * CALLBACKS WITH UINT8 ARGUMENT
 * ========================================================================= */

subscr_status_e subscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_register, uint8_t subscription_table_size)
{
    subscr_status_e status = CALLBACK_ERROR_INVALID_ARGUMENT;
    uint8_t i;
    uint8_t free_index = subscription_table_size;

    if ((subscription_table != NULL) && (cb_2_register != NULL) && (subscription_table_size != 0u))
    {
        status = CALLBACK_ERROR_TABLE_FULL;

        for (i = 0u; i < subscription_table_size; ++i)
        {
            if (subscription_table[i] == cb_2_register)
            {
                status = CALLBACK_SUBSCR_OK;
                break;
            }

            if ((subscription_table[i] == NULL) && (free_index == subscription_table_size))
            {
                free_index = i;
            }
        }

        if ((status != CALLBACK_SUBSCR_OK) && (free_index < subscription_table_size))
        {
            subscription_table[free_index] = cb_2_register;
            status = CALLBACK_SUBSCR_OK;
        }
    }

    return status;
}

void unsubscribe_u8(observer_cb_u8_arg_t *subscription_table, observer_cb_u8_arg_t cb_2_register, uint8_t subscription_table_size)
{
    uint8_t i, j;

    if ((subscription_table == NULL) || (cb_2_register == NULL) || (subscription_table_size == 0u))
    {
        return;
    }

    for (i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] == cb_2_register)
        {
            for (j = i; j < (uint8_t)(subscription_table_size - 1u); ++j)
            {
                subscription_table[j] = subscription_table[j + 1u];
            }
            subscription_table[subscription_table_size - 1u] = NULL;
            break;
        }
    }
}

void notify_u8(observer_cb_u8_arg_t *subscription_table, uint8_t subscription_table_size, uint8_t data)
{
    uint8_t i;

    if ((subscription_table == NULL) || (subscription_table_size == 0u))
    {
        return;
    }

    for (i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] != NULL)
        {
            subscription_table[i](data);
        }
    }
}
