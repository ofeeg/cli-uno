#include "../headers/card.h"
#include <stdio.h>

int main(void)
{
  char message[100];
  card r = {7, GREEN};
  printf("%s", get_cvalue(r));
}
