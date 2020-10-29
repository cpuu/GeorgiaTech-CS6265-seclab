#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int main(int argc, char * argv[])
{
  char *a, *arr[9];
  int i=0;
  for(i = 0 ; i < 3 ; i++)
  {
    arr[i] = malloc(0x20);
  }

  for(i = 3 ; i < 5 ; i++)
  {
    arr[i] = malloc(0x30);
  }

  for(i = 5 ; i < 7 ; i++)
  {
    arr[i] = malloc(0x40);
  }

  a = malloc(0x420);
  arr[8] = malloc(0x20);  // temporary chunk to prevent last chunk merging issue .
  free(a);

  for(i = 0 ; i < 7 ; i++)
  {
    free(arr[i]);
  }
}
