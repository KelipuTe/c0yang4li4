#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = 2818;

  printf("find pid by elf name,pid=%d\n", pid);

  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
    printf("ptrace() PTRACE_ATTACH failed\n");
    printf("errno=%d,strerror=%s\n", errno, strerror(errno));
    exit(0);
  }

  waitpid(pid, NULL, 0);

  long dataInMemory;

  int *p7 = (int *)0x7ffd8cdb34c4;
  int num = 100;

  dataInMemory = ptrace(PTRACE_PEEKDATA, pid, (void *)p7, NULL);
  printf("find target num in addr=%p\n", p7);
  printf("data in memory is=%d(10), data in memory is=%x(16)\n", (int)dataInMemory,(int)dataInMemory);

  // 跟踪进程修改目标进程内存上的数据
  if (ptrace(PTRACE_POKEDATA, pid, (void *)p7, (void *)100) == -1) {
    printf("ptrace() PTRACE_POKEDATA failed\n");
    printf("errno=%d,strerror=%s\n", errno, strerror(errno));
    exit(0);
  }

  printf("edit data to %d(10),%x(16)\n", num, num);

  // 跟踪进程脱离目标进程
  if (ptrace(PTRACE_DETACH, pid, NULL, NULL) == -1) {
    printf("ptrace() PTRACE_DETACH failed\n");
    printf("errno=%d,strerror=%s\n", errno, strerror(errno));
    exit(0);
  }

  return 0;
}