// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 2                       //
// Implementing Graph ADT     //
// ========================== //

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "List.h"


//defining structure for Graphobj
typedef struct Graphobj{
    List* neighbor;
    int* color;
    int* parent;
    int* distance;
    int order;
    int size;
    int recentVertex;
} GraphObj;

/*** Constructor ***/
Graph makeGraph(int n){
    Graph graph = malloc(sizeof(GraphObj));
    assert(graph != NULL);
    graph->order = n;
    graph->size = NULL;
    graph->recentVertex = NULL;
    graph->neighbor = NULL;
    graph->color = NULL;
    graph->parent = NULL;
    graph->distance = NULL;
    return graph;
}

/*** Destructor ***/
void freegraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
int getOrder(Graph G){
    if(G){
        return G->order;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getOrder(): NULL pointer\n");
        exit(1);
    }
}

int getSize(Graph G){
    if(G){
        return G->size;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSize(): NULL pointer\n");
        exit(1);
    }
}

int getSource(Graph G){
    if(G){
        return G->recentVertex;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSource(): NULL pointer\n");
        exit(1);
    }
}

int getParent(Graph G, int u){
    if(G){
        return G->parent;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getParent(): NULL pointer\n");
        exit(1);
    }
}

int getDist(Graph G, int u){
    if(G){
        return G->distance;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getDist(): NULL pointer\n");
        exit(1);
    }
}

void getPath(List L, Graph G, int u){
    if(G){
        return G->;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getOrder(): NULL pointer\n");
        exit(1);
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
        if(L){
        Graph t = G->order;
    	Graph temp = t;
    	while (G->size > 0) {
            temp = t->recentVertex;
            deleteFront(G);
        	t = temp;
   	    }
        graph->order = n;
        graph->size = NULL;
        graph->recentVertex = NULL;
        graph->neighbor = NULL;
        graph->color = NULL;
        graph->parent = NULL;
        graph->distance = NULL;

    } else {
        fprintf(stderr, " List ADT; ERROR in clear(): NULL pointer\n");
        exit(1);
    }
}

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);