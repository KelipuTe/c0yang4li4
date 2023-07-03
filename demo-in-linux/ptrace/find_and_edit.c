#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 通过文件名找到找到对应的进程 pid
int f8FindPidByFilename(char filename[64]) {
  pid_t pid = 0;

  // 读取 /proc 目录
  DIR *procDir = opendir("/proc");
  if (NULL == procDir) {
    perror("opendir");
    return pid;
  }

  // 遍历 /proc 目录下的每一项
  struct dirent *eachItem;
  while (1) {
    eachItem = readdir(procDir);
    if (NULL == eachItem) {
      break;
    }
    // 判断是不是目录，名字是不是由 0-9 的数字组成的
    if (eachItem->d_type == DT_DIR && isdigit(eachItem->d_name[0])) {
      // 拼 /proc/{pid}/cmdline 的全路径
      char cmdlinePath[512];
      snprintf(cmdlinePath, sizeof(cmdlinePath), "/proc/%s/cmdline", eachItem->d_name);
      // 读取 cmdline
      FILE *cmdlineFile = fopen(cmdlinePath, "r");
      if (NULL != cmdlineFile) {
        char cmdline[256];
        fgets(cmdline, sizeof(cmdline), cmdlineFile);
        // 通过 cmdline 里的启动命令含不含 filename 找到对应的进程 pid
        if (NULL != strstr(cmdline, filename)) {
          printf("pid=%s,cmdline=%s\n", eachItem->d_name, cmdline);
          pid = (pid_t)atoi(eachItem->d_name);
          break;
        }
        fclose(cmdlineFile);
      }
    }
  }
  closedir(procDir);
  return pid;
}

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

unsigned long f8FindIntValueInTraceeProcess(pid_t pid, s6OnePairAddress addressRange, int value) {
  unsigned long targetAddress = 0;

  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
    perror("ptrace(PTRACE_ATTACH)");
    return targetAddress;
  }

  if (waitpid(pid, NULL, 0) == -1) {
    perror("waitpid() after ptrace()");
    return targetAddress;
  }

  for (unsigned long t4address = addressRange.start; t4address < addressRange.end; t4address++) {
    long dataInMemory = ptrace(PTRACE_PEEKDATA, pid, t4address, NULL);
    if (dataInMemory == -1 && errno != 0) {
      perror("ptrace(PTRACE_PEEKDATA)");
      break;
    }

    // long 类型的变量 = 起始地址 + 8 个字节的数据
    // 把 long* 类型的地址强转成 int* 类型的地址 = 地址 + 前面 4 个字节的数据
    int valueInMemory = *((int *)&dataInMemory);
    if (valueInMemory == value) {
      printf("find data %d(10),%x(16) at address %lx\n", value, value, t4address);
      targetAddress = t4address;

      printf("t4address=%lx,", t4address);
      for (unsigned char *t4address2 = (unsigned char *)&dataInMemory; t4address2 < (unsigned char *)&dataInMemory + 8; t4address2++) {
        printf("%02x,", *t4address2);
      }
      printf("\n");
    }
  }
  if (ptrace(PTRACE_DETACH, pid, NULL, NULL) == -1) {
    perror("ptrace(PTRACE_DETACH)");
    return targetAddress;
  }

  return targetAddress;
}

void f8EditIntValueInTraceeProcess(pid_t pid, unsigned long targetAddress, int value) {
  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
    perror("ptrace(PTRACE_ATTACH)");
    return;
  }

  if (waitpid(pid, NULL, 0) == -1) {
    perror("waitpid() after ptrace()");
    return;
  }
  int value = 100;
      (ptrace(PTRACE_POKEDATA, pid, (void *)targetAddress, (void *)value)
  if (ptrace(PTRACE_POKEDATA, pid, (void *)targetAddress, (void *)value) == -1) {
    perror("ptrace(PTRACE_POKEDATA)");
    return;
  }

  printf("edit data at address %lx to %d(10),%x(16)\n", targetAddress, value, value);

  if (ptrace(PTRACE_DETACH, pid, NULL, NULL) == -1) {
    perror("ptrace(PTRACE_DETACH)");
    return;
  }
}

int main() {
  printf("getpid()=%d\n", getpid());

  char filename[64] = "target_process.elf";
  pid_t pid = f8FindPidByFilename(filename);
  if (0 == pid) {
    printf("f8FindPidByFilename failed\n");
    return 0;
  } else {
    printf("f8FindPidByFilename=%d\n", pid);
  }

  s6OnePairAddress addressRange = f8FindStackRangeByPid(pid);
  if (0 == addressRange.start && 0 == addressRange.end) {
    printf("f8FindStackRangeByPid failed\n");
    return 0;
  } else {
    printf("f8FindStackRangeByPid=[0x%lx,0x%lx]\n", addressRange.start, addressRange.end);
  }

  unsigned long targetAddress = 0;
  for (int i = 0; i < 2; i++) {
    targetAddress = f8FindIntValueInTraceeProcess(pid, addressRange, 20000);
    if (0 == targetAddress) {
      printf("f8FindIntValueInTraceeProcess failed\n");
      return 0;
    } else {
      printf("f8FindIntValueInTraceeProcess=0x%lx\n", targetAddress);
    }
  }

  f8EditIntValueInTraceeProcess(pid, targetAddress, 100);

  return 0;
}