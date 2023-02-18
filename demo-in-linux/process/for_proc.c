#include <stdio.h>
#include <unistd.h>

int main() {
  printf("[debug]:getpid()=%d\n", getpid());
  while (1) {
    sleep(10);
  }
  return 0;
}