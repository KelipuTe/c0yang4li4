#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  printf("[debug]:getpid()=%d\n", getpid());
  const char *arg1 = "aaa";
  char *arg2 = "bbb";
  // 如果底层的 execve() 成功，后面的代码不会执行。
  // 如果底层的 execve() 失败，后面的代码会执行。
  int execResult = execl("call_by_exec", arg1, arg2, NULL);
  printf("[error]:execl(), failed, execResult=%d\n", execResult);
  printf("[error]:errno=%d, strerror=%s\n", errno, strerror(errno));
  return 0;
}