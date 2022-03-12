#include "../headers/interface.h"
#include <ncurses.h>

extern WINDOW *windows[];

int main(void)
{
  init_uno();
  init_uno_interface();
  refresh();
  wrefresh(windows[TABLE_W]);
  wrefresh(windows[9]);
  wrefresh(windows[SCORES_W]);
  wrefresh(windows[LOG_W]);
  wrefresh(windows[13]);
  wrefresh(windows[12]);
  uno_menu_control();
  refresh();
  endwin();
  return 0;
}
