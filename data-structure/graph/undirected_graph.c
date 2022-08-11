#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ## 无向图-使用邻接矩阵（adjacency matrix）实现 ##

// 边的默认权重
#define DEFAULT_WEIGHT 1
// 边的不可达权重，看情况设置一个极大值
#define UNREACHABLE_WEIGHT 999

// 无向图
typedef struct UndirectedGraph {
  // 边数
  int edgeNum;
  // 二维数组，边（弧、路径）集，int[edgeNum][3]，第二维的三个元素，前两个元素表示一条无向边的两个顶点，第三个元素表示无向边的权重。
  // 注意括号，int (*a)[n]，表示 a 是一个指针，指向的类型是 int[n]。
  // 如果是，int *a[n]，表示 a 是一个长度为 n 的数组，数组元素是 int *。
  // 可以以数组的形式使用，p1Graph->arr1Edges[i][0]，也可以以指针的形式使用，(*(p1Graph->arr1Edges + i))[0]。
  // 以指针的形式使用时，需要通过 *(p1Graph->arr1Edges + i) 得到数组后，才能使用数组的方式操作元素 (*(p1Graph->arr1Edges + i))[0]。
  int (*arr1Edges)[3];
  // 顶点数
  int vertexNum;
  // 一维数组，顶点集，int[vertexNum]
  int *arr1Vertex;
  // 二维数组，邻接矩阵，int[vertexNum][vertexNum]
  // 这个二维数组是动态申请内存构建的，会丢失数组维度，只能通过地址偏移的方式访问
  int *arr2Matrix;
} UndirectedGraph;

extern UndirectedGraph *InitUndirectedGraph();
extern void SetEdge(UndirectedGraph *, int (*)[3], int);
extern void BuildMatrix(UndirectedGraph *);
extern void PrintUndirectedGraph(UndirectedGraph *);
extern void BreadthFirstSearch(UndirectedGraph *);
extern void DepthFirstSearch(UndirectedGraph *);
extern void PrimAlgorithm(UndirectedGraph *);
extern void KruskalAlgorithm(UndirectedGraph *);
extern void DijkstraAlgorithm(UndirectedGraph *, int);
extern void FloydAlgorithm(UndirectedGraph *);

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
 * @param arr1Edges，int (*a)[3] 也可以定义成 int a[][3]
 * @param arr1EdgesLen
 */
