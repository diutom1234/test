#include "jrb.h"
typedef JRB Graph;

Graph createGraph();
void addEdge_int(Graph graph, int v1, int v2);
void addEdge_str(Graph graph, char* v1, char* v2);
int getAdjacentVertices_int (Graph graph, int v, int* output);
int getAdjacentVertices_str (Graph graph, char* v, char output[10][10]);

void dropGraph(Graph graph);
