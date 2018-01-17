#include<stdio.h>
#include<stdlib.h>

typedef struct edgee
{
	int v1, v2;
	int w;
} edge;


/*
The individual element in the adjacency list consisting of the following:

*/
typedef struct neighborr{
	int v; // vertex label, a value from 1 - V
	edge* e;
	struct neighborr *next; // pointer to the next neighbor element
}neighbor;


/*
The graph structure

*/
typedef struct gg{

	int V;  // total num of v
	int E;  // total num of e
	int T;  // total num of terminals
	int *d; // the array of degrees. d[i] denotes the degree of vertex i (index starting from 1)
	edge * edges;
	neighbor **list; // the adjacency list

	// 	   list (ptr)
	//      |
	//	    v

	//      neighbor-11 (v, w) -> neighbor-12 -> ....  -> neighbor-d1 -> NULL
	//      neighbor-21 (v, w) -> neighbor-22 -> ....  -> neighbor-d1 -> NULL
	//      ..
	//      ..
	//      neighbor-V1 (v, w) -> neighbor-d2 -> ....  -> neighbor-d1 -> NULL

	int *t; // the array of terminals. (index starting from 0)
} graph;


// used to update the edges and the degree
void add(graph *g, int eIndex, int vertex1, int vertex2, int weight){
	neighbor* ngh;
	
	g -> edges[eIndex].v1 = vertex1;
	g -> edges[eIndex].v2 = vertex2;
	g -> edges[eIndex].w = weight;

	g -> d[vertex1] ++;
	ngh = (neighbor *)malloc(sizeof(neighbor));
	ngh -> v = vertex2;
	ngh -> e = &(g -> edges[eIndex]);
	if(g -> list[vertex1] == NULL){
		ngh -> next = NULL;
		g -> list[vertex1] = ngh;
	} else {
		ngh -> next = g -> list[vertex1];
		g -> list[vertex1] = ngh;
	}

	g -> d[vertex2] ++;
	ngh = (neighbor *)malloc(sizeof(neighbor));
	ngh -> v = vertex1;
	ngh -> e = &(g -> edges[eIndex]);
	if(g -> list[vertex2] == NULL){
		ngh -> next = NULL;
		g -> list[vertex2] = ngh;
	} else {
		ngh -> next = g -> list[vertex2];
		g -> list[vertex2] = ngh;
	}
}


// report the specs of the graph (V, E, degree for each v, all neighbors of a v, the terminals)
void tranverse(graph *g){
	printf("The graph has %d vertices and %d edges.\n", g -> V, g -> E);
	for(int i = 1; i <= g -> V; i++){
		printf("%d[%d]: ", i, g->d[i]);
		neighbor * ptr = g -> list[i];
		while (ptr != NULL){
			printf("(%d, %d) ", ptr -> v, ptr->e->w);
			ptr = ptr -> next;
		}
		printf("\n");
	}
	printf("The terminals are: ");
	for(int i = 0; i < g -> T; i++){
		printf("%d ", g -> t[i]);
	}
	printf("\n");

}

void readInput(graph *g){
	int v,e,t,v1,v2,w,tt;

	// read the vertices and edges
	scanf("SECTION Graph\nNodes %d\nEdges %d\n", &v, &e);
	g -> V = v;
	g -> E = e;
	g -> d = (int*) malloc((v+1) * sizeof(int));
	g -> edges = (edge *)malloc(e * sizeof(edge));
	g -> list = (neighbor**)malloc((v+1) * sizeof(neighbor*)); 

	for(int i = 0; i < e; i++){
		scanf("E %d %d %d\n", &v1, &v2, &w);
		add(g, i, v1, v2, w);
	}

	// read the terminals
	scanf("END\nSECTION Terminals\nTerminals %d\n", &t);
	g -> T = t;
	g -> t = (int*) malloc(t * sizeof(int));
	
	for(int i = 0; i < t; i++){
		scanf("T %d\n", &tt);
		g -> t[i] = tt;
	}
}


int main(){
	graph *g = (graph *)malloc(sizeof(graph));
	readInput(g);
	tranverse(g);
	return 0;
}