#include <ncurses.h>

int main(void) {
  int x = 20, y = 10;
  int c = 0;

  initscr();
  keypad(stdscr, 1);
  noecho();
  curs_set(0);

  do {
    clear();

    switch (c) {
      case KEY_UP:
        y--;
        break;
      case KEY_DOWN:
        y++;
        break;
      case KEY_LEFT:
        x--;
        break;
      case KEY_RIGHT:
        x++;
        break;
      default:
        continue;
    }

    mvaddch(y, x, '@');
  } while ((c = getch()) && c != 27);  // 27 = ESC

  endwin();

  return 0;
}