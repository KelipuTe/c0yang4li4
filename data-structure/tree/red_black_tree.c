#include <stdio.h>
#include <stdlib.h>

// ## 红黑树（R-B TREE） ##
// 红黑树是一种高级的二叉排序树

#define RED 'r'
#define BLACK 'b'

typedef struct RedBlackTreeNode {
  // 结点值
  int num;
  // 指向左子树的根结点
  struct RedBlackTreeNode *p1Left;
  // 指向右子树的根结点
  struct RedBlackTreeNode *p1Right;
  // 指向父结点
  struct RedBlackTreeNode *p1Prev;
  // 结点颜色，'r'=红色；'b'=黑色
  char color;
} RedBlackTreeNode;

// 添加结点
// RedBlackTreeNode **，指向二叉树的，指向左子树的根结点的指针或者指向右子树的根结点的指针，的指针
// RedBlackTreeNode **，指向，指向根结点的指针，的指针
extern void AddNode(RedBlackTreeNode **, int, RedBlackTreeNode **);
// 左旋，和平衡二叉树一个过程
// RedBlackTreeNode *，指向要旋转的那个结点
// RedBlackTreeNode **，指向，指向根结点的指针，的指针
void leftRotate(RedBlackTreeNode *, RedBlackTreeNode **);
// 右旋，和平衡二叉树一个过程
// RedBlackTreeNode *，指向要旋转的那个结点
// RedBlackTreeNode **，指向，指向根结点的指针，的指针
void rightRotate(RedBlackTreeNode *, RedBlackTreeNode **);
// 添加结点时的修正
// RedBlackTreeNode *，指向要修正的那个结点
// RedBlackTreeNode **，指向，指向根结点的指针，的指针
void addNodeFixUp(RedBlackTreeNode *, RedBlackTreeNode **);
// 中序遍历，左根右
// BinaryTreeNode *，指向根结点
extern void InorderTraversal(RedBlackTreeNode *);
void doInorderTraversal(RedBlackTreeNode *);

void AddNode(RedBlackTreeNode **p2Node, int num, RedBlackTreeNode **p2Root) {
  // 没有根结点时，初始化结点
  if (NULL == *p2Node) {
    *p2Node = (RedBlackTreeNode *)malloc(sizeof(RedBlackTreeNode));
    (*p2Node)->num = num;
    (*p2Node)->p1Left = NULL;
    (*p2Node)->p1Right = NULL;
    (*p2Node)->p1Prev = NULL;
    (*p2Node)->color = BLACK;
    return;
  }

  // 有根结点时，寻找插入插入值的位置
  if (num < (*p2Node)->num) {
    // 插入值小于结点值，去左子树继续查询
    if (NULL == (*p2Node)->p1Left) {
      // 如果左子树不存在，则插入值就插到这个位置
      (*p2Node)->p1Left = (RedBlackTreeNode *)malloc(sizeof(RedBlackTreeNode));
      (*p2Node)->p1Left->num = num;
      (*p2Node)->p1Left->p1Left = NULL;
      (*p2Node)->p1Left->p1Right = NULL;
      (*p2Node)->p1Left->p1Prev = *p2Node;
      (*p2Node)->p1Left->color = RED;
      addNodeFixUp((*p2Node)->p1Left, p2Root);
    } else {
      // 如果左子树存在，就在左子树中继续寻找插入插入值的位置
      AddNode(&(*p2Node)->p1Left, num, p2Root);
    }
  } else if (num > (*p2Node)->num) {
    // 插入值大于结点值，去右子树继续查询
    if (NULL == (*p2Node)->p1Right) {
      // 如果右子树不存在，则插入值就插到这个位置
      (*p2Node)->p1Right = (RedBlackTreeNode *)malloc(sizeof(RedBlackTreeNode));
      (*p2Node)->p1Right->num = num;
      (*p2Node)->p1Right->p1Left = NULL;
      (*p2Node)->p1Right->p1Right = NULL;
      (*p2Node)->p1Right->p1Prev = *p2Node;
      (*p2Node)->p1Right->color = RED;
      addNodeFixUp((*p2Node)->p1Right, p2Root);
    } else {
      // 如果右子树存在，就在右子树中继续寻找插入插入值的位置
      AddNode(&(*p2Node)->p1Right, num, p2Root);
    }
  } else {
    // 插入值已经存在，什么都不用做
    return;
  }
}

void leftRotate(RedBlackTreeNode *p1Node, RedBlackTreeNode **p2Root) {
  RedBlackTreeNode *p1Prev = p1Node->p1Prev;
  RedBlackTreeNode *p1Right = p1Node->p1Right;
  RedBlackTreeNode *p1RightLeft = p1Node->p1Right->p1Left;

  if (p1Node == *p2Root) {
    *p2Root = p1Right;
  }

  p1Node->p1Right = NULL;
  p1Node->p1Prev = p1Right;
  p1Right->p1Left = p1Node;
  p1Right->p1Prev = p1Prev;

  if (p1Prev != NULL) {
    if (p1Node == p1Prev->p1Left) {
      p1Prev->p1Left = p1Right;
    } else if (p1Node == p1Prev->p1Right) {
      p1Prev->p1Right = p1Right;
    }
  }

  p1Node->p1Right = p1RightLeft;
  if (p1RightLeft != NULL) {
    p1RightLeft->p1Prev = p1Node;
  }
}

