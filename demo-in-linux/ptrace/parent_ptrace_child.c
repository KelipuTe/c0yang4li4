#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("parent,getpid()=%d\n", getpid());

  int data = 0;

  pid_t pid = fork();
  if (pid == -1) {
    printf("parent,fock() failed\n");
    printf("errno=%d,strerror=%s\n", errno, strerror(errno));
    exit(0);
  }

  if (pid == 0) {
    data = 200;
    while (1) {
      printf("child,getpid()=%d,data=%x,&data=%p\n", getpid(), data, &data);
      sleep(2);
    }
  }

  sleep(2);

  // 跟踪进程附加目标进程
  // 当附加操作成功后，调用进程（父进程）成为跟踪进程，目标进程（子进程）成为被跟踪进程。
  // 跟踪进程获得了检查和修改被跟踪进程的内存、寄存器、执行状态的能力。被追踪进程通常被停止或中断，进入停止状态。
  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
    printf("parent,ptrace() PTRACE_ATTACH failed\n");
    printf("errno=%d,strerror=%s\n", errno, strerror(errno));
    exit(0);
  }

  // 跟踪进程调用 waitpid() 的目的是，确保目标进程已经被成功附加。
  // 当跟踪进程使用 ptrace() 附加到目标进程时，跟踪进程会请求操作系统附加到目标进程并开始追踪它。
  // 然而，附加过程可能不是瞬间完成的，目标进程可能不会立即停止或处于可追踪的状态。
  // 一旦 waitpid() 返回，就表明目标进程已经停止，跟踪进程可以继续进行后面的操作。
  waitpid(pid, NULL, 0);

  long dataInMemory;

  // 跟踪进程读取目标进程内存上的数据
  dataInMemory = ptrace(PTRACE_PEEKDATA, pid, (void *)&data, NULL);
  printf("parent,&data=%p,dataInMemory=%lx\n", &data, dataInMemory);

  // 跟踪进程修改目标进程内存上的数据
  if (ptrace(PTRACE_POKEDATA, pid, (void *)&data, (void *)100) == -1) {
    printf("parent,ptrace() PTRACE_POKEDATA failed\n");
    printf("errno=%d,strerror=%s\n", errno, strerror(errno));
    exit(0);
  }

  // 跟踪进程脱离目标进程
  if (ptrace(PTRACE_DETACH, pid, NULL, NULL) == -1) {
    printf("parent,ptrace() PTRACE_DETACH failed\n");
    printf("errno=%d,strerror=%s\n", errno, strerror(errno));
    exit(0);
  }

  return 0;
}