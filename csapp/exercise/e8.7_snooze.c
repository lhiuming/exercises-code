// interuputable snooze
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

unsigned int snooze(unsigned int);

void sigint_handler(int sig) {
  printf(" pressed.\n");
}

int main(int argc, char **argv) {
  /* check the number of arguments */
  if (argc < 2) {
    printf("No enough arguments!\n");
    return -1;
  }
  /* read the first argument as integer */
  unsigned int secs;
  if ( sscanf(argv[1], "%u", &secs) == 0) {
    printf("Invalid input: %s\n", argv[1]);
    return -1;
  }

  /* install the handler */
  if (signal(SIGINT, sigint_handler) == SIG_ERR)
    printf("signal error");

  /* call snooze */
  snooze(secs);

  return 0;
}
