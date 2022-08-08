#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ## 无向图-使用邻接矩阵（adjacency matrix）实现 ##

typedef struct UndirectedGraph {
  // 边
  int edgeNum;
  // 边集，二维数组，int[edgeNum][2]，第二维的两个元素表示一条无向边。
  // 注意括号，int (*p1arr1Edges)[2]，表示 p1arr1Edges 是一个指针，指向的类型是 int[2]。
  // 如果是，int *p1arr1Edges[2]，表示 p1arr1Edges 是一个长度为 2 的数组，数组元素是 int *。
  int (*p1arr1Edges)[2];
  // 顶点数
  int vertexNum;
  // 顶点集，一维数组，int[vertexNum]
  int *p1arr1Vertex;
  // 邻接矩阵，二维数组，int[vertexNum][vertexNum]
  int *p1arr2Matrix;
} UndirectedGraph;

extern void SetEdge(UndirectedGraph *, int (*)[2], int);
extern UndirectedGraph *InitUndirectedGraph();
extern void BuildMatrix(UndirectedGraph *);
extern void PrintUndirectedGraph(UndirectedGraph *);
extern void BreadthFirstSearch(UndirectedGraph *);
extern void DepthFirstSearch(UndirectedGraph *);

/**
 * 初始化
 */
UndirectedGraph *InitUndirectedGraph() {
  UndirectedGraph *p1UG = (UndirectedGraph *)malloc(sizeof(UndirectedGraph));
  return p1UG;
}

/**
 * 设置边集
 * @param p1UG
 * @param p1arr1Edges
 * @param p1arr1EdgesLen
 */
void SetEdge(UndirectedGraph *p1UG, int (*p1arr1Edges)[2], int p1arr1EdgesLen) {
  p1UG->edgeNum = p1arr1EdgesLen;
  p1UG->p1arr1Edges = (int(*)[2])malloc(sizeof(int[2]) * p1arr1EdgesLen);
  for (int i = 0; i < p1arr1EdgesLen; i++) {
    // 注意括号，p1UG->p1arr1Edges 和 p1arr1Edges 都是指向 int[2] 的指针。
    // 计算偏移量之后，需要先进行 * 运算 *(p1UG->p1arr1Edges + i) 和 *(p1arr1Edges + i) 得到数组。
    // 得到数组后才能使用数组的方式操作元素 (*(p1UG->p1arr1Edges + i))[0] 和 (*(p1arr1Edges + i))[0]。
    (*(p1UG->p1arr1Edges + i))[0] = (*(p1arr1Edges + i))[0];
    (*(p1UG->p1arr1Edges + i))[1] = (*(p1arr1Edges + i))[1];
  }
}

/**
 * 构造无向图
 * @param p1UG
 */
void BuildMatrix(UndirectedGraph *p1UG) {
  // 统计顶点，顶点的数量最多是边的数量的两倍
  int8_t *p1arr1Vertex = (int8_t *)malloc(sizeof(int8_t) * p1UG->edgeNum * 2);
  for (int i = 0; i < p1UG->edgeNum; i++) {
    *(p1arr1Vertex + (*(p1UG->p1arr1Edges + i))[0]) = 1;
    *(p1arr1Vertex + (*(p1UG->p1arr1Edges + i))[1]) = 1;
  }

  p1UG->vertexNum = 0;
  for (int i = 0; i < p1UG->edgeNum * 2; i++) {
    if (*(p1arr1Vertex + i) == 1) {
      p1UG->vertexNum++;
    }
  }

  p1UG->p1arr1Vertex = (int *)malloc(sizeof(int) * p1UG->vertexNum);
  for (int i = 0, j = 0; i < p1UG->edgeNum * 2; i++) {
    if (*(p1arr1Vertex + i) == 1) {
      *(p1UG->p1arr1Vertex + j) = i;
      j++;
    }
  }

  // 构造邻接矩阵
  p1UG->p1arr2Matrix = (int *)malloc(sizeof(int) * p1UG->vertexNum * p1UG->vertexNum);
  memset(p1UG->p1arr2Matrix, 0, sizeof(int) * p1UG->vertexNum * p1UG->vertexNum);
  for (int i = 0; i < p1UG->edgeNum; i++) {
    // 无向图是对称的
    *(p1UG->p1arr2Matrix + ((*(p1UG->p1arr1Edges + i))[0] * p1UG->vertexNum + (*(p1UG->p1arr1Edges + i))[1])) = 1;
    *(p1UG->p1arr2Matrix + ((*(p1UG->p1arr1Edges + i))[1] * p1UG->vertexNum + (*(p1UG->p1arr1Edges + i))[0])) = 1;
  }
}

/**
 * 在控制台输出无向图
 * @param p1UG
 */
