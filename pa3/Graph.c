// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 3                       //
// Implementing Graph ADT     //
// ========================== //

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "Graph.h"

//defining structure for Graphobj
typedef struct GraphObj{
    List* neighbor;             //An array of Lists whose i th element contains the neighbor of vertex i.
    int* color; 
    int* parent;                //An array of ints (or chars, or strings) whose i th element is the color (white, gray, black) of vertex i
    int* finish;                //An array of ints whose i th element is the parent of vertex i.
    int* discover;              //An array of ints whose i th element is the distance from the (most recent) source to vertex i.
    int order;
    int size;
} GraphObj;



/*** Constructors-Destructors ***/
Graph newGraph(int n){
    Graph graph = malloc(sizeof(GraphObj));
    assert(graph != NULL);
    graph->neighbor = malloc(sizeof(List*) * (n + 1));
    graph->color = malloc(sizeof(int*) * (n + 1));
    graph->parent = malloc(sizeof(int*) * (n + 1));
    graph->discover = malloc(sizeof(int*) * (n +1));

    for(int i = 0; i <= n; i++){
        graph->neighbor[i] = newList();
        graph->color[i] = WHITE;
        graph->parent[i] = NIL;
        graph->discover[i] = UNDEF;
    }
    graph->order = n;
    graph->size = 0;
    graph->finish = UNDEF;

    return graph;
}

void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);

int getSize(Graph G);

int getDiscover(Graph G, int u);

void getFinish(Graph G, int u);

/*** Manipulation procedures ***/

void addArc(Graph G, int u, int v);

void addEdge(Graph G, int u, int v);

void DFS(Graph G, List s);

/*** Other operations ***/
Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out , Graph G);