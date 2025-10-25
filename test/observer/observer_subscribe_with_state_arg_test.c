#include "unity/fixture/unity_fixture.h"
#include "observer.h"

#define SUBSCRIPTION_CALLBACKS_TABLE_SIZE 10
#define MOCK_COUNTER_QTY 3

static observer_cb_state_t subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE];
static uint8_t mock_fun_with_arg_counter[MOCK_COUNTER_QTY] = {0};

static void clear_subscription_table(void);
static void mock_reset_mock_fun_with_arg_counters(void);

// Mocki dla callbacków z argumentem
static void mock_fun_with_state_arg(event_state_e state)
{
    (void)state;
    mock_fun_with_arg_counter[0]++;
}
static void mock_fun_with_state_arg_2(event_state_e state)
{
    (void)state;
    mock_fun_with_arg_counter[1]++;
}
static void mock_fun_with_state_arg_3(event_state_e state)
{
    (void)state;
    mock_fun_with_arg_counter[2]++;
}
static void mock_dirty_fun_with_arg(event_state_e state)
{
    (void)state;
}

TEST_GROUP(observer_subscribe_with_state_arg);

TEST_SETUP(observer_subscribe_with_state_arg)
{
    clear_subscription_table();
    mock_reset_mock_fun_with_arg_counters();
}

TEST_TEAR_DOWN(observer_subscribe_with_state_arg)
{
}

TEST(observer_subscribe_with_state_arg, GivenSubscriptionTableEmptyWhenSubscribeMockFun1ThenFirstElementEqualsMockFun1AndRestAreEmpty)
{
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_state_t);
    static observer_cb_state_t expected_subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE] = {NULL};
    expected_subscription[0] = mock_fun_with_state_arg;

    subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subscription, subscription, memory_obj_byte_len, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
}

TEST(observer_subscribe_with_state_arg, GivenSubscriptionTableEmptyWhenSubscribeMockFun1ThenMockFun2ThenCorrectOrderInTable)
{
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_state_t);
    static observer_cb_state_t expected_subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE] = {NULL};
    expected_subscription[0] = mock_fun_with_state_arg;
    expected_subscription[1] = mock_fun_with_state_arg_2;

    subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subscription, subscription, memory_obj_byte_len, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
}

TEST(observer_subscribe_with_state_arg, GivenSubscriptionTableEmptyWhenSubscribe3FunctionsThenFirst3ElementsSetAccordingToOrder)
{
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_state_t);
    static observer_cb_state_t expected_subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE] = {NULL};
    expected_subscription[0] = mock_fun_with_state_arg;
    expected_subscription[1] = mock_fun_with_state_arg_2;
    expected_subscription[2] = mock_fun_with_state_arg_3;

    subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_3, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subscription, subscription, memory_obj_byte_len, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
}

TEST(observer_subscribe_with_state_arg, GivenEmptyTableWhenSubscribeSameCallback3TimesThenOnlyFirstSlotIsFilled)
{
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_state_t);
    static observer_cb_state_t expected_subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE] = {NULL};
    expected_subscription[0] = mock_fun_with_state_arg;

    subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subscription, subscription, memory_obj_byte_len, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
}

/* SUBSCRIBE RET VALUE test cases to run */
TEST(observer_subscribe_with_state_arg, GivenFullTableWhenSubscribeAnotherCallbackThenReturnTableFullError)
{
    for (uint8_t i = 0; i < SUBSCRIPTION_CALLBACKS_TABLE_SIZE; i++)
    {
        subscription[i] = mock_dirty_fun_with_arg;
    }

    TEST_ASSERT_EQUAL(OBSERVER_TABLE_FULL_ERROR, subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE));
}

TEST(observer_subscribe_with_state_arg, WhenSubscribeStateChangeMockFun1ToSubscriptionTableWitnNonZeroLenghtThenRetValueIsEqualToObserverOk)
{
    // Given
    // When
    subscr_status_e ret_status = subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_OK, ret_status);
}

TEST(observer_subscribe_with_state_arg, WhenSubscribeStateChangeMockFun1ToSubscriptionTableWith0LenghtThenReturnedValueIsEqualToCallbackErrorInvalidArgument)
{
    // Given
    // When
    subscr_status_e ret_status = subscribe_state_change(subscription, mock_fun_with_state_arg, 0);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_INVALID_ARGUMENT_ERROR, ret_status);
}

TEST(observer_subscribe_with_state_arg, WhenSubscribeStateChangeNullToSubscriptionTableWithWitnNonZeroLenghtThenReturnedValueIsEqualToCallbackErrorInvalidArgument)
{
    // Given
    // When
    subscr_status_e ret_status = subscribe_state_change(subscription, NULL, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_INVALID_ARGUMENT_ERROR, ret_status);
}

TEST(observer_subscribe_with_state_arg, WhenSubscribeStateChangeMockFun1ToNullPtrSubscriptionTableWitnNonZeroLenghtThenReturnedValueIsEqualToCallbackErrorInvalidArgument)
{
    // Given
    // When
    subscr_status_e ret_status = subscribe_state_change(NULL, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_INVALID_ARGUMENT_ERROR, ret_status);
}

static void clear_subscription_table(void)
{
    for (uint8_t i = 0; i < SUBSCRIPTION_CALLBACKS_TABLE_SIZE; i++)
    {
        subscription[i] = NULL;
    }
}

static void mock_reset_mock_fun_with_arg_counters(void)
{
    for (uint8_t i = 0; i < MOCK_COUNTER_QTY; i++)
    {
        mock_fun_with_arg_counter[i] = 0;
    }
}
