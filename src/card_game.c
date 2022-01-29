#include "../headers/card_game.h"
#include <stdint.h>

card *card_deck;

void load_cards(char game_mode)
{
  switch (game_mode) {
  case STANDARD_UNO:
    {
      card_deck = (card *) malloc(112 * (sizeof(card)));
      uint8_t colors[5] = {RED, BLUE, GREEN, YELLOW, NONE};
      uint8_t value = 0;
      for(size_t c_i = 0; c_i < 6; ++c_i) 
	{
	  value = 0;
	  if(c_i < 5)
	    {
	      for(size_t v_i = ((c_i * 26)); v_i < ((c_i*26)+26); v_i+=2)
		{
		  card_deck[v_i] = (card){.value=value, .color=colors[c_i]};
		  card_deck[v_i+1] = (card){.value=value, .color=colors[c_i]};
		  value++;
		}
	    }
	  else
	    {
	      value = 13;
	      for(size_t sv_i = 104; sv_i < 112; sv_i+=4)
		{
		  card_deck[(sv_i)] = (card){.value=value, .color=colors[c_i]};
		  card_deck[(sv_i+1)] = (card){.value=value, .color=colors[c_i]};
		  card_deck[(sv_i+2)] = (card){.value=value, .color=colors[c_i]};
		  card_deck[(sv_i+3)] = (card){.value=value, .color=colors[c_i]};
		  value++;
		}
	    }
	}
      break;
    }
    default:
      return;
  }
}
