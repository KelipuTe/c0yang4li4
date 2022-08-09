#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ## 有向图-使用邻接表（adjacency list）实现 ##

// 邻接表结点
typedef struct AdjacencyListNode {
  // 顶点
  int vertex;
  // 指向下一个结点的指针
  struct AdjacencyListNode *next;
} AdjacencyListNode;

// 有向图
typedef struct OrientedGraph {
  // 边数
  int edgeNum;
  // 边集，二维数组，int[edgeNum][2]，第二维的两个元素表示一条无向边。
  int (*arr1Edges)[2];
  // 顶点数
  int vertexNum;
  // 一维数组，顶点集，int[vertexNum]
  int *arr1Vertex;
  // 指针数组，邻接表，struct AdjacencyListNode *[vertexNum]
  // 指针数组的数组元素是指针，那么定义数组起始地址的时候，就是指向指针（数组元素）的指针（数组起始地址）
  struct AdjacencyListNode **arr1p1NodeList;
} OrientedGraph;

extern struct OrientedGraph *OrientedGraphInit();
extern void SetEdge(OrientedGraph *, int (*)[2], int);
extern void BuildList(OrientedGraph *);
extern void PrintOrientedGraph(OrientedGraph *);
extern void BreadthFirstSearch(OrientedGraph *);
extern void DepthFirstSearch(OrientedGraph *);

/**
 * 初始化
 */
struct OrientedGraph *OrientedGraphInit() {
  OrientedGraph *p1 = (OrientedGraph *)malloc(sizeof(OrientedGraph));
  return p1;
}

/**
 * 设置边集
 * @param p1Graph
 * @param arr1Edges
 * @param arr1EdgesLen
 */
void SetEdge(OrientedGraph *p1Graph, int (*arr1Edges)[2], int arr1EdgesLen) {
  p1Graph->edgeNum = arr1EdgesLen;
  p1Graph->arr1Edges = (int(*)[2])malloc(sizeof(int[2]) * arr1EdgesLen);
  for (int i = 0; i < arr1EdgesLen; i++) {
    p1Graph->arr1Edges[i][0] = arr1Edges[i][0];
    p1Graph->arr1Edges[i][1] = arr1Edges[i][1];
  }
}

/**
 * 构造邻接表
 * @param p1Graph
 */
void BuildList(OrientedGraph *p1Graph) {
  // 临时，一维数组，用于统计顶点，int8_t[p1Graph->edgeNum * 2]
  int8_t *t1arr1Vertex;
  // 临时，有向边的起点和终点
  int t1Start, t1End;
  // 临时，用于遍历
  AdjacencyListNode *t1p1Node;

  // 顶点的数量最多是边的数量的两倍
  t1arr1Vertex = (int8_t *)malloc(sizeof(int8_t) * p1Graph->edgeNum * 2);
  // 如果顶点出现过，就把顶点作为下标，并标记
  for (int i = 0; i < p1Graph->edgeNum; i++) {
    t1arr1Vertex[p1Graph->arr1Edges[i][0]] = 1;
    t1arr1Vertex[p1Graph->arr1Edges[i][1]] = 1;
  }
  // 统计顶点数量
  p1Graph->vertexNum = 0;
  for (int i = 0; i < p1Graph->edgeNum * 2; i++) {
    if (1 == t1arr1Vertex[i]) {
      p1Graph->vertexNum++;
    }
  }
  // 统计顶点
  p1Graph->arr1Vertex = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  for (int i = 0, j = 0; i < p1Graph->edgeNum * 2; i++) {
    if (1 == t1arr1Vertex[i]) {
      p1Graph->arr1Vertex[j] = i;
      j++;
    }
  }
  // 构造邻接表
  p1Graph->arr1p1NodeList = (AdjacencyListNode **)malloc(sizeof(AdjacencyListNode *) * p1Graph->vertexNum);
  memset(p1Graph->arr1p1NodeList, 0, sizeof(AdjacencyListNode *) * p1Graph->vertexNum);
  for (int i = 0; i < p1Graph->edgeNum; i++) {
    t1Start = p1Graph->arr1Edges[i][0];
    t1End = p1Graph->arr1Edges[i][1];
    if (NULL == *(p1Graph->arr1p1NodeList + t1Start)) {
      p1Graph->arr1p1NodeList[t1Start] = (AdjacencyListNode *)malloc(sizeof(AdjacencyListNode));
      p1Graph->arr1p1NodeList[t1Start]->vertex = t1End;
      p1Graph->arr1p1NodeList[t1Start]->next = NULL;
    } else {
      t1p1Node = p1Graph->arr1p1NodeList[t1Start];
      while (t1p1Node->next != NULL) {
        t1p1Node = t1p1Node->next;
      }
      t1p1Node->next = (AdjacencyListNode *)malloc(sizeof(AdjacencyListNode));
      t1p1Node->next->vertex = t1End;
      t1p1Node->next->next = NULL;
    }
  }
}

