#include "../headers/interface.h"
#include <curses.h>

extern WINDOW *windows[];

int main(void)
{
  init_uno_interface();
  refresh();
  wrefresh(windows[0]);
  getch();
  endwin();
  return 0;
}
