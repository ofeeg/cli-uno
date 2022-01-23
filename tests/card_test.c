#include "../headers/card.h"
#include <stdio.h>

int main(void)
{
  char message[100];
  card r = {7, GREEN};
  printf("%s, %s\n", get_ccolor(r), get_cvalue(r));
}