/**
 * 在控制台输出有向图
 * @param p1Graph
 */
void PrintOrientedGraph(OrientedGraph *p1Graph) {
  // 临时，用于遍历
  AdjacencyListNode *t1p1Node;

  printf("PrintOrientedGraph:\r\n");
  printf("edgeNum:%d\r\n", p1Graph->edgeNum);

  printf("arr1Edges:");
  for (int i = 0; i < p1Graph->edgeNum; i++) {
    printf("[%d,%d],", p1Graph->arr1Edges[i][0], p1Graph->arr1Edges[i][1]);
  }
  printf("\r\n");

  printf("vertexNum:%d\r\n", p1Graph->vertexNum);

  printf("arr1Vertex:");
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    printf("[%d],", p1Graph->arr1Vertex[i]);
  }
  printf("\r\n");

  printf("arr1p1NodeList:\r\n");
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    t1p1Node = *(p1Graph->arr1p1NodeList + i);
    while (t1p1Node != NULL) {
      printf("[%d=>%d],", i, t1p1Node->vertex);
      t1p1Node = t1p1Node->next;
    }
    printf("\r\n");
  }
  printf("\r\n");
}

/**
 * 广度优先遍历
 * @param p1Graph
 */
void BreadthFirstSearch(OrientedGraph *p1Graph) {
  // 队列（数组结构），广度优先遍历需要借助队列结构
  int *arr1Queue;
  // 队列头；队列尾
  int queueHead = 0, queueTail = 0;
  // 一维数组，访问过的顶点
  int *arr1Visited;
  // 临时，顶点
  int t1Vertex;
  // 临时，用于遍历
  AdjacencyListNode *t1p1Node;

  arr1Queue = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  arr1Visited = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  memset(arr1Visited, 0, sizeof(int) * p1Graph->vertexNum);

  printf("BreadthFirstSearch:");
  // 外层循环保证每个顶点都被访问一次
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    if (1 == arr1Visited[i]) {
      continue;
    }
    printf("[%d],", i);
    arr1Visited[i] = 1;
    // 入队
    arr1Queue[queueTail] = i;
    queueTail++;
    while (queueHead < queueTail) {
      // 出队
      t1Vertex = arr1Queue[queueHead];
      queueHead++;
      t1p1Node = p1Graph->arr1p1NodeList[t1Vertex];
      // 遍历顶点在邻接表中的链表，寻找有没有连通的顶点
      while (t1p1Node != NULL) {
        if (1 == arr1Visited[t1p1Node->vertex]) {
          t1p1Node = t1p1Node->next;
          continue;
        }
        printf("[%d],", t1p1Node->vertex);
        arr1Visited[t1p1Node->vertex] = 1;
        // 入队
        arr1Queue[queueTail] = t1p1Node->vertex;
        queueTail++;
        t1p1Node = t1p1Node->next;
      }
    }
  }
  printf("\r\n");
}

/**
 * 深度优先遍历
 * @param p1Graph
 */
void DepthFirstSearch(OrientedGraph *p1Graph) {
  // 栈（数组结构），深度优先遍历需要借助栈存储结构
  int *arr1Stark;
  // 栈顶
  int startTop = 0;
  // 一维数组，访问过的顶点
  int *arr1Visited;
  // 临时，顶点
  int t1Vertex;
  // 临时，用于遍历
  AdjacencyListNode *t1p1Node;

  arr1Stark = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  arr1Visited = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  memset(arr1Visited, 0, sizeof(int) * p1Graph->vertexNum);

  printf("DepthFirstSearch:");
  // 外层循环保证每个顶点都被访问一次
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    // 判断顶点是否访问过
    if (1 == arr1Visited[i]) {
      continue;
    }
    // 没有访问过就访问该顶点并标记
    printf("[%d],", i);
    arr1Visited[i] = 1;
    // 入栈
    arr1Stark[startTop] = i;
    startTop++;
    while (startTop > 0) {
      // 出栈
      startTop--;
      t1Vertex = arr1Stark[startTop];
      t1p1Node = p1Graph->arr1p1NodeList[t1Vertex];
      // 遍历顶点在邻接表中的链表，寻找有没有连通的顶点
      while (t1p1Node != NULL) {
        if (1 == arr1Visited[t1p1Node->vertex]) {
          t1p1Node = t1p1Node->next;
          continue;
        }
        printf("[%d],", t1p1Node->vertex);
        arr1Visited[t1p1Node->vertex] = 1;
        // 这里先把自己入栈，然后再把要访问的新顶点入栈
        // 这样就实现了，新顶点访问结束后，再回来继续访问自己的逻辑
        arr1Stark[startTop] = t1Vertex;
        startTop++;
        arr1Stark[startTop] = t1p1Node->vertex;
        startTop++;
        break;
      }
    }
  }
  printf("\r\n");
}
