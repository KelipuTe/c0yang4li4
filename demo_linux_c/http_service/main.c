#include "service.h"

http_service service = {
    .app_debug = 1,
    .ip = SERVICE_IP,
    .port = SERVICE_PORT,
    .backlog = CLIENT_MAX_NUM,
    .thread_num = 2,
    .call_num = 0,
    .socket_init = socket_init,
    .socket_bind_addr = socket_bind_addr,
    .socket_listen = socket_listen,
    .service_start = service_start,
};

// gcc -std=c99 main.c service.c thread.c reactor.c epoll.c connection.c -o main -lpthread

// 简单的http服务
// 实现了表单解析
int main() {
  printf("[info]:http service start,pid=%d\r\n", getpid());
  // 启动服务
  service.socket_init();
  service.socket_bind_addr();
  service.socket_listen();
  service.service_start();

  // 无限循环
  while (1) {
    sleep(1);
  }

  return 0;
}