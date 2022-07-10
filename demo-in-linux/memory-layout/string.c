#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char arr1Statically[16] = "arr1Statically1";
  printf("arr1Statically  value=%p\r\n", arr1Statically);
  printf("arr1Statically  value=%s\r\n", arr1Statically);

  char *p1Statically = "p1Statically1";
  printf("p1Statically    value=%p\r\n", p1Statically);
  printf("p1Statically    value=%s\r\n", p1Statically);

  p1Statically = "p1Statically2";
  printf("p1Statically    value=%p\r\n", p1Statically);
  printf("p1Statically    value=%s\r\n", p1Statically);

  char *p1Dynamically = malloc(sizeof(char) * 16);
  strcpy(p1Dynamically, "p1Dynamically1");
  printf("p1Dynamically   value=%p\r\n", p1Dynamically);
  printf("p1Dynamically   value=%s\r\n", p1Dynamically);
  printf("malloc_usable_size=%ld\r\n", malloc_usable_size(p1Dynamically));

  free(p1Dynamically);
  p1Dynamically = NULL;

  return 0;
}