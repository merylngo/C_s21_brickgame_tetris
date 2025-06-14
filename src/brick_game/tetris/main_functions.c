/**
 * @file main_functions.c
 * @brief file with input-output lib functionc
 *
 */

#include "free_game.h"
#include "init_game.h"
#include "main_header.h"
#include "moving.h"
#include "spawn.h"

/**
 * @brief Handles user input actions for the game.
 *
 * This function processes user actions such as starting, pausing, terminating
 * the game, or moving a block based on the specified action. It updates the
 * game state accordingly.
 *
 * @param action The action to be performed by the user. This should be one of
 * the values from the UserAction_t enumeration, which includes:
 *               - Start: Initializes the game and spawns a new block.
 *               - Pause: Toggles the pause state of the game.
 *               - Terminate: Sets the game state to GAME_OVER and frees game
 * resources.
 *               - Any other value: Moves the block according to the specified
 * action.
 * @param hold An integer parameter that is currently unused. It is included for
 * future compatibility or extension of the function.
 */
void userInput(UserAction_t action, int hold) {
  (void)hold;
  BackGameInfo_t *game_state = get_game_state();

  if (action == Start) {
    init_game();
    spawn_block();
  } else if (action == Pause) {
    game_state->pause = !game_state->pause;
  } else if (action == Terminate) {
    game_state->fsm_state = GAME_OVER;
    free_game();
  } else {
    move_block(action);
  }
}

/**
 * @brief Retrieves the current game state.
 *
 * This function returns a constant pointer to the current game state structure,
 * which contains information about the game's status and settings. The returned
 * pointer points to a static instance of the game state, ensuring that the same
 * state is accessed throughout the game's lifecycle. It used in tests in order
 * to see the user's action result on game_state
 *
 * @return A constant pointer to the current BackGameInfo_t structure
 * representing the game state.
 */
const BackGameInfo_t *update_current_state() {
  const BackGameInfo_t *game_state = get_game_state();
  return game_state;
}

/**
 * @brief Gets a pointer to the game state.
 *
 * This function initializes and returns a pointer to a static instance of the
 * BackGameInfo_t structure. The static instance ensures that the game state
 * persists across multiple calls to this function, allowing for consistent
 * access to the game's state information.
 *
 * @return A pointer to the BackGameInfo_t structure representing the game
 * state.
 */
BackGameInfo_t *get_game_state() {
  static BackGameInfo_t game_state = {0};

  return &game_state;
}

/**
 * @brief Updates the current game state and returns a GameInfo_t structure.
 *
 * This function retrieves the current game state from the static game state
 * instance, allocates memory for a new GameInfo_t structure, and populates it
 * with the current game information, including level, speed, high score, score,
 * and the game field. It also handles the creation of matrices for the game
 * field and the next block.
 *
 * If the game is in the GAME_OVER state, the pause value is set to 2. The
 * function checks the status of the matrices and updates the game field based
 * on the current figure's position and color. If the matrix creation fails, the
 * game state is set to GAME_OVER.
 *
 * @return A GameInfo_t structure containing the updated game information. The
 * caller is responsible for freeing the allocated memory for the GameInfo_t
 * structure.
 */
GameInfo_t updateCurrentState() {
  BackGameInfo_t *game_state = get_game_state();
  GameInfo_t game_info;

  game_info.field = game_info.next = NULL;

  game_info.level = game_state->level;
  game_info.speed = game_state->speed;
  game_info.high_score = game_state->high_score;
  game_info.score = game_state->score;

  matrix_status field_status =
      create_matrix(&game_info.field, FIELD_SIZE_Y, FIELD_SIZE_X);
  matrix_status next_block_status =
      create_matrix(&game_info.next, BLOCK_SIZE, BLOCK_SIZE);

  if (field_status == NORM && next_block_status == NORM) {
    if (game_state->fsm_state == GAME_OVER) {
      game_info.pause = 2;
    } else {
      game_info.pause = game_state->pause;
      copy_field_game_info(&game_info);
      copy_matrix_pt(game_state->next_block, &game_info.next);
    }
  } else {
    game_state->fsm_state = GAME_OVER;
  }

  return game_info;
}

void copy_field_game_info(GameInfo_t *game_info) {
  BackGameInfo_t *game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      game_info->field[i][j] = game_state->field[i][j];
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game_state->figure.matrix[i][j] &&
          game_info->field[(game_state->figure.y + i) % FIELD_SIZE_Y]
                          [(game_state->figure.x + j) % FIELD_SIZE_X] == 0) {
        game_info->field[(game_state->figure.y + i) % FIELD_SIZE_Y]
                        [(game_state->figure.x + j) % FIELD_SIZE_X] =
            (int)game_state->figure.color;
      }
    }
  }
}