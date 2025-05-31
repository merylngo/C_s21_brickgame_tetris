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
  // nodelay(stdscr, TRUE);
  timeout(1000);
}

void play_game() {
  /*
  int start_key;

  while ((start_key = getch()) && start_key != '\n') {
    print_start_screen();
  }

  */
  clear();

  userInput(Start, false);
  BackGameInfo_t *game_state;

  do {
    int command = getch();
    UserAction_t action = get_action(command);

    userInput(action, false);

    game_state = updateCurrentState();

    print_current_state(*game_state);
  } while (game_not_over(game_state));

  int finish_key;

  while ((finish_key = getch()) && finish_key != 27) {
    print_final_screen(*game_state);
  }
}

UserAction_t get_action(int command) {
  UserAction_t action = 0;

  if (command == KEY_LEFT) {
    action = Left;
  }

  switch (command) {
    case '\n':
      action = Start;
      break;
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
    case KEY_DOWN:
      action = Down;
      break;

    default:
      action = 0;
      break;
  }

  return action;
}

int game_not_over(BackGameInfo_t *game_state) {
  return game_state->fsm_state == GAME_OVER;
}