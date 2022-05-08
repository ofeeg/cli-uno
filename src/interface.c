#include "../headers/interface.h"
#include <stdio.h>
#include <stdlib.h>
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

char *anonimized_hand = "#######";

void ui_print(WINDOW *win, int starty, int startx, size_t s_length, char *string, chtype color);
void ui_print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void ui_print_vertically(WINDOW *win, int starty, int startx, int s_length, char *string, chtype color);



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
  ui_print_vertically(hand_textp2, 1, 1, 7, "p2 Hand", COLOR_PAIR(DEFAULT_C));
  ui_print_in_middle(hand_textp3, 1, 0, 9, "p3 Hand", COLOR_PAIR(DEFAULT_C));
  ui_print_vertically(hand_textp4, 1, 1, 7, "p4 Hand", COLOR_PAIR(DEFAULT_C));
  ui_print_in_middle(score_box_text, 1, 0, 26, "Score", COLOR_PAIR(DEFAULT_C));
  ui_print_in_middle(log_text, 1, 0, 24, "Log", COLOR_PAIR(DEFAULT_C));
  ui_print_vertically(p2_hand, 1, 1, 4, anonimized_hand, COLOR_PAIR(DEFAULT_C));
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


static void display_hand(uint8_t *hand, size_t cursor_index, uint8_t player);

static void wait_for_turns();

void uno_menu_control()
{
  const char *log_msg;
  uint8_t position = 1;
  int cursor_index = 0;
  display_hand(hand, cursor_index,1);
  refresh();
  while(1){
    mvaddstr(23, 1, "                                ");
    ui_print_vertically(windows[P2_HAND_W], 1, 1, 7, "       ", COLOR_PAIR(DEFAULT_C));
    ui_print_vertically(windows[P4_HAND_W], 1, 1, 7, "       ", COLOR_PAIR(DEFAULT_C));
    ui_print(windows[P3_HAND_W], 1, 1, 7, "       ", COLOR_PAIR(DEFAULT_C));
    mvaddstr(23, 1, get_ccolor(set_of_cards[hand[hand_size+cursor_index]]));
    mvaddstr(23, 8, get_cvalue(set_of_cards[hand[hand_size+cursor_index]]));
    display_hand(hand2, 0, 2);
    display_hand(hand3, 0, 3);
    display_hand(hand4, 0, 4);
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
      case KEY_DOWN:
	hand[--hand_size] = draw_card(uno_deck, num_of_cards);
	display_hand(hand, ((cursor_index+1)-(position)) ,1);	
	wrefresh(windows[YOUR_HAND_W]);
	break;
      case KEY_UP:
	if (hand_size < num_of_cards-2) {
	  wprintw(windows[LOG_W], "Cannot declare uno.");
	  wrefresh(windows[LOG_W]);
	  break;
	}
	wprintw(windows[LOG_W], "You declared uno!");
	wrefresh(windows[LOG_W]);
      case 10:
	if(set_of_cards[hand[((cursor_index+hand_size)%num_of_cards)]].color == NONE)
	  {
	    char choice = 0;
	    mvaddstr(23, 1, "                                ");
	    mvaddstr(23, 1, "Select Color: 1.R 2.B 3.G 4.Y");
	    while(choice > '4' || choice < '1')
	      {
		choice = 0;
		choice = getch();
	      }
	    log_msg = uno_validate_play(set_of_cards, hand, &hand_size, ((cursor_index+hand_size) % num_of_cards), atoi(&choice));
	  }
	else
	  {
	    log_msg = uno_validate_play(set_of_cards, hand, &hand_size, ((cursor_index+hand_size) % num_of_cards), 0);
	  }
	wprintw(windows[LOG_W], log_msg);
	display_hand(hand, 0, 1);
	position = 1;
	cursor_index = 0;
	wrefresh(windows[LOG_W]);
	refresh();
	if(log_msg[0] != 'N' && log_msg[4] != 'c'){wait_for_turns();}
	break;
      }
  }
}

#define TURN_COUNTER 4
static void wait_for_turns()
{
  for(size_t i = 2; i <= TURN_COUNTER; ++i)
    {
      for(size_t n = (num_of_cards-1); n > 0; --n)
	{
	  if(i == 2)
	    {
	      const char *c = uno_validate_play(set_of_cards, hand2, &hand_size2, n, 1);
	      if(c[0] =='N'){
		hand2[--hand_size2] = draw_card(uno_deck, num_of_cards); ++n;}
	       //"You can't play this card.\n"
	      else if(c[4] != 'c'){
		wprintw(windows[LOG_W], c);
		wrefresh(windows[LOG_W]);
		refresh();
		break;
	      } //checking for c in message
	    }
	  else if(i == 3)
	    {
	      const char *c = uno_validate_play(set_of_cards, hand3, &hand_size3, n, 2);
	      if(c[0] =='N'){hand3[--hand_size3] = draw_card(uno_deck, num_of_cards); ++n;}
	      else if(c[4] != 'c'){
		wprintw(windows[LOG_W], c);
		wrefresh(windows[LOG_W]);
		refresh();
		break;
	      }
	    }
	  else 
	    {
	      const char *c = uno_validate_play(set_of_cards, hand4, &hand_size4, n, 3);
	      if(c[0] =='N'){hand4[--hand_size4] = draw_card(uno_deck, num_of_cards); ++n;}
	      else if(c[4] != 'c'){
		wprintw(windows[LOG_W], c);
		wrefresh(windows[LOG_W]);
		refresh();
		break;
	      }
	    }
	}
    }
  return;
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

void ui_print(WINDOW *win, int starty, int startx, size_t s_length, char *string, chtype color)
    {
      int x, y;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(s_length == 0)
		s_length = 80;

	wattron(win, color);
	for(int i = 0; i < s_length; ++i)
	  {
	    mvwaddch(win, y, x+i, string[i]);
	  };
	wattroff(win, color);
	wrefresh(win);
	refresh();
    }

void ui_print_vertically(WINDOW *win, int starty, int startx, int s_length, char *string, chtype color)
{	int x, y;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(s_length == 0)
		s_length = 80;

	wattron(win, color);
	for(int i = 0; i < s_length; ++i)
	  {
	    mvwaddch(win, y+i, x, string[i]);
	  };
	wattroff(win, color);
	wrefresh(win);
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
	  if(hand_size+i >= num_of_cards)
	    {
	      mvaddch(20, 8+(i-cursor_index), ' ');
	    }
	  else if(hand[hand_size+i] == 250)
	    {
	      mvaddch(20, 8+(i-cursor_index), ' ');
	    }
	  else
	    {
	      color_selector(hand[hand_size+i], windows[YOUR_HAND_W]);
	      switch(set_of_cards[hand[hand_size+i]].value)
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
  else
    {
    WINDOW *win;
    size_t h_size;
    switch (player) {
    case 2:
      win = windows[P2_HAND_W];
      h_size = hand_size2;
      break;
    case 3:
      win = windows[P3_HAND_W];
      h_size = hand_size3;
      break;
    case 4:
      win = windows[P4_HAND_W];
      h_size = hand_size4;
      break;
    }
    if(h_size < 105) h_size = 7;
    else h_size = num_of_cards - h_size;
    if(player != 3) {ui_print_vertically(win, 1, 1,  h_size, anonimized_hand, COLOR_PAIR(DEFAULT_C));}
    else {ui_print(win, 1, 1, h_size, anonimized_hand, COLOR_PAIR(DEFAULT_C));}
    wrefresh(win);
    refresh();
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
