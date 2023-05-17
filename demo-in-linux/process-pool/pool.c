#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 简单的进程池
// 父进程轮询调用子进程并传递数据，子进程输出父进程传过来的数据
// 父子进程之间通过匿名管道传递数据，父进程通过命名管道接收外部输入

// 程序运行标志，1=运行，2=停止，默认1
static int runningSymbol = 1;
// 命名管道，用于接收外部输入
char readPipePath[] = "/tmp/process_pool_fifo";

// 进程池中进程的数据
typedef struct processItem {
  pid_t pid;     // 进程 id
  int pipefd[2]; // 管道，用于父子进程通信
} processItem;

// 进程池
typedef struct processPool {
  int processNum;         // 进程的数量
  processItem *a5process; // 进程的数据
  int callTimes;          // 进程池被调用次数
} processPool;

// 信号处理函数
void signalHandler(int signalNo) {
  printf("[debug]:signalHandler(), pid=%d, signal_no=%d\n", getpid(), signalNo);
  runningSymbol = 0;
}

int main() {
  processPool pool;
  processPool *p7pool;

  pid_t tempPID;
  int pipeResult;
  int readByteNum;
  int mkfifoResult;
  int waitpidStatus;

  printf("[debug]:parent, pid=%d,start\n", getpid());

  // 处理中断（ctrl+c），退出（ctrl+/），终止（kill pid）信号
  signal(SIGINT, signalHandler);
  signal(SIGQUIT, signalHandler);
  signal(SIGTERM, signalHandler);

  p7pool = &pool;

  p7pool->processNum = 3;
  p7pool->a5process = (processItem *)malloc(sizeof(processItem) * p7pool->processNum);
  p7pool->callTimes = 0;

  for (int i = 0; i < p7pool->processNum; i++) {
    // 匿名管道
    pipeResult = pipe(p7pool->a5process[i].pipefd);
    if (0 != pipeResult) {
      printf("[debug]:parent, processItem=%d, pipe() fail\n", i);
      printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));
      return 0;
    }

    // fork 进程
    p7pool->a5process[i].pid = fork();
    if (-1 == p7pool->a5process[i].pid) {
      printf("[debug]:parent, processItem=%d, fork() fail\n", i);
      printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));
      return 0;
    }
    if (0 == p7pool->a5process[i].pid) {
      // child
      printf("[debug]:child, pid=%d, start\n", getpid());

      // 关闭写管道
      close(p7pool->a5process[i].pipefd[1]);
      // 设置 read() 非阻塞
      int pipefd = p7pool->a5process[i].pipefd[0];
      // 把文件设置为非阻塞模式，非阻塞的文件描述符称为非阻塞 IO
      // F_GETFL 表示获取文件描述符的状态
      int option = fcntl(pipefd, F_GETFL);
      // 这个写法表示在原有的基础上附加 O_NONBLOCK
      // O_NONBLOCK 会让 read() 在没有数据时，直接返回 EAGAIN 错误，而不是阻塞
      option = option | O_NONBLOCK;
      // F_SETFL 表示修改文件描述符的状态
      fcntl(pipefd, F_SETFL, option);

      char msg[1024] = {0};
      while (runningSymbol) {
        readByteNum = read(pipefd, msg, sizeof(msg));
        if (-1 == readByteNum && errno == EAGAIN) {
          continue;
        }
        if (0 == readByteNum) {
          break;
        }
        printf("[debug]:child, pid=%d, readByteNum=%d, msg=%s\n", getpid(), readByteNum, msg);
        memset(msg, 0, sizeof(msg));
      }

      close(pipefd);

      printf("[debug]:child, pid=%d, exit\n", getpid());

      return 0;
    } else {
      // parent

      // 关闭读管道
      close(p7pool->a5process[i].pipefd[0]);

      continue;
    }
  }

  // 命名管道，用于接收外部输入
  if (access(readPipePath, F_OK)) {
    mkfifoResult = mkfifo(readPipePath, 0666);
    if (0 != mkfifoResult) {
      printf("[debug]:parent, mkfifo() fail\n");
      printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));
      return 0;
    }
  }

  int readPipeFd = open(readPipePath, O_RDONLY);
  int option = fcntl(readPipeFd, F_GETFL);
  option = option | O_NONBLOCK;
  fcntl(readPipeFd, F_SETFL, option);

  char msg[1024] = {0};
  while (runningSymbol) {
    readByteNum = read(readPipeFd, msg, sizeof(msg));
    if (-1 == readByteNum && errno == EAGAIN) {
      continue;
    }
    if (0 == readByteNum) {
      break;
    }

    // 轮询
    p7pool->callTimes++;
    int childPID = p7pool->callTimes % p7pool->processNum;
    printf("[debug]:parent, call child=%d\n", childPID);
    write(p7pool->a5process[childPID].pipefd[1], msg, sizeof(msg));

    // strncasecmp(3)，比较两个字符串，忽略大小写
    if (0 == strncasecmp("exit", msg, 4)) {
      // 如果收到 exit 字符串，就退出
      break;
    }
  }

  // 关闭所有子进程
  for (int i = 0; i < p7pool->processNum; i++) {
    // 关闭每个子进程的写管道
    close(p7pool->a5process[i].pipefd[1]);
    // kill(2)，向子进程发送 SIGKILL 信号
    kill(p7pool->a5process[i].pid, SIGKILL);
  }
  // 获取每个子进程退出的状态
  for (int i = 0; i < p7pool->processNum; i++) {
    tempPID = waitpid(-1, &waitpidStatus, 0);
    if (tempPID > 0) {
      printf("[debug]:child, pid=%d, exit, exit status=%d\n", tempPID, waitpidStatus);
    }
  }

  close(readPipeFd);

  printf("[debug]:parent, pid=%d, exit\n", getpid());

  return 0;
}