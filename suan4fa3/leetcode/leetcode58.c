#include <stdio.h>
#include <string.h>

/*#####leetcode58-最后一个单词的长度#####*/

int lengthOfLastWord(char *s) {
    int iStrLen = 0, iLastLen = 0;

    iStrLen = strlen(s);
    for (int i = iStrLen - 1; i >= 0; i--) {
        if (s[i] == ' ' && iLastLen == 0) {
            continue;
        }
        if (s[i] != ' ') {
            iLastLen++;
        } else {
            break;
        }
    }

    return iLastLen;
}

int main() {
    // char sStr[] = "Hello World";
    // char sStr[] = "Hello";
    // char sStr[] = "Hello ";
    // char sStr[] = " Hello";
    char sStr[] = " ";

    int iLastLen = 0;
    iLastLen = lengthOfLastWord(sStr);
    printf("%d\n", iLastLen);
}