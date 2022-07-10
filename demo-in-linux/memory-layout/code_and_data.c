#include <stdio.h>

int x = 1 << 4;
// 0b 00000000 00000000 00000000 00010000
// 0x    0   0    0   0    0   0    1   0
// 0x 10 00 00 00 --小端字节序

int y = 1 << 8;
// 0b 00000000 00000000 00000001 00000000
// 0x    0   0    0   0    0   1    0   0
// 0x 00 01 00 00 --小端字节序

int func1(int a) {
  return a + (1 << 4);
}

int func2(int b) {
  return b + (1 << 8);
}

int main() {
  printf("&x start address=%p\r\n", &x);
  printf("&x   end address=%p\r\n", (char*)&x + sizeof(int)-1);
  // &x 取到的是 int*，后面 +4 时指针会移动 4 个 int 的长度
  // 把 &x 强转成 char*，后面 +4 时指针会移动 4 个 char 的长度

  printf("&y start address=%p\r\n", &y);
  printf("&y   end address=%p\r\n", (char*)&y + sizeof(int)-1);

  int a = 1 << 4;
  printf("&a start address=%p\r\n", &a);

  func1(a);

  int b = 1 << 8;
  printf("&b start address=%p\r\n", &b);

  func2(b);

  return 0;
}