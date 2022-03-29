#include "../headers/uno.h"
#include <curses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
extern size_t num_of_cards;
extern uint8_t *played_cards;
extern uint8_t plays;
extern card *set_of_cards;
uint8_t *uno_deck;
uint8_t hand_size, hand_size2, hand_size3, hand_size4;
uint8_t *hand;
uint8_t *hand2;
uint8_t *hand3;
uint8_t *hand4;
static void distribute_hands();

void init_uno()
{
  load_cards(STANDARD_UNO);
  uno_deck = init_deck();
  hand_size = hand_size2 = hand_size3 = hand_size4 = num_of_cards;
  hand = (uint8_t *)malloc(num_of_cards*sizeof(uint8_t));
  memset(hand, 250, num_of_cards);
  hand2 = (uint8_t *)malloc(num_of_cards*sizeof(uint8_t));
  memset(hand2, 250, num_of_cards);
  hand3 = (uint8_t *)malloc(num_of_cards*sizeof(uint8_t));
  memset(hand3, 250, num_of_cards);
  hand4 = (uint8_t *)malloc(num_of_cards*sizeof(uint8_t));
  memset(hand4, 250, num_of_cards);
  shuffle_deck(uno_deck, num_of_cards);
  distribute_hands();
}

static void distribute_hands()
{
  for(int i = 0; i < 7; ++i)
    {
      hand[--hand_size] = draw_card(uno_deck, num_of_cards);
      hand2[--hand_size2] = draw_card(uno_deck, num_of_cards);
      hand3[--hand_size3] = draw_card(uno_deck, num_of_cards);
      hand4[--hand_size4] = draw_card(uno_deck, num_of_cards);
    }
}


void shift_hand(uint8_t *hand, size_t index)
{
  size_t empty;
  for(size_t n = index; n >= 0; --n)
    {
      if(hand[n] == 250)
	{
	  empty = n;
	  break;
	}
    }
  hand[index] = 250;
  uint8_t tmp;
  for(size_t i=index; i > empty; --i)
    {
      tmp = hand[i];
      hand[i] = hand[i-1];
      hand[i-1] = tmp;
    }
}

char *concatf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

const char* uno_validate_play(card* set, uint8_t *hand, uint8_t *hand_size, size_t index)
{
  if(hand[index] == (uint8_t)250) return concatf("Not a card.");
  uint8_t card = hand[index];
  uint8_t arr_index = num_of_cards - plays;
  if(plays == 1 || set[card].color == NONE)    {   
      played_cards[arr_index] = card;
      ++*hand_size;
      play_card(card);
      shift_hand(hand, index);
      return concatf("You have played a %s %s!\n",get_ccolor(set_of_cards[card]), get_cvalue(set_of_cards[card]));
    }
  else
    {
      if(set[card].color != set[played_cards[arr_index+1]].color || set[card].value != set[played_cards[arr_index+1]].value)
	{
	  return concatf("You can't play this card.\n");
	}
      if(set[played_cards[arr_index]].value == WILD_CARD || set[played_cards[arr_index]].value == DRAW_4) set[played_cards[arr_index]].color = NONE;
      played_cards[arr_index] = card;
      ++*hand_size;
      play_card(card);
      shift_hand(hand, index);
    }
  return concatf("You have played a %s %s!\n",get_ccolor(set_of_cards[card]), get_cvalue(set_of_cards[card]));
}

void exit_uno()
{
  free(hand);
  free(hand2);
  free(hand3);
  free(hand4);
  free(set_of_cards);
  free(uno_deck);
}

#include <stdarg.h>
char *concatf(const char *fmt, ...) 
{
  va_list args;
  va_start(args, fmt);
  char* buf = NULL;
  int n = vsnprintf(NULL, 0, fmt, args);
  va_end(args);
  if (n >= 0) {
    va_start(args, fmt);
    buf = malloc(n+1);
    if (buf) vsnprintf(buf, n+1, fmt, args);
    va_end(args);
  }
  return buf;
} 
