#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ## 有向图-使用邻接表（adjacency list）实现 ##

// 邻接表结点
typedef struct AdjacencyListNode {
  // 顶点
  int vertex;
  // 权重
  int weight;
  // 指向下一个结点的指针
  struct AdjacencyListNode *p1Next;
} AdjacencyListNode;

// 有向图
typedef struct OrientedGraph {
  // 边数
  int edgeNum;
  // 二维数组，边（弧、路径）集，int[edgeNum][3]。
  // 第二维的三个元素，前两个元素表示一条边的两个顶点，第三个元素表示边的权重。
  int (*arr1Edges)[3];
  // 顶点数
  int vertexNum;
  // 一维数组，顶点集，int[vertexNum]
  int *arr1Vertex;
  // 指针数组，邻接表，struct AdjacencyListNode *[vertexNum]。
  // 数组下表是边的起点，链表结点是边的终点。
  // 指针数组的数组元素是指针，那么定义数组起始地址的时候，就是指向指针（数组元素）的指针（数组起始地址）
  struct AdjacencyListNode **arr1p1NodeList;
} OrientedGraph;

extern struct OrientedGraph *OrientedGraphInit();
extern void SetEdge(OrientedGraph *, int (*)[3], int);
extern void BuildList(OrientedGraph *);
extern void PrintOrientedGraph(OrientedGraph *);
extern void BreadthFirstSearch(OrientedGraph *);
extern void DepthFirstSearch(OrientedGraph *);
extern void TopologicalSorting(OrientedGraph *);

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
void SetEdge(OrientedGraph *p1Graph, int (*arr1Edges)[3], int arr1EdgesLen) {
  p1Graph->edgeNum = arr1EdgesLen;
  p1Graph->arr1Edges = (int(*)[3])malloc(sizeof(int[3]) * arr1EdgesLen);
  for (int i = 0; i < arr1EdgesLen; i++) {
    p1Graph->arr1Edges[i][0] = arr1Edges[i][0];
    p1Graph->arr1Edges[i][1] = arr1Edges[i][1];
    p1Graph->arr1Edges[i][2] = arr1Edges[i][2];
  }
}

/**
 * 构造邻接表
 * @param p1Graph
 */
void BuildList(OrientedGraph *p1Graph) {
  // 临时，一维数组，用于统计顶点，int8_t[p1Graph->edgeNum * 2]
  int8_t *t1arr1Vertex;
  // 临时，有向边的起点、终点、权重
  int t1Start, t1End, t1Weight;
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
    t1Weight = p1Graph->arr1Edges[i][2];
    if (NULL == *(p1Graph->arr1p1NodeList + t1Start)) {
      p1Graph->arr1p1NodeList[t1Start] = (AdjacencyListNode *)malloc(sizeof(AdjacencyListNode));
      p1Graph->arr1p1NodeList[t1Start]->vertex = t1End;
      p1Graph->arr1p1NodeList[t1Start]->weight = t1Weight;
      p1Graph->arr1p1NodeList[t1Start]->p1Next = NULL;
    } else {
      t1p1Node = p1Graph->arr1p1NodeList[t1Start];
      while (t1p1Node->p1Next != NULL) {
        t1p1Node = t1p1Node->p1Next;
      }
      t1p1Node->p1Next = (AdjacencyListNode *)malloc(sizeof(AdjacencyListNode));
      t1p1Node->p1Next->vertex = t1End;
      t1p1Node->p1Next->weight = t1Weight;
      t1p1Node->p1Next->p1Next = NULL;
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
    printf("[%d,%d,%d],", p1Graph->arr1Edges[i][0], p1Graph->arr1Edges[i][1], p1Graph->arr1Edges[i][2]);
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
      printf("[%2d=>%2d,%2d],", i, t1p1Node->vertex, t1p1Node->weight);
      t1p1Node = t1p1Node->p1Next;
    }
    printf("\r\n");
  }
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
          t1p1Node = t1p1Node->p1Next;
          continue;
        }
        printf("[%d],", t1p1Node->vertex);
        arr1Visited[t1p1Node->vertex] = 1;
        // 入队
        arr1Queue[queueTail] = t1p1Node->vertex;
        queueTail++;
        t1p1Node = t1p1Node->p1Next;
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
          t1p1Node = t1p1Node->p1Next;
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

