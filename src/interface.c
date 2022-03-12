#include "../headers/interface.h"
#include <curses.h>
#include <stdint.h>

#define DEFAULT_C 27
WINDOW *windows[14];

extern card *set_of_cards;
extern uint8_t plays;
extern uint8_t *uno_deck;
extern size_t num_of_cards;
extern uint8_t hand_size;

void ui_print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void ui_print_in_middle_v(WINDOW *win, int starty, int startx, int width, char *string, chtype color);


void init_uno_interface()
{
  int main_cols, main_rows;
  initscr();
  noecho();
  //nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  cbreak();
  getmaxyx(stdscr, main_rows, main_cols);
  WINDOW *table = newwin(22, 22, 1, 1);
  box(table,0,0);
  WINDOW *your_hand = derwin(table, 3, 9, 18, 6);
  WINDOW *p2_hand = derwin(table, 9, 3, 6, 18);
  WINDOW *p3_hand = derwin(table,3, 9, 1, 6);
  WINDOW *p4_hand = derwin(table, 9, 3, 6, 1);
  WINDOW *hand_text = subwin(table, 3, 9, 17, 7);
  WINDOW *hand_textp2 = subwin(table, 9, 3, 7, 17);
  WINDOW *hand_textp3 = subwin(table, 3, 9, 4, 7);
  WINDOW *hand_textp4 = subwin(table, 9, 3, 7, 4);
  WINDOW *scores = newwin(3, 26, 3, 28);
  WINDOW *score_box_text = newwin(3,26, 1, 28);
  WINDOW *log_box = newwin(14, 24, 11, 30);
  WINDOW *log = newwin(12, 22, 12, 31);
  scrollok(log, TRUE);
  WINDOW *log_text = newwin(3, 24, 9, 30);
  box(log_box,0,0);
  box(log_text,0,0);
  box(scores,0,0);
  box(score_box_text,0,0);
  box(hand_text, 0, 0);
  box(your_hand,0,0);
  box(p2_hand, 0, 0);
  box(hand_textp2,0,0);
  box(p3_hand, 0, 0);
  box(hand_textp3,0,0);
  box(p4_hand, 0, 0);
  box(hand_textp4,0,0);
  start_color();
  init_pair(DEFAULT_C, COLOR_BLACK, COLOR_WHITE);
  init_pair(RED, COLOR_WHITE, COLOR_RED);
  init_pair(BLUE, COLOR_WHITE, COLOR_BLUE);
  init_pair(GREEN, COLOR_WHITE, COLOR_GREEN);
  init_pair(YELLOW, COLOR_WHITE, COLOR_YELLOW);
  ui_print_in_middle(hand_text, 1, 0, 9, "My Hand", COLOR_PAIR(DEFAULT_C));
  ui_print_in_middle_v(hand_textp2, 0, 1, 9, "p2 Hand", COLOR_PAIR(DEFAULT_C));
  ui_print_in_middle(hand_textp3, 1, 0, 9, "p3 Hand", COLOR_PAIR(DEFAULT_C));
  ui_print_in_middle_v(hand_textp4, 0, 1, 9, "p4 Hand", COLOR_PAIR(DEFAULT_C));
  ui_print_in_middle(score_box_text, 1, 0, 26, "Score", COLOR_PAIR(DEFAULT_C));
  ui_print_in_middle(log_text, 1, 0, 24, "Log", COLOR_PAIR(DEFAULT_C));
  ui_print_in_middle(scores, 1, 0, 26, "1:000 2:000 3:000 4:000", COLOR_PAIR(DEFAULT_C));
  windows[0] = table;
  windows[1] = your_hand;
  windows[2] = hand_text;
  windows[3] = p2_hand;
  windows[4] = p3_hand;
  windows[5] = p4_hand;
  windows[6] = hand_textp2;
  windows[7] = hand_textp3;
  windows[8] = hand_textp4;
  windows[9] = score_box_text;
  windows[10] = scores;
  windows[11] = log;
  windows[12] = log_text;
  windows[13] = log_box;
}

void uno_menu_control()
{
  uint8_t position = 1;
  refresh();
  while(1){
    int c = mvgetch(20, (7+position));
    refresh();
    switch(c)
      {
      case KEY_RIGHT:
	if(position < 7) ++position;
	break;
      case KEY_LEFT:
	if(position > 1) --position;
	break;
      case 10:
	wprintw(windows[LOG_W], uno_validate_play(set_of_cards, position, &hand_size));
	wrefresh(windows[LOG_W]);
	refresh();
	break;
      }
  }
}

void ui_print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}


void ui_print_in_middle_v(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	y = starty + (int)temp;
	wattron(win, color);
	for(int i = 0; i < 7; ++i)
	  {
	    mvwaddch(win, y+i, x, string[i]);
	  };
	wattroff(win, color);
	refresh();
}
