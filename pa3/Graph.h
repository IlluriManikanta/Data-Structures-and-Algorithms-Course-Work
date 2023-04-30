// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 3                       //
// Header file for Graph.c    //
// ========================== //


#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdio.h>
#include <stdbool.h>
#include "List.h"

#define NIL 0
#define UNDEF -1

#define WHITE 0
#define GRAY 1
#define BLACK 2


//Defining Pointer to Struct 
typedef struct GraphObj* Graph;


/*** Constructors-Destructors ***/
Graph newGraph(int n);

void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

/*** Manipulation procedures ***/

void addArc(Graph G, int u, int v);

void addEdge(Graph G, int u, int v);

void DFS(Graph G, List s);

/*** Other operations ***/
Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out , Graph G);

#endif