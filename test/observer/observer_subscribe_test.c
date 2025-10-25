#include "unity/fixture/unity_fixture.h"
#include "observer.h"
#include "mock_fun.h"

#define SUBSCRIPTION_CALBACKS_TABLE_SIZE 10
static observer_cb_t subscription[SUBSCRIPTION_CALBACKS_TABLE_SIZE];

static void clear_subscription_table(void);

TEST_GROUP(observer_subscribe);

TEST_SETUP(observer_subscribe)
{
    /* Init before every test */
    clear_subscription_table();
}

TEST_TEAR_DOWN(observer_subscribe)
{
    /* Cleanup after every test */
}

/* SYS_TIM usage subsribe Test cases to run */
TEST(observer_subscribe, GivenSubscriptionTableEmptyWhenSubscribeMockFun1ToSubscriptionTableThenFirstElementOfSubscriptionTableIsEqualToMockFun1AndRestElementsAreEmpty)
{
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static observer_cb_t expexted_subscription[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    expexted_subscription[0] = mock_fun_1;
    // Given
    // When
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expexted_subscription, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_subscribe, GivenSubscriptionTableEmptyWhenSubscribeMockFun1AndNextSubscribedMockFun2ToSubscriptionTableThenInElemnt0IsEqualMockFun1AdresElement1IsEqualMockFun2AdrAndRestElementsAreEmpty)
{
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static observer_cb_t expexted_subscription[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    expexted_subscription[0] = mock_fun_1;
    expexted_subscription[1] = mock_fun_2;
    // Given
    // When
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_2, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expexted_subscription, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_subscribe, GivenSubscriptionTableEmptyWhenSubscribe3functionsThenFirst3CllbackTableElementsAreEqualToFunctionAdresssesAccordingToRegistrationOrderAndRestAreEqualNull)
{
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static observer_cb_t expexted_subscription[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    expexted_subscription[0] = mock_fun_1;
    expexted_subscription[1] = mock_fun_2;
    expexted_subscription[2] = mock_fun_3;
    // Given
    // When
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_2, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_3, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expexted_subscription, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_subscribe, GivenSubscriptionTableEmptyWhenSubscribeMockFun1ToSubscriptionTableThreeTimesThenFirstElementOfSubscriptionTableIsEqualToMockFun1AndRestElementsAreEmpty)
{
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static observer_cb_t expexted_subscription[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    expexted_subscription[0] = mock_fun_1;
    // Given
    // When
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expexted_subscription, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

static void clear_subscription_table(void)
{
    for (uint8_t i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        subscription[i] = NULL;
    }
}

/* SUBSCRIBE RET VALUE test cases to run */
TEST(observer_subscribe, GivenSubscriptionTableFullWhenSubscribeMockFun1ToSubscriptionTableThenFunctionReturnSubscriptionTableFullStatus)
{
    // Given
    for (uint8_t i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        subscription[i] = mock_dirty_fun;
    }
    // When
    // Then
    TEST_ASSERT_EQUAL(SUBSCR_ERROR_TABLE_FULL, subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE));
    // Then
}

TEST(observer_subscribe, WhenSubscribeMockFun1ToSubscriptionTableWitnNonZeroLenghtThenRetValueIsEqualToObserverOk)
{
    // Given
    // When
    subscr_status_e ret_status = subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(OBSERVER_OK, ret_status);
}

TEST(observer_subscribe, WhenSubscribeMockFun1ToSubscriptionTableWith0LenghtThenReturnedValueIsEqualToCallbackErrorInvalidArgument)
{
    // Given
    // When
    subscr_status_e ret_status = subscribe(subscription, mock_fun_1, 0);
    // Then
    TEST_ASSERT_EQUAL(SUBSCR_ERROR_INVALID_ARGUMENT, ret_status);
}

TEST(observer_subscribe, WhenSubscribeNullToSubscriptionTableWithWitnNonZeroLenghtThenReturnedValueIsEqualToCallbackErrorInvalidArgument)
{
    // Given
    // When
    subscr_status_e ret_status = subscribe(subscription, NULL, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(SUBSCR_ERROR_INVALID_ARGUMENT, ret_status);
}

TEST(observer_subscribe, WhenSubscribeMockFun1ToNullPtrSubscriptionTableWitnNonZeroLenghtThenReturnedValueIsEqualToCallbackErrorInvalidArgument)
{
    // Given
    // When
    subscr_status_e ret_status = subscribe(NULL, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(SUBSCR_ERROR_INVALID_ARGUMENT, ret_status);
}