void SetEdge(UndirectedGraph *p1Graph, int (*arr1Edges)[3], int arr1EdgesLen) {
  p1Graph->edgeNum = arr1EdgesLen;
  p1Graph->arr1Edges = (int(*)[3])malloc(sizeof(int[3]) * arr1EdgesLen);
  for (int i = 0; i < arr1EdgesLen; i++) {
    p1Graph->arr1Edges[i][0] = arr1Edges[i][0];
    p1Graph->arr1Edges[i][1] = arr1Edges[i][1];
    p1Graph->arr1Edges[i][2] = arr1Edges[i][2];
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
  // 初始化矩阵
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    for (int j = 0; j < p1Graph->vertexNum; j++) {
      if (i == j) {
        p1Graph->arr2Matrix[i * p1Graph->vertexNum + j] = 0;
      } else {
        p1Graph->arr2Matrix[i * p1Graph->vertexNum + j] = UNREACHABLE_WEIGHT;
      }
    }
  }
  // 填入边的数据
  for (int i = 0; i < p1Graph->edgeNum; i++) {
    // 无向图是对称的
    p1Graph->arr2Matrix[p1Graph->arr1Edges[i][0] * p1Graph->vertexNum + p1Graph->arr1Edges[i][1]] = p1Graph->arr1Edges[i][2];
    p1Graph->arr2Matrix[p1Graph->arr1Edges[i][1] * p1Graph->vertexNum + p1Graph->arr1Edges[i][0]] = p1Graph->arr1Edges[i][2];
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
    printf("[%d,%d,%d],", p1Graph->arr1Edges[i][0], p1Graph->arr1Edges[i][1], p1Graph->arr1Edges[i][2]);
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
      printf("%3d,", p1Graph->arr2Matrix[i * p1Graph->vertexNum + j]);
    }
    printf("\r\n");
  }
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
        if (UNREACHABLE_WEIGHT != p1Graph->arr2Matrix[t1Vertex * p1Graph->vertexNum + j]) {
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
        if (UNREACHABLE_WEIGHT != p1Graph->arr2Matrix[t1Vertex * p1Graph->vertexNum + j]) {
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

/**
 * 普里姆算法，求最小生成树（minimum spanning tree，MST）
 * @param p1Graph
 * @return int[edgeNum][2]
 */
void PrimAlgorithm(UndirectedGraph *p1Graph) {
  printf("prim algorithm\r\n");
  // 假设从顶点 0 开始，找最小生成树

  // 一维数组，记录最小生成树中的顶点到达不在最小生成树中的各个顶点的最短路径的权重。
  // 数组的下标是顶点，数组的元素是到达该顶点的最短路径的权重。
  // 已经在最小生成树中的顶点，最短路径的权重标为 0。如果没有路径到达对应的顶点，就设置为不可达权重。
  int *t1arr1MinWeight;
  // 一维数组，数组下标为终点，数组元素为起点。记录到终点的最短路径是从哪个起点来的，可以标记一条边。
  int *t1arr1StartVertex;
  // 最小生成树的边，int[p1Graph->vertexNum - 1][2]
  int *arr1Tree;

  t1arr1MinWeight = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  t1arr1StartVertex = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  arr1Tree = (int *)malloc(sizeof(int) * 2 * (p1Graph->vertexNum - 1));

  // 因为是假设从顶点 0 开始的，所以所有的顶点，即使不可达，也都是从顶点 0 出发的。
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    t1arr1MinWeight[i] = p1Graph->arr2Matrix[i];
    t1arr1StartVertex[i] = 0;
  }
  // 顶点 0 就不需要参与循环了
  for (int i = 1, t1Index = 0; i < p1Graph->vertexNum; i++) {
    int t1MinWeight = UNREACHABLE_WEIGHT;
    int t1Vertex = 0;

    // printf("t1arr1MinWeight:");
    // for (int i = 0; i < p1Graph->vertexNum; i++) {
    //   printf("[%d],", t1arr1MinWeight[i]);
    // }
    // printf("\r\n");
    //
    // printf("t1arr1StartVertex:");
    // for (int i = 0; i < p1Graph->vertexNum; i++) {
    //   printf("[%d],", t1arr1StartVertex[i]);
    // }
    // printf("\r\n");

    // 找到本轮的最小权重的边
    for (int j = 1; j < p1Graph->vertexNum; j++) {
      if (t1arr1MinWeight[j] != 0 && t1arr1MinWeight[j] < t1MinWeight) {
        t1MinWeight = t1arr1MinWeight[j];
        t1Vertex = j;
      }
    }
    // 记录最小生成树的边
    arr1Tree[t1Index * 2] = t1arr1StartVertex[t1Vertex];
    arr1Tree[t1Index * 2 + 1] = t1Vertex;
    t1Index++;
    // 标记顶点为在最小生成树中
    t1arr1MinWeight[t1Vertex] = 0;
    // 加入从这个顶点出发的边，看看有没有路径更短的
    for (int j = 1; j < p1Graph->vertexNum; j++) {
      if (p1Graph->arr2Matrix[t1Vertex * p1Graph->vertexNum + j] < t1arr1MinWeight[j]) {
        t1arr1MinWeight[j] = p1Graph->arr2Matrix[t1Vertex * p1Graph->vertexNum + j];
        t1arr1StartVertex[j] = t1Vertex;
      }
    }
  }

  printf("minimum spanning tree:");
  for (int i = 0; i < p1Graph->vertexNum - 1; i++) {
    printf("[%d,%d],", arr1Tree[i * 2], arr1Tree[i * 2 + 1]);
  }
  printf("\r\n");
}

/**
 * 克鲁斯卡尔算法，求最小生成树（minimum spanning tree，MST）
 * @param p1Graph
 * @return
 */
void KruskalAlgorithm(UndirectedGraph *p1Graph) {
  printf("kruskal algorithm\r\n");
  // 克鲁斯卡尔算法不需要把邻接矩阵构造出来
  // 假设从顶点 0 开始，找最小生成树

  // 临时，二维数组，边集，int[edgeNum][3]
  int(*t1arr1Edges)[3];
  // 一维数组，数组下标为终点，数组元素为起点。记录到终点的最短路径是从哪个起点来的，可以标记一条边。
  int *t1arr1StartVertex;
  // 最小生成树的边，int[p1Graph->vertexNum - 1][2]
  int *arr1Tree;

  t1arr1Edges = (int(*)[3])malloc(sizeof(int[3]) * p1Graph->edgeNum);
  for (int i = 0; i < p1Graph->edgeNum; i++) {
    t1arr1Edges[i][0] = p1Graph->arr1Edges[i][0];
    t1arr1Edges[i][1] = p1Graph->arr1Edges[i][1];
    t1arr1Edges[i][2] = p1Graph->arr1Edges[i][2];
  }

  // 初始化，到终点的最短路径初始化为从无效的起点 -1 来的
  t1arr1StartVertex = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    t1arr1StartVertex[i] = -1;
  }
  arr1Tree = (int *)malloc(sizeof(int) * 2 * (p1Graph->vertexNum - 1));

  // 把路径列表按照权重升序排序
  for (int i = 0; i < p1Graph->edgeNum; i++) {
    int t1MinWeightIndex = i;
    for (int j = i; j < p1Graph->edgeNum; j++) {
      if (t1arr1Edges[j][2] < t1arr1Edges[t1MinWeightIndex][2]) {
        t1MinWeightIndex = j;
      }
    }
    int t1Start = t1arr1Edges[i][0];
    int t1End = t1arr1Edges[i][1];
    int t1Weight = t1arr1Edges[i][2];
    t1arr1Edges[i][0] = t1arr1Edges[t1MinWeightIndex][0];
    t1arr1Edges[i][1] = t1arr1Edges[t1MinWeightIndex][1];
    t1arr1Edges[i][2] = t1arr1Edges[t1MinWeightIndex][2];
    t1arr1Edges[t1MinWeightIndex][0] = t1Start;
    t1arr1Edges[t1MinWeightIndex][1] = t1End;
    t1arr1Edges[t1MinWeightIndex][2] = t1Weight;
  }

  printf("t1arr1Edges:");
  for (int i = 0; i < p1Graph->edgeNum; i++) {
    printf("[%d,%d,%d],", t1arr1Edges[i][0], t1arr1Edges[i][1], t1arr1Edges[i][2]);
  }
  printf("\r\n");

  // 依次遍历排序后的路径列表
  for (int i = 0, t1Index = 0; i < p1Graph->edgeNum; i++) {
    // 追溯路径的两个顶点，向上追溯来源顶点
    int t1Start1 = t1arr1Edges[i][0];
    int t1Start2 = t1arr1Edges[i][1];

    // printf("t1arr1StartVertex:");
    // for (int i = 0; i < p1Graph->vertexNum; i++) {
    //   printf("[%d],", t1arr1StartVertex[i]);
    // }
    // printf("\r\n");

    while (t1arr1StartVertex[t1Start1] != -1) {
      t1Start1 = t1arr1StartVertex[t1Start1];
    }
    while (t1arr1StartVertex[t1Start2] != -1) {
      t1Start2 = t1arr1StartVertex[t1Start2];
    }

    // 如果追溯不到同一个顶点，那么这条路径就需要记录下来
    if (t1Start1 != t1Start2) {
      // 无向图不需要处理边的方向，这里任选一个顶点当来源
      t1arr1StartVertex[t1arr1Edges[i][0]] = t1arr1Edges[i][1];
      // 记录最小生成树的边
      arr1Tree[t1Index * 2] = t1arr1Edges[i][0];
      arr1Tree[t1Index * 2 + 1] = t1arr1Edges[i][1];
      t1Index++;
    }

    // 当找到的边数大于等于顶点数 -1 的时候，说明最小生成树已经找到了。
    if (t1Index >= p1Graph->vertexNum - 1) {
      break;
    }
  }

  printf("minimum spanning tree:");
  for (int i = 0; i < p1Graph->vertexNum - 1; i++) {
    printf("[%d,%d],", arr1Tree[i * 2], arr1Tree[i * 2 + 1]);
  }
  printf("\r\n");
}

