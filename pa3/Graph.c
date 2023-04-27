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
//DONE
typedef struct GraphObj{
    List* neighbor;             
    int* color; 
    int* parent;                
    int* finish;                
    int* discover;              
    int order;
    int size;
} GraphObj;



/*** Constructors-Destructors ***/
//NEED TO TEST
Graph newGraph(int n){
    Graph graph = malloc(sizeof(GraphObj));
    assert(graph != NULL);
    graph->neighbor = malloc(sizeof(List*) * (n + 1));
    graph->color = malloc(sizeof(int*) * (n + 1));
    graph->parent = malloc(sizeof(int*) * (n + 1));
    graph->discover = malloc(sizeof(int*) * (n +1));
    graph->finish = malloc(sizeof(int*) * (n + 1));

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

//NEED TO TEST
void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        for(int i = 0; i <= (*pG)->order; i++){
            freeList(&((*pG)->neighbor[i]));
        }
        free((*pG)->neighbor);
        free((*pG)->color);
        free((*pG)->discover);
        free((*pG)->parent);
        free((*pG)->finish);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
//DONE
int getOrder(Graph G){
    if(G){
        return G->order;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getOrder(): NULL pointer\n");
        exit(1);
    }
}

//DONE
int getSize(Graph G){
    if(G){
        return G->size;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSize(): NULL pointer\n");
        exit(1);
    }
}

//NEED TO FINISH
int getParent(Graph G, int u){
    if(G){
        return G->parent;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSize(): NULL pointer\n");
        exit(1);
    }
}

//
int getDiscover(Graph G, int u){
    if(G){
        return G->discover;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSource(): NULL pointer\n");
        exit(1);
    }
}

//NEED TO FINISH
void getFinish(Graph G, int u){
    if(G){
        return G->finish;
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSource(): NULL pointer\n");
        exit(1);
    }
}

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v){
    if(G){
        if (v > getOrder(G) || u > getOrder(G)){
            fprintf(stderr, " Graph Error; ERROR in addEdge(): Inputs provided are greater than Graph Order\n");
            exit(1);
        }
        if (v < 1 || u < 1){
            fprintf(stderr, " Graph Error; ERROR in addEdge(): Inputs provided are less than 1\n");
            exit(1);
        }
        addArc(G, u, v);
        G->size--;

        addArc(G, v, u);
    } else {
        fprintf(stderr, " Graph ADT; ERROR in addEdge(): NULL pointer\n");
        exit(1);
    }
}

void addArc(Graph G, int u, int v){
    if(G){
        if (v > getOrder(G) || u > getOrder(G)){
            fprintf(stderr, " Graph Error; ERROR in addEdge(): Inputs provided are greater than Graph Order\n");
            exit(1);
        }
        if (v < 1 || u < 1){
            fprintf(stderr, " Graph Error; ERROR in addEdge(): Inputs provided are less than 1\n");
            exit(1);
        }
        if (length(G->neighbor[u]) == 0){
            append(G->neighbor[u], v);
            G->size++;
        } else {
            List X = G->neighbor[u];
            moveFront(X);
            int i = 1;
            while(i <= length(X)){
                if (get(X) > v){
                    insertBefore(X, v);
                    G->size++;
                    break;
                } else{
                    moveNext(X);
                    if (index(X) == -1){
                        append(X, v);
                        G->size++;
                        break;
                    }
                }
                i++;
            }
        } 
    } else {
        fprintf(stderr, " Graph ADT; ERROR in addArc(): NULL pointer\n");
        exit(1);
    }
}

void DFS(Graph G, List s){
    if(G){
        if (length(s) != getOrder(G)) {
            printf("Graph Error; ERROR in DFS(): Precondiction not met ");
            exit(1);
        }

        for(int i = 1; i <= G->neighbor; i++) {
            G->discover[i] = UNDEF;
            G->finish[i] = UNDEF;
            G->parent[i] = NIL;
            G->color[i] = 0;
        }

        int time = 0;
        for(moveFront(s); index(s) >= 0; moveNext(s)) {
            int temp = get(s);
            if(G->color[temp] == WHITE){
                G->discover[temp]= time++;
                G->color[temp] = GRAY;
                List G_neighbor_Fs = G->neighbor[front(s)];
                moveFront(G_neighbor_Fs);
                while(index(G_neighbor_Fs >= 0)){
                    if(G->color[get(G_neighbor_Fs)] == WHITE){
                        G_neighbor_Fs = front(s);
// call visit

                    }
                }
            }
        }
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSource(): NULL pointer\n");
        exit(1);
    }
}

/*** Other operations ***/
Graph transpose(Graph G){
    if(G){
        

    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSource(): NULL pointer\n");
        exit(1);
    }
}

Graph copyGraph(Graph G){
    if(G){


    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSource(): NULL pointer\n");
        exit(1);
    }
}

void printGraph(FILE* out , Graph G){
    if(G){


    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSource(): NULL pointer\n");
        exit(1);
    }
}