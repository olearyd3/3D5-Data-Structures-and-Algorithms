#ifndef T1_H_
#define T1_H_

//define max size
#define SIZE 100

//struct for a node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

//struct for the queue to be used for BFS
typedef struct Queue {
    int items[SIZE];
    int front; //front of the queue
    int rear; //back of the queue
} Queue;

typedef struct Graph {
    int num_vertices; //number of vertices
    int num_edges; //number of edges
    Node** adjacency_list; //adjacency list
    int* visited; //to check if a node has been visited or not
} Graph;

Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to); // adds a directed edge
void enqueue(Queue* q, int value); //adding something to a queue
int dequeue(Queue* q); //function to remove something from a queue
int is_empty(Queue* q); //checks if queue is empty
void bfs(Graph* g, int origin); //implements breath first search and prints the results
void dfs(Graph* g, int origin); //implements depth first search and prints the results
void delete_graph(Graph *g);

#endif
