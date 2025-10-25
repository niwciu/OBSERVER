#include "unity/fixture/unity_fixture.h"
#include "observer.h"

#define SUBSCRIPTION_CALLBACKS_TABLE_SIZE 10
#define MOCK_COUNTER_QTY 3

static observer_cb_state_t subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE];
static uint8_t mock_fun_with_arg_counter[MOCK_COUNTER_QTY] = {0};

static void clear_subscription_table(void);
static void mock_reset_mock_fun_with_arg_counters(void);

// Mockowane funkcje z argumentem (przyjmują `void*` i zwiększają odpowiedni licznik)
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

TEST_GROUP(observer_notify_with_state_arg);

TEST_SETUP(observer_notify_with_state_arg)
{
    clear_subscription_table();
    mock_reset_mock_fun_with_arg_counters();
}

TEST_TEAR_DOWN(observer_notify_with_state_arg)
{
}

TEST(observer_notify_with_state_arg, GivenMockCountersResetedAndAll3SubscribedWhenNotifyWithStateArgCalledThenEachCounterIncreased)
{
    static uint8_t expected_mock_counter[MOCK_COUNTER_QTY] = {1, 1, 1};

    // Given
    subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_3, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

    // When
    notify_enter_exit(subscription, SUBSCRIPTION_CALLBACKS_TABLE_SIZE, EVENT_STATE_ENTER);

    // Then
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_mock_counter, mock_fun_with_arg_counter, MOCK_COUNTER_QTY);
}

TEST(observer_notify_with_state_arg, GivenAll3SubscribedAndOneUnsubscribedWhenNotifyWithStateArgCalledThenOnlyRemainingAreNotified)
{
    static uint8_t expected_mock_counter[MOCK_COUNTER_QTY] = {2, 1, 2};

    // Given
    subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_3, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

    notify_enter_exit(subscription, SUBSCRIPTION_CALLBACKS_TABLE_SIZE, EVENT_STATE_ENTER);

    unsubscribe_state_change(subscription, mock_fun_with_state_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

    // When
    notify_enter_exit(subscription, SUBSCRIPTION_CALLBACKS_TABLE_SIZE, EVENT_STATE_EXIT);

    // Then
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_mock_counter, mock_fun_with_arg_counter, MOCK_COUNTER_QTY);
}

/* SUBSCRIBE RET VALUE test cases to run */
TEST(observer_notify_with_state_arg, GivenMockFun1MockFun2MockFun3SubscribedWhenNotifyWithStateCalledWithSubscrCallbackTablePtrAndNonZeroSubscrTableLenThenRetValueEqualObserverOk)
{

    // Given
    subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_3, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = notify_enter_exit(subscription, SUBSCRIPTION_CALLBACKS_TABLE_SIZE, EVENT_STATE_ENTER);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_OK, ret_status);
}

TEST(observer_notify_with_state_arg, GivenMockFun1MockFun2MockFun3SubscribedWhenNotifyWithStateCalledWithNullPtrAndNonZeroSubscrTableLenThenRetValueEqualObserverOk)
{

    // Given
    subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_3, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = notify_enter_exit(NULL, SUBSCRIPTION_CALLBACKS_TABLE_SIZE,EVENT_STATE_ENTER);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_INVALID_ARGUMENT_ERROR, ret_status);
}

TEST(observer_notify_with_state_arg, GivenMockFun1MockFun2MockFun3SubscribedWhenNotifyWithStateCalledWithSubscrCallbackTablePtrAndSubscrTableLenEqual0ThenRetValueEqualObserverOk)
{
    // Given
    subscribe_state_change(subscription, mock_fun_with_state_arg, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_2, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    subscribe_state_change(subscription, mock_fun_with_state_arg_3, SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = notify_enter_exit(subscription, 0, EVENT_STATE_ENTER);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_INVALID_ARGUMENT_ERROR, ret_status);
}
TEST(observer_notify_with_state_arg, GivenSubscriptionTableEmptyWhenNotifyWithStateCalledWithSubscrCallbackTablePtrAndNonZeroSubscrTableLenThenRetValueEqualObserverTableEmptyError)
{
    // Given
    clear_subscription_table();
    // When
    subscr_status_e ret_status = notify_enter_exit(subscription, SUBSCRIPTION_CALLBACKS_TABLE_SIZE,EVENT_STATE_EXIT);
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
