#include <stdlib.h>
#include <stdio.h>
#include "t2.h"

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

// creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
Graph* create_graph(int num_nodes) {
    //malloc new memory for the graph
    Graph* new_graph = (Graph*)malloc(sizeof(Graph));
    //there are 7 nodes
    new_graph->num_vertices = num_nodes;
    //allocate memory for whether a node is permanent or not and for the matrix
    new_graph->permanent = malloc(num_nodes*sizeof(int));
    new_graph->adjacency_matrix = malloc(num_nodes*sizeof(int*));
    //allocate memory for each slot of the matrix and set each slot to 0.
    for(int i = 0; i < num_nodes; i++) {
        new_graph->adjacency_matrix[i] = calloc(sizeof(int), num_nodes);
    }
    //return the graph
    return new_graph;
} 

// adds a weighted edge
void add_edge(Graph *g, int from, int to, int weight) {
    //store the distance between the two nodes in the corresponding matrix slots
    g->adjacency_matrix[from][to] = weight;
    g->adjacency_matrix[to][from] = weight;
} 

//implement dijkstra algo and print order in which nodes are made permanent and length of shortest path between origin node and all others
void dijkstra(Graph* g, int origin) {
    //initialise arrays for the cost of the path, the distance and whether or not something is permanent
    int cost[g->num_vertices][g->num_vertices];
    int distance[g->num_vertices];
    int permanent[g->num_vertices];

    //for each slot in the adjacency matrix
    for(int i = 0; i < g->num_vertices; i++) {
        for(int j = 0; j < g->num_vertices; j++) {
            //if the slot is 0, make its cost be infinite, i.e. there is no path
            if(g->adjacency_matrix[i][j] == 0) {
                cost[i][j] = INFINITE;
            }
            //otherwise let the cost be the weight of the path
            else {
                cost[i][j] = g->adjacency_matrix[i][j];
            }
        }
    }
    
    //for each node
    for(int i = 0; i < g->num_vertices; i++){
        //let the distance be the weight of the path
        distance[i] = cost[origin][i];
        //mark each as not permanent
        permanent[i] = 0;
    }

    //set the distance from first node to itself to 0 - this is the starting point
    distance[origin] = 0;
    //set the first node as permanent and add 1 to counter
    permanent[origin] = 1;
    int count = 1;
    int next_node;
    //print the starting node
    char startpoint = val2char(origin);
    printf("%c ", startpoint);

    //while there are still nodes to be made permanent
    while(count < g->num_vertices){
        int min = INFINITE;

        //if the distance to i is less than the path's minimum and it isn't permanent, set the minimum to the distance and the next_node to i
        for(int i = 0; i < g->num_vertices; i++) {
            if(min > distance[i] && permanent[i] == 0) {
                min = distance[i];
                next_node = i;
            }
        }
        permanent[next_node] = 1;
        //for each node after the starting one
        for(int i = 0; i < g->num_vertices; i++) {
            //calculate the distances by adding the weight and the cost arrays
            int dist = min + cost[next_node][i];
            //if the new path is shorter, update the distance value
            if(dist < distance[i] && permanent[i] == 0) {
                distance[i] = dist;
            }
        }
        //make the current node permanent and print it out. Add 1 to the counter
        char c = val2char(next_node);
        printf("%c ", c);
        count++;
    }
    printf("\n");

    //printing the length of the shortest path from A to each node
    for(int i = 0; i < g->num_vertices; i++) {
        char ch = val2char(i);
        printf("The length of the shortest path between %c and %c is %i", startpoint, ch, distance[i]);
        printf("\n");
    }
}

//delete the graph and all its data structures
void delete_graph(Graph *g) {
    //free each row of the matrix
    for(int i = 0; i < g->num_vertices; i++) {
        free(g->adjacency_matrix[i]);
    }
    //free permanent and the matrix
    free(g->permanent);
    free(g->adjacency_matrix);
    //free the graph
    free(g);
}

int main(){
    int num_nodes = 10;
    Graph *graph = create_graph(num_nodes);
    add_edge(graph, char2val('A'), char2val('E'), 190);
    add_edge(graph, char2val('B'), char2val('D'), 110);
    add_edge(graph, char2val('C'), char2val('F'), 240);
    add_edge(graph, char2val('D'), char2val('E'), 90);
    add_edge(graph, char2val('D'), char2val('F'), 130);
    add_edge(graph, char2val('D'), char2val('G'), 250);
    add_edge(graph, char2val('E'), char2val('G'), 150);
    add_edge(graph, char2val('E'), char2val('H'), 90);
    add_edge(graph, char2val('F'), char2val('G'), 150);
    add_edge(graph, char2val('F'), char2val('I'), 80);
    add_edge(graph, char2val('G'), char2val('H'), 100);
    add_edge(graph, char2val('G'), char2val('I'), 110);
    add_edge(graph, char2val('G'), char2val('J'), 250);
    add_edge(graph, char2val('H'), char2val('J'), 300);
    add_edge(graph, char2val('I'), char2val('J'), 280);
    
    printf("   ");
    for (int i = 0; i < graph->num_vertices; i++) {
    printf("%c  ", i + 'A');
    }
    printf("\n");

    for (int i = 0; i < graph->num_vertices; i++) {
        printf("%c: ", i + 'A');
        for (int j = 0; j < graph->num_vertices; j++) {
            printf("%i  ", graph->adjacency_matrix[i][j]);
        }
        printf("\n");
    }

    dijkstra(graph, char2val('J'));
    
    delete_graph(graph);

}