void PrintUndirectedGraph(UndirectedGraph *p1UG) {
  printf("PrintUndirectedGraph:\r\n");
  printf("edgeNum:%d\r\n", p1UG->edgeNum);

  printf("p1arr1Edges:");
  for (int i = 0; i < p1UG->edgeNum; i++) {
    printf("[%d,%d],", (*(p1UG->p1arr1Edges + i))[0], (*(p1UG->p1arr1Edges + i))[1]);
  }
  printf("\r\n");

  printf("vertexNum:%d\r\n", p1UG->vertexNum);

  printf("p1arr1Vertex:");
  for (int i = 0; i < p1UG->vertexNum; i++) {
    printf("[%d],", *(p1UG->p1arr1Vertex + i));
  }
  printf("\r\n");

  printf("p1arr2Matrix:\r\n");
  for (int i = 0; i < p1UG->vertexNum; i++) {
    for (int j = 0; j < p1UG->vertexNum; j++) {
      printf("%d,", *(p1UG->p1arr2Matrix + (i * p1UG->vertexNum + j)));
    }
    printf("\r\n");
  }
  printf("\r\n");
}

/**
 * 广度优先遍历
 * @param p1UG
 */
void BreadthFirstSearch(UndirectedGraph *p1UG) {
  // 队列（数组结构），广度优先遍历需要借助队列结构
  int *p1arr1Queue;
  // 队列头；队列尾
  int queueHead = 0, queueTail = 0;
  // 访问过的顶点
  int *p1arr1Visited;
  // 临时，顶点
  int t1Vertex;

  p1arr1Queue = (int *)malloc(sizeof(int) * p1UG->vertexNum);
  p1arr1Visited = (int *)malloc(sizeof(int) * p1UG->vertexNum);
  memset(p1arr1Visited, 0, sizeof(int) * p1UG->vertexNum);

  printf("BreadthFirstSearch:");
  // 外层循环保证每个顶点都被访问一次
  for (int i = 0; i < p1UG->vertexNum; i++) {
    // 判断顶点是否访问过
    if (1 == *(p1arr1Visited + i)) {
      continue;
    }
    // 没有访问过就访问该顶点并标记
    printf("[%d],", i);
    *(p1arr1Visited + i) = 1;
    // 入队
    p1arr1Queue[queueTail] = i;
    queueTail++;
    while (queueHead < queueTail) {
      // 出队
      t1Vertex = p1arr1Queue[queueHead];
      queueHead++;
      // 遍历顶点在矩阵中的那一层数据，寻找有没有连通的顶点
      for (int j = 0; j < p1UG->vertexNum; j++) {
        if (*(p1UG->p1arr2Matrix + (t1Vertex * p1UG->vertexNum + j)) != 1) {
          continue;
        }
        if (1 == *(p1arr1Visited + j)) {
          continue;
        }
        printf("[%d],", j);
        *(p1arr1Visited + j) = 1;
        p1arr1Queue[queueTail] = j;
        queueTail++;
      }
    }
  }
  printf("\r\n");
}

/**
 * 深度优先遍历
 * @param p1UG
 */
void DepthFirstSearch(UndirectedGraph *p1UG) {
  // 栈（数组结构），深度优先遍历需要借助栈存储结构
  int *p1arr1Stark;
  // 栈顶
  int startTop = 0;
  // 访问过的顶点
  int *p1arr1Visited;
  // 临时，顶点
  int t1Vertex;

  p1arr1Stark = (int *)malloc(sizeof(int) * p1UG->vertexNum);
  p1arr1Visited = (int *)malloc(sizeof(int) * p1UG->vertexNum);
  memset(p1arr1Visited, 0, sizeof(int) * p1UG->vertexNum);

  printf("DepthFirstSearch:");
  // 外层循环保证每个顶点都被访问一次
  for (int i = 0; i < p1UG->vertexNum; i++) {
    // 判断顶点是否访问过
    if (1 == *(p1arr1Visited + i)) {
      continue;
    }
    // 没有访问过就访问该顶点并标记
    printf("[%d],", i);
    *(p1arr1Visited + i) = 1;
    // 入栈
    p1arr1Stark[startTop] = i;
    startTop++;
    while (startTop > 0) {
      // 出栈
      startTop--;
      t1Vertex = p1arr1Stark[startTop];
      // 遍历顶点在矩阵中的那一层数据，寻找有没有连通的顶点
      for (int j = 0; j < p1UG->vertexNum; j++) {
        if (*(p1UG->p1arr2Matrix + (t1Vertex * p1UG->vertexNum + j)) != 1) {
          continue;
        }
        if (1 == *(p1arr1Visited + j)) {
          continue;
        }
        printf("[%d],", j);
        *(p1arr1Visited + j) = 1;
        // 这里先把自己入栈，然后再把要访问的新顶点入栈
        // 这样就实现了，新顶点访问结束后，再回来继续访问自己的逻辑
        p1arr1Stark[startTop] = i;
        startTop++;
        p1arr1Stark[startTop] = j;
        startTop++;
        break;
      }
    }
  }
  printf("\r\n");
}
