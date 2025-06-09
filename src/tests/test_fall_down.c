#include "main.h"

START_TEST(test_1) {
  /*
  BackGameInfo_t* game_state = get_game_state();

  init_game();

  copy_matrix(block_1, game_state->next_block);
  init_current_block();
  fall_down();

  // проверка - разницу матриц 10 на 20 и наложением найти фигуру а матрицу 10
  на 20 просто генерить

  ck_assert_msg(game_state->field != NULL,
                RED_BCGR "function failed 1" RESET_COLORS);

  free_game();
  */

  ck_assert_msg(1, RED_BCGR "function failed 1" RESET_COLORS);
}
END_TEST

Suite* fall_down_test(void) {
  Suite* suite = suite_create(GREEN_BCGR WHITE_FONT
                              ">     fall_down_test     <" RESET_COLORS);

  TCase* tcase_core = tcase_create("fall_down_test");

  tcase_add_test(tcase_core, test_1);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
