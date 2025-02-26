#include <ncurses.h>

#define FIELD_SIZE_Y 20
#define FIELD_SIZE_X 20
#define BLOCK_SIZE 4

// typedef struct game_state_t
// {
//   int field_matrix[FIELD_SIZE_X][FIELD_SIZE_Y];
//   int current_block[BLOCK_SIZE][BLOCK_SIZE];
// } game_state_t;


void init_field(char field[FIELD_SIZE_X + 2][FIELD_SIZE_Y + 2]);
void print_field_with_x_y(char field[FIELD_SIZE_X + 2][FIELD_SIZE_Y + 2], int y,
                          int x);

void init_field(char field[FIELD_SIZE_X + 2][FIELD_SIZE_Y + 2]) {
  for (int i = 0; i <= FIELD_SIZE_X + 1; i++) {
    for (int j = 0; j <= FIELD_SIZE_Y + 1; j++) {
      if (i == 0 || i == FIELD_SIZE_X + 1) {
        field[i][j] = '|';
      } else if (j == 0 || j == FIELD_SIZE_Y + 1) {
        field[i][j] = '-';
      } else {
        field[i][j] = ' ';
      }
    }
  }
}


void print_field_with_x_y(char field[FIELD_SIZE_X + 2][FIELD_SIZE_Y + 2], int y,
                          int x) {
   for (int i = 0; i <= FIELD_SIZE_X + 1; i++) {
    for (int j = 0; j <= FIELD_SIZE_Y + 1; j++) {
      if (i == 0 || i == FIELD_SIZE_X + 1) {
        field[i][j] = '|';
      } else if (j == 0 || j == FIELD_SIZE_Y + 1) {
        field[i][j] = '-';
      } else {
        field[i][j] = ' ';
      }
    }
  }

  for (int i = 0; i <= FIELD_SIZE_X + 1; i++) {
    for (int j = 0; j <= FIELD_SIZE_Y + 1; j++) {
      mvaddch(y + j, x + i, field[i][j]);
    }
  }
}

void init_field(char field[FIELD_SIZE_X + 2][FIELD_SIZE_Y + 2]);

int main(void) {
  int x0 = 10, y0 = 10, x = 15, y = 15;
  int command = 0;
  // int cols, rows;

  initscr();
  keypad(stdscr, 1);
  noecho();
  curs_set(0);
  // getmaxyx(stdscr, rows, cols);  

   WINDOW *local_win;

    local_win = newwin(20, 20, 10, 10); // Создание нового окна
    box(local_win, 0, 0);

  char field[FIELD_SIZE_X + 2][FIELD_SIZE_Y + 2];

  init_field(field);

  do {
    clear();
    // printw("rows = %d\ncols=%d\n", rows, cols);

    print_field_with_x_y(field, y0, x0);

    mvwprintw(local_win, 1, 1, "HELLO ");
    //wrefresh(local_win);

    if (command == KEY_DOWN && y < y0 + FIELD_SIZE_Y) {
      y++;
    }

    if (command == KEY_LEFT && x > x0 + 1) {
      x--;
    }

    if (command == KEY_RIGHT && x < x0 + FIELD_SIZE_X) {
      x++;
    }

    mvaddch(y, x, '@');
  } while ((command = getch()) && command != 27);  // 27 = ESC

  delwin(local_win);
  endwin();

  return 0;
}