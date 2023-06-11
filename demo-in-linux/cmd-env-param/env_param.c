#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
  printf("argc=%d\n", argc);

  while (*envp) {
    printf("envp=%s\n", *envp);
    envp++;
  }

  return 0;
}