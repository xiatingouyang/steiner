#include<stdio.h>
#include<stdlib.h>

typedef struct neighborr{
	int v;
	int w;
	struct neighborr *next;
}neighbor;

typedef struct gg{

	int V;
	int E;
	int T;
	neighbor **list;
	int *d;
	int *t;
}graph;

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

	scanf("SECTION Graph\nNodes %d\nEdges %d\n", &v, &e);
	g -> V = v;
	g -> E = e;
	g -> list = (neighbor**)malloc((v+5) * sizeof(neighbor*));
	g -> d = (int*) malloc((v+5) * sizeof(int));

	for(int i = 0; i < e; i++){
		scanf("E %d %d %d\n", &v1, &v2, &w);
		add(g, v2, v1, w);
		add(g, v1, v2, w);

	}

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