#include "main.h"

START_TEST(test_1) {
  userInput(Start, 0);
  userInput(Pause, 0);

  const BackGameInfo_t* game_state = updateCurrentState();

  ck_assert_msg(game_state->pause, RED_BCGR "function failed 1" RESET_COLORS);

  userInput(Pause, 0);

  game_state = updateCurrentState();

  ck_assert_msg(!game_state->pause, RED_BCGR "function failed 2" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_2) {
  userInput(Start, 0);
  userInput(Terminate, 0);

  const BackGameInfo_t* game_state = updateCurrentState();

  ck_assert_msg(game_state->fsm_state == GAME_OVER,
                RED_BCGR "function failed 1" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_3) {
  userInput(Start, 0);
  userInput(Pause, 0);

  const BackGameInfo_t* game_state = updateCurrentState();

  ck_assert_msg(game_state->pause, RED_BCGR "function failed 1" RESET_COLORS);

  userInput(Terminate, 0);

  game_state = updateCurrentState();

  ck_assert_msg(game_state->fsm_state == GAME_OVER,
                RED_BCGR "function failed 2" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_4) {
  userInput(Start, 0);
  userInput(Left, 0);
  userInput(Pause, 0);

  const BackGameInfo_t* game_state = updateCurrentState();

  ck_assert_msg(game_state->pause, RED_BCGR "function failed 1" RESET_COLORS);

  userInput(Pause, 0);

  game_state = updateCurrentState();

  ck_assert_msg(!game_state->pause, RED_BCGR "function failed 2" RESET_COLORS);

  free_game();
}
END_TEST

Suite* front_frunctions_test(void) {
  Suite* suite = suite_create(GREEN_BCGR WHITE_FONT
                              ">     front_frunctions     <" RESET_COLORS);

  TCase* tcase_core = tcase_create("front_frunctions_test");

  tcase_add_test(tcase_core, test_1);
  tcase_add_test(tcase_core, test_2);
  tcase_add_test(tcase_core, test_3);
  tcase_add_test(tcase_core, test_4);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
