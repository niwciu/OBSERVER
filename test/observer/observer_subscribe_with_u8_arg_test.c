#include "observer.h"
#include "unity/fixture/unity_fixture.h"

#define SUBSCRIPTION_CALLBACKS_TABLE_SIZE 10
#define MOCK_COUNTER_QTY 3

static observer_cb_u8_arg_t subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE];
static uint8_t mock_fun_with_arg_counter[MOCK_COUNTER_QTY] = {0};

static void clear_subscription_table(void);
static void mock_reset_mock_fun_with_arg_counters(void);

// Mocki dla callbacków z argumentem
static void mock_fun_with_arg_1(uint8_t state) {
  (void)state;
  mock_fun_with_arg_counter[0]++;
}
static void mock_fun_with_arg_2(uint8_t state) {
  (void)state;
  mock_fun_with_arg_counter[1]++;
}
static void mock_fun_with_arg_3(uint8_t state) {
  (void)state;
  mock_fun_with_arg_counter[2]++;
}
static void mock_dirty_fun_with_arg(uint8_t state) { (void)state; }

TEST_GROUP(observer_subscribe_with_u8_arg);

TEST_SETUP(observer_subscribe_with_u8_arg) {
  clear_subscription_table();
  mock_reset_mock_fun_with_arg_counters();
}

TEST_TEAR_DOWN(observer_subscribe_with_u8_arg) {}

TEST(
    observer_subscribe_with_u8_arg,
    GivenSubscriptionTableEmptyWhenSubscribeMockFun1ThenFirstElementEqualsMockFun1AndRestAreEmpty) {
  static uint32_t memory_obj_byte_len = sizeof(observer_cb_u8_arg_t);
  static observer_cb_u8_arg_t
      expected_subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE] = {NULL};
  expected_subscription[0] = mock_fun_with_arg_1;

  subscribe_u8(subscription, mock_fun_with_arg_1,
                        SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subscription, subscription,
                                 memory_obj_byte_len,
                                 SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
}

TEST(
    observer_subscribe_with_u8_arg,
    GivenSubscriptionTableEmptyWhenSubscribeMockFun1ThenMockFun2ThenCorrectOrderInTable) {
  static uint32_t memory_obj_byte_len = sizeof(observer_cb_u8_arg_t);
  static observer_cb_u8_arg_t
      expected_subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE] = {NULL};
  expected_subscription[0] = mock_fun_with_arg_1;
  expected_subscription[1] = mock_fun_with_arg_2;

  subscribe_u8(subscription, mock_fun_with_arg_1,
                        SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
  subscribe_u8(subscription, mock_fun_with_arg_2,
                        SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subscription, subscription,
                                 memory_obj_byte_len,
                                 SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
}

TEST(
    observer_subscribe_with_u8_arg,
    GivenSubscriptionTableEmptyWhenSubscribe3FunctionsThenFirst3ElementsSetAccordingToOrder) {
  static uint32_t memory_obj_byte_len = sizeof(observer_cb_u8_arg_t);
  static observer_cb_u8_arg_t
      expected_subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE] = {NULL};
  expected_subscription[0] = mock_fun_with_arg_1;
  expected_subscription[1] = mock_fun_with_arg_2;
  expected_subscription[2] = mock_fun_with_arg_3;

  subscribe_u8(subscription, mock_fun_with_arg_1,
                        SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
  subscribe_u8(subscription, mock_fun_with_arg_2,
                        SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
  subscribe_u8(subscription, mock_fun_with_arg_3,
                        SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subscription, subscription,
                                 memory_obj_byte_len,
                                 SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
}

TEST(observer_subscribe_with_u8_arg,
     GivenFullTableWhenSubscribeAnotherCallbackThenReturnTableFullError) {
  for (uint8_t i = 0; i < SUBSCRIPTION_CALLBACKS_TABLE_SIZE; i++) {
    subscription[i] = mock_dirty_fun_with_arg;
  }

  TEST_ASSERT_EQUAL(CALLBACK_TABLE_FULL_ERROR,
                    subscribe_u8(subscription, mock_fun_with_arg_1,
                                          SUBSCRIPTION_CALLBACKS_TABLE_SIZE));
}

TEST(observer_subscribe_with_u8_arg,
     GivenNotFullTableWhenSubscribeThenReturnCallbackSubscribedOk) {
  for (uint8_t i = 0; i < SUBSCRIPTION_CALLBACKS_TABLE_SIZE - 1; i++) {
    subscription[i] = mock_dirty_fun_with_arg;
  }

  TEST_ASSERT_EQUAL(CALLBACK_SUBSCR_OK,
                    subscribe_u8(subscription, mock_fun_with_arg_1,
                                          SUBSCRIPTION_CALLBACKS_TABLE_SIZE));
}

TEST(observer_subscribe_with_u8_arg,
     GivenEmptyTableWhenSubscribeSameCallback3TimesThenOnlyFirstSlotIsFilled) {
  static uint32_t memory_obj_byte_len = sizeof(observer_cb_u8_arg_t);
  static observer_cb_u8_arg_t
      expected_subscription[SUBSCRIPTION_CALLBACKS_TABLE_SIZE] = {NULL};
  expected_subscription[0] = mock_fun_with_arg_1;

  subscribe_u8(subscription, mock_fun_with_arg_1,
                        SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
  subscribe_u8(subscription, mock_fun_with_arg_1,
                        SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
  subscribe_u8(subscription, mock_fun_with_arg_1,
                        SUBSCRIPTION_CALLBACKS_TABLE_SIZE);

  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected_subscription, subscription,
                                 memory_obj_byte_len,
                                 SUBSCRIPTION_CALLBACKS_TABLE_SIZE);
}

static void clear_subscription_table(void) {
  for (uint8_t i = 0; i < SUBSCRIPTION_CALLBACKS_TABLE_SIZE; i++) {
    subscription[i] = NULL;
  }
}

static void mock_reset_mock_fun_with_arg_counters(void) {
  for (uint8_t i = 0; i < MOCK_COUNTER_QTY; i++) {
    mock_fun_with_arg_counter[i] = 0;
  }
}
