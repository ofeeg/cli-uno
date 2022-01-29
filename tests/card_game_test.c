#include "../headers/card_game.h"

extern card *card_deck;
int main(void) {
  load_cards(STANDARD_UNO);
  free(card_deck);
  return 0;
}
