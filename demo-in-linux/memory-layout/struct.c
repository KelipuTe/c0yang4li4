#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
  char *name;
  int age;
  char sex;
} Person;

int main() {
  printf("sizeof(Person) value=%ld\r\n", sizeof(struct Person));

  struct Person a, *p1b;

  a.name = (char *)malloc(sizeof(char) * 16);
  memcpy(a.name, "aaa", sizeof("aaa"));
  a.age = 18;
  a.sex = 'f';

  printf("sizeof(a) value=%ld\r\n", sizeof(a));
  printf("&a        value=%p\r\n", &a);
  printf("&a.name   value=%p\r\n", &a.name);
  printf("&a.age    value=%p\r\n", &a.age);
  printf("&a.sex    value=%p\r\n", &a.sex);

  p1b = (struct Person *)malloc(sizeof(struct Person));
  p1b->name = (char *)malloc(sizeof(char) * 16);
  memcpy(p1b->name, "bbb", sizeof("bbb"));
  p1b->age = 18;
  p1b->sex = 'f';

  printf("sizeof(p1b) value=%ld\r\n", sizeof(struct Person *));
  printf("p1b          value=%p\r\n", p1b);
  printf("&p1b->name   value=%p\r\n", &p1b->name);
  printf("&p1b->age    value=%p\r\n", &p1b->age);
  printf("&p1b->sex    value=%p\r\n", &p1b->sex);

  free(p1b->name);
  free(p1b);

  return 0;
}