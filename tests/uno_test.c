#include "../headers/uno.h"
#include <stdio.h>

extern char table[];

int main(void)
{
  init_uno();
  puts(table);
  return 0;
}
