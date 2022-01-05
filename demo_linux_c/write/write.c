#include <unistd.h>

int main() {
  // write(2)
  // #include <unistd.h>
  // write to a file descriptor，向一个文件描述符写入数据
  // linux进程默认情况下会有3个缺省打开的文件描述符，分别是标准输入=0， 标准输出=1， 标准错误=2
  write(1, "hello, world\r\n", 14);
  return 0;
}