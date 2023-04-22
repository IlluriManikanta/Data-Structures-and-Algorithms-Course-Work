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

    fscanf(in_file, "%d", &x);
    Graph Graph = newGraph(x);
    while (fscanf(in_file, "%d %d", &y, &z) == 2) {
        if (x != 0 && z != 0) {
            addEdge(Graph, y, z);
        } else {
            break;  
        }
        
    }

    printGraph(out_file, Graph);
    fprintf(out_file, "\n");
    List path = newList();

    while (fscanf(in_file, "%d %d", &y, &z) == 2) {
        if (y == 0 && z == 0) {
            break;
        }

    BFS(Graph, y);
        clear(path);
        getPath(path, Graph, z);
        // int distance = ;
        fprintf(out_file, "The distance from %d to %d is ", y, z);
        if (getDist(Graph, z) == INF) {
            fprintf(out_file, "infinity\n");
            fprintf(out_file, "No %d-%d path exists\n", y, z);
        } else {
            fprintf(out_file, "%d\n", getDist(Graph, z));
            fprintf(out_file, "A shortest %d-%d path is: ", y, z);
            moveNext(path);
            printList(out_file, path);
        }
        fprintf(out_file, "\n");
    }
    freeGraph(&Graph);
    freeList(&path);

    fclose(in_file);
    fclose(out_file);
    return 0;


}