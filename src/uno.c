#include "../headers/uno.h"

extern size_t num_of_cards;
extern uint8_t *played_cards;
extern uint8_t plays;
extern card *set_of_cards;
uint8_t *uno_deck;

void init_uno()
{
  load_cards(STANDARD_UNO);
  uno_deck = init_deck();
  shuffle_deck(uno_deck, num_of_cards);
  /* create_table(); */
  /* for(size_t i =0; i < 7; ++i) */
  /*   { */
  /*     table[PLAYER_2_SPACE+i] = CARD_SPACE; */
  /*     table[PLAYER_1_SPACE+i] = CARD_SPACE; */
  /*     table[PLAYER_4_SPACE+(i*21)] = CARD_SPACE; */
  /*     table[PLAYER_3_SPACE+(i*21)] = CARD_SPACE; */
  /*   } */
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
   //printf("You have played a %s %s!\n",get_ccolor(set_of_cards[card]), get_cvalue(set_of_cards[card]));
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
