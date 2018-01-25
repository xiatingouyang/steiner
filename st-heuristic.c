#include<stdio.h>
#include<stdlib.h>

/*
information about an edge
*/
struct neighborr;

typedef struct edgee
{

	int v1, v2;	// the two vertex connected by the edge
	int w;		// weight
	int choose;	// 1 -- included in solution;	0 -- not included in solution； -1 temporarly deleted from the graph
	struct neighborr* e1;
	struct neighborr* e2; // pointer to the specify edge of the two adjacency list of the two neighbor;
} edge;


/*
all the neighbors of a certain vertex
*/
typedef struct neighborr{
	int v; 					// vertex label, a value from 1 - V
	edge* e;				// edge
	struct neighborr *next; // pointer to the next neighbor element
	struct neighborr *pre;  // pointer to the previous neighbor element
} neighbor;

/*
information about a vertex
*/
typedef struct nodee
{
	int d;				// degree
	int choose;			// 1 -- included in solution;	0 -- not included in solution, -1 deleted from the graph
	int isTerminal;		// 1 -- is a terminal vertex,   0 -- isn't a terminal
	neighbor* nghList;	// the adjacency list(doubly linked list): neighbor1 (v, e) <-> neighbor2 (v, e) <-> ....  <-> neighbor-d (v,e) -> NULL

} node;


/*
The graph structure

*/
typedef struct gg{

	int V;  // total num of v
	int E;  // total num of e
	int T;  // total num of terminals
	edge ** edges;	// all edges  (index starting from 0)
	node* nodeList;	// all vertices (index starting from 1)
	int *t; // the array of terminals. (index starting from 0)
} graph;

// add an edge into vertex1's adjacency list which connects vertex2.
neighbor * addEdge(graph *g, int eIndex, int vertex1, int vertex2){
	neighbor* ngh;
	(g -> nodeList[vertex1]).d++;
	ngh = (neighbor *)malloc(sizeof(neighbor));
	ngh -> v = vertex2;
	ngh -> e = g -> edges[eIndex];
	if(g -> nodeList[vertex1].nghList == NULL){ // if the adjacency list is null
		ngh->next = NULL;
		ngh->pre = NULL;
		g -> nodeList[vertex1].nghList = ngh;
	} else { // add to the head of the list
		(g -> nodeList[vertex1]).nghList -> pre = ngh;
		ngh -> next = g -> nodeList[vertex1].nghList;
		ngh -> pre = NULL;
		g -> nodeList[vertex1].nghList = ngh;
	}

	return ngh;
}


// used for input
void add(graph *g, int eIndex, int vertex1, int vertex2, int weight){
	neighbor* ngh;


	// add the edge to the graph
	g -> edges[eIndex] = (edge*)malloc(sizeof(edge));
	g -> edges[eIndex]->v1 = vertex1;
	g -> edges[eIndex]->v2 = vertex2;
	g -> edges[eIndex]->w = weight;
	g -> edges[eIndex]->choose = 0;


	// add the edge to the adjancency list of the two vertex
	g -> edges[eIndex] -> e1 = addEdge(g, eIndex, vertex1, vertex2);
	g -> edges[eIndex] -> e2 = addEdge(g, eIndex, vertex2, vertex1);

	/*g -> nodeList[vertex1].d ++;
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
	}*/
}


// delete the specify node and all the edges connected with this node. (also will delete the specified node in the adjacency list)

void deleteNode(graph * g, int n){
	neighbor* ngh = g -> nodeList[n].nghList;
	//edge* e = ngh -> e;

	//printf("\n%d- ", n);
	while(ngh != NULL){
		int num = ngh -> v;
		edge* e = ngh -> e;
		e -> choose = -1;
		//printf("%d e1:%d e2:%d\n", num, e -> e1 -> v, e -> e2 -> v);
		neighbor* other = e -> e1;
		if(e -> e2 -> v == n)
			other = e -> e2;
		if(other -> pre == NULL){
	        //printf("other next: %d\n", other -> v);
			g -> nodeList[num].nghList = other -> next;

			if(other -> next != NULL){
				other -> next -> pre = other -> pre;
			}

		} else {
			other -> pre -> next = other -> next;
			if(other -> next != NULL){
				other -> next -> pre = other -> pre;
			}
		}
		
		ngh = ngh -> next;
	}

	g -> nodeList[n].choose = -1;



    free(g -> nodeList[n].nghList);
	g -> nodeList[n].nghList = NULL;

	for (int i = 0; i < g -> E; i++){
        while(g -> edges[i] -> choose == -1){
        	if(i == g -> E - 1){
        		g -> E --;
        		break;
        	}
        	//printf("%d, %d, - e1:%d e2:%d\n", i, g -> E, g -> edges[i] -> e1 -> v, g -> edges[i] -> e2 -> v);
        	g -> edges[i] = g -> edges[--(g -> E)];
        }
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
			if(ptr -> pre != NULL)
				printf("[pre:%d] ", ptr -> pre -> v);
			ptr = ptr -> next;
		}
		printf("\n");
	}
	// test the "pointing each other"
	printf("-----\n");
	for(int i = 0; i < g -> E; i++){
		if(g -> edges[i] == NULL){
			printf("null edge\n");
			continue;
		}
		printf("edge %d connecting vertex <%d, %d>\n", i, g -> edges[i] -> e1 -> v, g -> edges[i] -> e2 -> v);
	}

	printf("-----\n");
	printf("The terminals are: ");
	for(int i = 0; i < g -> T; i++){
		printf("%d ", g -> t[i]);
	}
	printf("\n");

}

void reduceEdge(graph * g){
	int queue[g -> V + 10];
	int st = 0, ed = 0;
	for(int i = 1; i <= g -> V; i++){
		if(g -> nodeList[i].d == 1 && !g -> nodeList[i].isTerminal){
			queue[ed] = i;
			ed++;
		}
	}
	while(st < ed){
		int cur = queue[st], i;
		//report(g);
		st++;
		i = g -> nodeList[cur].nghList -> v;


		deleteNode(g, cur);
		g -> nodeList[cur].d--;
		g -> nodeList[i].d--;
		if(g -> nodeList[i].d == 1 && !g -> nodeList[i].isTerminal){
			queue[ed] = i;
			ed++;
		}
	}

    printf("total deleted: %d\n", st);
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
		g -> nodeList[i].d = 0;
		g -> nodeList[i].choose = 0;
		g -> nodeList[i].isTerminal = 0;
		g -> nodeList[i].nghList = NULL;
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
		g -> nodeList[i].isTerminal = 1;
		g -> t[i] = tt;
	}

	reduceEdge(g);


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

// a test method to compute a spanning tree
int testST(graph *g) {
	int finish = 0;
	g->edges[0]->choose = 1;
	g->nodeList[g->edges[0]->v1].choose = 1;
	g->nodeList[g->edges[0]->v2].choose = 1;
	while (!finish) {
		finish = 1;
		for (int i=1; i<g->E; i++) {
            //if(g->nodeList[g->edges[i]->v1] == NULL || g->nodeList[g->edges[i]->v2] == NULL) continue;
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

void testDelete(graph * g){
	deleteNode(g, 2);
}

int main(){
	graph *g = (graph *)malloc(sizeof(graph));
	readInput(g);
	report(g);
	testST(g);
	testDelete(g);
	report(g);
	return 0;
}
