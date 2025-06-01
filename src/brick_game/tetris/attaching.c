#include "blocks.h"
#include "main_header.h"

void copy_top_layers(int layer_number) {
  BackGameInfo_t *game_state = get_game_state();

  for (int i = layer_number; i > 0; i--) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      game_state->field[i][j] = game_state->field[i - 1][j];
    }
  }

  for (int j = 0; j < FIELD_SIZE_X; j++) {
    game_state->field[0][j] = 0;
  }
}

void remove_full_layers() {
  BackGameInfo_t *game_state = get_game_state();

  int layers[FIELD_SIZE_Y] = {0};
  int cnt_layers = 0;

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    int sum_in_layer = 0;

    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (game_state->field[i][j]) {
        sum_in_layer++;
      }
    }

    if (sum_in_layer == FIELD_SIZE_X) {
      layers[i] = 1;
      cnt_layers++;
    }
  }

  for (int k = 0; k < FIELD_SIZE_Y; k++) {
    if (layers[k]) {
      copy_top_layers(k);
      layers[k] = 0;
    }
  }

  int prev_score = game_state->score;

  switch (cnt_layers) {
    case 1:
      game_state->score += 100;
      break;
    case 2:
      game_state->score += 300;
      break;
    case 3:
      game_state->score += 700;
      break;
    case 4:
      game_state->score += 1500;
      break;
    default:
      break;
  }

  update_level(prev_score);
}

void update_level(int prev_score) {
  BackGameInfo_t *game_state = get_game_state();

  if (game_state->score - prev_score >= 600) {
    game_state->level++;
    game_state->speed++;
  }
}

void attach_block() {
  BackGameInfo_t *game_state = get_game_state();

  game_state->fsm_state = ATTACHING;

  // поставили блок на поле - не совсем корректно, но норм
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game_state->figure.matrix[i][j]) {
        game_state->field[(game_state->figure.y + i) % FIELD_SIZE_Y]
                         [(game_state->figure.x + j) % FIELD_SIZE_X] =
            (int)game_state->figure.color;
      }
    }
  }

  // освободили заполненные слои
  remove_full_layers();

  if (game_is_over()) {
    game_state->fsm_state = GAME_OVER;
  }
}

int game_is_over() { return achieved_top_layer() || achieved_max_level(); }

int achieved_top_layer() {
  BackGameInfo_t *game_state = get_game_state();

  int last_i;
  int cnt_empty_strings = 0;

  for (last_i = BLOCK_SIZE - 1; last_i > 0; last_i--) {
    int j;

    for (j = 0; j < BLOCK_SIZE; j++) {
      if (game_state->figure.matrix[last_i][j]) {
        break;
      }
    }

    if (game_state->figure.matrix[last_i][j]) {
      break;
    }
  }

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    int cnt = 0;

    for (int j = 0; j < FIELD_SIZE_X; j++) {
      cnt += game_state->field[i][j];
    }

    if (cnt == 0) {
      cnt_empty_strings++;
    } else {
      break;
    }
  }

  return cnt_empty_strings < last_i + 1;
}

int achieved_max_level() {
  BackGameInfo_t *game_state = get_game_state();

  return game_state->level == 10;
}