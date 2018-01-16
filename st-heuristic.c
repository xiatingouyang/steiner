#include<stdio.h>
#include<stdlib.h>

/*
The individual element in the adjacency list consisting of the following:

*/
typedef struct neighborr{
	int v; // vertex label, a value from 1 - V
	int w; // edge weight
	struct neighborr *next; // pointer to the next neighbor element
}neighbor;


/*
The graph structure

*/
typedef struct gg{

	int V;  // total num of v
	int E;  // total num of e
	int T;  // total num of terminals
	neighbor **list; // the adjacency list

	// 	   list (ptr)
	//      |
	//	    v

	//      neighbor-11 (v, w) -> neighbor-12 -> ....  -> neighbor-d1 -> NULL
	//      neighbor-21 (v, w) -> neighbor-22 -> ....  -> neighbor-d1 -> NULL
	//      ..
	//      ..
	//      neighbor-V1 (v, w) -> neighbor-d2 -> ....  -> neighbor-d1 -> NULL

	int *d; // the array of degrees. d[i] denotes the degree of vertex i (index starting from 1)
	int *t; // the array of terminals. (index starting from 0)
}graph;


// used to update the edges and the degree
void add(graph *g, int v, int v1, int w){
	neighbor* n = (neighbor *)malloc(sizeof(neighbor));
	g -> d[v] ++;

	n -> v = v1;
	n -> w = w;
	if(g -> list[v] == NULL){
		n -> next = NULL;
		g -> list[v] = n;
		return;
	}
	n -> next = g -> list[v];
	g -> list[v] = n;

}


// report the specs of the graph (V, E, degree for each v, all neighbors of a v, the terminals)
void tranverse(graph *g){
	printf("The graph has %d vertices and %d edges.\n", g -> V, g -> E);
	for(int i = 1; i <= g -> V; i++){
		printf("%d[%d]: ", i, g->d[i]);
		neighbor * ptr = g -> list[i];
		while (ptr != NULL){
			printf("(%d, %d) ", ptr -> v, ptr->w);
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
	int v;
	int e;
	int t;
	int v1, v2;
	int w;
	int tt;

	// read the vertices and edges
	scanf("SECTION Graph\nNodes %d\nEdges %d\n", &v, &e);
	g -> V = v;
	g -> E = e;
	g -> list = (neighbor**)malloc((v+1) * sizeof(neighbor*)); 
	g -> d = (int*) malloc((v+1) * sizeof(int));

	for(int i = 0; i < e; i++){
		scanf("E %d %d %d\n", &v1, &v2, &w);
		add(g, v2, v1, w);
		add(g, v1, v2, w);
	}

	// read the terminals
	scanf("END\nSECTION Terminals\nTerminals %d\n", &t);
	g -> T = t;
	g -> t = (int*) malloc((t+5) * sizeof(int));
	int num = 0;
	
	for(int i = 0; i < t; i++){
		scanf("T %d\n", &tt);
		g -> t[num++] = tt;
	}
}


int main(){
	graph *g = (graph *)malloc(sizeof(graph));
	readInput(g);
	tranverse(g);
	return 0;
}