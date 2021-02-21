#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####leetcode14-最长公共前缀#####*/

char *longestCommonPrefix(char **strs, int strsSize) {
    int iOneCharSize = sizeof(char), iOneLineSize = sizeof(char) * 201;
    char *sResStr = malloc(iOneLineSize);

    memset(sResStr, 0, iOneLineSize);

    if (strsSize == 0) {
        return sResStr;
    }
    {
        // 传进来的二维指针会失去在外面时候作为二维数组的指针的作用
        // 原来+1=移动数组的一行；现在+1真的就是移动一个字节；甚至不是移动一个char的长度
        int i = 0, j = 0, ibBreak = 0;
        char tc = '\0';
        while (1) {
            tc = *(*strs + j * iOneCharSize);
            ibBreak = 0;
            i = 1;
            while (i < strsSize) {
                if (*(*strs + i * iOneLineSize + j * iOneCharSize) != tc) {
                    ibBreak = 1;
                    break;
                }
                i++;
            }
            if (ibBreak == 1) {
                break;
            }
            sResStr[j] = tc;
            j++;
        }
    }

    return sResStr;
}

int main() {
    char sArr[3][201] = {{"flower"}, {"flow"}, {"flight"}};
    // char sArr[3][201] = {{"dog"}, {"racecar"}, {"car"}};
    // pSArr是一个指针，指向的数据类型是char[201]
    char(*pSArr)[201] = sArr;
    int iSArrLen = 3;
    char *sResStr = NULL;

    sResStr = longestCommonPrefix(&pSArr, iSArrLen);
    printf("%s\n", sResStr);
}