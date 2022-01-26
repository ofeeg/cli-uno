#ifndef CARD_H
#define CARD_H
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define RED 0b001
#define YELLOW 0b111
#define GREEN 0b011
#define BLUE 0b100
#define NONE 0b000

#define SKIP 10
#define REVERSE 11
#define DRAW_2 12
#define WILD_CARD 13
#define DRAW_4 14

typedef struct card
{
    unsigned int value : 4;
    unsigned int color : 3;

}card;

char *get_cvalue(card c);
char *get_ccolor(card c);


#endif
