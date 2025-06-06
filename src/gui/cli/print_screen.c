#include "print_screen.h"

void print_start_screen() {
  mvprintw(10, 10, "Press ENTER to start\n");
  mvprintw(11, 10, "Press ESCAPE to quit\n");
}

void init_colors() {
  start_color();
  init_pair(RED, COLOR_RED, COLOR_RED);
  init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
  init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
  init_pair(PINK, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(PURPLE, COLOR_CYAN, COLOR_CYAN);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
}

void print_cell(int color_code, int x, int y, char sign) {
  if (color_code) {
    attron(COLOR_PAIR(color_code));

    mvaddch(BORDER_LEFT + x, BORDER_UP + y, sign);

    attroff(COLOR_PAIR(color_code));
  } else {
    mvaddch(BORDER_LEFT + x, BORDER_UP + y, sign);
  }
}

void print_field(int color_flag, BackGameInfo_t game_state) {
  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (game_state.field[i][j] && color_flag) {
        print_cell(game_state.field[i][j], i, j * 2, '[');
        print_cell(game_state.field[i][j], i, j * 2 + 1, ']');
      } else if (game_state.field[i][j] && color_flag == 0) {
        print_cell(0, i, j * 2, '[');
        print_cell(0, i, j * 2 + 1, ']');
      } else {
        print_cell(0, i, j * 2, '-');
        print_cell(0, i, j * 2 + 1, '-');
      }
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++)
      if (game_state.figure.matrix[i][j] && color_flag) {
        print_cell(game_state.figure.color, game_state.figure.y + i,
                   (game_state.figure.x + j) * 2, '[');
        print_cell(game_state.figure.color, game_state.figure.y + i,
                   (game_state.figure.x + j) * 2 + 1, ']');
      } else if (game_state.figure.matrix[i][j] && color_flag == 0) {
        print_cell(0, game_state.figure.y + i, (game_state.figure.x + j) * 2,
                   '[');
        print_cell(0, game_state.figure.y + i,
                   (game_state.figure.x + j) * 2 + 1, ']');
      } /*
      else {
        print_cell(0, game_state.figure.y + i,
                   (game_state.figure.x + j) * 2, '[');
        print_cell(0, game_state.figure.y + i,
                   (game_state.figure.x + j) * 2 + 1, ']');
      } */
  }
}

void print_info_screen(BackGameInfo_t game_state) {
  for (int i = 0; i < 12; i++) {
    mvaddch(BORDER_UP + i, BORDER_RIGHT * 2, '|');
  }

  int k = 0;

  mvprintw(BORDER_UP + k++, BORDER_RIGHT * 2 + 1, "game_info:");

  k++;

  mvprintw(BORDER_UP + k++, BORDER_RIGHT * 2 + 1, "score: %d",
           game_state.score);
  mvprintw(BORDER_UP + k++, BORDER_RIGHT * 2 + 1, "max_score: %d",
           game_state.high_score);
  mvprintw(BORDER_UP + k++, BORDER_RIGHT * 2 + 1, "level: %d",
           game_state.level);
  mvprintw(BORDER_UP + k++, BORDER_RIGHT * 2 + 1, "speed: %d",
           game_state.speed);

  k++;

  mvprintw(BORDER_UP + k++, BORDER_RIGHT * 2 + 1, "next_block:");

  k++;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game_state.next_block && game_state.next_block[i][j]) {
        mvaddch(BORDER_UP + k + i, (BORDER_RIGHT + j) * 2 + 2, '[');
        mvaddch(BORDER_UP + k + i, (BORDER_RIGHT + j) * 2 + 3, ']');
      }
    }
  }
}

void print_current_state(BackGameInfo_t game_state) {
  clear();
  print_field(1, game_state);
  print_info_screen(game_state);
}

void print_pause_screen(BackGameInfo_t game_state) {
  clear();

  mvprintw(BORDER_UP - 1, BORDER_LEFT, "PAUSE: press 'p' to continue");

  print_field(1, game_state);
  print_info_screen(game_state);
}

void print_final_screen(BackGameInfo_t game_state) {
  clear();

  print_field(0, game_state);

  for (int i = 0; i < 5; i++) {
    mvaddch(BORDER_UP + i, BORDER_RIGHT * 2, '|');
  }

  int k = 0;
  mvprintw(BORDER_UP + k++, BORDER_RIGHT * 2 + 1, "GAME_OVER");
  mvprintw(BORDER_UP + k++, BORDER_RIGHT * 2 + 1, "YOUR_SCORE: %d",
           game_state.score);
  mvprintw(BORDER_UP + k++, BORDER_RIGHT * 2 + 1, "HIGHEST_SCORE: %d",
           game_state.high_score);
  mvprintw(BORDER_UP + k++, BORDER_RIGHT * 2 + 1, "ACHIEVED_LEVEL: %d",
           game_state.level);
  mvprintw(BORDER_UP + k++, BORDER_RIGHT * 2 + 1, "PRESS ESC TO EXIT GAME");
}