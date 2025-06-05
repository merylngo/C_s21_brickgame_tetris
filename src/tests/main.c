#include "main.h"

int main(void) {
  int failed = 0;
  int total = 0;

  Suite* list[] = {init_game_test(), fall_down_test(), NULL};

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

void generate_field() {
  BackGameInfo_t* game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (i > FIELD_SIZE_Y / 2) {
        game_state->field[i][j] = rand() % 5;
      }
    }
  }
}

int check_block_on_field(int field_before[][FIELD_SIZE_X]) {
  BackGameInfo_t* game_state = get_game_state();
  int result = 1;

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      game_state->field[i][j] -= field_before[i][j];
    }
  }

  int i_bl = 0, j_bl = 0;

  for (; i_bl < BLOCK_SIZE; i_bl++) {
    for (; j_bl < BLOCK_SIZE; j_bl++) {
      if (game_state->figure.matrix[i_bl][j_bl]) {
        break;
      }
    }
  }

  int i_fi = 0, j_fi = 0;

  for (; i_fi < FIELD_SIZE_Y; i_fi++) {
    for (; j_fi < FIELD_SIZE_X; j_fi++) {
      if (game_state->field[i_fi][j_fi]) {
        break;
      }
    }
  }

  // в этот момент нашли координаты начал фигуры - вопрос как проверить
  // наложение?

  return result;
}