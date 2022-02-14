#include "../headers/player.h"
#include <stdio.h>
#include <stdlib.h>


char arr[6] = {'&','&','&','&','&', '\0'};
unsigned char select_index = 0;
void selector(const char input);
int main(void)
{
  while(1){
    selector(read_input());
  }
  return 0;
}

void selector(const char input)
{
  switch(input){
  case 'a':
    if(select_index==0){break;}
    arr[select_index] = '&';
    select_index-=1;
    arr[select_index] = select_index;
    break;
  case 'd':
    if(select_index==5){break;}
    arr[select_index] = '&';
    select_index+=1;
    arr[select_index] = select_index;
    break;
  case ' ':
    printf("You have selected %i.", select_index);
    exit(1);
    break;
  default:
    break;
  }
}
