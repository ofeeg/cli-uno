#include "../headers/interface.h"
#include <ncurses.h>

extern WINDOW *windows[];

int main(void)
{
  init_uno();
  init_uno_interface();
  refresh();
  wrefresh(windows[0]);
  wrefresh(windows[9]);
  wrefresh(windows[10]);
  wrefresh(windows[11]);
  wrefresh(windows[12]);
  refresh();
  getch();
  endwin();
  return 0;
}
