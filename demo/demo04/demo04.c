#include <unistd.h>

int main() {
  write(1, "hello,world\r\n", 13);
  return 0;
}