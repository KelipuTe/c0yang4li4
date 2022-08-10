#include "undirected_graph.c"

int main() {
  UndirectedGraph *p1Graph = InitUndirectedGraph();

  int arr1Edges[][3] = {
      {4, 5, 16},
      {4, 7, 7},
      {5, 1, 13},
      {5, 6, 9},
      {6, 7, 3},
      {0, 1, 10},
      {0, 5, 11},
      {1, 2, 8},
      {1, 6, 16},
      {2, 3, 22},
      {3, 6, 4},
      {3, 7, 6},
  };
  int arr1EdgesLen = sizeof(arr1Edges) / sizeof(int[3]);
  SetEdge(p1Graph, arr1Edges, arr1EdgesLen);

  BuildMatrix(p1Graph);
  PrintUndirectedGraph(p1Graph);

  BreadthFirstSearch(p1Graph);
  DepthFirstSearch(p1Graph);

  PrimAlgorithm(p1Graph);
  return 0;
}
