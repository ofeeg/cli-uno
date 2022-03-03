#include "../headers/interface.h"
#include <curses.h>
WINDOW *windows[4];

void init_uno_interface()
{
  int main_cols, main_rows;
  initscr();
  getmaxyx(stdscr, main_rows, main_cols);
  WINDOW *table = newwin(22, 22, 1, 1);
  box(table,0,0);
  windows[0] = table;
}
