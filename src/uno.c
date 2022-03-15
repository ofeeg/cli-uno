#include "../headers/uno.h"
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
  memset(hand, 250, num_of_cards);
  hand3 = (uint8_t *)malloc(num_of_cards*sizeof(uint8_t));
  memset(hand, 250, num_of_cards);
  hand4 = (uint8_t *)malloc(num_of_cards*sizeof(uint8_t));
  memset(hand, 250, num_of_cards);
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

char *concatf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

const char* uno_validate_play(card* set, uint8_t card, uint8_t *hand_size)
{
 uint8_t arr_index = num_of_cards - plays;
 if(plays == 1 || set[card].color == NONE)
  {
   played_cards[arr_index] = card;
   ++*hand_size;
   play_card(card);
   return concatf("You have played a %s %s!\n",get_ccolor(set_of_cards[card]), get_cvalue(set_of_cards[card]));
  }
 else
  {
   if(set[card].color != set[played_cards[arr_index+1]].color || set[played_cards[arr_index+1]].color == NONE)
    {
     return concatf("You can't play this card.\n");
    }
   played_cards[arr_index] = card;
   ++*hand_size;
   play_card(card);
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
