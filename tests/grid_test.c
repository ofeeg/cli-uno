#include "../headers/grid.h"
#include <stdio.h>

extern char table[];

int main(void)
{
  create_table();
  puts(table);
  return 0;
}
