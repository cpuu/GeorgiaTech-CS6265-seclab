#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
  setreuid(geteuid(), geteuid());
  char buf[16];
  printf("IOLI Crackme Level 0x00\n");
  printf("Password:");

  scanf("%s", buf);
  
  if (!strcmp(buf, "250382"))
    printf("Password OK :)\n");
  else
    printf("Invalid Password!\n");
  
  return 0;
}
