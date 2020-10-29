#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void prompt(char *fmt, ...)
{
  va_list args;
  
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);

  getchar();
}

int main()
{
  void *fb_0 = malloc(16);
  void *fb_1 = malloc(32);
  void *fb_2 = malloc(16);
  void *fb_3 = malloc(32);
  prompt("Stage 1");

  free(fb_1);
  free(fb_3);
  prompt("Stage 2");

  free(fb_0);
  free(fb_2); 
  malloc(32);
  prompt("Stage 3");

  void *nb_0 = malloc(100);
  void *nb_1 = malloc(120);
  void *nb_2 = malloc(140);
  void *nb_3 = malloc(160);
  void *nb_4 = malloc(180);
  prompt("Stage 4");

  free(nb_1);
  free(nb_3); 
  prompt("Stage 5");

  void *nb_5 = malloc(240);
  prompt("Stage 6");

  free(nb_2);
  prompt("Stage 7");
 
  return 0;
}
