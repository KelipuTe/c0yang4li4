#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("parent,getpid()=%d\r\n", getpid());
  pid_t pid = fork();

  if (pid == 0) {
    printf("child,getpid()=%d\r\n", getpid());
    // 定义一个指向字符数组的指针常量，指针不可修改，但是字符数组可以改
    char *const argv[] = {"aaa", "bbb"};
    // exec(3)
    // #include <unistd.h>
    // execute a file，执行文件
    // execv()直接用新的可执行文件的代码覆盖了子进程原来的代码
    // 所以从调用execv()这里开始，后面的代码不会执行
    int rtvl = execv("call", argv);

    printf("child,rtvl=%d\r\n", rtvl);

    return 0;
  }

  int status;
  pid = wait(&status);
  // 这里返回值会拿到256，但是用strace看，子进程退出状态码确实是1。
  // 这个问题不用深究。
  if (pid > 0) {
    printf("parent,child exit,getpid()=%d,status=%d\r\n", getpid(), status);
  }

  return 0;
}