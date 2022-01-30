#include "../headers/card_game.h"
#include <stdint.h>
#include <stdlib.h>

card *set_of_cards;
size_t num_of_cards;
uint8_t set_check = NO_CARDSET;

void load_cards(char game_mode)
{
  switch (game_mode) {
  case STANDARD_UNO:
    {
      set_of_cards = (card *) malloc(112 * sizeof(card));
      num_of_cards = 112;
      uint8_t colors[5] = {RED, BLUE, GREEN, YELLOW, NONE};
      uint8_t value = 0;
      for(size_t c_i = 0; c_i < 5; ++c_i) 
	{
	  value = 0;
	  if(c_i < 4)
	    {
	      for(size_t v_i = ((c_i * 26)); v_i < ((c_i*26)+26); v_i+=2)
		{
		  set_of_cards[v_i] = (card){.value=value, .color=colors[c_i]};
		  set_of_cards[v_i+1] = (card){.value=value, .color=colors[c_i]};
		  value++;
		}
	    }
	  else
	    {
	      value = 13;
	      for(size_t sv_i = 104; sv_i < 112; sv_i+=4)
		{
		  set_of_cards[(sv_i)] = (card){.value=value, .color=colors[c_i]};
		  set_of_cards[(sv_i+1)] = (card){.value=value, .color=colors[c_i]};
		  set_of_cards[(sv_i+2)] = (card){.value=value, .color=colors[c_i]};
		  set_of_cards[(sv_i+3)] = (card){.value=value, .color=colors[c_i]};
		  value++;
		}
	    }
	}
      break;
    }
    default:
      return;
  }
  set_check = 1;
}

uint8_t* init_deck()
{
  if(set_check == NO_CARDSET){printf("No cards to make deck. How did that happen? Exiting..."); exit(2);}
  uint8_t *deck = (uint8_t *) malloc(num_of_cards);
  for(uint8_t i = 0; i < 5; ++i){deck[i] = i;}
  return deck;
}
