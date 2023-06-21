#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("pid=%d\n", getpid());

  int a5I[4] = {2, 4, 8, 16};
  printf("&a5I=%p\n", a5I);
  printf("&a5I[0]=%p\n", &a5I[0]);
  printf("&a5I[1]=%p\n", &a5I[1]);
  printf("&a5I[2]=%p\n", &a5I[2]);
  printf("&a5I[3]=%p\n", &a5I[3]);

  int a5J[2][2] = {32, 64, 128, 256};
  printf("&a5J=%p\n", a5J);
  printf("&a5J[0][0]=%p\n", &a5J[0][0]);
  printf("&a5J[0][1]=%p\n", &a5J[0][1]);
  printf("&a5J[1][0]=%p\n", &a5J[1][0]);
  printf("&a5J[1][1]=%p\n", &a5J[1][1]);

  int(*p7a5K)[4];
  p7a5K = malloc(sizeof(int[4]));
  (*p7a5K)[0] = 2;
  (*p7a5K)[1] = 4;
  (*p7a5K)[2] = 8;
  (*p7a5K)[3] = 16;
  int *p7k = (int *)p7a5K;
  printf("&p7a5K=%p\n", p7a5K);
  printf("(*p7a5K)[0]=%d,&(*p7a5K)[0]=%p,p7k=%d,p7k=%p\n", (*p7a5K)[0], &(*p7a5K)[0], *p7k, p7k);
  printf("(*p7a5K)[1]=%d,&(*p7a5K)[1]=%p,p7k+1=%d,p7k+1=%p\n", (*p7a5K)[1], &(*p7a5K)[1], *(p7k + 1), p7k + 1);
  printf("(*p7a5K)[2]=%d,&(*p7a5K)[2]=%p,p7k+2=%d,p7k+2=%p\n", (*p7a5K)[2], &(*p7a5K)[2], *(p7k + 2), p7k + 2);
  printf("(*p7a5K)[3]=%d,&(*p7a5K)[3]=%p,p7k+3=%d,p7k+3=%p\n", (*p7a5K)[3], &(*p7a5K)[3], *(p7k + 3), p7k + 3);

  int(*p7a5L)[2][2];
  p7a5L = malloc(sizeof(int[2][2]));
  (*p7a5L)[0][0] = 32;
  (*p7a5L)[0][1] = 64;
  (*p7a5L)[1][0] = 128;
  (*p7a5L)[1][1] = 256;
  int(*p7l)[2] = (int(*)[2])p7a5L; // 二维数组的元素是一维数组
  int *p7ll = (int *)p7l;          // 一维数组的元素才是一个元素
  printf("&p7a5L=%p\n", p7a5L);
  printf("(*p7a5L)[0]=%p,p7l=%p\n", &(*p7a5L)[0], p7l); // 二维数组第一行
  printf("(*p7a5L)[0][0]=%d,&(*p7a5L)[0][0]=%p,p7ll=%d,p7ll=%p\n", (*p7a5L)[0][0], &(*p7a5L)[0][0], *p7ll, p7ll);
  printf("(*p7a5L)[0][1]=%d,&(*p7a5L)[0][1]=%p,p7ll+1=%d,p7ll+1=%p\n", (*p7a5L)[0][1], &(*p7a5L)[0][1], *p7ll + 1, p7ll + 1);
  p7ll = (int *)(p7l + 1);
  printf("(*p7a5L)[1]=%p,p7l+1=%p\n", &(*p7a5L)[1], p7l + 1); // 二维数组第二行
  printf("(*p7a5L)[1][0]=%d,&(*p7a5L)[1][0]=%p,p7ll=%d,p7ll=%p\n", (*p7a5L)[1][0], &(*p7a5L)[1][0], *p7ll, p7ll);
  printf("(*p7a5L)[1][0]=%d,&(*p7a5L)[1][1]=%p,p7ll+1=%d,p7ll+1=%p\n", (*p7a5L)[1][0], &(*p7a5L)[1][1], *(p7ll + 1), p7ll + 1);

  free(p7a5K);
  free(p7a5L);

  return 0;
}