#include <unistd.h>
#include <stdio.h>

unsigned int snooze(unsigned int secs) {

  unsigned int left = sleep(secs);

  printf("Slept for %i of %i secs.\n",
    secs - left,
    secs);

  return left;
}
