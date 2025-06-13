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
    {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

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
    {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

int main(void) {
  int failed = 0;
  int total = 0;

  Suite* list[] = {init_free_test(),
                   spawn_test(),
                   moving_test(),
                   attaching_test(),
                   front_frunctions_test(),
                   fall_down_test(),
                   NULL};

  update_high_score_for_tests();

  for (int i = 0; list[i]; i++) {
    SRunner* sr = srunner_create(list[i]);

    srunner_set_fork_status(sr, CK_NOFORK);

    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    total += srunner_ntests_run(sr);

    srunner_free(sr);
  }

  printf(RED_BCGR WHITE_FONT " >>> FAILED : %-3d <<< " RESET_COLORS "\n",
         failed);
  printf(GREEN_BCGR WHITE_FONT " >>> SUCCESS: %-3d <<< " RESET_COLORS "\n",
         total - failed);
  printf(GREEN_BCGR WHITE_FONT " >>> TOTAL: %-3d <<<  " RESET_COLORS "\n",
         total);

  return 0;
}

void update_high_score_for_tests() {
  FILE* file_score = fopen("./brick_game/tetris/high_score.txt", "w");

  if (file_score) {
    fprintf(file_score, "%d", 0);

    fclose(file_score);
  }
}

void create_field_1() {
  BackGameInfo_t* game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (i == FIELD_SIZE_Y - 1) {
        game_state->field[i][j] = 1;
      }
    }
  }
}

void create_field_2() {
  BackGameInfo_t* game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (i >= FIELD_SIZE_Y - 2) {
        game_state->field[i][j] = 1;
      }
    }
  }
}

void create_field_3() {
  BackGameInfo_t* game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (i >= FIELD_SIZE_Y - 3) {
        game_state->field[i][j] = 1;
      }
    }
  }
}

void create_field_4() {
  BackGameInfo_t* game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (i >= FIELD_SIZE_Y - 4) {
        game_state->field[i][j] = 1;
      }
    }
  }
}

void create_field_5() {
  BackGameInfo_t* game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (i >= FIELD_SIZE_Y - 5) {
        game_state->field[i][j] = 1;
      }
    }
  }
}

void create_field_full_no_one() {
  BackGameInfo_t* game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X - 1; j++) {
      game_state->field[i][j] = 1;
    }
  }
}

int check_equality() {
  const BackGameInfo_t* game_state = update_current_state();
  int res = 0;

  res = res || equal_matrix(game_state->figure.matrix, block_1);
  res = res || equal_matrix(game_state->figure.matrix, block_2);
  res = res || equal_matrix(game_state->figure.matrix, block_3);
  res = res || equal_matrix(game_state->figure.matrix, block_4);
  res = res || equal_matrix(game_state->figure.matrix, block_5);
  res = res || equal_matrix(game_state->figure.matrix, block_6);
  res = res || equal_matrix(game_state->figure.matrix, block_7);

  return res;
}

int equal_matrix(int** m1, int m2[][BLOCK_SIZE]) {
  int flag = 1;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      flag = flag && (m1[i][j] == m2[i][j]);
    }
  }

  return flag;
}

int check_block_on_field_after_clean(int block_before[][BLOCK_SIZE]) {
  BackGameInfo_t* game_state = get_game_state();

  normalize_field(game_state->field);

  int result = 1;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      result = result &&
               (block_before[i][j] == (game_state->field[i][j] != 0 ? 1 : 0));
    }
  }

  return result;
}

int check_block_on_field(int field_before[][FIELD_SIZE_X],
                         int block_before[][BLOCK_SIZE]) {
  BackGameInfo_t* game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      game_state->field[i][j] -= field_before[i][j];
    }
  }

  normalize_field(game_state->field);

  int result = 1;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      result = result &&
               (block_before[i][j] == (game_state->field[i][j] != 0 ? 1 : 0));
    }
  }

  return result;
}

int first_row_sum(int** matrix) {
  int sum = 0;

  for (int j = 0; j < FIELD_SIZE_X; j++) {
    sum += matrix[0][j];
  }

  return sum;
}

int first_col_sum(int** matrix) {
  int sum = 0;

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    sum += matrix[i][0];
  }

  return sum;
}

void normalize_field(int** matrix) {
  int empty_flag = 0;

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      empty_flag = empty_flag || (matrix[i][j] != 0);
    }
  }

  if (empty_flag != 0) {
    while (first_row_sum(matrix) == 0) {
      for (int i = 1; i < FIELD_SIZE_Y; i++) {
        for (int j = 0; j < FIELD_SIZE_X; j++) {
          matrix[i - 1][j] = matrix[i][j];
        }
      }

      for (int j = 0; j < FIELD_SIZE_X; j++) {
        matrix[FIELD_SIZE_Y - 1][j] = 0;
      }
    }

    while (first_col_sum(matrix) == 0) {
      for (int i = 0; i < FIELD_SIZE_Y; i++) {
        for (int j = 1; j < FIELD_SIZE_X; j++) {
          matrix[i][j - 1] = matrix[i][j];
        }
      }

      for (int i = 0; i < FIELD_SIZE_Y; i++) {
        matrix[i][FIELD_SIZE_X - 1] = 0;
      }
    }
  }
}

void remove_matrix_info(int** matrix, int rows) {
  if (matrix) {
    for (int i = 0; i < rows; i++) {
      if (matrix[i]) {
        free(matrix[i]);
      }
    }

    free(matrix);
  }

  matrix = NULL;
}

void free_game_info(GameInfo_t game_info) {
  remove_matrix_info(game_info.field, FIELD_SIZE_Y);
  remove_matrix_info(game_info.next, BLOCK_SIZE);
}