#include "main.h"

START_TEST(test_1) {
  ck_assert_msg(1, RED_BCGR "function failed 1" RESET_COLORS);
}
END_TEST

Suite* front_frunctions_test(void) {
  Suite* suite = suite_create(GREEN_BCGR WHITE_FONT
                              ">     front_frunctions     <" RESET_COLORS);

  TCase* tcase_core = tcase_create("front_frunctions_test");

  tcase_add_test(tcase_core, test_1);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
