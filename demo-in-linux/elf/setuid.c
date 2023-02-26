#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  char filepath[] = "./seteuid.c";
  int uid = getuid();
  int euid = geteuid();

  printf("[debug]:uid=%d, euid=%d\n", uid, euid);
  if (0 == access(filepath, W_OK)) {
    printf("[debug]:write ok\n");
  } else {
    printf("[debug]:write not ok\n");
  }

  setuid(euid);

  printf("[debug]:uid=%d, euid=%d\n", getuid(), euid);
  if (0 == access(filepath, W_OK)) {
    printf("[debug]:write ok\n");
  } else {
    printf("[debug]:write not ok\n");
  }

  setuid(uid);

  printf("[debug]:uid=%d, euid=%d\n", getuid(), euid);
  if (0 == access(filepath, W_OK)) {
    printf("[debug]:write ok\n");
  } else {
    printf("[debug]:write not ok\n");
  }

  return 0;
}
