#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid == -1) {
    printf("fock error\r\n");
  }

  // 父进程会拿到子进程pid，子进程会拿到0
  if (pid == 0) {
    printf("child pid=%d\r\n", pid);
  } else {
    sleep(2);
    printf("parent pid=%d\r\n", pid);
  }

  return 0;
}