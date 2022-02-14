#include "../headers/player.h"
#include <stdio.h>
#include <stdlib.h>

char arr[6] = {'&','&','&','&','&', '\0'};
unsigned char index = 0;
void selector(const char* input)
int main(void)
{
 selector(read_input());
 return 0;
}

void selector(const char* input)
{
 switch(input){
  case 'A':
   if(index==0){break;}
   arr[index] = '&';
   index-=1;
   arr[index] = index;
   break;
  case 'D':
   if(index==5){break;}
   arr[index] = '&';
   index+=1;
   arr[index] = index;
   break;
  case ' ':
   printf("You have selected %c.", input);
   exit(1);
   break;
  default:
   break;
 }
}
