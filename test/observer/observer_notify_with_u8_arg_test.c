#include "unity/fixture/unity_fixture.h"
#include "observer.h"

#define SUBSCRIPTION_CALLBACKS_TABLE_SIZE 10
#define MOCK_COUNTER_QTY 3

static observer_cb_u8_arg_t subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE];
static uint8_t mock_fun_with_arg_counter[MOCK_COUNTER_QTY] = {0};

static void clear_subscription_table(void);
static void mock_reset_mock_fun_with_arg_counters(void);

// Mockowane funkcje z argumentem (przyjmują `void*` i zwiększają odpowiedni licznik)
static void mock_fun_with_u8_arg_1(uint8_t u8_arg)
{
    (void)u8_arg;
    mock_fun_with_arg_counter[0]++;
}
static void mock_fun_with_u8_arg_2(uint8_t u8_arg)
{
    (void)u8_arg;
    mock_fun_with_arg_counter[1]++;
}
static void mock_fun_with_u8_arg_3(uint8_t u8_arg)
{
    (void)u8_arg;
    mock_fun_with_arg_counter[2]++;
}

TEST_GROUP(observer_notify_with_u8_arg);

TEST_SETUP(observer_notify_with_u8_arg)
{
    clear_subscription_table();
    mock_reset_mock_fun_with_arg_counters();
}

TEST_TEAR_DOWN(observer_notify_with_u8_arg)
{
}

TEST(observer_notify_with_u8_arg, GivenMockCountersResetedAndAll3SubscribedWhenNotifyWithArgCalledThenEachCounterIncreased)
{
    static uint8_t expected_mock_counter[MOCK_COUNTER_QTY] = {1, 1, 1};

    // Given
    subscribe_u8(subscription, mock_fun_with_u8_arg_1, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_u8(subscription, mock_fun_with_u8_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_u8(subscription, mock_fun_with_u8_arg_3, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

    // When
    notify_u8(subscription, SUBSCRIPTION_CALLBACKS_TABLE_SIZE, EVENT_STATE_ENTER);

    // Then
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_mock_counter, mock_fun_with_arg_counter, MOCK_COUNTER_QTY);
}

TEST(observer_notify_with_u8_arg, GivenAll3SubscribedAndOneUnsubscribedWhenNotifyWithArgCalledThenOnlyRemainingAreNotified)
{
    static uint8_t expected_mock_counter[MOCK_COUNTER_QTY] = {2, 1, 2};

    // Given
    subscribe_u8(subscription, mock_fun_with_u8_arg_1, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_u8(subscription, mock_fun_with_u8_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_u8(subscription, mock_fun_with_u8_arg_3, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

    notify_u8(subscription, SUBSCRIPTION_CALLBACKS_TABLE_SIZE, EVENT_STATE_ENTER);

    unsubscribe_u8(subscription, mock_fun_with_u8_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

    // When
    notify_u8(subscription, SUBSCRIPTION_CALLBACKS_TABLE_SIZE, EVENT_STATE_EXIT);

    // Then
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_mock_counter, mock_fun_with_arg_counter, MOCK_COUNTER_QTY);
}

/* SUBSCRIBE RET VALUE test cases to run */
TEST(observer_notify_with_u8_arg, GivenMockFun1MockFun2MockFun3SubscribedWhenNotifyWithU8CalledWithSubscrCallbackTablePtrAndNonZeroSubscrTableLenThenRetValueEqualObserverOk)
{

    // Given
    subscribe_u8(subscription, mock_fun_with_u8_arg_1, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_u8(subscription, mock_fun_with_u8_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_u8(subscription, mock_fun_with_u8_arg_3, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = notify_u8(subscription, SUBSCRIPTION_CALLBACKS_TABLE_SIZE, EVENT_STATE_ENTER);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_OK, ret_status);
}

TEST(observer_notify_with_u8_arg, GivenMockFun1MockFun2MockFun3SubscribedWhenNotifyWithU8CalledWithNullPtrAndNonZeroSubscrTableLenThenRetValueEqualObserverOk)
{

    // Given
    subscribe_u8(subscription, mock_fun_with_u8_arg_1, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_u8(subscription, mock_fun_with_u8_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_u8(subscription, mock_fun_with_u8_arg_3, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = notify_u8(NULL, SUBSCRIPTION_CALLBACKS_TABLE_SIZE,EVENT_STATE_ENTER);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_INVALID_ARGUMENT_ERROR, ret_status);
}

TEST(observer_notify_with_u8_arg, GivenMockFun1MockFun2MockFun3SubscribedWhenNotifyWithU8CalledWithSubscrCallbackTablePtrAndSubscrTableLenEqual0ThenRetValueEqualObserverOk)
{
    // Given
    subscribe_u8(subscription, mock_fun_with_u8_arg_1, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_u8(subscription, mock_fun_with_u8_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_u8(subscription, mock_fun_with_u8_arg_3, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = notify_u8(subscription, 0, EVENT_STATE_ENTER);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_INVALID_ARGUMENT_ERROR, ret_status);
}
TEST(observer_notify_with_u8_arg, GivenSubscriptionTableEmptyWhenNotifyWithU8CalledWithSubscrCallbackTablePtrAndNonZeroSubscrTableLenThenRetValueEqualObserverTableEmptyError)
{
    // Given
    clear_subscription_table();
    // When
    subscr_status_e ret_status = notify_u8(subscription, SUBSCRIPTION_CALLBACKS_TABLE_SIZE,EVENT_STATE_EXIT);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_TABLE_EMPTY_ERROR, ret_status);
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
