#include "../headers/card_game.h"

extern card *set_of_cards;
extern size_t num_of_cards;

int main(void) {
  load_cards(STANDARD_UNO);
  uint8_t *card_deck = init_deck();
  int c = draw_card(card_deck, num_of_cards);
  free(set_of_cards);
  free(card_deck);
  return 0;
}
