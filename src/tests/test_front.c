#include "main.h"

START_TEST(test_1) {
  userInput(Start, 0);
  userInput(Pause, 0);

  const BackGameInfo_t* game_state = update_current_state();

  ck_assert_msg(game_state->pause, RED_BCGR "function failed 1" RESET_COLORS);

  userInput(Pause, 0);

  game_state = update_current_state();

  ck_assert_msg(!game_state->pause, RED_BCGR "function failed 2" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_2) {
  userInput(Start, 0);
  userInput(Terminate, 0);

  const BackGameInfo_t* game_state = update_current_state();

  ck_assert_msg(game_state->fsm_state == GAME_OVER,
                RED_BCGR "function failed 1" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_3) {
  userInput(Start, 0);
  userInput(Pause, 0);

  const BackGameInfo_t* game_state = update_current_state();

  ck_assert_msg(game_state->pause, RED_BCGR "function failed 1" RESET_COLORS);

  userInput(Terminate, 0);

  game_state = update_current_state();

  ck_assert_msg(game_state->fsm_state == GAME_OVER,
                RED_BCGR "function failed 2" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_4) {
  userInput(Start, 0);
  userInput(Left, 0);
  userInput(Pause, 0);

  const BackGameInfo_t* game_state = update_current_state();

  ck_assert_msg(game_state->pause, RED_BCGR "function failed 1" RESET_COLORS);

  userInput(Pause, 0);

  game_state = update_current_state();

  ck_assert_msg(!game_state->pause, RED_BCGR "function failed 2" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_5) {
  userInput(Start, 0);
  userInput(Left, 0);
  userInput(Pause, 0);

  const BackGameInfo_t* game_state = update_current_state();
  GameInfo_t game_info = updateCurrentState();

  ck_assert_msg(game_state->pause == game_info.pause,
                RED_BCGR "function failed 1" RESET_COLORS);
  ck_assert_msg(game_state->level == game_info.level,
                RED_BCGR "function failed 2" RESET_COLORS);
  ck_assert_msg(game_state->speed == game_info.speed,
                RED_BCGR "function failed 3" RESET_COLORS);
  ck_assert_msg(game_state->score == game_info.score,
                RED_BCGR "function failed 4" RESET_COLORS);
  ck_assert_msg(game_state->high_score == game_info.high_score,
                RED_BCGR "function failed 5" RESET_COLORS);

  int flag = 1;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      flag = flag && (game_info.next[i][j] == game_state->next_block[i][j]);
    }
  }

  free_game_info(game_info);
  free_game();

  ck_assert_msg(flag, RED_BCGR "function failed 6" RESET_COLORS);
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
  tcase_add_test(tcase_core, test_5);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
