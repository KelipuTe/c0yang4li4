#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid = fork();

  if (pid == 0) {
    printf("child,pid=%d\r\n", getpid());
    // 定义一个指向字符数组的指针常量，指针不可修改，但是字符数组可以改
    char *const argv2[] = {"aaa", "bbb"};
    int ret = execv("execv02", argv2);
    // execv直接用新的可执行文件的代码覆盖了子进程原来的代码
    // 所以从这里开始，后面的代码并没有执行
    printf("ret=%d\r\n", ret);

    return 0;
  }

  int status;
  pid = wait(&status);
  // 这里返回值会拿到256，但是用strace看，子进程退出状态码确实是1。
  // 这个问题不用深究。
  if (pid > 0) {
    printf("child exit,pid=%d,status=%d\r\n", pid, status);
  }

  return 0;
}