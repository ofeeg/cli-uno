#include "../headers/card_game.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

card *set_of_cards;
size_t num_of_cards;
uint8_t *cards_in_play;
uint8_t *played_cards;
size_t plays = 1;
uint8_t set_check = NO_CARDSET;
uint32_t draw_index = 0;

void load_cards(char game_mode)
{
  switch (game_mode) {
  case STANDARD_UNO:
    {
      num_of_cards = 112;
      set_of_cards = (card *) malloc(num_of_cards * sizeof(card));
      cards_in_play = (uint8_t *)malloc(num_of_cards*sizeof(uint8_t));
      played_cards = (uint8_t *)malloc(num_of_cards*sizeof(uint8_t));
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
  for(uint8_t i = 0; i < num_of_cards; ++i){deck[i] = i;}
  return deck;
}

int draw_card(uint8_t *deck, size_t d_size)
{
  uint8_t card = deck[(draw_index % d_size)];
  cards_in_play[draw_index] = card;
  draw_index++;
  return card;
}

void play_card(card* set, uint8_t card)
{
  size_t arr_index = num_of_cards - plays;
  played_cards[arr_index] = card;
  ++plays;
}

#define FISCHER_YATES_CONDITION(i, k, n) (i <= k && k < n)

void shuffle_deck(uint8_t *deck, size_t d_size)
{
 srand(time(0));
 for(size_t i = 0; i<d_size-2; ++i){
  size_t r_num  =  (rand() % d_size);
  if(!FISCHER_YATES_CONDITION(i, r_num, d_size)){while(!FISCHER_YATES_CONDITION(i, r_num, d_size)){r_num = (rand() % d_size);}}
  uint8_t tmp = deck[i];
  deck[i] = deck[r_num];
  deck[r_num] = tmp;
 }
}