/**
 * 拓补排序
 * @param p1Graph
 */
void TopologicalSorting(OrientedGraph *p1Graph) {
  // 一维数组，每个顶点的入度（in-degree）
  int *arr1VertexInDegree;
  // 临时，用于遍历
  AdjacencyListNode *t1p1Node;

  arr1VertexInDegree = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  memset(arr1VertexInDegree, 0, sizeof(int) * p1Graph->vertexNum);

  // 统计所有顶点的入度
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    t1p1Node = p1Graph->arr1p1NodeList[i];
    while (t1p1Node != NULL) {
      arr1VertexInDegree[t1p1Node->vertex]++;
      t1p1Node = t1p1Node->p1Next;
    }
  }

  printf("arr1VertexInDegree:");
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    printf("[%d:%d],", i, arr1VertexInDegree[i]);
  }
  printf("\r\n");

  // 拓扑排序就是不断地寻找入度为 0 的顶点
  printf("topological sorting:");
  while (1) {
    int8_t isDone = 1;
    for (int i = 0; i < p1Graph->vertexNum; i++) {
      if (arr1VertexInDegree[i] > 0) {
        // 顶点入度不为 0，循环继续
        isDone = 0;
      } else if (arr1VertexInDegree[i] == 0) {
        // 找到入度为 0 的顶点，移除这个顶点。
        // 同时，移除所有以这个顶点为起点的边。边对应的终点，入度 -1。
        t1p1Node = p1Graph->arr1p1NodeList[i];
        while (t1p1Node != NULL) {
          arr1VertexInDegree[t1p1Node->vertex]--;
          t1p1Node = t1p1Node->p1Next;
        }
        printf("%d,", i);
        // 这个顶点处理完成，将这个顶点的数据标记为无效
        arr1VertexInDegree[i] = -1;
      }
    }
    if (isDone == 1) {
      printf("\r\n");
      break;
    }
  }
}

/**
 * 计算关键路径
 * @param p1Graph
 */
