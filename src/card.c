#include "../headers/card.h"

char* get_cvalue(card c)
{
  char* msg;
  msg = malloc(sizeof(char)*10);
  if(c.value > DRAW_4){strcpy(msg, "invalid");}
  else if(c.value == DRAW_4){strcpy(msg, "Draw 4");}
  else if(c.value == WILD_CARD){strcpy(msg, "Wild Card");}
  else if(c.value == DRAW_2){strcpy(msg, "Draw 2");}
  else if(c.value == REVERSE){strcpy(msg, "Reverse");}
  else if(c.value == SKIP){strcpy(msg, "Skip");}
  else{sprintf(msg, "%d", c.value);}
  return msg;
}

