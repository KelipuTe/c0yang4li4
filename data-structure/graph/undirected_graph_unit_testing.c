#include "undirected_graph.c"

int main() {
  UndirectedGraph *p1UG = InitUndirectedGraph();
  int arr1Edges[][2] = {{4, 5}, {4, 7}, {5, 1}, {5, 6}, {6, 7}, {0, 1}, {0, 5}, {1, 2}, {1, 6}, {2, 3}, {3, 6}, {3, 7}};
  int arr1EdgesLen = sizeof(arr1Edges) / sizeof(int[2]);

  SetEdge(p1UG, arr1Edges, arr1EdgesLen);
  BuildMatrix(p1UG);
  PrintUndirectedGraph(p1UG);
  BreadthFirstSearch(p1UG);
  DepthFirstSearch(p1UG);
}