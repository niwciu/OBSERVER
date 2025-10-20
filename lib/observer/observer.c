/**
 * @file observer.c
 * @author niwciu
 * @brief Observer pattern implementation (deterministic, safety-critical)
 * @version 1.0.0
 * @date 2025-10-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "observer.h"
#include <stdint.h>
#include <stdio.h>

/* ========================================================================================================================
 *                                            CALLBACKS WITHOUT ARGUMENT (void)
 * ======================================================================================================================== */

subscr_status_e subscribe(observer_cb_t *subscription_table, observer_cb_t cb_2_register, uint8_t subscription_table_size)
{
    if ((subscription_table == NULL) || (cb_2_register == NULL) || (subscription_table_size == 0u))
    {
        return CALLBACK_TABLE_IDX_TO_HIGH;
    }

    for (uint8_t i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] == cb_2_register)
        {
            return CALLBACK_SUBSCR_OK;
        }

        if (subscription_table[i] == NULL)
        {
            subscription_table[i] = cb_2_register;
            return CALLBACK_SUBSCR_OK;
        }
    }

    return CALLBACK_TABLE_FULL_ERROR;
}

void unsubscribe(observer_cb_t *subscription_table,
                 observer_cb_t cb_2_register,
                 uint8_t subscription_table_size)
{
    if ((subscription_table == NULL) || (cb_2_register == NULL))
    {
        return;
    }

    for (uint8_t i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] == cb_2_register)
        {
            for (uint8_t j = i; j < (subscription_table_size - 1u); ++j)
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
    if (subscription_table == NULL)
    {
        return;
    }

    for (uint8_t i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] != NULL)
        {
            subscription_table[i]();
        }
    }
}

/* ========================================================================================================================
 *                                  CALLBACKS WITH TWO STATE ARGUMENT (event_state_e)
 * ======================================================================================================================== */

subscr_status_e subscribe_enter_exit(observer_cb_arg_t *subscription_table, observer_cb_arg_t cb_2_register, uint8_t subscription_table_size)
{
    if ((subscription_table == NULL) || (cb_2_register == NULL) || (subscription_table_size == 0u))
    {
        return CALLBACK_TABLE_IDX_TO_HIGH;
    }

    for (uint8_t i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] == cb_2_register)
        {
            return CALLBACK_SUBSCR_OK;
        }

        if (subscription_table[i] == NULL)
        {
            subscription_table[i] = cb_2_register;
            return CALLBACK_SUBSCR_OK;
        }
    }

    return CALLBACK_TABLE_FULL_ERROR;
}

void unsubscribe_enter_exit(observer_cb_arg_t *subscription_table,
                            observer_cb_arg_t cb_2_register,
                            uint8_t subscription_table_size)
{
    if ((subscription_table == NULL) || (cb_2_register == NULL))
    {
        return;
    }

    for (uint8_t i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] == cb_2_register)
        {
            for (uint8_t j = i; j < (subscription_table_size - 1u); ++j)
            {
                subscription_table[j] = subscription_table[j + 1u];
            }
            subscription_table[subscription_table_size - 1u] = NULL;
            break;
        }
    }
}

void notify_enter_exit(observer_cb_arg_t *subscription_table,
                       uint8_t subscription_table_size,
                       event_state_e state)
{
    if (subscription_table == NULL)
    {
        return;
    }

    for (uint8_t i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] != NULL)
        {
            subscription_table[i](state);
        }
    }
}

/* ========================================================================================================================
 *                                         CALLBACKS WITH UINT8 ARGUMENT
 * ======================================================================================================================== */

subscr_status_e subscribe_u8(observer_cb_u8_arg_t *subscription_table,
                              observer_cb_u8_arg_t cb_2_register,
                              uint8_t subscription_table_size)
{
    if ((subscription_table == NULL) || (cb_2_register == NULL) || (subscription_table_size == 0u))
    {
        return CALLBACK_TABLE_IDX_TO_HIGH;
    }

    for (uint8_t i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] == cb_2_register)
        {
            return CALLBACK_SUBSCR_OK;
        }

        if (subscription_table[i] == NULL)
        {
            subscription_table[i] = cb_2_register;
            return CALLBACK_SUBSCR_OK;
        }
    }

    return CALLBACK_TABLE_FULL_ERROR;
}

void unsubscribe_u8(observer_cb_u8_arg_t *subscription_table,
                     observer_cb_u8_arg_t cb_2_register,
                     uint8_t subscription_table_size)
{
    if ((subscription_table == NULL) || (cb_2_register == NULL))
    {
        return;
    }

    for (uint8_t i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] == cb_2_register)
        {
            for (uint8_t j = i; j < (subscription_table_size - 1u); ++j)
            {
                subscription_table[j] = subscription_table[j + 1u];
            }
            subscription_table[subscription_table_size - 1u] = NULL;
            break;
        }
    }
}

void notify_u8(observer_cb_u8_arg_t *subscription_table,
               uint8_t subscription_table_size,
               uint8_t data)
{
    if (subscription_table == NULL)
    {
        return;
    }

    for (uint8_t i = 0u; i < subscription_table_size; ++i)
    {
        if (subscription_table[i] != NULL)
        {
            subscription_table[i](data);
        }
    }
}
