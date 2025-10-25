#include "unity/fixture/unity_fixture.h"
#include "observer.h"

#define SUBSCRIPTION_CALBACKS_TABLE_SIZE 10
#define FUN_ADR_OFFSET 0x200U
#define LAST_CB_TAB_ELEMENT (SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1)

static observer_cb_state_t subscription[SUBSCRIPTION_CALBACKS_TABLE_SIZE];

static void clear_subscription_table(void);
static void dummy_cb(event_state_e arg)
{
    (void)arg;
}

TEST_GROUP(observer_unsubscribe_with_state_arg);

TEST_SETUP(observer_unsubscribe_with_state_arg)
{
    clear_subscription_table();
}

TEST_TEAR_DOWN(observer_unsubscribe_with_state_arg)
{
}

TEST(observer_unsubscribe_with_state_arg, GivenMockFun1SubscribedWhenUnsubThenTableIsEmpty)
{
    static uint32_t len = sizeof(observer_cb_state_t);
    static observer_cb_state_t expected[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};

    subscribe_state_change(subscription, dummy_cb, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    unsubscribe_state_change(subscription, dummy_cb, SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, subscription, len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe_with_state_arg, GivenFun1To5SubscribedWhenUnsubFun3ThenTableEqualExpected)
{
    static uint32_t len = sizeof(observer_cb_state_t);
    static observer_cb_state_t expected[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};

    expected[0] = (&dummy_cb + (FUN_ADR_OFFSET * 0));
    expected[1] = (&dummy_cb + (FUN_ADR_OFFSET * 1));
    expected[2] = (&dummy_cb + (FUN_ADR_OFFSET * 3));
    expected[3] = (&dummy_cb + (FUN_ADR_OFFSET * 4));

    for (int i = 0; i < 5; i++)
    {
        subscribe_state_change(subscription, (&dummy_cb + (FUN_ADR_OFFSET * i)), SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    }

    unsubscribe_state_change(subscription, (&dummy_cb + (FUN_ADR_OFFSET * 2)), SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, subscription, len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe_with_state_arg, GivenFun1To5SubscribedWhenUnsubFun5ThenTableEqualExpected)
{
    static uint32_t len = sizeof(observer_cb_state_t);
    static observer_cb_state_t expected[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};

    for (int i = 0; i < 4; i++)
        expected[i] = (&dummy_cb + (FUN_ADR_OFFSET * i));

    for (int i = 0; i < 5; i++)
        subscribe_state_change(subscription, (&dummy_cb + (FUN_ADR_OFFSET * i)), SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    unsubscribe_state_change(subscription, (&dummy_cb + (FUN_ADR_OFFSET * 4)), SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, subscription, len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe_with_state_arg, GivenTableFullWhenUnsubOneBeforeLastThenTableEqualExpected)
{
    static observer_cb_state_t expected[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_state_t unsubscr_fun;
    static uint32_t len = sizeof(observer_cb_state_t);

    for (uint8_t i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        expected[i] = (&dummy_cb + (FUN_ADR_OFFSET * i));
        subscription[i] = expected[i];
    }

    unsubscr_fun = expected[LAST_CB_TAB_ELEMENT - 1];
    expected[LAST_CB_TAB_ELEMENT - 1] = expected[LAST_CB_TAB_ELEMENT];
    expected[LAST_CB_TAB_ELEMENT] = NULL;

    unsubscribe_state_change(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, subscription, len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe_with_state_arg, GivenTableFullWhenUnsub5thElementThenTableEqualExpected)
{
#define UNSUBSCR_CB_TABLE_ELEMENT 4U

    static observer_cb_state_t expected[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_state_t unsubscr_fun;
    static uint32_t len = sizeof(observer_cb_state_t);
    static uint8_t i;

    for (i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        expected[i] = (&dummy_cb + (FUN_ADR_OFFSET * i));
        subscription[i] = expected[i];
    }

    unsubscr_fun = expected[UNSUBSCR_CB_TABLE_ELEMENT];
    for (i = UNSUBSCR_CB_TABLE_ELEMENT; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1; i++)
    {
        expected[i] = expected[i + 1];
    }
    expected[LAST_CB_TAB_ELEMENT] = NULL;

    unsubscribe_state_change(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, subscription, len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe_with_state_arg, GivenTableFullWhenUnsubLastElementThenTableEqualExpected)
{
    static observer_cb_state_t expected[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_state_t unsubscr_fun;
    static uint32_t len = sizeof(observer_cb_state_t);

    for (uint8_t i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        expected[i] = (&dummy_cb + (FUN_ADR_OFFSET * i));
        subscription[i] = expected[i];
    }

    unsubscr_fun = expected[LAST_CB_TAB_ELEMENT];
    expected[LAST_CB_TAB_ELEMENT] = NULL;

    unsubscribe_state_change(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, subscription, len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe_with_state_arg, GivenTableWithLastNullWhenUnsubOneBeforeLastThenTableEqualExpected)
{
#define UNSUBSCR_FUNC_TAB_ELEMENT (LAST_CB_TAB_ELEMENT - 2)

    static observer_cb_state_t expected[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_state_t unsubscr_fun;
    static uint32_t len = sizeof(observer_cb_state_t);

    for (uint8_t i = 0; i < LAST_CB_TAB_ELEMENT; i++)
    {
        expected[i] = (&dummy_cb + (FUN_ADR_OFFSET * i));
        subscription[i] = expected[i];
    }

    unsubscr_fun = expected[UNSUBSCR_FUNC_TAB_ELEMENT];
    expected[UNSUBSCR_FUNC_TAB_ELEMENT] = expected[UNSUBSCR_FUNC_TAB_ELEMENT + 1];
    expected[UNSUBSCR_FUNC_TAB_ELEMENT + 1] = NULL;

    unsubscribe_state_change(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, subscription, len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe_with_state_arg, GivenTableWithLastNullWhenUnsub5thFunctionThenTableEqualExpected)
{
#define UNSUBSCR_CB_TABLE_ELEMENT 4U

    static observer_cb_state_t expected[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_state_t unsubscr_fun;
    static uint32_t len = sizeof(observer_cb_state_t);
    static uint8_t i;

    for (i = 0; i < LAST_CB_TAB_ELEMENT; i++)
    {
        expected[i] = (&dummy_cb + (FUN_ADR_OFFSET * i));
        subscription[i] = expected[i];
    }

    unsubscr_fun = expected[UNSUBSCR_CB_TABLE_ELEMENT];
    for (i = UNSUBSCR_CB_TABLE_ELEMENT; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1; i++)
    {
        expected[i] = expected[i + 1];
    }
    expected[LAST_CB_TAB_ELEMENT] = NULL;

    unsubscribe_state_change(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, subscription, len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe_with_state_arg, GivenTableWithLastNullWhenUnsubLastSubscribedThenTableEqualExpected)
{
    static observer_cb_state_t expected[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_state_t unsubscr_fun;
    static uint32_t len = sizeof(observer_cb_state_t);

    for (uint8_t i = 0; i < LAST_CB_TAB_ELEMENT; i++)
    {
        expected[i] = (&dummy_cb + (FUN_ADR_OFFSET * i));
        subscription[i] = expected[i];
    }

    unsubscr_fun = expected[LAST_CB_TAB_ELEMENT - 1];
    expected[LAST_CB_TAB_ELEMENT - 1] = NULL;

    unsubscribe_state_change(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, subscription, len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe_with_state_arg, GivenTableFullOfSameFunWhenUnsubThenTableIsEmpty)
{
    static observer_cb_state_t expected[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static uint32_t len = sizeof(observer_cb_state_t);

    for (uint8_t i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1; i++)
    {
        subscribe_state_change(subscription, dummy_cb, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    }

    unsubscribe_state_change(subscription, dummy_cb, SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, subscription, len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

/* SUBSCRIBE RET VALUE test cases to run */
TEST(observer_unsubscribe_with_state_arg, GivenMocFun1FuncionSubscribedWhenUnsubscribeStateChangeMockFun1FromSubscriptionTableWitnNonZeroLenghtThenRetValueIsEqualToCalbbackSubscrOk)
{
    // Given
    subscribe_state_change(subscription, dummy_cb, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = unsubscribe_state_change(subscription, dummy_cb, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_OK, ret_status);
}

TEST(observer_unsubscribe_with_state_arg, GivenMocFun1FuncionSubscribedWhenUnsubscribeStateChangeMockFun1FromSubscriptionTableWitZeroLenghtThenRetValueIsEqualToCalbbackSubscrErrorInvalidArgument)
{
    // Given
    subscribe_state_change(subscription, dummy_cb, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = unsubscribe_state_change(subscription, dummy_cb, 0);
    // Then
    TEST_ASSERT_EQUAL(SUBSCR_ERROR_INVALID_ARGUMENT, ret_status);
}

TEST(observer_unsubscribe_with_state_arg, GivenMocFun1FuncionSubscribedWhenUnsubscribeStateChangeNullPtrFromSubscriptionTableWitnNonZeroLenghtThenRetValueIsEqualToCalbbackSubscrErrorInvalidArgument)
{
    // Given
    subscribe_state_change(subscription, dummy_cb, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = unsubscribe_state_change(subscription, NULL, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(SUBSCR_ERROR_INVALID_ARGUMENT, ret_status);
}

TEST(observer_unsubscribe_with_state_arg, GivenMocFun1FuncionSubscribedWhenUnsubscribeStateChangeMockFun1FromNullPtrSubscrTableWitnNonZeroLenghtThenRetValueIsEqualToCalbbackSubscrErrorInvalidArgument)
{
    // Given
    subscribe_state_change(subscription, dummy_cb, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = unsubscribe_state_change(NULL, dummy_cb, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(SUBSCR_ERROR_INVALID_ARGUMENT, ret_status);
}

static void clear_subscription_table(void)
{
    for (uint8_t i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        subscription[i] = NULL;
    }
}
