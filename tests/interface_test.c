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
  mvwprintw(windows[P2_HAND_W], 1, 1, "T");
  mvwprintw(windows[P2_HAND_W], 7, 1, "T");
  while (1) {
    char c = wgetch(windows[LOG_W]);
    switch(c) {
    default:
      wprintw(windows[LOG_W], "You have played a\n  Wild Card!\n");
      wrefresh(windows[LOG_W]);
      wrefresh(windows[P2_HAND_W]);
    }
  }
  refresh();
  getch();
  endwin();
  return 0;
}
