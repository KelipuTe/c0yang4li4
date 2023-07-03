#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int CONTROL_TAG = 20000;

typedef struct s6OnePairAddress {
  unsigned long start;
  unsigned long end;
} s6OnePairAddress;

s6OnePairAddress f8FindStackRangeByPid(pid_t pid) {
  s6OnePairAddress addressRange;
  addressRange.start = 0;
  addressRange.end = 0;

  // 拼 /proc/{pid}/maps 的全路径
  char mapsPath[256];
  snprintf(mapsPath, sizeof(mapsPath), "/proc/%d/maps", pid);
  // 读取 maps
  FILE *mapsFile = fopen(mapsPath, "r");
  if (NULL == mapsFile) {
    perror("fopen");
    return addressRange;
  }

  char eachLine[256];
  while (NULL != fgets(eachLine, sizeof(eachLine), mapsFile)) {
    // 通过 maps 里的 "[stack]" 字符串，找到栈的地址信息
    if (strstr(eachLine, "[stack]") != NULL) {
      sscanf(eachLine, "%lx-%lx", &addressRange.start, &addressRange.end);
      printf("stack address range=[0x%lx,0x%lx]\n", addressRange.start, addressRange.end);
      break;
    }
  }

  fclose(mapsFile);
  return addressRange;
}

void f8PrintDataAtAddressRange(s6OnePairAddress addressRange) {
  char *t4address = (char *)addressRange.start;
  int index = 0;
  for (; t4address < (char *)addressRange.end; t4address++) {
    if (0 == index) {
      printf("address=%p,", t4address);
    }
    printf("%02x,", *t4address);
    index++;
    if (16 == index) {
      printf("\n");
      index = 0;
    }
  }
  return;
}

int main() {
  int tag = 20000;
  pid_t pid = getpid();
  // s6OnePairAddress addressRange = f8FindStackRangeByPid(pid);
  // f8PrintDataAtAddressRange(addressRange);
  while (CONTROL_TAG == tag) {
    printf("getpid()=%d,tag=%d(10),tag=%x(16),&tag=%p\n", pid, tag, tag, &tag);
    sleep(2);
  }
  // 我要让它跑到这里
  printf("getpid()=%d,tag=%d(10),tag=%x(16),&tag=%p\n", pid, tag, tag, &tag);
  return 0;
}