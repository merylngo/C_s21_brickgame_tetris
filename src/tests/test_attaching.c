#include "main.h"

START_TEST(test_1) {
  userInput(Start, 0);

  create_field_1();

  int block_before[BLOCK_SIZE][BLOCK_SIZE] = {0};

  const BackGameInfo_t* game_state = updateCurrentState();

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block_before[i][j] = game_state->figure.matrix[i][j];
    }
  }

  userInput(Down, 0);

  // printf("score == %d\n", game_state->score);

  ck_assert_msg(check_block_on_field_after_clean(block_before) &&
                    game_state->score == 100,
                RED_BCGR "function failed 1" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_2) {
  userInput(Start, 0);

  create_field_2();

  int block_before[BLOCK_SIZE][BLOCK_SIZE] = {0};

  const BackGameInfo_t* game_state = updateCurrentState();

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block_before[i][j] = game_state->figure.matrix[i][j];
    }
  }

  userInput(Down, 0);

  // printf("score == %d\n", game_state->score);

  ck_assert_msg(check_block_on_field_after_clean(block_before) &&
                    game_state->score == 300,
                RED_BCGR "function failed 1" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_3) {
  userInput(Start, 0);

  create_field_3();

  int block_before[BLOCK_SIZE][BLOCK_SIZE] = {0};

  const BackGameInfo_t* game_state = updateCurrentState();

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block_before[i][j] = game_state->figure.matrix[i][j];
    }
  }

  userInput(Down, 0);

  // printf("score == %d\n", game_state->score);

  ck_assert_msg(check_block_on_field_after_clean(block_before) &&
                    game_state->score == 700 && game_state->level == 1,
                RED_BCGR "function failed 1" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_4) {
  userInput(Start, 0);

  create_field_4();

  int block_before[BLOCK_SIZE][BLOCK_SIZE] = {0};

  const BackGameInfo_t* game_state = updateCurrentState();

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block_before[i][j] = game_state->figure.matrix[i][j];
    }
  }

  userInput(Down, 0);

  ck_assert_msg(check_block_on_field_after_clean(block_before) &&
                    game_state->score == 1500 && game_state->level == 2,
                RED_BCGR "function failed 1" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_5) {
  userInput(Start, 0);

  create_field_5();

  int block_before[BLOCK_SIZE][BLOCK_SIZE] = {0};

  const BackGameInfo_t* game_state = updateCurrentState();

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block_before[i][j] = game_state->figure.matrix[i][j];
    }
  }

  userInput(Down, 0);

  ck_assert_msg(check_block_on_field_after_clean(block_before) &&
                    game_state->score == 3100 && game_state->level == 5,
                RED_BCGR "function failed 1" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_6) {
  userInput(Start, 0);

  create_field_full_no_one();

  const BackGameInfo_t* game_state = updateCurrentState();

  userInput(Down, 0);

  printf("game_state = %d\n", game_state->fsm_state);

  ck_assert_msg(game_state->fsm_state == GAME_OVER,
                RED_BCGR "function failed" RESET_COLORS);

  free_game();
}
END_TEST

Suite* attaching_test(void) {
  Suite* suite = suite_create(GREEN_BCGR WHITE_FONT
                              ">     attaching_test     <" RESET_COLORS);

  TCase* tcase_core = tcase_create("attaching_test");

  tcase_add_test(tcase_core, test_1);
  tcase_add_test(tcase_core, test_2);
  tcase_add_test(tcase_core, test_3);
  tcase_add_test(tcase_core, test_4);
  tcase_add_test(tcase_core, test_5);
  tcase_add_test(tcase_core, test_6);

  suite_add_tcase(suite, tcase_core);

  return suite;
}