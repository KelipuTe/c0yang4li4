#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
  printf("[debug]:parent, getpid()=%d\n", getpid());
  pid_t forkResult = fork();

  if (forkResult < 0) {
    printf("[error]:fock(), failed\n");
    printf("[error]:errno=%d, strerror=%s\n", errno, strerror(errno));
  } else if (0 == forkResult) {
    int setpriorityResult = setpriority(PRIO_PROCESS, getpid(), 5);
    printf("[debug]:child, setpriorityResult=%d\n", setpriorityResult);
    int getpriorityResult = getpriority(PRIO_PROCESS, getpid());
    printf("[debug]:child, getpriorityResult=%d\n", getpriorityResult);
    for (long i = 0; i < 4000000000; i++) {
    }
    printf("[debug]:child, getpid()=%d\n", getpid());
  } else {
    int setpriorityResult = setpriority(PRIO_PROCESS, getpid(), 10);
    printf("[debug]:parent, setpriorityResult=%d\n", setpriorityResult);
    int getpriorityResult = getpriority(PRIO_PROCESS, getpid());
    printf("[debug]:parent, getpriorityResult=%d\n", getpriorityResult);
    for (long i = 0; i < 4000000000; i++) {
    }
    printf("[debug]:parent, getpid()=%d\n", getpid());
  }

  return 0;
}
