#include <stdio.h>

int main()
{
    printf("hello world!");
    int m[10];
    for (int i = 0; i < 10; i++)
    {
        m[i] = i * 2;
    }
    printf("%d", m[5]);
    return 0;
}