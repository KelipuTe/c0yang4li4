#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
  printf("argc=%d\r\n", argc);

  while (*envp) {
    printf("envp=%s\r\n", *envp);
    envp++;
  }

  return 0;
}