/**
 * 迪杰斯特拉算法，求一个顶点到其余各顶点的最短路径，贪心思路
 * @param p1Graph
 * @param vertexIndex 指定算哪个顶点
 */
void DijkstraAlgorithm(UndirectedGraph *p1Graph, int vertexIndex) {
  printf("dijkstra algorithm\r\n");

  // 一维数组，顶点到其余各顶点的最短路径的权重。
  // 如果没有路径到达对应的顶点，就设置为不可达权重。
  int *t1arr1MinWeight;
  // 一维数组，数组下标为终点，数组元素为起点。记录到终点的最短路径是从哪个起点来的，可以标记一条边。
  int *t1arr1StartVertex;
  // 一维数组，已完成的顶点
  int8_t *t1arr1DoneVertex;

  t1arr1MinWeight = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  t1arr1StartVertex = (int *)malloc(sizeof(int) * p1Graph->vertexNum);
  t1arr1DoneVertex = (int8_t *)malloc(sizeof(int8_t) * p1Graph->vertexNum);
  memset(t1arr1DoneVertex, 0, sizeof(int8_t) * p1Graph->vertexNum);

  // 因为是假设从顶点 vertexIndex 开始的，所以所有的顶点，即使不可达，也都是从顶点 vertexIndex 出发的。
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    t1arr1MinWeight[i] = p1Graph->arr2Matrix[vertexIndex * p1Graph->vertexNum + i];
    t1arr1StartVertex[i] = vertexIndex;
  }
  // 把顶点 vertexIndex 标记为已完成。
  t1arr1DoneVertex[vertexIndex] = 1;

  for (int i = 0; i < p1Graph->vertexNum; i++) {
    // 遍历顶点到其余各顶点的最短路径的权重，权重最小的那个顶点就是本轮能确定最短路径的顶点 k。
    int k = 0;
    int t1MinWeight = UNREACHABLE_WEIGHT;

    // printf("t1arr1MinWeight");
    // for (int i = 0; i < p1Graph->vertexNum; i++) {
    //   printf("[%d,%d],", i, t1arr1MinWeight[i]);
    // }
    // printf("\r\n");
    //
    // printf("t1arr1StartVertex");
    // for (int i = 0; i < p1Graph->vertexNum; i++) {
    //   printf("[%d,%d],", i, t1arr1StartVertex[i]);
    // }
    // printf("\r\n");
    //
    // printf("t1arr1DoneVertex");
    // for (int i = 0; i < p1Graph->vertexNum; i++) {
    //   printf("[%d,%d],", i, t1arr1DoneVertex[i]);
    // }
    // printf("\r\n");

    for (int j = 0; j < p1Graph->vertexNum; j++) {
      if (t1arr1DoneVertex[j] != 0) {
        continue;
      }
      if (t1arr1MinWeight[j] < t1MinWeight) {
        k = j;
        t1MinWeight = t1arr1MinWeight[j];
      }
    }
    // 标记顶点 k 为已完成顶点
    t1arr1DoneVertex[k] = 1;
    // 重新计算从顶点 vertexIndex 开始到各个顶点的最短路径权重。
    // 计算的时候注意，需要带上从顶点 vertexIndex 到顶点 k 的路径权重。
    for (int j = 0; j < p1Graph->vertexNum; j++) {
      if (t1arr1DoneVertex[j] != 0) {
        continue;
      }
      // 如果发现从顶点 k 出发能找到到某些顶点的更短的路径，就更新最短路径。
      if (t1MinWeight + p1Graph->arr2Matrix[k * p1Graph->vertexNum + j] < t1arr1MinWeight[j]) {
        t1arr1MinWeight[j] = t1MinWeight + p1Graph->arr2Matrix[k * p1Graph->vertexNum + j];
        t1arr1StartVertex[j] = k;
      }
    }
  }

  printf("t1arr1MinWeight");
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    printf("[%d,%d],", i, t1arr1MinWeight[i]);
  }
  printf("\r\n");

  printf("t1arr1StartVertex");
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    printf("[%d,%d],", i, t1arr1StartVertex[i]);
  }
  printf("\r\n");

  printf("path\r\n");
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    int t1Start1 = i;
    printf("[%d]", t1Start1);
    while (1) {
      printf("<=[%d]", t1arr1StartVertex[t1Start1]);
      t1Start1 = t1arr1StartVertex[t1Start1];
      if (t1Start1 == vertexIndex) {
        printf("\r\n");
        break;
      }
    }
  }
}

