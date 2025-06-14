#include "main.h"

int main(void) {
  init_cli();
  play_game();
  endwin();

  return 0;
}

void init_cli() {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  cbreak();
  init_colors();
  nodelay(stdscr, TRUE);
}

void play_game() {
  int game_status = PLAYING_STATUS;
  int delay = START_TIMEOUT;

  timeout(delay);

  while (game_status != EXIT_STATUS) {
    on_start_state(&game_status);

    GameInfo_t game_info = {0};
    int delay = START_TIMEOUT;
    clock_t start_time = clock();

    while (game_status != GAMEOVER_STATUS && game_status != EXIT_STATUS) {
      timeout(delay);

      game_info = updateCurrentState();
      game_status = game_info.pause;

      if (game_status == PAUSE_STATUS) {
        on_pause_state(game_info);
      } else if (game_status == PLAYING_STATUS) {
        on_playing_state(game_info, &delay, &start_time);
      } else if (game_status == GAMEOVER_STATUS) {
        on_game_over_state(&game_status, game_info);
      }

      free_game_info(game_info);

      if (game_status == EXIT_STATUS || game_status == NEW_GAME_STATUS) {
        break;
      }
    }

    if (game_status == EXIT_STATUS) {
      break;
    }
  }
}

void on_start_state(int *game_status) {
  int start_key;

  while ((start_key = getch()) &&
         (start_key != START_KEY && start_key != FINISH_KEY)) {
    print_start_screen();
  }

  if (start_key == START_KEY) {
    userInput(Start, false);
  } else {
    userInput(Terminate, false);
    *game_status = EXIT_STATUS;
  }
}

void on_pause_state(GameInfo_t game_info) {
  print_pause_screen(game_info);

  int command = getch();
  UserAction_t action = get_action(command);

  if (action == Pause || action == Terminate) {
    userInput(action, false);
  }
}

void on_playing_state(GameInfo_t game_info, int *delay, clock_t *start_time) {
  print_current_state(game_info);
  *delay = START_TIMEOUT - DELAY_MUL * game_info.speed;

  double time = ((double)(clock() - *start_time)) / (CLOCKS_PER_SEC);
  time *= 100;

  if (time > ((double)(*delay)) / 1000) {
    userInput(Empty, false);
    *start_time = clock();
  }

  int command = getch();
  UserAction_t action = get_action(command);
  userInput(action, false);
}

void on_game_over_state(int *game_status, GameInfo_t game_info) {
  int finish_key;

  while ((finish_key = getch()) &&
         (finish_key != START_KEY && finish_key != FINISH_KEY)) {
    print_final_screen(game_info);
  }

  *game_status = (finish_key == FINISH_KEY) ? EXIT_STATUS : NEW_GAME_STATUS;
}

UserAction_t get_action(int command) {
  UserAction_t action = 0;

  switch (command) {
    case 'p':
      action = Pause;
      break;
    case 'q':
      action = Terminate;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_UP:
      action = Action;
      break;
    case 32:
      action = Down;
      break;

    default:
      action = Empty;
      break;
  }

  return action;
}

void remove_matrix_info(int **matrix, int rows) {
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