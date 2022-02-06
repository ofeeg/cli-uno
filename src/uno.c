#include "../headers/uno.h"
#include "../headers/table.h"
#define CARD_SPACE '&'

extern char table[];

void init_uno()
{
  create_table();
  for(size_t i =0; i < 7; ++i)
    {
      table[PLAYER_2_SPACE+i] = CARD_SPACE;
      table[PLAYER_1_SPACE+i] = CARD_SPACE;
      table[PLAYER_4_SPACE+(i*21)] = CARD_SPACE;
      table[PLAYER_3_SPACE+(i*21)] = CARD_SPACE;
    }
}
