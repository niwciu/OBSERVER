#include "unity/fixture/unity_fixture.h"

static void run_all_tests(void);

int main(int argc, const char **argv) {
  int test_resoult = UnityMain(argc, argv, run_all_tests);

  return test_resoult;
}

static void run_all_tests(void) {
  RUN_TEST_GROUP(observer_subscribe);
  RUN_TEST_GROUP(observer_subscribe_with_arg);
  RUN_TEST_GROUP(observer_subscribe_with_u8_arg);
  RUN_TEST_GROUP(observer_unsubscribe);
  RUN_TEST_GROUP(observer_unsubscribe_with_arg);
  RUN_TEST_GROUP(observer_unsubscribe_with_u8_arg);
  RUN_TEST_GROUP(observer_notice);
  RUN_TEST_GROUP(observer_notice_with_arg);
  RUN_TEST_GROUP(observer_notice_with_u8_arg);
}