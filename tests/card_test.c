#include "../headers/card.h"
#include <stdio.h>

struct card uno_deck[112];

int main(void)
{
  uint8_t colors[5] = {RED, BLUE, GREEN, YELLOW, NONE};
  uint8_t value = 0;
  for(size_t c_i = 0; c_i < 6; ++c_i) //you can make a deck this way, if you like
    {
      value = 0;
      if(c_i < 5)
	{
	  for(size_t v_i = ((c_i * 26)); v_i < ((c_i*26)+26); v_i+=2)
	    {
	      uno_deck[v_i] = (card){.value=value, .color=colors[c_i]};
	      uno_deck[v_i+1] = (card){.value=value, .color=colors[c_i]};
	      value++;
	    }
	}
      else
	{
	  value = 13;
	  for(size_t sv_i = 104; sv_i < 112; sv_i+=4)
	    {
	      uno_deck[(sv_i)] = (card){.value=value, .color=colors[c_i]};
	      uno_deck[(sv_i+1)] = (card){.value=value, .color=colors[c_i]};
	      uno_deck[(sv_i+2)] = (card){.value=value, .color=colors[c_i]};
	      uno_deck[(sv_i+3)] = (card){.value=value, .color=colors[c_i]};
	      value++;
	    }
	}
    };
  
  card r = {7, GREEN};
  printf("%s, %s\n", get_ccolor(r), get_cvalue(r));
  card hand[5];
  hand[1] = (card){.value=6, .color=YELLOW};
  printf("%s, %s\n", get_ccolor(hand[1]), get_cvalue(hand[1]));
  printf("%s, %s\n", get_ccolor(hand[0]), get_cvalue(hand[0]));
  for(size_t i = 0; i < sizeof(uno_deck)/sizeof(card); ++i){printf("%s, %s\n", get_ccolor(uno_deck[i]), get_cvalue(uno_deck[i]));}
}
