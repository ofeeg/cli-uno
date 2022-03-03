#include "table.h"
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

void init_uno_interface();
