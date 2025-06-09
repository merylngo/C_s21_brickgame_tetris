#include "main.h"

// [][][][]
static int block_1[BLOCK_SIZE][BLOCK_SIZE] = {
    {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

// [][]
// [][]
static int block_2[BLOCK_SIZE][BLOCK_SIZE] = {
    {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

// [][]
//   [][]
static int block_3[BLOCK_SIZE][BLOCK_SIZE] = {
    {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

// [][][]
// []
static int block_4[BLOCK_SIZE][BLOCK_SIZE] = {
    {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

//   []
// [][][]
static int block_5[BLOCK_SIZE][BLOCK_SIZE] = {
    {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

//   [][]
// [][]
static int block_6[BLOCK_SIZE][BLOCK_SIZE] = {
    {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

// [][][]
//     []
static int block_7[BLOCK_SIZE][BLOCK_SIZE] = {
    {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

START_TEST(test_1) {
  userInput(Start, 0);

  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_2) {
  userInput(Start, 0);

  spawn_block();

  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_3) {
  userInput(Start, 0);

  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);
  spawn_block();
  ck_assert_msg(!check_equality(), RED_BCGR "function failed" RESET_COLORS);

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

int check_equality() {
  const BackGameInfo_t* game_state = updateCurrentState();
  int res = 0;

  res |= equal_matrix(game_state->figure.matrix, block_1);
  res |= equal_matrix(game_state->figure.matrix, block_2);
  res |= equal_matrix(game_state->figure.matrix, block_3);
  res |= equal_matrix(game_state->figure.matrix, block_4);
  res |= equal_matrix(game_state->figure.matrix, block_5);
  res |= equal_matrix(game_state->figure.matrix, block_6);
  res |= equal_matrix(game_state->figure.matrix, block_7);

  return res;
}

int equal_matrix(int** m1, int m2[][BLOCK_SIZE]) {
  int flag = 1;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      flag &= (m1[i][j] != m2[i][j]);
    }

    if (!flag) {
      break;
    }
  }

  return flag;
}