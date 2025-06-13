#include "main.h"

START_TEST(test_1) {
  userInput(Start, 0);

  const BackGameInfo_t* game_state = update_current_state();

  int field_before[FIELD_SIZE_Y][FIELD_SIZE_X] = {0};
  int block_before[BLOCK_SIZE][BLOCK_SIZE] = {0};

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      field_before[i][j] = game_state->field[i][j];
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block_before[i][j] = game_state->figure.matrix[i][j];
    }
  }

  userInput(Down, 0);

  ck_assert_msg(check_block_on_field(field_before, block_before),
                RED_BCGR "function failed" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_2) {
  userInput(Start, 0);

  const BackGameInfo_t* game_state = update_current_state();

  int field_before[FIELD_SIZE_Y][FIELD_SIZE_X] = {0};
  int block_before[BLOCK_SIZE][BLOCK_SIZE] = {0};

  spawn_block();
  spawn_block();
  spawn_block();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      field_before[i][j] = game_state->field[i][j];
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block_before[i][j] = game_state->figure.matrix[i][j];
    }
  }

  userInput(Down, 0);

  ck_assert_msg(check_block_on_field(field_before, block_before),
                RED_BCGR "function failed" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_3) {
  userInput(Start, 0);

  const BackGameInfo_t* game_state = update_current_state();

  int field_before[FIELD_SIZE_Y][FIELD_SIZE_X] = {0};
  int block_before[BLOCK_SIZE][BLOCK_SIZE] = {0};

  spawn_block();
  spawn_block();
  spawn_block();
  spawn_block();
  spawn_block();
  spawn_block();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      field_before[i][j] = game_state->field[i][j];
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block_before[i][j] = game_state->figure.matrix[i][j];
    }
  }

  userInput(Down, 0);

  ck_assert_msg(check_block_on_field(field_before, block_before),
                RED_BCGR "function failed" RESET_COLORS);

  free_game();
}
END_TEST

Suite* fall_down_test(void) {
  Suite* suite = suite_create(GREEN_BCGR WHITE_FONT
                              ">     fall_down_test     <" RESET_COLORS);

  TCase* tcase_core = tcase_create("fall_down_test");

  tcase_add_test(tcase_core, test_1);
  tcase_add_test(tcase_core, test_2);
  tcase_add_test(tcase_core, test_3);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
