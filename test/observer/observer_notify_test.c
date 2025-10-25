#include "unity/fixture/unity_fixture.h"
#include "observer.h"
#include "mock_fun.h"

// #include "tested_module.h"

#define SUBSCRIPTION_CALBACKS_TABLE_SIZE 10
static observer_cb_t subscription[SUBSCRIPTION_CALBACKS_TABLE_SIZE];

static void clear_subscription_table(void);

TEST_GROUP(observer_notify);

TEST_SETUP(observer_notify)
{
    /* Init before every test */
    clear_subscription_table();
}

TEST_TEAR_DOWN(observer_notify)
{
    /* Cleanup after every test */
}

TEST(observer_notify, GivenMockFunCountersResetedAndMockFun1MockFun2MockFun3SubscribedWhenNotifyCalledThenSubscribedMockFunCountersEqual1)
{
    static uint8_t expected_mock_counter[MOCK_COUNTER_QTY] = {0};
    expected_mock_counter[0] = 1;
    expected_mock_counter[1] = 1;
    expected_mock_counter[2] = 1;

    // Given
    mock_reset_mock_fun_counters();
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_2, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_3, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    notify(subscription, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_mock_counter, mock_fun_counter, MOCK_COUNTER_QTY);
}

TEST(observer_notify, GivenMockFunCountersResetedAndMockFun1MockFun2MockFun3SubscribedAndNotifyCalledAndMock2FunUnsubscribedWhenNotifyCalledThenSubscribedMockFun1AndMockFun3CountersEqual2AndMockFun2CounterEqual1)
{
    static uint8_t expected_mock_counter[MOCK_COUNTER_QTY] = {0};
    expected_mock_counter[0] = 2;
    expected_mock_counter[1] = 1;
    expected_mock_counter[2] = 2;

    // Given
    mock_reset_mock_fun_counters();
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_2, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_3, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    notify(subscription, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    unsubscribe(subscription, mock_fun_2, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    notify(subscription, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_mock_counter, mock_fun_counter, MOCK_COUNTER_QTY);
}

/* SUBSCRIBE RET VALUE test cases to run */
TEST(observer_notify, GivenMockFun1MockFun2MockFun3SubscribedWhenNotifyCalledWithSubscrCallbackTablePtrAndNonZeroSubscrTableLenThenRetValueEqualObserverOk)
{

    // Given
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_2, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_3, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = notify(subscription, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_OK, ret_status);
}

TEST(observer_notify, GivenMockFun1MockFun2MockFun3SubscribedWhenNotifyCalledWithNullPtrAndNonZeroSubscrTableLenThenRetValueEqualObserverOk)
{

    // Given
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_2, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_3, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = notify(NULL, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_INVALID_ARGUMENT_ERROR, ret_status);
}

TEST(observer_notify, GivenMockFun1MockFun2MockFun3SubscribedWhenNotifyCalledWithSubscrCallbackTablePtrAndSubscrTableLenEqual0ThenRetValueEqualObserverOk)
{
    // Given
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_2, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_3, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = notify(subscription, 0);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_INVALID_ARGUMENT_ERROR, ret_status);
}
TEST(observer_notify, GivenSubscriptionTableEmptyWhenNotifyCalledWithSubscrCallbackTablePtrAndNonZeroSubscrTableLenThenRetValueEqualObserverTableEmptyError)
{
    // Given
    clear_subscription_table();
    // When
    subscr_status_e ret_status = notify(subscription, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_TABLE_EMPTY_ERROR, ret_status);
}

// TEST(observer_notify, )
// {
//     // Given

//     // When

//     // Then
//     TEST_FAIL_MESSAGE("Added new test")
// }

static void clear_subscription_table(void)
{
    for (uint8_t i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        subscription[i] = NULL;
    }
}