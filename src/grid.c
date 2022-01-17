#include "../headers/grid.h"
#define TABLE_SIZE  485
static const char empty_space = ' ';
char table[TABLE_SIZE];


void create_table()
{
  memset(table, ' ', sizeof table);

  for (size_t i=0; i < 20; ++i)
  {
    if(i > 0){
      table[(i * 21) - 2] = WALL;
      table[(i * 21)] = WALL;
      table[420 - (21 - i )] = WALL;
      table[(i * 21) - 1] = '\n';
    }
    table[i] = WALL;
  }
      
};
