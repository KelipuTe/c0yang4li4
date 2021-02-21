#include <stdio.h>
#include <string.h>

/*#####leetcode20-有效的括号#####*/

int isValid(char *s) {
    char arr[10001] = {'\0'};
    int iStrLen = 0, iIndex = 0;

    iStrLen = strlen(s);
    for (int i = 0; i < iStrLen; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            arr[iIndex] = s[i];
            iIndex++;
        } else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
            if (iIndex == 0) {
                return 0;
            }
            if (s[i] == ')' && arr[iIndex - 1] == '(') {
                iIndex--;
            } else if (s[i] == ']' && arr[iIndex - 1] == '[') {
                iIndex--;
            } else if (s[i] == '}' && arr[iIndex - 1] == '{') {
                iIndex--;
            } else {
                return 0;
            }
        }
    }
    if (iIndex == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    // char sStr[] = {"()"};
    // char sStr[] = {"()[]"};
    char sStr[] = {"([)]"};
    int ibRes = 0;

    ibRes = isValid(sStr);
    printf("%d\n", ibRes);
}