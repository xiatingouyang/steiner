#include<stdio.h>
#include<stdlib.h>

typedef struct edgee
{
	int v1, v2;
	int w;
	int choose;	// 1 -- included in solution;	0 -- not included in solution
} edge;


/*
The individual element in the adjacency list consisting of the following:

*/
typedef struct neighborr{
	int v; // vertex label, a value from 1 - V
	edge* e;
	struct neighborr *next; // pointer to the next neighbor element
} neighbor;


typedef struct nodee
{
	int d;	// degree
	int choose;	// 1 -- included in solution;	0 -- not included in solution
	neighbor* nghList;// the adjacency list
	//      neighbor-11 (v, w) -> neighbor-12 -> ....  -> neighbor-d1 -> NULL
} node;


/*
The graph structure

*/
typedef struct gg{

	int V;  // total num of v
	int E;  // total num of e
	int T;  // total num of terminals
	edge ** edges;
	node* nodeList;
	int *t; // the array of terminals. (index starting from 0)
} graph;


// used to update the edges and the degree
void add(graph *g, int eIndex, int vertex1, int vertex2, int weight){
	neighbor* ngh;
	
	g -> edges[eIndex] = (edge*)malloc(sizeof(edge));
	g -> edges[eIndex]->v1 = vertex1;
	g -> edges[eIndex]->v2 = vertex2;
	g -> edges[eIndex]->w = weight;
	g -> edges[eIndex]->choose = 0;

	g -> nodeList[vertex1].d ++;
	ngh = (neighbor *)malloc(sizeof(neighbor));
	ngh -> v = vertex2;
	ngh -> e = g -> edges[eIndex];
	if(g -> nodeList[vertex1].nghList == NULL){
		ngh -> next = NULL;
		g -> nodeList[vertex1].nghList = ngh;
	} else {
		ngh -> next = g -> nodeList[vertex1].nghList;
		g -> nodeList[vertex1].nghList= ngh;
	}

	g -> nodeList[vertex2].d ++;
	ngh = (neighbor *)malloc(sizeof(neighbor));
	ngh -> v = vertex1;
	ngh -> e = g -> edges[eIndex];
	if(g -> nodeList[vertex2].nghList == NULL){
		ngh -> next = NULL;
		g -> nodeList[vertex2].nghList = ngh;
	} else {
		ngh -> next = g -> nodeList[vertex2].nghList;
		g -> nodeList[vertex2].nghList = ngh;
	}
}


// report the specs of the graph (V, E, degree for each v, all neighbors of a v, the terminals)
void report(graph *g){
	printf("The graph has %d vertices and %d edges.\n", g -> V, g -> E);
	for(int i = 1; i <= g -> V; i++){
		printf("%d[%d]: ", i, g->nodeList[i].d);
		neighbor * ptr = g -> nodeList[i].nghList;
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
	g -> edges = (edge**)malloc(e * sizeof(edge*));
	g -> nodeList = (node*)malloc((v+1) * sizeof(node));
	for (int i=1; i<=v; i++) {
		g->nodeList[i].d = 0;
		g->nodeList[i].choose = 0;
		g->nodeList[i].nghList = NULL;
	}

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

void outputResult(graph *g) {
	long long value = 0;
	for (int i=0; i<g->E; i++) {
		if (g->edges[i]->choose==1) {
			value += g->edges[i]->w;
		}
	}
	printf("VALUE %lld\n", value);
	for (int i=0; i<g->E; i++) {
		if (g->edges[i]->choose==1) {
			printf("%d %d\n", g->edges[i]->v1, g->edges[i]->v2);
		}
	}
}


int testST(graph *g) {
	int finish = 0;
	g->edges[0]->choose = 1;
	g->nodeList[g->edges[0]->v1].choose = 1;
	g->nodeList[g->edges[0]->v2].choose = 1;
	while (!finish) {
		finish = 1;
		for (int i=1; i<g->E; i++) {
			if (g->nodeList[g->edges[i]->v1].choose + g->nodeList[g->edges[i]->v2].choose==1) {
				g->edges[i]->choose = 1;
				g->nodeList[g->edges[i]->v1].choose = 1;
				g->nodeList[g->edges[i]->v2].choose = 1;
				finish = 0;
				break;
			}
		}
	}
	outputResult(g);
}


int main(){
	graph *g = (graph *)malloc(sizeof(graph));
	readInput(g);
	report(g);
	testST(g);
	return 0;
}