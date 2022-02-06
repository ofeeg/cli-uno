#include "../headers/table.h"

char table[TABLE_SIZE];


void create_table()
{
  memset(table, EMPTY_SPACE, sizeof table);

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
