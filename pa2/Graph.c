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
#include <assert.h>

#include "Graph.h"



//defining structure for Graphobj
typedef struct GraphObj{
    List* neighbor;             //An array of Lists whose i th element contains the neighbor of vertex i.
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
        for(int i = 0; i <= (*pG)->order; i++){
            freeList(&((*pG)->neighbor[i]));
        }
        free((*pG)->neighbor);
        free((*pG)->color);
        free((*pG)->distance);
        free((*pG)->parent);
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
        if(1 <= u && u <= getOrder(G)){
            return G->parent[u];
        } else {
            fprintf(stderr, " Graph ADT; ERROR in getParent(): Input provided is greater than graph order and less than 1.\n");
            exit(1);
        }
        
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getParent(): NULL pointer\n");
        exit(1);
    }
}

int getDist(Graph G, int u){
    if(G){
        if(1 <= u && u <= getOrder(G)){
            return G->distance[u];
        } else {
            fprintf(stderr, " Graph ADT; ERROR in getDist(): Input provided is greater than graph order and less than 1.\n");
            exit(1);
        }
    } else {
        fprintf(stderr, " Graph ADT; ERROR in getDist(): NULL pointer\n");
        exit(1);
    }
}

//TA Sheel helped me
void getPath(List L, Graph G, int u){
    if(G){
        if(getSource(G) == NIL){
            fprintf(stderr, "GraphADT; Error in getPath(): getPath() is being called before BFS() was run");
        }
        if(getSource(G) == u){
            append(L, u);
        } else if(getParent(G, u) == NIL){
            append(L, NIL);
        } else {
            getPath(L, G, getParent(G, u));
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
        G->size = 0;
        G->source= NIL;
        int i = 0;
        while(i <= getOrder(G)){
            G->parent[i] = NIL;
            G->distance[i] = INF;
            G->color[i]= WHITE;
            clear(G->neighbor[i]);
            i++;
        }
    } else {
        fprintf(stderr, " Graph ADT; ERROR in makeNull(): NULL pointer\n");
        exit(1);
    }
}

//TA More helped me with the addEdge function
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

//TA More helped me with the addArc function
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

//Used sudo code provided and got help from TA Sheel
void BFS(Graph G, int s){
    if(G){
        for(int i = 1; i <= getOrder(G); i++){
            G->parent[i] = NIL;
            G->color[i] = WHITE;
            G->distance[i] = INF;
        }
        G->parent[s] = NIL; 
        G->color[s] = GRAY;
        G->distance[s] = 0;
        G->source = s;

        List new_queue = newList();
        append(new_queue, s);
        while(length(new_queue) > 0){

            moveFront(new_queue);
            int v = get(new_queue);
            deleteFront(new_queue);
            if(length(G->neighbor[v]) > 0){
                moveFront(G->neighbor[v]);
            }
            while(index(G->neighbor[v]) != -1){
                int got = get(G->neighbor[v]);
                if(G->color[got] == WHITE){
                    G->color[got] = GRAY;
                    G->distance[got] = G->distance[v] + 1;
                    G->parent[got] = v;
                    append(new_queue, got);
                }
                moveNext(G->neighbor[v]);
            }
            G->color[v] = BLACK;
        }
        clear(new_queue);
        freeList(&new_queue);

    } else {
        fprintf(stderr, " Graph ADT; ERROR in addBFS(): NULL pointer\n");
        exit(1);
    }
}

// /*** Other operations ***/
void printGraph(FILE* out, Graph G){
    if(G){
       for (int i = 1; i <= getOrder(G); i++) 
        {
            fprintf(out, "%d:", i); 
            if (length(G->neighbor[i]) != 0) 
            {
                fprintf(out, " ");
                moveFront(G->neighbor[i]); 
                while (index(G->neighbor[i]) != -1) 
                {
                    fprintf(out, "%d", get(G->neighbor[i])); 
                    moveNext(G->neighbor[i]); 
                    if (index(G->neighbor[i]) != -1)
                    {
                        fprintf(out, " "); 
                    }
                    else 
                    {
                        if (i != getOrder(G)){ 
                            fprintf(out, "\n");
                        }
                    }
                }
            }
            else
            {
                fprintf(out, "\n"); 
            }
        }
        fprintf(out, "\n");
    } else {
        fprintf(stderr, " Graph ADT; ERROR in printGraph(): NULL pointer\n");
        exit(1);
    }
}