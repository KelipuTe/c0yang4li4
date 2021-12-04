#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
  printf("argc=%d\r\n", argc);

  while (*argv) {
    printf("argc=%s\r\n", *argv);
    argv++;
  }

  while (*envp) {
    printf("envp=%s\r\n", *envp);
    envp++;
  }

  return 0;
}