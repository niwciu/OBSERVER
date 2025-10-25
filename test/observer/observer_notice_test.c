#include "unity/fixture/unity_fixture.h"
#include "observer.h"
#include "mock_fun.h"

// #include "tested_module.h"

#define SUBSCRIPTION_CALBACKS_TABLE_SIZE 10
static observer_cb_t subscription[SUBSCRIPTION_CALBACKS_TABLE_SIZE];

static void clear_subscription_table(void);

TEST_GROUP(observer_notice);

TEST_SETUP(observer_notice)
{
    /* Init before every test */
    clear_subscription_table();
}

TEST_TEAR_DOWN(observer_notice)
{
    /* Cleanup after every test */
}

TEST(observer_notice, GivenMockFunCountersResetedAndMockFun1MockFun2MockFun3SubscribedWhenNoticeCalledThenSubscribedMockFunCountersEqual1)
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

TEST(observer_notice, GivenMockFunCountersResetedAndMockFun1MockFun2MockFun3SubscribedAndNoticeCalledAndMock2FunUnsubscribedWhenNoticeCalledThenSubscribedMockFun1AndMockFun3CountersEqual2AndMockFun2CounterEqual1)
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

TEST(observer_notice, GivenMockFun1MockFun2MockFun3SubscribedWhenNoticeCalledThenRetValueEqualObserverOk)
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

// TEST(observer_notice, )
// {
//     // Given

//     // When

//     // Then
//     TEST_FAIL_MESSAGE("Added new test")
// }

// TEST(observer_notice, )
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