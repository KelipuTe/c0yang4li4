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

// 全局变量

// 程序运行标志，1=运行，2=停止，默认1
static int running_symbol = 1;
// 命名管道，用于接收外部输入
char read_pipe_path[] = "/tmp/process_pool/pool_fifo";

// 进程个体
typedef struct process_item {
  pid_t pid;     //进程id
  int pipefd[2]; //管道，用于父子进程通信
} process_item;

// 进程池
typedef struct process_pool {
  int process_num;                //进程数量
  process_item *arr1process_item; //长度不定的结构体数组，用指针表示
  int call_times;                 //调用次数
} process_pool;

// 信号处理函数
void signal_handler(int signal_no) {
  printf("signal_handler,pid=%d,signal_no=%d\r\n", getpid(), signal_no);
  running_symbol = 0;
}

int main() {
  process_pool pool;
  process_pool *p1pool;

  pid_t temp_pid;
  int temp_retval;

  p1pool = &pool;

  printf("parent,pid=%d,start\r\n", getpid());

  //处理中断，退出，终止信号
  signal(SIGINT, signal_handler);
  signal(SIGQUIT, signal_handler);
  signal(SIGTERM, signal_handler);

  p1pool->process_num = 3;
  p1pool->arr1process_item = (process_item *)malloc(sizeof(process_item) * p1pool->process_num);
  p1pool->call_times = 0;

  for (int i = 0; i < p1pool->process_num; i++) {
    temp_retval = pipe(p1pool->arr1process_item[i].pipefd);
    if (0 != temp_retval) {
      printf("parent,process_item=%d,pipe fail\r\n", i);
      printf("errno=%d,strerror=%s\r\n", errno, strerror(errno));
      return 0;
    }

    // fork进程
    p1pool->arr1process_item[i].pid = fork();
    if (-1 == p1pool->arr1process_item[i].pid) {
      printf("parent,process_item=%d,fork fail\r\n", i);
      printf("errno=%d,strerror=%s\r\n", errno, strerror(errno));
      return 0;
    }
    if (0 == p1pool->arr1process_item[i].pid) {
      // child
      printf("child,pid=%d,start\r\n", getpid());

      // 关闭写管道
      close(p1pool->arr1process_item[i].pipefd[1]);
      // 设置read()非阻塞
      int pipefd = p1pool->arr1process_item[i].pipefd[0];
      // fcntl(2)，F_GETFL表示获取文件描述符
      int option = fcntl(pipefd, F_GETFL);
      // O_NONBLOCK会让read()在没有数据时，直接返回EAGAIN错误，而不是阻塞
      option = option | O_NONBLOCK;
      // fcntl(2)，F_SETFL表示修改文件描述符
      fcntl(pipefd, F_SETFL, option);

      char msg[1024] = {0};
      while (running_symbol) {
        temp_retval = read(pipefd, msg, sizeof(msg));
        if (temp_retval == -1 && errno == EAGAIN) {
          continue;
        }
        if (temp_retval == 0) {
          break;
        }
        printf("child,pid=%d,read bytes=%d,msg=%s\r\n", getpid(), temp_retval, msg);
        memset(msg, 0, sizeof(msg));
      }

      close(pipefd);

      printf("child,pid=%d,exit\r\n", getpid());

      return 0;
    } else {
      // parent

      // 关闭读管道
      close(p1pool->arr1process_item[i].pipefd[0]);

      continue;
    }
  }

  // 创建命名管道，用于接收外部输入
  if (access(read_pipe_path, F_OK)) {
    temp_retval = mkfifo(read_pipe_path, 0666);
    if (0 != temp_retval) {
      printf("parent,mkfifo fail\r\n");
      printf("errno=%d,strerror=%s\r\n", errno, strerror(errno));
      return 0;
    }
  }

  int read_pipe_fd = open(read_pipe_path, O_RDONLY);
  int option = fcntl(read_pipe_fd, F_GETFL);
  option = option | O_NONBLOCK;
  fcntl(read_pipe_fd, F_SETFL, option);

  char msg[1024] = {0};
  while (running_symbol) {
    temp_retval = read(read_pipe_fd, msg, sizeof(msg));
    if (temp_retval == -1 && errno == EAGAIN) {
      continue;
    }
    if (temp_retval == 0) {
      break;
    }

    //轮询
    p1pool->call_times++;
    int child_id = p1pool->call_times % p1pool->process_num;
    printf("parent,call child=%d\r\n", child_id);
    write(p1pool->arr1process_item[child_id].pipefd[1], msg, sizeof(msg));

    // strncasecmp(3)，比较两个字符串，忽略大小写
    if (0 == strncasecmp("exit", msg, 4)) {
      // 如果收到exit字符串，就退出
      break;
    }
  }

  // 关闭所有子进程
  for (int i = 0; i < p1pool->process_num; i++) {
    // 关闭每个子进程的写管道
    close(p1pool->arr1process_item[i].pipefd[1]);
    // kill(2)，向子进程发送信号
    kill(p1pool->arr1process_item[i].pid, SIGKILL);
  }
  // 获取每个子进程退出的状态
  for (int i = 0; i < p1pool->process_num; i++) {
    temp_pid = waitpid(-1, &temp_retval, 0);
    if (temp_pid > 0) {
      printf("child,pid=%d,exit,exit status=%d\r\n", temp_pid, temp_retval);
    }
  }

  close(read_pipe_fd);

  printf("parent,pid=%d,exit\r\n", getpid());

  return 0;
}