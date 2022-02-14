#include "../headers/player.h"
#include <stdio.h>

char player_input;

const char read_input()
{
  scanf("%c", &player_input);
  return player_input;
}
