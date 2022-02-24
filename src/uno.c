#include "../headers/uno.h"
#include "../headers/table.h"
#define CARD_SPACE '&'

extern char table[];
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
  create_table();
  for(size_t i =0; i < 7; ++i)
    {
      table[PLAYER_2_SPACE+i] = CARD_SPACE;
      table[PLAYER_1_SPACE+i] = CARD_SPACE;
      table[PLAYER_4_SPACE+(i*21)] = CARD_SPACE;
      table[PLAYER_3_SPACE+(i*21)] = CARD_SPACE;
    }
}

void uno_validate_play(card* set, uint8_t card, uint8_t *hand_size)
{
 uint8_t arr_index = num_of_cards - plays;
 if(plays == 1 || set[card].color == NONE)
  {
   played_cards[arr_index] = card;
   ++*hand_size;
   play_card(card);
   printf("You have played a %s %s!\n",get_ccolor(set_of_cards[card]), get_cvalue(set_of_cards[card]));
   return;
  }
 else
  {
   if(set[card].color != set[played_cards[arr_index+1]].color || set[played_cards[arr_index+1]].color == NONE)
    {
     printf("You can't play this card.\n"); return;
    }
   played_cards[arr_index] = card;
   ++*hand_size;
   play_card(card);
  }
 printf("You have played a %s %s!\n",get_ccolor(set_of_cards[card]), get_cvalue(set_of_cards[card]));
}
