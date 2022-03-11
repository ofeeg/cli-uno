#ifndef INTERFACE_H
#define INTERFACE_H
#include "uno.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define WALL '#'
#define UNKNOWN '@'
#define CARD_SPACE '&'
#define TABLE_SIZE  485
#define EMPTY_SPACE ' '
#define PLAYER_2_SPACE 27
#define PLAYER_3_SPACE 127
#define PLAYER_4_SPACE 144
#define PLAYER_1_SPACE 384

#define TABLE_W 0
#define YOUR_HAND_W 1
#define P2_HAND_W 3
#define P3_HAND_W 4
#define P4_HAND_W 5
#define SCORES_W 10
#define LOG_W 11

void init_uno_interface();
#endif
