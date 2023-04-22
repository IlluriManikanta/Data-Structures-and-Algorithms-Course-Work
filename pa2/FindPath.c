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
fscanf(in_file, "%d", &x);
Graph Graph = newGraph(x);

int read_result = fscanf(in_file, "%d %d", &y, &z);
while(read_result == 2){
    if (read_result != 2 || (y == 0 && z == 0)) {
        break;
    }
    addEdge(Graph, y, z);
}

// print adjacency list representation of graph
//fprintf(out, "Adjacency list representation of graph:\n");
printGraph(out_file, Graph);
fprintf(out_file, "\n");
List path = newList();

// process source-destination pairs
for (;;) {
    int read_result = fscanf(in_file, "%d %d", &y, &z);
    if (read_result != 2 || (y == 0 && z == 0)) {
        break;
    }

    //Calling BFS on graph "Graph"
    BFS(Graph, y);
    clear(path);
    getPath(path, Graph, z);
   
    //Printing output in specified format
    fprintf(out_file, "The distance from %d to %d is ", y, z);
    if (getDist(Graph, z) != INF){
        fprintf(out_file, "%d\n", getDist(Graph, z));
        fprintf(out_file, "A shortest %d-%d path is: ", y, z);
        moveNext(path);
        printList(out_file, path);
        
    } else {
        fprintf(out_file, "infinity\n");
        fprintf(out_file, "No %d-%d path exists\n", y, z);
    }
    fprintf(out_file, "\n");
}

//Freeing Graph and List
freeGraph(&Graph);
freeList(&path);

//Closing input and output files
fclose(in_file);
fclose(out_file);

return 0;

}