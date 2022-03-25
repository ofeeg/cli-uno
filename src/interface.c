#include "../headers/interface.h"
#include <curses.h>
#include <stdint.h>

#define DEFAULT_C 27
WINDOW *windows[15];

extern card *set_of_cards;
extern uint8_t plays;
extern uint8_t *uno_deck;
extern size_t num_of_cards;
extern uint8_t *hand;
extern uint8_t *hand2;
extern uint8_t *hand3;
extern uint8_t *hand4;
extern uint8_t hand_size;
extern uint8_t hand_size2;
extern uint8_t hand_size3;
extern uint8_t hand_size4;

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
  init_pair(1, COLOR_WHITE, COLOR_RED);
  init_pair(2, COLOR_WHITE, COLOR_BLUE);
  init_pair(3, COLOR_WHITE, COLOR_GREEN);
  init_pair(4, COLOR_WHITE, COLOR_YELLOW);
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


static void  display_hand(uint8_t *hand, size_t cursor_index, uint8_t player);

void uno_menu_control()
{
  uint8_t position = 1;
  int cursor_index = 0;
  display_hand(hand, cursor_index,1);
  refresh();
  while(1){
    mvaddstr(23, 1, "                                ");
    mvaddstr(23, 1, get_ccolor(set_of_cards[hand[hand_size+cursor_index]]));
    mvaddstr(23, 8, get_cvalue(set_of_cards[hand[hand_size+cursor_index]]));
    int c = mvgetch(20, (7+position));
    refresh();
    switch(c)
      {
      case KEY_RIGHT:
	if(position < 7){++position; ++cursor_index;}
	else{
	  if(num_of_cards-(cursor_index+1) > hand_size){
	    display_hand(hand, (++cursor_index)-6, 1);
	    wrefresh(windows[YOUR_HAND_W]);
	  }
	}
	break;
      case KEY_LEFT:
	if(position > 1){ --position; --cursor_index;}
	else{
	  if(cursor_index-1 >= 0){
	    display_hand(hand, (--cursor_index), 1);
	    wrefresh(windows[YOUR_HAND_W]);
	  }
	}
	break;
      case 10:
	wprintw(windows[LOG_W], uno_validate_play(set_of_cards, hand, &hand_size, ((cursor_index+hand_size) % num_of_cards)));
	display_hand(hand, 0, 1);
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

static void color_selector(uint8_t card, WINDOW *win);
static void color_off(uint8_t card, WINDOW *win);
static void  display_hand(uint8_t *hand, size_t cursor_index, uint8_t player)
{
  if(player == 1)
    {
      for(size_t i = cursor_index; i < cursor_index+7; ++i)
	{
	  if(hand_size+i > num_of_cards){mvaddch(20, 8+(i-cursor_index), ' ');}
	  else if(hand[hand_size+i] == 250)
	    {
	      mvaddch(20, 8+(i-cursor_index), ' ');
	    }
	  else
	    {
	      color_selector(hand[hand_size+i], windows[YOUR_HAND_W]);
	      switch(set_of_cards[hand[hand_size-i]].value)
		{
		case SKIP:
		  mvaddch(20, 8+(i-cursor_index), 'S');
		  color_off(hand[hand_size+i], windows[YOUR_HAND_W]);
		  break;
		case REVERSE:
		  mvaddch(20, 8+(i-cursor_index), 'U');
		  color_off(hand[hand_size+i], windows[YOUR_HAND_W]);
		  break;
		case DRAW_2:
		  mvaddch(20, 8+(i-cursor_index), 'D');
		  color_off(hand[hand_size+i], windows[YOUR_HAND_W]);
		  break;
		case WILD_CARD:
		  mvaddch(20, 8+(i-cursor_index), 'W');
		  color_off(hand[hand_size+i], windows[YOUR_HAND_W]);
		  break;
		case DRAW_4:
		  mvaddch(20, 8+(i-cursor_index), 'D');
		  color_off(hand[hand_size+i], windows[YOUR_HAND_W]);
		  break;
		default:
		  mvaddch(20, 8+(i-cursor_index), get_cvalue(set_of_cards[hand[hand_size+i]])[0]);
		  color_off(hand[hand_size+i], windows[YOUR_HAND_W]);
		  break;
		}
	    }
	}
    }
}

static void color_selector(uint8_t card, WINDOW *win){
  switch(set_of_cards[card].color)
    {
    case RED:
      attron(COLOR_PAIR(1));
      break;
    case BLUE:
      attron(COLOR_PAIR(2));
      break;
    case GREEN:
      attron(COLOR_PAIR(3));
      break;
    case YELLOW:
      attron(COLOR_PAIR(4));
      break;
    default:
      attron(COLOR_PAIR(DEFAULT_C));
      break;
    }
}
  

static void color_off(uint8_t card, WINDOW *win){
  switch(set_of_cards[card].color)
    {
    case RED:
      attroff(COLOR_PAIR(1));
      break;
    case BLUE:
      attroff(COLOR_PAIR(2));
      break;
    case GREEN:
      attroff(COLOR_PAIR(3));
      break;
    case YELLOW:
      attroff(COLOR_PAIR(4));
      break;
    default:
      attroff(COLOR_PAIR(DEFAULT_C));
      break;
    }
}
