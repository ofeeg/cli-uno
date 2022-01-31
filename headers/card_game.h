#ifndef CARD_GAME_H
#define CARD_GAME_H
#include "card.h"
#define NO_CARDSET 69
#define STANDARD_UNO 0

void load_cards(char game_mode);
uint8_t* init_deck();
int draw_card(uint8_t * deck, size_t d_size);
void play_card(card* set, uint8_t card);
#endif
