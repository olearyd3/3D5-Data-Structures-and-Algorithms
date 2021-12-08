#ifndef T2_H_
#define T2_H_

#define INFINITE 9999 // definte a very large value

typedef struct Graph {
    int* permanent;
    int num_vertices;
    int** adjacency_matrix;
} Graph;

Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to, int weight); // adds a weighted edge
void dijkstra(Graph* g, int origin);
void delete_graph(Graph* g);

#endif
