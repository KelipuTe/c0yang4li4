#include <stdio.h>

int main() {
  printf("hello world\n");

  int count = 13;
  int from2=0,to2=0;
  int *from = &from2, *to  =&to2;
  switch (count % 8) {
    case 0: do {  *to = *from++;
    case 7:       *to = *from++;
    case 6:       *to = *from++;
    case 5:       *to = *from++;
    case 4:       *to = *from++;
    case 3:       *to = *from++;
    case 2:       *to = *from++;
    case 1:       *to = *from++;
            } while ((count -= 8) > 0);
  }

  return 0;
}