/**
 * 弗洛伊德算法，求顶点到其余各顶点的最短路径，动态规划思路
 * @param p1Graph
 * @param vertexIndex
 */
void FloydAlgorithm(UndirectedGraph *p1Graph) {
  printf("floyd algorithm\r\n");

  // 二维数组，邻接矩阵
  // 初始化的时候，是无向图的邻接矩阵。结束的时候，就是计算好的顶点到其余各顶点的最短路径。
  // a[i][j]=k 表示顶点 i 到顶点 j 的最短路径的权重是 k
  int *t1arr2Matrix;
  // 二维数组，最短路径来源，a[i][j]=k 表示顶点 i 到顶点 j 需要经过顶点 k
  int *t1arr2PassVertex;

  t1arr2Matrix = (int *)malloc(sizeof(int) * p1Graph->vertexNum * p1Graph->vertexNum);
  t1arr2PassVertex = (int *)malloc(sizeof(int) * p1Graph->vertexNum * p1Graph->vertexNum);
  // 初始化邻接矩阵
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    for (int j = 0; j < p1Graph->vertexNum; j++) {
      t1arr2Matrix[i * p1Graph->vertexNum + j] = p1Graph->arr2Matrix[i * p1Graph->vertexNum + j];
    }
  }
  // 初始化最短路径来源
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    for (int j = 0; j < p1Graph->vertexNum; j++) {
      t1arr2PassVertex[i * p1Graph->vertexNum + j] = i;
    }
  }

  // 依次以顶点 k 为中转点
  for (int k = 0; k < p1Graph->vertexNum; k++) {
    // 依次选两个顶点，顶点 i 和顶点 j
    for (int i = 0; i < p1Graph->vertexNum; i++) {
      for (int j = 0; j < p1Graph->vertexNum; j++) {
        // 状态转移方程 a{k}(i,j) = min(a{k-1}(i,j),a{k-1}(i,k)+a{k-1}(k,j)
        // 比较边（i,j）的权重与边（i,k）的权重和边(k,j)的权重之和的大小
        if (t1arr2Matrix[i * p1Graph->vertexNum + j] > t1arr2Matrix[i * p1Graph->vertexNum + k] + t1arr2Matrix[k * p1Graph->vertexNum + j]) {
          t1arr2Matrix[i * p1Graph->vertexNum + j] = t1arr2Matrix[i * p1Graph->vertexNum + k] + t1arr2Matrix[k * p1Graph->vertexNum + j];
          t1arr2PassVertex[i * p1Graph->vertexNum + j] = k;

          // printf("t1arr2Matrix,k=%d,i=%d,j=%d\r\n", k, i, j);
          // for (int i = 0; i < p1Graph->vertexNum; i++) {
          //   for (int j = 0; j < p1Graph->vertexNum; j++) {
          //     printf("[%3d],", t1arr2Matrix[i * p1Graph->vertexNum + j]);
          //   }
          //   printf("\r\n");
          // }
        }
      }
    }
  }

  printf("t1arr2Matrix\r\n");
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    for (int j = 0; j < p1Graph->vertexNum; j++) {
      printf("[%2d],", t1arr2Matrix[i * p1Graph->vertexNum + j]);
    }
    printf("\r\n");
  }

  printf("t1arr2PassVertex\r\n");
  for (int i = 0; i < p1Graph->vertexNum; i++) {
    for (int j = 0; j < p1Graph->vertexNum; j++) {
      printf("[%d],", t1arr2PassVertex[i * p1Graph->vertexNum + j]);
    }
    printf("\r\n");
  }
}