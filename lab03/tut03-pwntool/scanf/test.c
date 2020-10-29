#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <err.h>

int main(int argc, char *argv[])
{
  char buf[16];
  memset(buf, 0, sizeof(buf));

  scanf("%s", buf);

  for (int i = 0; i < 16; i ++) {
    printf("%02x", (unsigned char)buf[i]);
  }
  printf("\n");
  
  return 0;
}