void CriticalPath(OrientedGraph *p1Graph) {
  // 计算关键路径还需要一个和 p1Graph->arr1p1NodeList 相反的邻接表。
  // 数组下表是边的终点，链表结点是边的起点。
  AdjacencyListNode **t1arr1p1NodeList;
  // 临时，有向边的起点、终点、权重
  int t1Start, t1End, t1Weight;
  // 临时，用于遍历
  AdjacencyListNode *t1p1Node;
  // 临时，用于计算最长路径的权重
  int t1MaxWeight;

  // 一维数组，每个顶点的入度
  int *arr1VertexInDegree;
  // 一维数组，每个顶点的出度（out-degree）
  int *arr1VertexOutDegree;
  // 一维数组，每个顶点的最早开始时间
  int *arr1EarliestStart;
  // 一维数组，每个顶点的最晚开始时间
  int *arr1LatestStart;

  arr1VertexInDegree = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  memset(arr1VertexInDegree, 0, sizeof(int) * p1Graph->vertexNum);
  arr1VertexOutDegree = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  memset(arr1VertexOutDegree, 0, sizeof(int) * p1Graph->vertexNum);

  arr1EarliestStart = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  memset(arr1EarliestStart, 0, sizeof(int) * p1Graph->vertexNum);
  arr1LatestStart = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  memset(arr1LatestStart, 0, sizeof(int) * p1Graph->vertexNum);

  // 计算每个顶点的最早开始时间

  // 统计所有顶点的入度
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    t1p1Node = p1Graph->arr1p1NodeList[i];
    while (t1p1Node != NULL) {
      arr1VertexInDegree[t1p1Node->vertex]++;
      t1p1Node = t1p1Node->p1Next;
    }
  }

  // 用拓扑排序的思路。计算一下从拓扑排序序列的第一个顶点到拓扑排序序列的最后一个顶点的最长路径权重。
  // 这个最长路径权重就等于最早开始时间。
  while (1) {
    int8_t isDone = 1;
    for (int i = 0; i < p1Graph->vertexNum; i++) {
      if (arr1VertexInDegree[i] > 0) {
        isDone = 0;
      } else if (arr1VertexInDegree[i] == 0) {
        t1p1Node = p1Graph->arr1p1NodeList[i];
        while (t1p1Node != NULL) {
          // 看看其余顶点的最长路径权重，有没有被这个移除的顶点影响到。
          // 如果这个移除的顶点是其他顶点的前驱，就会被影响。
          if (arr1EarliestStart[t1p1Node->vertex] < arr1EarliestStart[i] + t1p1Node->weight) {
            arr1EarliestStart[t1p1Node->vertex] = arr1EarliestStart[i] + t1p1Node->weight;
          }
          // 看看全局的最长路径权重，有没有被这个移除的顶点影响到。
          if (t1MaxWeight < arr1EarliestStart[t1p1Node->vertex]) {
            t1MaxWeight = arr1EarliestStart[t1p1Node->vertex];
          }
          arr1VertexInDegree[t1p1Node->vertex]--;
          t1p1Node = t1p1Node->p1Next;
        }
        arr1VertexInDegree[i] = -1;
      }
    }
    if (isDone == 1) {
      break;
    }
  }

  printf("arr1EarliestStart:");
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    printf("[%d:%d],", i, arr1EarliestStart[i]);
  }
  printf("\r\n");

  // 计算每个顶点的最晚开始时间

  // 构造相反的邻接表，用于统计顶点的出度
  t1arr1p1NodeList = (AdjacencyListNode **)malloc(sizeof(AdjacencyListNode *) * p1Graph->vertexNum);
  memset(t1arr1p1NodeList, 0, sizeof(AdjacencyListNode *) * p1Graph->vertexNum);
  for (int i = 0; i < p1Graph->edgeNum; i++) {
    t1Start = p1Graph->arr1Edges[i][1];
    t1End = p1Graph->arr1Edges[i][0];
    t1Weight = p1Graph->arr1Edges[i][2];
    if (NULL == *(t1arr1p1NodeList + t1Start)) {
      t1arr1p1NodeList[t1Start] = (AdjacencyListNode *)malloc(sizeof(AdjacencyListNode));
      t1arr1p1NodeList[t1Start]->vertex = t1End;
      t1arr1p1NodeList[t1Start]->weight = t1Weight;
      t1arr1p1NodeList[t1Start]->p1Next = NULL;
    } else {
      t1p1Node = t1arr1p1NodeList[t1Start];
      while (t1p1Node->p1Next != NULL) {
        t1p1Node = t1p1Node->p1Next;
      }
      t1p1Node->p1Next = (AdjacencyListNode *)malloc(sizeof(AdjacencyListNode));
      t1p1Node->p1Next->vertex = t1End;
      t1p1Node->p1Next->weight = t1Weight;
      t1p1Node->p1Next->p1Next = NULL;
    }
  }

  // 统计所有顶点的出度
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    t1p1Node = t1arr1p1NodeList[i];
    while (t1p1Node != NULL) {
      arr1VertexOutDegree[t1p1Node->vertex]++;
      t1p1Node = t1p1Node->p1Next;
    }
  }

  // 所有顶点的最晚开始时间都设置为全局最长路径的权重
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    arr1LatestStart[i] = t1MaxWeight;
  }
  // 拓扑排序的思路反过来用。计算一下从拓扑排序序列的最后一个顶点到拓扑排序序列的第一个顶点的没有顶点可以晚一点开始。
  while (1) {
    int8_t isDone = 1;
    for (int i = 0; i < p1Graph->vertexNum; i++) {
      if (arr1VertexOutDegree[i] > 0) {
        isDone = 0;
      } else if (arr1VertexOutDegree[i] == 0) {
        t1p1Node = t1arr1p1NodeList[i];
        while (t1p1Node != NULL) {
          if (arr1LatestStart[t1p1Node->vertex] > arr1LatestStart[i] - t1p1Node->weight) {
            arr1LatestStart[t1p1Node->vertex] = arr1LatestStart[i] - t1p1Node->weight;
          }
          arr1VertexOutDegree[t1p1Node->vertex]--;
          t1p1Node = t1p1Node->p1Next;
        }
        arr1VertexOutDegree[i] = -1;
      }
    }
    if (isDone == 1) {
      break;
    }
  }

  printf("arr1LatestStart:");
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    printf("[%d:%d],", i, arr1LatestStart[i]);
  }
  printf("\r\n");

  // 最后，如果顶点的最早开始时间和最晚开始时间一样，那说明这个顶点在关键路径上
}
