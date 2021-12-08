#ifndef T3_H_
#define T3_H_

#define MAX_STRING_SIZE 50
#define MAX_GRAPH 8000
#define INFINITE 99999

typedef struct Graph {
    int* permanent;
    int num_vertices;
    int adjacency_matrix[MAX_GRAPH][MAX_GRAPH];
} Graph;

typedef struct Edges {
    int vertex1;
    int vertex2;
    int weight;
} Edges;

typedef struct Vertices {
    int StopId;
    char name[MAX_STRING_SIZE];
    double latitude;
    double longitude;
} Vertices;

int load_edges ( char *fname ); //loads the edges from the CSV file of name fname
int load_vertices ( char *fname );  //loads the vertices from the CSV file of name fname
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory ( void ) ; // frees any memory that was used

#endif
