#include <stdio.h>
#include <stdlib.h>

/*#####Trie树#####*/

// Trie树结点
typedef struct TrieJieDian {
    // 结点数值
    char cZiFu;
    // 每个Trie树结点有26个子树
    struct TrieJieDian arrpTJD[26];
} ZJD;