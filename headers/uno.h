#ifndef UNO_H
#define UNO_H
#include "card_game.h"
#include <string.h>
void init_uno();
void shift_hand(uint8_t *hand, size_t index);
const char *uno_validate_play(card *set, uint8_t *hand, uint8_t *hand_size, size_t index, size_t color_mode);
void exit_uno();
#endif
