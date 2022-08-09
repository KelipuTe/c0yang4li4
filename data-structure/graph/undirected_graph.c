#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ## 无向图-使用邻接矩阵（adjacency matrix）实现 ##

// 无向图
typedef struct UndirectedGraph {
  // 边数
  int edgeNum;
  // 二维数组，边集，int[edgeNum][2]，第二维的两个元素，表示一条无向边的两个顶点。
  // 注意括号，int (*arr1Edges)[2]，表示 arr1Edges 是一个指针，指向的类型是 int[2]。
  // 如果是，int *arr1Edges[2]，表示 arr1Edges 是一个长度为 2 的数组，数组元素是 int *。
  // 可以以数组的形式使用，p1Graph->arr1Edges[i][0]，也可以以指针的形式使用，(*(p1Graph->arr1Edges + i))[0]。
  // 以指针的形式使用时，需要通过 *(p1Graph->arr1Edges + i) 得到数组后，才能使用数组的方式操作元素 (*(p1Graph->arr1Edges + i))[0]。
  int (*arr1Edges)[2];
  // 顶点数
  int vertexNum;
  // 一维数组，顶点集，int[vertexNum]
  int *arr1Vertex;
  // 二维数组，邻接矩阵，int[vertexNum][vertexNum]
  // 这个二维数组是动态申请内存构建的，会丢失数组维度，只能通过地址偏移的方式访问
  int *arr2Matrix;
} UndirectedGraph;

extern UndirectedGraph *InitUndirectedGraph();
extern void SetEdge(UndirectedGraph *, int (*)[2], int);
extern void BuildMatrix(UndirectedGraph *);
extern void PrintUndirectedGraph(UndirectedGraph *);
extern void BreadthFirstSearch(UndirectedGraph *);
extern void DepthFirstSearch(UndirectedGraph *);

/**
 * 初始化
 */
UndirectedGraph *InitUndirectedGraph() {
  UndirectedGraph *p1Graph = (UndirectedGraph *)malloc(sizeof(UndirectedGraph));
  return p1Graph;
}

/**
 * 设置边集
 * @param p1Graph
 * @param arr1Edges
 * @param arr1EdgesLen
 */
void SetEdge(UndirectedGraph *p1Graph, int (*arr1Edges)[2], int arr1EdgesLen) {
  p1Graph->edgeNum = arr1EdgesLen;
  p1Graph->arr1Edges = (int(*)[2])malloc(sizeof(int[2]) * arr1EdgesLen);
  for (int i = 0; i < arr1EdgesLen; i++) {
    p1Graph->arr1Edges[i][0] = arr1Edges[i][0];
    p1Graph->arr1Edges[i][1] = arr1Edges[i][1];
  }
}

/**
 * 构造邻接矩阵
 * @param p1Graph
 */
void BuildMatrix(UndirectedGraph *p1Graph) {
  // 顶点的数量最多是边的数量的两倍
  int8_t *t1arr1Vertex = (int8_t *)malloc(sizeof(int8_t) * p1Graph->edgeNum * 2);
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
  // 构造邻接矩阵
  p1Graph->arr2Matrix = (int *)malloc(sizeof(int) * p1Graph->vertexNum * p1Graph->vertexNum);
  memset(p1Graph->arr2Matrix, 0, sizeof(int) * p1Graph->vertexNum * p1Graph->vertexNum);
  for (int i = 0; i < p1Graph->edgeNum; i++) {
    // 无向图是对称的
    p1Graph->arr2Matrix[p1Graph->arr1Edges[i][0] * p1Graph->vertexNum + p1Graph->arr1Edges[i][1]] = 1;
    p1Graph->arr2Matrix[p1Graph->arr1Edges[i][1] * p1Graph->vertexNum + p1Graph->arr1Edges[i][0]] = 1;
  }
}

/**
 * 在控制台输出无向图
 * @param p1Graph
 */
void PrintUndirectedGraph(UndirectedGraph *p1Graph) {
  printf("PrintUndirectedGraph:\r\n");
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

  printf("arr2Matrix:\r\n");
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    for (int j = 0; j < p1Graph->vertexNum; j++) {
      printf("%d,", p1Graph->arr2Matrix[i * p1Graph->vertexNum + j]);
    }
    printf("\r\n");
  }
  printf("\r\n");
}

/**
 * 广度优先遍历
 * @param p1Graph
 */
void BreadthFirstSearch(UndirectedGraph *p1Graph) {
  // 队列（数组结构），广度优先遍历需要借助队列结构
  int *arr1Queue;
  // 队列头；队列尾
  int queueHead = 0, queueTail = 0;
  // 一维数组，访问过的顶点
  int *arr1Visited;
  // 临时，顶点
  int t1Vertex;

  arr1Queue = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  arr1Visited = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  memset(arr1Visited, 0, sizeof(int) * p1Graph->vertexNum);

  printf("BreadthFirstSearch:");
  // 外层循环保证每个顶点都被访问一次
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    // 判断顶点是否访问过
    if (1 == arr1Visited[i]) {
      continue;
    }
    // 没有访问过就访问该顶点并标记
    printf("[%d],", i);
    arr1Visited[i] = 1;
    // 入队
    arr1Queue[queueTail] = i;
    queueTail++;
    while (queueHead < queueTail) {
      // 出队
      t1Vertex = arr1Queue[queueHead];
      queueHead++;
      // 遍历顶点在矩阵中的那一层数据，寻找有没有连通的顶点
      for (int j = 0; j < p1Graph->vertexNum; j++) {
        if (p1Graph->arr2Matrix[t1Vertex * p1Graph->vertexNum + j] != 1) {
          continue;
        }
        if (1 == arr1Visited[j]) {
          continue;
        }
        printf("[%d],", j);
        arr1Visited[j] = 1;
        // 入队
        arr1Queue[queueTail] = j;
        queueTail++;
      }
    }
  }
  printf("\r\n");
}

/**
 * 深度优先遍历
 * @param p1Graph
 */
void DepthFirstSearch(UndirectedGraph *p1Graph) {
  // 栈（数组结构），深度优先遍历需要借助栈存储结构
  int *arr1Stark;
  // 栈顶
  int startTop = 0;
  // 一维数组，访问过的顶点
  int *arr1Visited;
  // 临时，顶点
  int t1Vertex;

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
      // 遍历顶点在矩阵中的那一层数据，寻找有没有连通的顶点
      for (int j = 0; j < p1Graph->vertexNum; j++) {
        if (p1Graph->arr2Matrix[t1Vertex * p1Graph->vertexNum + j] != 1) {
          continue;
        }
        if (1 == arr1Visited[j]) {
          continue;
        }
        printf("[%d],", j);
        arr1Visited[j] = 1;
        // 这里先把自己入栈，然后再把要访问的新顶点入栈
        // 这样就实现了，新顶点访问结束后，再回来继续访问自己的逻辑
        arr1Stark[startTop] = i;
        startTop++;
        arr1Stark[startTop] = j;
        startTop++;
        break;
      }
    }
  }
  printf("\r\n");
}
