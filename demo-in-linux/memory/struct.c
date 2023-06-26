#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

struct Person {
  char *name;
  int age;
  char sex;
} Person;

int main() {
  printf("pid=%d\n", getpid());

  struct Person s6a, *p7b;

  s6a.name = (char *)malloc(sizeof(char) * 16);
  memcpy(s6a.name, "aaa", sizeof("aaa"));
  s6a.age = 18;
  s6a.sex = 'f';

  printf("sizeof(s6a)=%ld\n", sizeof(s6a));
  printf("&s6a=%p\n", &s6a);
  printf("&s6a.name=%p\n", &s6a.name);
  printf("s6a.name=%p\n", s6a.name);
  printf("&s6a.age=%p\n", &s6a.age);
  printf("&s6a.sex=%p\n", &s6a.sex);

  p7b = (struct Person *)malloc(sizeof(struct Person));
  p7b->name = (char *)malloc(sizeof(char) * 16);
  memcpy(p7b->name, "bbb", sizeof("bbb"));
  p7b->age = 18;
  p7b->sex = 'f';

  printf("sizeof(p7b)=%ld\n", sizeof(p7b));
  printf("p7b=%p\n", p7b);
  printf("&p7b->name=%p\n", &p7b->name);
  printf("p7b->name=%p\n", p7b->name);
  printf("&p7b->age=%p\n", &p7b->age);
  printf("&p7b->sex=%p\n", &p7b->sex);

  free(p7b->name);
  free(p7b);

  return 0;
}