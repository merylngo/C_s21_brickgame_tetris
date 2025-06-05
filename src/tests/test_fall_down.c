#include "main.h"
// [][][][]
static block_1[BLOCK_SIZE][BLOCK_SIZE] = {
    {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

// [][]
// [][]
static block_2[BLOCK_SIZE][BLOCK_SIZE] = {
    {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

// [][]
//   [][]
static block_3[BLOCK_SIZE][BLOCK_SIZE] = {
    {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

// [][][]
// []
static block_4[BLOCK_SIZE][BLOCK_SIZE] = {
    {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

//   []
// [][][]
static block_5[BLOCK_SIZE][BLOCK_SIZE] = {
    {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

//   [][]
// [][]
static block_6[BLOCK_SIZE][BLOCK_SIZE] = {
    {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

// [][][]
//     []
static block_7[BLOCK_SIZE][BLOCK_SIZE] = {
    {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

START_TEST(test_1) {
  BackGameInfo_t* game_state = get_game_state();

  init_game();

  spawn_block();

  ck_assert_msg(game_state->field != NULL,
                RED_BCGR "function failed 2" RESET_COLORS);

  free_game();
}
END_TEST

Suite* fall_down_test(void) {
  Suite* suite =
      suite_create(GREEN_BCGR WHITE_FONT ">     fall_down     <" RESET_COLORS);

  TCase* tcase_core = tcase_create("test_fall_down");

  tcase_add_test(tcase_core, test_1);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
