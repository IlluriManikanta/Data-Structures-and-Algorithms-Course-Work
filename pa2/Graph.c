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
    List* neighbor;             //An array of Lists whose i th element contains the neighbors of vertex i.
    int* color;                 //An array of ints (or chars, or strings) whose i th element is the color (white, gray, black) of vertex i
    int* parent;                //An array of ints whose i th element is the parent of vertex i.
    int* distance;              //An array of ints whose i th element is the distance from the (most recent) source to vertex i.
    int order;
    int size;
    int source;
} GraphObj;


/*** Constructor ***/
Graph newGraph(int n){
    Graph graph = malloc(sizeof(GraphObj));
    assert(graph != NULL);
    graph->neighbor = malloc(sizeof(List*) * (n + 1));
    graph->color = malloc(sizeof(int*) * (n + 1));
    graph->parent = malloc(sizeof(int*) * (n + 1));
    graph->distance = malloc(sizeof(int*) * (n +1));

    for(int i = 0; i <= n; i++){
        graph->neighbor[i] = newList();
        graph->color[i] = WHITE;
        graph->parent[i] = NIL;
        graph->distance[i] = INF;
    }
    graph->order = n;
    graph->size = 0;
    graph->source = NIL;

    return graph;
}

/*** Destructor ***/
void freeGraph(Graph* pG){
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
        if(G->source == NIL){
            return NIL;
        }
        return G->source;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSource(): NULL pointer\n");
        exit(1);
    }
}

int getParent(Graph G, int u){
    if(G){
        if(G->parent == NIL){
            return NIL;
        }
        List p = G->parent;

        return G->parent[u];
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getParent(): NULL pointer\n");
        exit(1);
    }
}

int getDist(Graph G, int u){
    if(G){
        if(G->source == INF){
            return INF;
        }
        return G->distance[u];
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getDist(): NULL pointer\n");
        exit(1);
    }
}

//finish this shit
void getPath(List L, Graph G, int u){
    if(G){
        if (u == G->source){
            append(L, u);                       // append to the list 
        }   
        else if (G->parent[u] == NIL){
            append(L, NIL);
        } else{
            getPath(L, G, G->parent[u])
            append(L, u);
        }

    } else {
        fprintf(stderr, " Graph ADT; ERROR in getPath(): NULL pointer\n");
        exit(1);
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
        if(G){
        Graph t = G->order;
    	Graph temp = t;
    	while (G->size > 0) {
            temp = t->source;
            deleteFront(G);
        	t = temp;
   	    }
        graph->order = n;
        graph->size = NULL;
        graph->source = NULL;
        graph->neighbor = NULL;
        graph->color = NULL;
        graph->parent = NULL;
        graph->distance = NULL;

    } else {
        fprintf(stderr, " List ADT; ERROR in clear(): NULL pointer\n");
        exit(1);
    }
}

// void addEdge(Graph G, int u, int v);

// void addArc(Graph G, int u, int v);

// void BFS(Graph G, int s);

// /*** Other operations ***/
// void printGraph(FILE* out, Graph G);