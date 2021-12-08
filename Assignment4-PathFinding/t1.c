#include <stdio.h>
#include <stdlib.h>
#include "t1.h"

int counter = 0;

// converts an upper case character (A-Z) to a numerical value (between 0 and 25) 
static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}

	return c-'A';
}

//function to convert an integer from 0-25 to the relevant alphabet character
static char val2char(int i) {
    if(i < 0 || i > 25) {
        return -1;
    }
    return i + 'A';
}


//function to create a node
Node* create_node(int vertex) {
    //allocate memory
    Node* new_node = malloc(sizeof(Node));
    //set the vertex to the first one
    new_node->vertex = vertex;
    //set next to null
    new_node->next = NULL;
    return new_node;
}

// creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
Graph* create_graph(int num_nodes) {
    //malloc new memory
    Graph* new_graph = (Graph*)malloc(sizeof(Graph));
    //allocate memory for visited and adjacency_list and 
    new_graph->num_vertices = num_nodes;
    new_graph->adjacency_list = malloc(num_nodes*sizeof(Node*));
    new_graph->visited = malloc(num_nodes*sizeof(int));
    //for each node, set that slot of adjacency list and visited to Null/0
    for(int i = 0; i < num_nodes; i++) {
        new_graph->adjacency_list[i] = NULL;
        new_graph->visited[i] = 0;
    }
    return new_graph;
}

//function to create a queue
Queue* create_queue() {
    //allocate memory to queue
    Queue* q = (Queue*)malloc(sizeof(Queue));
    //set the front and back of the queue to -1
    q->front = -1;
    q->rear = -1;
    return q;
}

//adds a directed edge
void add_edge(Graph *g, int from, int to) {
    //create a new node
    Node* new_node = create_node(to);
    //put where the node came from in next.
    new_node->next = g->adjacency_list[from];
    //set the from slot of the adjacency list to new_node
    g->adjacency_list[from] = new_node;
}

//function to check if a queue is empty
int is_empty(Queue* q) {
    //if the end of the queue is -1, return true
    if(q->rear == -1) {
        return 1;
    }
    //else false
    else {
        return 0;
    }
}

//function to add elements to a queue
void enqueue(Queue* q, int value) {
    //if the queue is full, print a warning message
    if(q->rear == SIZE-1) {
        printf("\nThere is no more room");
    }
    //otherwise if the front is -1 set the front to 0
    else {
        if(q->front == -1) {
            q->front = 0;
        }
        //add 1 to the back
        q->rear++;
        //set to value
        q->items[q->rear] = value;
    }
}

//function to remove elements from a queue
int dequeue(Queue* q) {
    int letter;
    //if the queue is empty set the letter to -1
    if(is_empty(q)) {
        printf("\nThe queue is empty");
        letter = -1;
    }
    //otherwise
    else {
        letter = q->items[q->front];
        //add 1 to front
        q->front++;
        //if the front is greater than the back set them to -1
        if(q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return letter;
}

//implements breadth first search and prints the results
void bfs(Graph* g, int origin) { 
    //create a new queue
    Queue* q = create_queue();
    //set visited back to zero for each vertex, since it will have been marked as 1 from DFS
    int count = 0;
    if(count == 0) {
        for(int i = 0; i < g->num_vertices; i++) {
            g->visited[i] = 0;
        }
        count++;
        printf("\n");
        printf("BFS ");
    }
    //mark the first vertex as visited
    g->visited[origin] = 1;
    //add it to the queue
    enqueue(q, origin);
    //while the queue is not empty
    while(!is_empty(q)) {
        //set current to the value to be dequeued
        int current = dequeue(q);
        char c = val2char(current);
        printf(" %c ", c);

        //create a temporary variable and set it equal to the value in the current slot of the adjacency list
        Node* temp = g->adjacency_list[current];
        //while this temporary variable exists
        while(temp) {
            //set the adjacent vertex equal to the vertex
            int adjacent_vertex = temp->vertex;
            //if the adjacent vertex slot has not been visited
            if(g->visited[adjacent_vertex] == 0) {
                //mark it as visited
                g->visited[adjacent_vertex] = 1;
                //add it to the queue
                enqueue(q, adjacent_vertex);
            }
            //set temp equal next
            temp = temp->next;
        }
    }
    printf("\n");
    free(q);
}

//implements depth first search and prints the results
void dfs(Graph* g, int origin) {
    //create a temporary variable for the adjacenct list
    Node* adj_list = g->adjacency_list[origin];
    Node* temp = adj_list;
    //printing
    if(counter == 0) {
        printf("DFS:");
        counter++;
    }
    //mark the vertex as visited
    g->visited[origin] = 1;
    //convert the integer back to character
    char c = val2char(origin);
    printf(" %c ", c);
    //while the temporary variable isn't NULL
    while(temp != NULL) {
        int connection = temp->vertex;
        //if the connection is 0
        if(!(g->visited[connection])) {
            //recursively carry out DFS
            dfs(g, connection);
        }
        //set temp = to next temp
        temp = temp->next;
    }
}

//function to free memory
void delete_graph(Graph *g) {
    for(int i = 0; i < g->num_vertices; i++) {
        Node* temp = g->adjacency_list[i];
        while(temp != NULL) {
            Node* new_temp = temp;
            temp = temp->next;
            free(new_temp);
        }
    }
    free(g->visited);
    free(g->adjacency_list);
    free(g);
}

int main() {
    int num_nodes = 7;
    Graph *graph = create_graph(num_nodes);
   
    add_edge(graph, char2val('A'), char2val('E'));
    add_edge(graph, char2val('B'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('B'));
    add_edge(graph, char2val('B'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('B'));
    add_edge(graph, char2val('E'), char2val('D'));
    add_edge(graph, char2val('D'), char2val('F'));
    add_edge(graph, char2val('F'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('D'));
    add_edge(graph, char2val('D'), char2val('G'));

    dfs(graph, char2val('A'));
    bfs(graph, char2val('A'));

    delete_graph(graph);

}
