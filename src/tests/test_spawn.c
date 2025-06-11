#include "main.h"

START_TEST(test_1) {
  userInput(Start, 0);

  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_2) {
  userInput(Start, 0);

  const BackGameInfo_t* game_state = updateCurrentState();

  spawn_block();

  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_3) {
  userInput(Start, 0);

  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(check_equality(), RED_BCGR "function failed" RESET_COLORS);

  free_game();
}
END_TEST

Suite* spawn_test(void) {
  Suite* suite =
      suite_create(GREEN_BCGR WHITE_FONT ">     spawn_test     <" RESET_COLORS);

  TCase* tcase_core = tcase_create("spawn_test");

  tcase_add_test(tcase_core, test_1);
  tcase_add_test(tcase_core, test_2);
  tcase_add_test(tcase_core, test_3);

  suite_add_tcase(suite, tcase_core);

  return suite;
}