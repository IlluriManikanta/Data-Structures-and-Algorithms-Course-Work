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
    graph->neighbor = malloc(sizeof(List) * (n + 1));
    graph->color = malloc(sizeof(int) * (n + 1));
    graph->parent = malloc(sizeof(int) * (n + 1));
    graph->discover = malloc(sizeof(int) * (n +1));
    graph->finish = malloc(sizeof(int) * (n + 1));

    for(int i = 0; i <= n; i++){
        graph->neighbor[i] = newList();
        graph->color[i] = WHITE;
        graph->parent[i] = NIL;
        graph->discover[i] = UNDEF;
        graph->finish[i] = UNDEF;
    }

    graph->order = n;
    graph->size = 0;

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
        return G->parent[u];
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSize(): NULL pointer\n");
        exit(1);
    }
}

int getDiscover(Graph G, int u){
    if(G){
        return G->discover[u];
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSource(): NULL pointer\n");
        exit(1);
    }
}


int getFinish(Graph G, int u){
    if(G){
        return G->finish[u];
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

int Visit(Graph G, List S, int u, int time){
    // int temp = time;
    time++;
    G->discover[u] = time;
    G->color[u] = GRAY;

    if(length(G->neighbor[u]) > 0){
        moveFront(G->neighbor[u]);
        while(index(G->neighbor[u]) >= 0){
            if(G->color[get(G->neighbor[u])] == WHITE){
                G->parent[get(G->neighbor[u])] = u;
                time = Visit(G, S, get(G->neighbor[u]), time);
            }
            moveNext(G->neighbor[u]);
        }
    }

    G->color[u] = BLACK;
    time++;
    printf("%s%d\n", "G finish u: ", G->finish[u]);
    G->finish[u] = time;
    prepend(S, u);
    return time;
}

void DFS(Graph G, List s){
    if(G){
        if (length(s) != getOrder(G)) {
            printf("Graph Error; ERROR in DFS(): Precondiction not met ");
            exit(1);
        }

        for(int i = 1; i <= getOrder(G); i++) {
            G->parent[i] = NIL;
            G->color[i] = WHITE;
        }

        List new = newList();
 
        int time = 0;
        
        while(length(s) > 0){
            int x = front(s);
            deleteFront(s);
            if(G->color[x] == WHITE){
                time = Visit(G, new, x, time);
            }
        }

        moveFront(new);
        while(index(new) >= 0){
            append(s, get(new));
            moveNext(new);
        }
        freeList(&new);
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSource(): NULL pointer\n");
        exit(1);
    }
}

/*** Other operations ***/
Graph transpose(Graph G){
    if(G){
        Graph g = newGraph(getOrder(G));  
        for(int i = 0; i <= getOrder(G); i++){
            moveFront(G->neighbor[i]);
            while(index(G->neighbor[i]) >= 0){
                addArc(g, get(G->neighbor[i]), i);
                moveNext(G->neighbor[i]);
            }
        }        
    return g;
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
        for(int i = 1; i <= getOrder(G); i++){
            int temp = G->neighbor[i];  
            fprintf(out, "%d:", i);
            if (length(temp) != 0){
                moveFront(temp);
                while(index(temp) >= 0){
                    int neighbor = get(temp);
                    fprintf(out, " %d", neighbor);
                    moveNext(temp);
                }
                fprintf(out, "\n");
            } else {
                fprintf(out, "\n");
            }
            
        }
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getSource(): NULL pointer\n");
        exit(1);
    }
}