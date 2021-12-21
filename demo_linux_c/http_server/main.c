#include "service.h"

service service1 = {
    .ip = "0.0.0.0",
    .port = 9501,
    .backlog = 1024,
    .thread_num = 2,
    .my_init_socket = my_init_socket,
    .my_bind = my_bind,
    .my_listen = my_listen,
    .my_run = my_run,
};

int main() {
  printf("tcp server start,pid=%d\r\n", getpid());

  service1.my_init_socket();
  service1.my_bind();
  service1.my_listen();
  service1.my_run();

  while (1) {
    sleep(1);
  }

  return 0;
}