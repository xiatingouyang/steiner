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
	struct edge * chr; // new edge to replace the original edge
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
	int father;			// father node index (for Kruskal algorithm)
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
	int cur_v_num; // after reduction, the current number of nodes
	int cur_e_num; // after reduction, the current number of edges
} graph;

typedef struct edge_list{
    edge * parent;
    neighbor * edge_list;
} chr_edges;




int main(){
	graph *g = (graph *)malloc(sizeof(graph));
	readInput(g);
	//report(g);
	kruskal(g);
	//testST(g);
	outputResult(g);
	return 0;
}


void readInput(graph *g){
	int v,e,t,v1,v2,w,tt;

	// read the vertices and edges
	scanf("SECTION Graph\nNodes %d\nEdges %d\n", &v, &e);
	g -> V = v;
    g -> cur_v_num = v;
	g -> E = e;
    g -> cur_e_num = e;
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
		g -> nodeList[tt].isTerminal = 1;
		g -> t[i] = tt;
	}

	//reduce(g);

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
	g -> edges[eIndex]->chr = null;


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


//do optimization by reducing some nodes with degree 1 and 2

void reduce(graph * g){
    reduce_d1(graph * g);
    reduce_d2(graph * g);
}


void reduce_d1(graph * g){
    int queue_d1[g -> V + 10];
    int beg = 0, end = 0;

    //add all nodes with degree 1 into the queue
    for(int i = 1; i <= g -> V; i++)
        if(g->nodeList[i].d == 1)
            queue_d1[end++]=1;

    //deal with nodes with degree 1 one by one
    int cur, ngh_node;
    while(beg < end){
        cur = queue_d1[beg++];
        ngh_node = g -> nodeList[cur].nghList -> v;

        // choose terminal, deleter non-terminal
        if(g -> nodeList[i].isTerminal)
            chooseNode_(g, cur, nodeList[cur].nghList -> e);
        else
            deleteNode(g, cur);

        if(g -> nodeList[i].d == 1)
            queue[end++] = 1;
    }

}

void chooseNode(graph * g, int n, edge * e){
    g -> nodeList[n].choose = 1;
    e -> choose = 1;
}

// delete the specify node and all the edges connected with this node. (also will delete the specified node in the adjacency list)

void deleteNode(graph * g, int n){
	neighbor* ngh = g -> nodeList[n].nghList;
	//edge* e = ngh -> e;

	//printf("\n%d- ", n);
	while(ngh != NULL){
		int num = ngh -> v;
		edge* e = ngh -> e;

        g -> nodeList[num].d--; // add from reduceEdge
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


void reduce_d2(graph * g){
    int queue_d2[g -> V + 10];
    int beg = 0, end = 0;

    //add all nodes with degree 1 into the queue
    for(int i = 1; i <= g -> V; i++)
        if( g -> nodeList[i].d == 2)
            queue_d2[end++] = i;

    //deal with nodes with degree 1 one by one
    int cur, ngh1, ngh2, w1, w2;
    edge * e1 = null, e2 = null;
    while(beg < end){
        cur = queue_d2[beg++];
        ngh1 = g -> nodeList[cur].nghList -> v;
        ngh2 = g -> nodeList[cur].nghList -> next -> v;
        e1 = nodeList[cur].nghList -> e;
        e2 = nodeList[cur].nghList -> next -> e;
        int w1 = e1 -> w;
        int w2 = e2 -> w;

        if(!g -> nodeList[cur].isTerminal && !g -> nodeList[ngh1].isTerminal && !nodeList[ngh2].isTerminal)
            nodeList[cur].choose = -1;

        else if(g -> nodeList[cur].isTerminal){
            if(w1 <= w2 && nodeList[ngh1].isTerminal){
               g -> nodeList[cur].choose = 1;
               g -> nodeList[ngh1].nghList -> e -> choose = 1;
               g -> nodeList[ngh2].nghList -> e -> choose = -1;
            }
            if(w1 >= w2 && nodeList[ngh2].isTerminal){
               g -> nodeList[cur].choose = 1;
               g -> nodeList[ngh1].nghList -> e -> choose = -1;
               g -> nodeList[ngh2].nghList -> e -> choose = 1;
            }

        else if(!g -> nodeList[cur].isTerminal){
            g -> nodeList[cur].choose = -1;
            g -> nodeList[ngh1].nghList -> e -> choose = -1;
            g -> nodeList[ngh2].nghList -> e -> choose = -1;
            replace_edge(g, ngh1, ngh2, w1 + w2, e1, e2);
            }
        }
    }


}

replace_edge(graph * g, int v1, int v2, int w, edge * e1, edge * e2){
    int eIndex = g -> cur_edg;
    neighbor* ngh;


	// add the edge to the graph
	g -> edges[eIndex] = (edge*)malloc(sizeof(edge));
	g -> edges[eIndex]->v1 = v1;
	g -> edges[eIndex]->v2 = v2;
	g -> edges[eIndex]->w = w;
	g -> edges[eIndex]->choose = 0;
	g -> edges[eIndex] -> cur_v_num++;
	g -> edges[eIndex] -> cur_e_num--;
	chr_edges * chr = (chr_edges *)malloc(sizeof(chr_edges));
    g -> edges[eIndex]->chr = chr;


	// add the edge to the adjancency list of the two vertex
	g -> edges[eIndex] -> e1 = addEdge(g, eIndex, vertex1, vertex2);
	g -> edges[eIndex] -> e2 = addEdge(g, eIndex, vertex2, vertex1);

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
		printf("edge %d connecting vertex <%d, %d> with weight %d\n", i, g -> edges[i] -> v1, g -> edges[i] -> v2, g -> edges[i]-> w);
	}

	printf("-----\n");
	printf("The terminals are: ");
	for(int i = 0; i < g -> T; i++){
		printf("%d ", g -> t[i]);
	}
	printf("\n");

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


int cmpfunc (const void * a, const void * b) {
	return ( (*(edge**)a)->w - (*(edge**)b)->w );
}


/* sort edges according to edge weight (small to large) */
void sortEdges(graph *g) {
	qsort(g->edges, g->E, sizeof(edge*), cmpfunc);
}


int getFather(graph *g, int nodeIndex) {
	int f1, f2;
	f1 = g->nodeList[nodeIndex].father;
	if (f1==nodeIndex) {
		return nodeIndex;
	} else {
		f2 = getFather(g, f1);
		g->nodeList[nodeIndex].father = f2;
		return f2;
	}

}


void kruskal(graph *g) {
	int i, f1, f2;

	sortEdges(g);

	// initialize nodes, the father for each node is itself at the beginning
	for (i=1; i<=g->V; i++) {
		g->nodeList[i].father = i;
	}

	// enumerate all edges
	for (i=0; i<g->E; i++) {
		f1 = getFather(g, g->nodeList[g->edges[i]->v1].father);
		f2 = getFather(g, g->nodeList[g->edges[i]->v2].father);
		if (f1!=f2) {
			g->nodeList[g->edges[i]->v1].choose = 1;
			g->nodeList[g->edges[i]->v2].choose = 1;
			g->edges[i]->choose = 1;
			g->nodeList[f1].father = f2;
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
}

void testDelete(graph * g){
	deleteNode(g, 2);
}
