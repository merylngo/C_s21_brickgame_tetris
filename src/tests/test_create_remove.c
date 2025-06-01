#include "main.h"

START_TEST(test_1) {
  BackGameInfo_t* game_state = get_game_state();

  matrix_status status =
      create_matrix(&game_state->field, FIELD_SIZE_Y, FIELD_SIZE_X);

  ck_assert_msg(status == NORM, RED_BCGR "function failed 1" RESET_COLORS);
  ck_assert_msg(game_state->field != NULL,
                RED_BCGR "function failed 2" RESET_COLORS);

  remove_matrix(game_state->field, FIELD_SIZE_Y);
  // free_game();
}
END_TEST

START_TEST(test_2) {
  BackGameInfo_t* game_state = get_game_state();

  matrix_status status =
      create_matrix(&game_state->next_block, BLOCK_SIZE, BLOCK_SIZE);

  ck_assert_msg(status == NORM, RED_BCGR "function failed 1" RESET_COLORS);
  ck_assert_msg(game_state->next_block != NULL,
                RED_BCGR "function failed 2" RESET_COLORS);

  remove_matrix(game_state->next_block, BLOCK_SIZE);

  // free_game();
}
END_TEST

START_TEST(test_3) {
  BackGameInfo_t* game_state = get_game_state();

  matrix_status status =
      create_matrix(&game_state->figure.matrix, BLOCK_SIZE, BLOCK_SIZE);

  ck_assert_msg(status == NORM, RED_BCGR "function failed 1" RESET_COLORS);
  ck_assert_msg(game_state->figure.matrix != NULL,
                RED_BCGR "function failed 2" RESET_COLORS);

  remove_matrix(game_state->figure.matrix, BLOCK_SIZE);
  // free_game();
}
END_TEST

Suite* create_remove_test(void) {
  Suite* suite = suite_create(GREEN_BCGR WHITE_FONT
                              ">     create_&_remove     <" RESET_COLORS);

  TCase* tcase_core = tcase_create("test_create_&_remove");

  tcase_add_test(tcase_core, test_1);
  tcase_add_test(tcase_core, test_2);
  tcase_add_test(tcase_core, test_3);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
