// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 2                       //
// Implementing FindPath      //
// ========================== //

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Graph.h"

int main(int argc, char * argv[]){
    FILE *in_file = stdin;
    FILE *out_file = stdout;
    int x;
    int y;
    int z;

    //Checking for correct number of arguments
    if(argc != 3){
        fprintf(stderr, " FindPath: ERROR: Unexpected number of arguments\n");
        fprintf(stderr, "FindPath: Please enter: ./FindPath <input file> <output file>\n");
        exit(1);
    }

    //Opening in and out files 
    in_file = fopen(argv[1], "r");
    out_file = fopen(argv[2], "w");
   
    //Checking if files are NULL or not
    if(in_file == NULL){
        fprintf(stderr, " FindPath: ERROR: Unable to open file to read\n");
        exit(1);
    } 
    if(out_file == NULL){
        fprintf(stderr, " FindPath: ERROR: Unable to open file to write\n");
        exit(1);
    }

    // read graph from input file
fscanf(in, "%d", &n);
Graph G = newGraph(n);
int u, v;
for (;;) {
    int read_result = fscanf(in, "%d %d", &u, &v);
    if (read_result != 2 || (u == 0 && v == 0)) {
        break;
    }
    addEdge(G, u, v);
}

// print adjacency list representation of graph
//fprintf(out, "Adjacency list representation of graph:\n");
printGraph(out, G);
fprintf(out, "\n");
List path = newList();

// process source-destination pairs
for (;;) {
    int read_result = fscanf(in, "%d %d", &u, &v);
    if (read_result != 2 || (u == 0 && v == 0)) {
        break;
    }

    // perform BFS and print results
    BFS(G, u);
    clear(path);
    getPath(path, G, v);
    int distance = getDist(G, v);
    fprintf(out, "The distance from %d to %d is ", u, v);
    if (distance == INF) {
        fprintf(out, "infinity\n");
        fprintf(out, "No %d-%d path exists\n", u, v);
    } else {
        fprintf(out, "%d\n", distance);
        fprintf(out, "A shortest %d-%d path is: ", u, v);
        moveNext(path);
        printList(out, path);
    }
    fprintf(out, "\n");
}

// clean up
freeList(&path);
freeGraph(&G);
fclose(in);
fclose(out);
return 0;

    // fscanf(in_file, "%d", &x);
    // Graph Graph = newGraph(x);
    // for (; fscanf(in_file, "%d %d", &y, &z) == 2; ) {
    //     if (x != 0 && z != 0) {
    //         addEdge(Graph, y, z);
    //     } else {
    //         break;
    //     }
    // }

    // printGraph(out_file, Graph);
    // fprintf(out_file, "\n");
    // List p = newList();
    // for (; fscanf(in_file, "%d %d", &y, &z) == 2; ) {
    //     if (y == 0 && z == 0) {
    //         break;
    //     }
    // }

    // BFS(Graph, y);
    //     clear(p);
    //     getPath(p, Graph, z);
    //     // int distance = ;
    //     fprintf(out_file, "The distance from %d to %d is ", y, z);
    //     if (getDist(Graph, z) != -1) {
    //         fprintf(out_file, "%d\n", getDist(Graph, z));
    //         fprintf(out_file, "A shortest %d-%d path is: ", y, z);
    //         moveNext(p);
    //         printList(out_file, p);

            
    //     } else {
    //         fprintf(out_file, "infinity\n");
    //         fprintf(out_file, "No %d-%d path exists\n", y, z);

            
    //     }
    //     fprintf(out_file, "\n");
        
    
    // freeGraph(&Graph);
    // freeList(&p);

    // fclose(in_file);
    // fclose(out_file);
    // return 0;

}