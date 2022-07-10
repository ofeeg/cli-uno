#include "../headers/uno.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern card *set_of_cards;
extern uint8_t plays;
extern uint8_t *uno_deck;
extern size_t num_of_cards;
extern uint8_t hand_size;
extern uint8_t *hand;

int main(void) {
  init_uno();
  size_t index = num_of_cards - 2;
  hand[--hand_size] = draw_card(uno_deck, num_of_cards);
  hand[--hand_size] = draw_card(uno_deck, num_of_cards);
  printf(uno_validate_play(set_of_cards, hand, &hand_size, index, 1));
  printf(uno_validate_play(set_of_cards, hand, &hand_size, index+1, 0));
  uno_draw(set_of_cards, hand, &hand_size);
  printf("Can you play this card: %s %s?",get_ccolor(set_of_cards[hand[hand_size]]) ,get_cvalue(set_of_cards[hand[hand_size]]));
  exit_uno();
  return 0;
}
