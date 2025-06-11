#include "main.h"

START_TEST(test_1) {
  userInput(Start, 0);

  const BackGameInfo_t *game_state = updateCurrentState();

  int x_prev = game_state->figure.x;
  int y_prev = game_state->figure.y;

  if (able_to_move_left()) {
    userInput(Left, 0);

    game_state = updateCurrentState();

    ck_assert_msg(check_move_left(x_prev, y_prev),
                  RED_BCGR "function failed" RESET_COLORS);
  }

  free_game();
}
END_TEST

START_TEST(test_2) {
  userInput(Start, 0);

  const BackGameInfo_t *game_state = updateCurrentState();

  int x_prev = game_state->figure.x;
  int y_prev = game_state->figure.y;

  if (able_to_move_right()) {
    userInput(Right, 0);

    game_state = updateCurrentState();

    ck_assert_msg(check_move_right(x_prev, y_prev),
                  RED_BCGR "function failed" RESET_COLORS);
  }

  free_game();
}
END_TEST

START_TEST(test_3) {
  userInput(Start, 0);

  while (able_to_move_left()) {
    userInput(Left, 0);
  }

  const BackGameInfo_t *game_state = updateCurrentState();

  int x_prev = game_state->figure.x;
  int y_prev = game_state->figure.y;

  userInput(Left, 0);

  ck_assert_msg(check_no_move(x_prev, y_prev),
                RED_BCGR "function failed" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_4) {
  userInput(Start, 0);

  const BackGameInfo_t *game_state = updateCurrentState();

  int x_prev = game_state->figure.x;
  int y_prev = game_state->figure.y;

  userInput(Empty, 0);

  ck_assert_msg(check_move_down(x_prev, y_prev),
                RED_BCGR "function failed 1" RESET_COLORS);

  game_state = updateCurrentState();

  x_prev = game_state->figure.x;
  y_prev = game_state->figure.y;

  userInput(Empty, 0);

  ck_assert_msg(check_move_down(x_prev, y_prev),
                RED_BCGR "function failed 2" RESET_COLORS);

  free_game();
}
END_TEST

START_TEST(test_5) {
  userInput(Start, 0);

  const BackGameInfo_t *game_state = updateCurrentState();

  int figure_copy[BLOCK_SIZE][BLOCK_SIZE] = {0};

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      figure_copy[i][j] = game_state->figure.matrix[i][j];
    }
  }

  if (able_to_turn_left()) {
    userInput(Action, 0);
  }

  ck_assert_msg(check_turn(figure_copy),
                RED_BCGR "function failed" RESET_COLORS);

  free_game();
}
END_TEST

Suite *moving_test(void) {
  Suite *suite = suite_create(GREEN_BCGR WHITE_FONT
                              ">     moving_test     <" RESET_COLORS);

  TCase *tcase_core = tcase_create("moving_test");

  tcase_add_test(tcase_core, test_1);
  tcase_add_test(tcase_core, test_2);
  tcase_add_test(tcase_core, test_3);
  tcase_add_test(tcase_core, test_4);
  tcase_add_test(tcase_core, test_5);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int check_move_left(int x_prev, int y_prev) {
  const BackGameInfo_t *game_state = updateCurrentState();

  return (x_prev == game_state->figure.x + 1) &&
         (y_prev == game_state->figure.y - 1);
}

int check_move_right(int x_prev, int y_prev) {
  const BackGameInfo_t *game_state = updateCurrentState();

  return (x_prev == game_state->figure.x - 1) &&
         (y_prev == game_state->figure.y - 1);
}

int check_move_down(int x_prev, int y_prev) {
  const BackGameInfo_t *game_state = updateCurrentState();

  return (x_prev == game_state->figure.x) &&
         (y_prev == game_state->figure.y - 1);
}

int check_no_move(int x_prev, int y_prev) {
  const BackGameInfo_t *game_state = updateCurrentState();

  return (x_prev == game_state->figure.x) && (y_prev || !y_prev);
}

int check_turn(int m[][BLOCK_SIZE]) {
  const BackGameInfo_t *game_state = updateCurrentState();

  int right_matrix[BLOCK_SIZE][BLOCK_SIZE] = {0};

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      right_matrix[j][BLOCK_SIZE - i - 1] = game_state->figure.matrix[i][j];
    }
  }

  normalize_matrix(right_matrix);
  normalize_matrix(right_matrix);
  normalize_matrix(right_matrix);

  int flag = 1;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      flag = flag && (m[i][j] == right_matrix[i][j]);
    }

    if (!flag) {
      break;
    }
  }

  return flag;
}