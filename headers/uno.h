#ifndef UNO_H
#define UNO_H
#include "card_game.h"
#include <string.h>
void init_uno();
const char *uno_validate_play(card *set, uint8_t card, uint8_t *hand_size);
void exit_uno();
#endif
