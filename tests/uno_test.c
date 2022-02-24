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
  memset(hand, 250, num_of_cards);
  hand[--hand_size] = draw_card(uno_deck, num_of_cards);
  hand[--hand_size] = draw_card(uno_deck, num_of_cards);
  uno_validate_play(set_of_cards, hand[hand_size], &hand_size);
  uno_validate_play(set_of_cards, hand[hand_size], &hand_size);
  return 0;
}