void rightRotate(RedBlackTreeNode *p1Node, RedBlackTreeNode **p2Root) {
  RedBlackTreeNode *p1Prev = p1Node->p1Prev;
  RedBlackTreeNode *p1Left = p1Node->p1Left;
  RedBlackTreeNode *p1LeftRight = p1Node->p1Left->p1Right;

  if (p1Node == *p2Root) {
    *p2Root = p1Left;
  }

  p1Node->p1Left = NULL;
  p1Node->p1Prev = p1Left;
  p1Left->p1Right = p1Node;
  p1Left->p1Prev = p1Prev;

  if (p1Prev != NULL) {
    if (p1Node == p1Prev->p1Left) {
      p1Prev->p1Left = p1Left;
    } else if (p1Node == p1Prev->p1Right) {
      p1Prev->p1Right = p1Left;
    }
  }

  p1Node->p1Right = p1LeftRight;
  if (p1LeftRight != NULL) {
    p1LeftRight->p1Prev = p1Node;
  }
}

void addNodeFixUp(RedBlackTreeNode *p1Node, RedBlackTreeNode **p2Root) {
  // 叔叔结点（祖父结点的另一个子结点）
  RedBlackTreeNode *p1PrevPrevOtherChild;
  // 根结点不需要调整，父结点为红色时需要调整，如果父结点是黑色的，直接插入就行
  while (p1Node != *p2Root && RED == p1Node->p1Prev->color) {
    if (p1Node->p1Prev == p1Node->p1Prev->p1Prev->p1Left) {
      // 父结点是祖父结点的左子树的根结点，则叔叔结点是祖父结点的右子树的根结点
      p1PrevPrevOtherChild = p1Node->p1Prev->p1Prev->p1Right;
      if (p1PrevPrevOtherChild != NULL && RED == p1PrevPrevOtherChild->color) {
        // 叔叔结点是红色
        // 情况1：父结点和叔叔结点都是红色，则父结点和叔叔结点改黑色，祖父结点改红色
        p1Node->p1Prev->color = BLACK;
        p1PrevPrevOtherChild->color = BLACK;
        p1Node->p1Prev->p1Prev->color = RED;
        // 因为祖父结点改了红色，可能破坏红黑树，所以需要继续判断祖父结点是否需要调整
        p1Node = p1Node->p1Prev->p1Prev;
      } else {
        // 叔叔结点是黑色（叔叔结点不存在时，就相当于是定义中的黑色叶子结点）
        if (p1Node == p1Node->p1Prev->p1Right) {
          // 情况2：叔叔结点是黑色，自己是父结点的右子结点
          // 父结点左旋，由于左旋后父结点变成了自己的左子树，两个红色结点相连一定破坏红黑树，所以继续判断父结点（父结点在更下层）
          // 情况2 通过这个操作实际上演变成了情况 3
          leftRotate(p1Node->p1Prev, p2Root);
          // 把指针指向自己的左子结点（左旋后，父结点变成了自己的左子结点），让场景变成情况 3
          p1Node = p1Node->p1Left;
        } else {
          // 情况3：叔叔结点是黑色，自己是父结点的左子结点
          // 父结点改黑色，祖父结点改红色，祖父结点右旋
          p1Node->p1Prev->color = BLACK;
          p1Node->p1Prev->p1Prev->color = RED;
          rightRotate(p1Node->p1Prev->p1Prev, p2Root);
        }
      }
    } else {
      // 父结点是祖父结点的右子树的根结点
      // 把上面左子树的操作反过来就行了
      p1PrevPrevOtherChild = p1Node->p1Prev->p1Prev->p1Left;
      if (p1PrevPrevOtherChild != NULL && RED == p1PrevPrevOtherChild->color) {
        // 叔叔结点是红色
        // 情况1：父结点和叔叔结点都是红色
        p1Node->p1Prev->color = BLACK;
        p1PrevPrevOtherChild->color = BLACK;
        p1Node->p1Prev->p1Prev->color = RED;
        p1Node = p1Node->p1Prev->p1Prev;
      } else {
        // 叔叔结点是黑色
        if (p1Node == p1Node->p1Prev->p1Left) {
          // 情况2：叔叔结点是黑色，自己是父结点的左子结点
          rightRotate(p1Node, p2Root);
          p1Node = p1Node->p1Right;
        } else {
          // 情况3：叔叔结点是黑色，自己是父结点的右子结点
          p1Node->p1Prev->color = BLACK;
          p1Node->p1Prev->p1Prev->color = RED;
          leftRotate(p1Node->p1Prev->p1Prev, p2Root);
        }
      }
    }
  }
  // 根结点调整为黑色
  (*p2Root)->color = BLACK;
}

void InorderTraversal(RedBlackTreeNode *p1Root) {
  printf("InorderTraversal: ");
  doInorderTraversal(p1Root);
  printf("\r\n");
}

void doInorderTraversal(RedBlackTreeNode *p1Node) {
  if (p1Node == NULL) {
    return;
  }

  doInorderTraversal(p1Node->p1Left);
  printf("%d,", p1Node->num);
  doInorderTraversal(p1Node->p1Right);
}
