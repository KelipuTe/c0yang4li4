#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("[debug]:parent, getpid()=%d\n", getpid());
  pid_t forkResult = fork();

  if (forkResult < 0) {
    printf("[error]:fock(), failed\n");
    printf("[error]:errno=%d, strerror=%s\n", errno, strerror(errno));
  } else if (0 == forkResult) {
    printf("[debug]:child, getpid()=%d, forkResult=%d\n", getpid(), forkResult);

    exit(0);
  } else {
    int status;
    pid_t exitPID = waitpid(-1, &status, 0);
    printf("[debug]:parent, waitpid(), exitPID=%d, status=%d\n", exitPID, status);

    if (WIFEXITED(status)) {
      printf("[error]:WIFEXITED()!=0, WEXITSTATUS()=%d\n", WEXITSTATUS(status));
    }
  }

  return 0;
}