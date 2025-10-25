#include "unity/fixture/unity_fixture.h"

#include "observer.h"
#include "mock_fun.h"

// #include "tested_module.h"

#define SUBSCRIPTION_CALBACKS_TABLE_SIZE 10
static observer_cb_t subscription[SUBSCRIPTION_CALBACKS_TABLE_SIZE];

static void clear_subscription_table(void);

TEST_GROUP(observer_unsubscribe);

TEST_SETUP(observer_unsubscribe)
{
    /* Init before every test */
    clear_subscription_table();
}

TEST_TEAR_DOWN(observer_unsubscribe)
{
    /* Cleanup after every test */
}

TEST(observer_unsubscribe, GivenMocFun1FuncionSubscribedWhenMockFun1UnsubscribeThenSubscribtionTableEqualToExpected)
{
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static observer_cb_t expected_subsribtion[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    // Given

    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);

    // When
    unsubscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subsribtion, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe, GivenMocFun1ToMockFun5FuncionSubscribedWhenUnsubscribeMockFun3FunnctionCalledThenSubscribtionTableEqualToExpected)
{
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static observer_cb_t expected_subsribtion[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    expected_subsribtion[0] = mock_fun_1;
    expected_subsribtion[1] = mock_fun_2;
    expected_subsribtion[2] = mock_fun_4;
    expected_subsribtion[3] = mock_fun_5;
    // Given
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_2, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_3, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_4, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_5, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    unsubscribe(subscription, mock_fun_3, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subsribtion, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe, GivenMocFun1ToMockFun5FuncionSubscribedWhenUnsubscribeMockFun5FunnctionCalledThenSubscribtionTableEqualToExpected)
{
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static observer_cb_t expected_subsribtion[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};

    expected_subsribtion[0] = mock_fun_1;
    expected_subsribtion[1] = mock_fun_2;
    expected_subsribtion[2] = mock_fun_3;
    expected_subsribtion[3] = mock_fun_4;
    // Given
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_2, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_3, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_4, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    subscribe(subscription, mock_fun_5, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    unsubscribe(subscription, mock_fun_5, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subsribtion, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe, GivenSubscribtionTableFullWhenUnsubscribeOneBeforeLastFunctionThenSubscribtionTableEqualToExpected)
{
#define FUN_ADR_OFFSET 0x200U
#define LAST_CB_TAB_ELEMENT (SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1)

    static observer_cb_t expected_subsribtion[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_t unsubscr_fun;
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);

    for (uint8_t i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        expected_subsribtion[i] = (observer_cb_t)(&mock_fun_1 + (FUN_ADR_OFFSET * i));
    }
    unsubscr_fun = expected_subsribtion[LAST_CB_TAB_ELEMENT - 1];
    expected_subsribtion[LAST_CB_TAB_ELEMENT - 1] = expected_subsribtion[LAST_CB_TAB_ELEMENT];
    expected_subsribtion[LAST_CB_TAB_ELEMENT] = NULL;
    // Given
    for (uint8_t i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        subscribe(subscription, (observer_cb_t)(mock_fun_1 + (FUN_ADR_OFFSET * i)), SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    }
    // When
    unsubscribe(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subsribtion, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe, GivenSubscribtionTableFullWhenUnsubscribe5thFunctionInCallbackTableThenSubscribtionTableEqualToExpected)
{
#define FUN_ADR_OFFSET 0x200U
#define LAST_CB_TAB_ELEMENT (SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1)
#define UNSUBSCR_CB_TABLE_ELEMENT 4U

    static observer_cb_t expected_subsribtion[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_t unsubscr_fun;
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static uint8_t i;
    for (i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        expected_subsribtion[i] = (observer_cb_t)(&mock_fun_1 + (FUN_ADR_OFFSET * i));
    }
    unsubscr_fun = expected_subsribtion[UNSUBSCR_CB_TABLE_ELEMENT];
    for (i = UNSUBSCR_CB_TABLE_ELEMENT; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1; i++)
    {
        expected_subsribtion[i] = expected_subsribtion[i + 1];
    }
    expected_subsribtion[LAST_CB_TAB_ELEMENT] = NULL;
    // Given
    for (i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        subscribe(subscription, (observer_cb_t)(mock_fun_1 + (FUN_ADR_OFFSET * i)), SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    }
    // When
    unsubscribe(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subsribtion, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe, GivenSubscribtionTableFullWhenUnsubscribeLastFunctionThenSubscribtionTableEqualToExpected)
{
#define FUN_ADR_OFFSET 0x200U
#define LAST_CB_TAB_ELEMENT (SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1)

    static observer_cb_t expected_subsribtion[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_t unsubscr_fun;
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static uint8_t i;
    for (i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        expected_subsribtion[i] = (observer_cb_t)(&mock_fun_1 + (FUN_ADR_OFFSET * i));
    }
    unsubscr_fun = expected_subsribtion[LAST_CB_TAB_ELEMENT];
    expected_subsribtion[LAST_CB_TAB_ELEMENT] = NULL;
    // Given
    for (i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE; i++)
    {
        subscribe(subscription, (observer_cb_t)(mock_fun_1 + (FUN_ADR_OFFSET * i)), SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    }
    // When
    unsubscribe(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subsribtion, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe, GivenSubscribtionTableWithLastElementEqualNullWhenUnsubscribeOneBeforeLastSubscribedFunctionThenSubscribtionTableEqualToExpected)
{
#define FUN_ADR_OFFSET 0x200U
#define LAST_CB_TAB_ELEMENT (SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1)
#define UNSUBSCR_FUNC_TAB_ELEMENT (LAST_CB_TAB_ELEMENT - 2)

    static observer_cb_t expected_subsribtion[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_t unsubscr_fun;
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static uint8_t i;
    for (i = 0; i < LAST_CB_TAB_ELEMENT; i++)
    {
        expected_subsribtion[i] = (observer_cb_t)(&mock_fun_1 + (FUN_ADR_OFFSET * i));
    }
    unsubscr_fun = expected_subsribtion[UNSUBSCR_FUNC_TAB_ELEMENT];
    expected_subsribtion[UNSUBSCR_FUNC_TAB_ELEMENT] = expected_subsribtion[UNSUBSCR_FUNC_TAB_ELEMENT + 1];
    expected_subsribtion[UNSUBSCR_FUNC_TAB_ELEMENT + 1] = NULL;
    // Given
    for (i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1; i++)
    {
        subscribe(subscription, (observer_cb_t)(mock_fun_1 + (FUN_ADR_OFFSET * i)), SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    }
    // When
    unsubscribe(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subsribtion, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe, GivenSubscribtionTableWithLastElementEqualNullWhenUnsubscribe5thSubscribedFunctionThenSubscribtionTableEqualToExpected)
{
#define FUN_ADR_OFFSET 0x200U
#define LAST_CB_TAB_ELEMENT (SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1)
#define UNSUBSCR_CB_TABLE_ELEMENT 4U

    static observer_cb_t expected_subsribtion[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_t unsubscr_fun;
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static uint8_t i;
    for (i = 0; i < LAST_CB_TAB_ELEMENT; i++)
    {
        expected_subsribtion[i] = (observer_cb_t)(&mock_fun_1 + (FUN_ADR_OFFSET * i));
    }
    unsubscr_fun = expected_subsribtion[UNSUBSCR_CB_TABLE_ELEMENT];
    for (i = UNSUBSCR_CB_TABLE_ELEMENT; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1; i++)
    {
        expected_subsribtion[i] = expected_subsribtion[i + 1];
    }
    expected_subsribtion[LAST_CB_TAB_ELEMENT] = NULL;
    // Given
    for (i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1; i++)
    {
        subscribe(subscription, (observer_cb_t)(mock_fun_1 + (FUN_ADR_OFFSET * i)), SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    }
    // When
    unsubscribe(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subsribtion, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe, GivenSubscribtionTableWithLastElementEqualNullWhenUnsubscribeLastSubscribedFunctionThenSubscribtionTableEqualToExpected)
{
#define FUN_ADR_OFFSET 0x200U
#define LAST_CB_TAB_ELEMENT (SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1)

    static observer_cb_t expected_subsribtion[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static observer_cb_t unsubscr_fun;
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static uint8_t i;
    for (i = 0; i < LAST_CB_TAB_ELEMENT; i++)
    {
        expected_subsribtion[i] = (observer_cb_t)(&mock_fun_1 + (FUN_ADR_OFFSET * i));
    }
    unsubscr_fun = expected_subsribtion[LAST_CB_TAB_ELEMENT - 1];
    expected_subsribtion[LAST_CB_TAB_ELEMENT - 1] = NULL;
    // Given
    for (i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1; i++)
    {
        subscribe(subscription, (observer_cb_t)(mock_fun_1 + (FUN_ADR_OFFSET * i)), SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    }
    // When
    unsubscribe(subscription, unsubscr_fun, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subsribtion, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}

TEST(observer_unsubscribe, GivenSubscribtionTableFullWithMock1FunAdressesWhenMock1FunUnsubscribedThenSubscriptionTableIsEmpty)
{
    static observer_cb_t expected_subsribtion[SUBSCRIPTION_CALBACKS_TABLE_SIZE] = {NULL};
    static uint32_t memory_obj_byte_len = sizeof(observer_cb_t);
    static uint8_t i;
    // Given
    for (i = 0; i < SUBSCRIPTION_CALBACKS_TABLE_SIZE - 1; i++)
    {
        subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    }
    // When
    unsubscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subsribtion, subscription, memory_obj_byte_len, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
}


/* SUBSCRIBE RET VALUE test cases to run */
TEST(observer_unsubscribe, GivenMocFun1FuncionSubscribedWhenUnsubscribeMockFun1FromSubscriptionTableWitnNonZeroLenghtThenRetValueIsEqualToCalbbackSubscrOk)
{
    // Given
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = unsubscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(CALLBACK_SUBSCR_OK, ret_status);
}

TEST(observer_unsubscribe, GivenMocFun1FuncionSubscribedWhenUnsubscribeMockFun1FromSubscriptionTableWitZeroLenghtThenRetValueIsEqualToCalbbackSubscrErrorInvalidArgument)
{
    // Given
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = unsubscribe(subscription, mock_fun_1, 0);
    // Then
    TEST_ASSERT_EQUAL(CALLBACK_ERROR_INVALID_ARGUMENT, ret_status);
}

TEST(observer_unsubscribe, GivenMocFun1FuncionSubscribedWhenUnsubscribeNullPtrFromSubscriptionTableWitnNonZeroLenghtThenRetValueIsEqualToCalbbackSubscrErrorInvalidArgument)
{
    // Given
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = unsubscribe(subscription, NULL, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(CALLBACK_ERROR_INVALID_ARGUMENT, ret_status);
}

TEST(observer_unsubscribe, GivenMocFun1FuncionSubscribedWhenUnsubscribeMockFun1FromNullPtrSubscrTableWitnNonZeroLenghtThenRetValueIsEqualToCalbbackSubscrErrorInvalidArgument)
{
    // Given
    subscribe(subscription, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // When
    subscr_status_e ret_status = unsubscribe(NULL, mock_fun_1, SUBSCRIPTION_CALBACKS_TABLE_SIZE);
    // Then
    TEST_ASSERT_EQUAL(CALLBACK_ERROR_INVALID_ARGUMENT, ret_status);
}

// TEST(observer_unsubscribe, )
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