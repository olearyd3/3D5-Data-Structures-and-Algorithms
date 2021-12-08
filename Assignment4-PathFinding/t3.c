#include <stdio.h>
#include <stdlib.h>
#include "t3.h"

int num_vertices = 0;
int num_edges = 0;

Graph* g;
Vertices* ver[MAX_GRAPH];

//function to convert an integer from 0-25 to the relevant alphabet character
static char val2char(int i) {
    if(i < 0 || i > 25) {
        return -1;
    }
    return i + 'A';
}

void graph_init() {
    g = malloc(sizeof(Graph));
    for(int i = 0; i < MAX_STRING_SIZE; i++) {
        for(int j = 0; j < MAX_STRING_SIZE; j++) {   
            g->adjacency_matrix[i][j] = 0;
		}
	}		
}

// adds a weighted edge
void add_edge(int from, int to, int weight) {
    //store the distance between the two nodes in the corresponding matrix slots
    g->adjacency_matrix[from][to] = weight;
    g->adjacency_matrix[to][from] = weight;
} 

// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
int next_token(FILE* f, char *buf, int string_max) {
    int i=0, end=0, quoted=0;
	
	while(!feof(f)) {
		// fetch the next character from file		
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"') { 
			quoted=!quoted; 
			buf[i] = fgetc(f); 
    	}
		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted) { 
        	break; 
    	}
		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n') { 
			end=1; 
			break; 
    	} 
		// truncate fields that would overflow the buffer
		if(i < string_max-1) { 
        	++i; 
        } 
	}
	buf[i] = '\0'; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}

//function to fetch data
Edges *fetch_edges(FILE *csv) {
   	//malloc inside this
   	char buf[MAX_STRING_SIZE];
	Edges *edge = (Edges*)malloc(sizeof(Edges));

   	//call next_token for each term in a line
	next_token(csv, buf, MAX_STRING_SIZE);
	edge->vertex1 = atoi(buf);
	next_token(csv, buf, MAX_STRING_SIZE);
	edge->vertex2 = atoi(buf);
	next_token(csv, buf, MAX_STRING_SIZE);
	edge->weight = atoi(buf);
    num_edges++;
	return edge;
}

Vertices *fetch_vertices(FILE *csv) {
    //malloc
	char buf[MAX_STRING_SIZE];
	Vertices* v = (Vertices*)malloc(sizeof(Vertices));

    //call next_token for each term in a line
	next_token(csv, buf, MAX_STRING_SIZE);
	v->StopId = atof(buf);
	next_token(csv, v->name, MAX_STRING_SIZE);
	next_token(csv, buf, MAX_STRING_SIZE);
	v->latitude = atof(buf);
	next_token(csv, buf, MAX_STRING_SIZE);
	v->longitude = atof(buf);
    num_vertices++;

	return v;
}


//loads the edges from the CSV file of name fname
int load_edges(char *fname) {
    FILE *f;
    int i = 0;
    int j = 0;
    int weight;
    int num_edges = 0;

    // boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f)
    {
        printf("Unable to open %s\n", fname);
        return 0;
    }
    fetch_edges(f);
    graph_init();

    Edges *temp = malloc(sizeof(Edges));
    // read until the end of the file
    while (!feof(f))
    {
        temp = fetch_edges(f);
        i = temp->vertex1;
        j = temp->vertex2;
        weight = temp->weight;
        add_edge(i, j, weight);
        num_edges++;
    }

    // always remember to close your file stream
    fclose(f);
    free(temp);
    printf("Loaded %d edges\n", num_edges);

    return 1;
}

//loads the vertices from the CSV file of name fname
int load_vertices(char *fname) {
    FILE *f;
    //boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f) {
        printf("Unable to open %s\n", fname);
        return 0;
    }
    //remove the first line before reading in the rest of the file
    fetch_vertices(f);
    Vertices *tmp = malloc(sizeof(Vertices));
    // read until the end of the file
    while (!feof(f)) {
        tmp = fetch_vertices(f);
        ver[tmp->StopId] = tmp;
    }
    tmp = NULL;
    // always remember to close your file stream
    fclose(f);
    free(tmp);
    printf("Loaded %d vertices\n", num_vertices-1);
    return 1;
}  

//function to swap values
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int minimum(Graph *g, int dist[MAX_GRAPH], int bools[MAX_GRAPH]) {
    int min = INFINITE;
    int min_index;
    for (int v = 0; v < MAX_GRAPH; v++)
    {
        if (bools[v] == 0 && dist[v] < min)
        {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void dijkstra(Graph *g, int origin, int dest) {
    int distance[MAX_GRAPH], shortestPath[MAX_GRAPH], previous[MAX_GRAPH];
    for (int i = 0; i < MAX_GRAPH; i++)
    {
        distance[i] = INFINITE; //set distance to infinity
        shortestPath[i] = 0;   //and shortestPath to false
        previous[i] = 0;
    }
    distance[origin] = 0; // distance to the origin will always be 0;

    for (int eachNode = 0; eachNode < MAX_GRAPH; eachNode++)
    {
        int min_index = minimum(g, distance, shortestPath); //get min value of current set of unsearched vertices
        shortestPath[min_index] = 1;                        // set current index to true

        for (int j = 0; j < MAX_GRAPH; j++)
        {
            if (!shortestPath[j] && g->adjacency_matrix[min_index][j] && distance[min_index] != INFINITE && distance[min_index] + g->adjacency_matrix[min_index][j] < distance[j])
            {
                previous[j] = min_index;
                distance[j] = distance[min_index] + g->adjacency_matrix[min_index][j];
            }
        }
    }
    while (previous[dest] != origin)
    {
        printf("%d %s\n", ver[previous[dest]]->StopId, ver[previous[dest]]->name);
        dest = previous[dest];
    }
}

// prints the shortest path between startNode and endNode, if there is any
void shortest_path(int startNode, int endNode) {
    swap(&startNode, &endNode);
    printf("%d %s\n", ver[endNode]->StopId, ver[endNode]->name);
    dijkstra(g, startNode, endNode);
    printf("%d %s\n", ver[startNode]->StopId, ver[startNode]->name);
} 

// frees any memory that was used
void free_memory(void) {
	free(g);
}

int
main ( int argc, char *argv[] ) {

	if ( argc < 3 ) {
		printf("usage: ./bus VERTICES EDGES\n");
		return EXIT_FAILURE;
	}

	if ( !load_vertices( argv[1] ) ) {
		printf("Failed to load vertices\n");
		return EXIT_FAILURE;
	}

	if ( !load_edges( argv[2] ) ) {
		printf("Failed to load edges\n");		
		return EXIT_FAILURE;
	}

	


    // get the start and end point
    printf("Please enter stating bus stop >\t\t");
    int startingNode;
    scanf("%d", &startingNode);
    printf("Please enter destination bus stop >\t");
    int endingNode;
    scanf("%d", &endingNode);
	shortest_path(startingNode, endingNode);
    

	free_memory();

	return EXIT_FAILURE;
}
