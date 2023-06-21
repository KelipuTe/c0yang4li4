#include <stdio.h>

int globalI = 1024;
// 00000000,00000000,00000100,00000000(2进制);
// ___0___0,___0___0,___0___4,___0___0(16进制);

int main() {
  printf("globalI=%d(10),globalI=%x(16),&globalI=%p\n", globalI, globalI, &globalI);
  // 数据在内存里是按小端字节序存储的，所以，下面的输出依次是：00、04、00、00。
  printf("globalI[0]=%x,&globalI[0]=%p\n", *(char *)&globalI, (char *)&globalI);
  printf("globalI[1]=%x,&globalI[1]=%p\n", *((char *)&globalI + 1), ((char *)&globalI + 1));
  printf("globalI[2]=%x,&globalI[2]=%p\n", *((char *)&globalI + 2), ((char *)&globalI + 2));
  printf("globalI[3]=%x,&globalI[3]=%p\n", *((char *)&globalI + 3), ((char *)&globalI + 3));
  return 0;
}
