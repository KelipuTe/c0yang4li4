#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

int main() {
  printf("[debug]:parent, getpid()=%d\n", getpid());
  printf("[debug]:parent, getpid()=%d", getpid());
  return 0;
  // return 300;
  // exit(300);
  // _exit(0);
  // _Exit(0);
  // syscall(SYS_exit_group, 0);
  // abort();
}