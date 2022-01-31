#include "../headers/card_game.h"
#include <stdint.h>
#include <stdio.h>

extern card *set_of_cards;
extern size_t num_of_cards;
extern uint8_t plays;

int main(void) {
  load_cards(STANDARD_UNO);
  uint8_t *card_deck = init_deck();
  uint8_t crd = draw_card(card_deck, num_of_cards);
  printf("%d\n", plays);
  play_card(set_of_cards, crd);
  printf("%d\n", plays);
  free(set_of_cards);
  free(card_deck);
  return 0;
}
