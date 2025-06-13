#include "attaching.h"

#include "free_game.h"
#include "main_header.h"
#include "spawn.h"

/**
 * @brief Copies the top layers of the game field down by one layer.
 *
 * This function shifts all layers above the specified layer number down by one,
 * effectively removing the specified layer and filling the top layer with
 * zeros.
 *
 * @param layer_number The layer number to be removed. All layers above this
 * layer will be shifted down.
 */
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

/**
 * @brief Removes full layers from the game field and updates the score.
 *
 * This function checks each layer of the game field for completeness. If a
 * layer is completely filled, it is removed, and all layers above it are
 * shifted down. The score is updated based on the number of layers removed. If
 * the score exceeds the high score, the high score is updated.
 */
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
    case 5:
      game_state->score += 1600;
      break;
    case 6:
      game_state->score += 1700;
      break;
    case 7:
      game_state->score += 1800;
      break;

    default:
      break;
  }

  update_level();

  if (game_state->score > game_state->high_score) {
    game_state->high_score = game_state->score;
    update_high_score();
  }
}

/**
 * @brief Updates the high score in the score file.
 *
 * This function writes the current high score to a specified text file. If the
 * file is successfully opened, the high score is written to it.
 */
void update_high_score() {
  FILE *file_score = fopen("./brick_game/tetris/high_score.txt", "w");
  BackGameInfo_t *game_state = get_game_state();

  if (file_score) {
    fprintf(file_score, "%d", game_state->high_score);

    fclose(file_score);
  }
}

/**
 * @brief Updates the game level based on the current score.
 *
 * This function calculates the new level based on the current score. If the new
 * level is greater than the current level, it updates the level and increases
 * the game speed.
 */
void update_level() {
  BackGameInfo_t *game_state = get_game_state();
  int new_level = game_state->score / 600;

  if (new_level > game_state->level) {
    game_state->level = new_level;
    game_state->speed++;
  }
}

/**
 * @brief Attaches the current block to the game field.
 *
 * This function places the current block onto the game field based on its
 * position. It updates the game state to indicate that the block is being
 * attached. After placing the block, it checks for any full layers in the game
 * field and removes them. If the game is over after attaching the block, the
 * game state is set to GAME_OVER and resources are freed. Otherwise, a new
 * block is spawned.
 */
void attach_block() {
  BackGameInfo_t *game_state = get_game_state();

  game_state->fsm_state = ATTACHING;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game_state->figure.matrix[i][j]) {
        game_state->field[(game_state->figure.y + i) % FIELD_SIZE_Y]
                         [(game_state->figure.x + j) % FIELD_SIZE_X] =
            (int)game_state->figure.color;
      }
    }
  }

  remove_full_layers();

  if (game_is_over()) {
    game_state->fsm_state = GAME_OVER;
    free_game();
  } else {
    spawn_block();
  }
}

/**
 * @brief Checks if the game is over.
 *
 * This function determines if the game is over by checking if the top layer has
 * been achieved or if the maximum level has been reached.
 *
 * @return 1 if the game is over, 0 otherwise.
 */
int game_is_over() { return achieved_top_layer() || achieved_max_level(); }

/**
 * @brief Checks if the top layer has been achieved.
 *
 * This function checks if any part of the current block has reached the top of
 * the game field. It counts the number of empty rows at the top of the field
 * and compares it to the position of the current block.
 *
 * @return 1 if the top layer has been achieved, 0 otherwise.
 */
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

    if (last_i >= 0 && j < BLOCK_SIZE && game_state->figure.matrix[last_i][j]) {
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

/**
 * @brief Checks if the maximum level has been reached.
 *
 * This function checks if the current game level is equal to the maximum level
 * (level 10).
 *
 * @return 1 if the maximum level has been reached, 0 otherwise.
 */
int achieved_max_level() {
  BackGameInfo_t *game_state = get_game_state();

  return game_state->level == 10;
}