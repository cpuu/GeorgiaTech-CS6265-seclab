#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>

#include "flag.h"

unsigned int secret = 0xdeadbeef;

void handle_failure(char *buf) {
  char msg[100];
  snprintf(msg, sizeof(msg), "Invalid Password! %s\n", buf);
  printf(msg);
}

int main(int argc, char *argv[])
{
  setreuid(geteuid(), geteuid());
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);

  int tmp = secret;

  char buf[100];
  printf("IOLI Crackme Level 0x00\n");
  printf("Password:");

  fgets(buf, sizeof(buf), stdin);

  if (!strcmp(buf, "250382\n")) {
    printf("Password OK :)\n");
  } else {
    handle_failure(buf);
  }

  if (tmp != secret) {
    puts("The secret is modified!\n");
  }
  
  return 0;
}
