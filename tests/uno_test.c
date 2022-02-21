#include "../headers/uno.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern card *set_of_cards;
extern uint8_t plays;
extern char table[];
extern uint8_t *uno_deck;
extern size_t num_of_cards;


int main(void)
{
  init_uno();
  puts(table);
  uint8_t hand_size = num_of_cards;
  uint8_t hand[num_of_cards];
  memset(hand, 254, num_of_cards);
  hand[--hand_size] = draw_card(uno_deck, num_of_cards);
  hand[--hand_size] = draw_card(uno_deck, num_of_cards);
  play_card(set_of_cards, hand[hand_size+2]);
  printf("You have played a %s %s!\n",get_ccolor(set_of_cards[hand[hand_size]]), get_cvalue(set_of_cards[hand[hand_size]]));
  return 0;
}

