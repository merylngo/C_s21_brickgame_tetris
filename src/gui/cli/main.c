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
  timeout(300);
}

void play_game() {
  char start_key;

  while ((start_key = getch()) && start_key != '\n') {
    print_start_screen();
  }

  userInput(Start, false);
  GameInfo_t game_state = {0};

  do {
    char command = getch();
    UserAction_t action = get_action(command);
    userInput(action, false);

    game_state = updateCurrentState();

    print_current_state(&game_state);
  } while (game_not_over(&game_state));

  char finish_key;

  while ((finish_key = getch()) && finish_key != 27) {
    print_final_screen(&game_state);
  }
}

UserAction_t get_action(char command) {
  UserAction_t action = 0;

  switch (command) {
    case '\n':
      action = Start;
      break;
    case 'p':
      action = Pause;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case KEY_UP:
      action = Action;
      break;

    default:
      break;
  }

  return action;
}