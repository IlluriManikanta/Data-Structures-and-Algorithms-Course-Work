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
    //Initiating temp variables to hold values of vertices, and adjacency pairs
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

    //Reading inputfile and storing number of vertices in x
    fscanf(in_file, "%d", &x);
    //Creating new graph with x number of vertices
    Graph Graph = newGraph(x);

    for(;;){
        //Checking if pair is present and if pair is "0,0" dummy pair
        if(fscanf(in_file, "%d %d", &y, &z) != 2 || (y == 0 && z == 0)){
            break;
        }
        //adding edge if pair is correct and exists
        addEdge(Graph, y, z); 
    }
 
    //Calling printGraph Function to print Adjacency list representation
    printGraph(out_file, Graph);
    List p = newList();
    //Sourcing & Destination pair Checks
    for (;;) {
        //Checking if pair is present and if pair is "0,0" dummy pair
        if(fscanf(in_file, "%d %d", &y, &z) != 2 || (y == 0 && z == 0)){
            break;
        }
    }

        //Calling BFS on graph "Graph"
        BFS(Graph, y);
        //Clearing path
        clear(p);
        getPath(p, Graph, z);

        //Printing output in specified format
        //Checking if distance G->distance[u] is != -1
        if(getDist(Graph, z) != -1){
            fprintf(out_file, "\n");
            fprintf(out_file, "The distance from %d to %d is ", y, z);
            fprintf(out_file, "%d\n", getDist(Graph, z));
            fprintf(out_file, "A shortest %d-%d path is: ", y, z);

            moveNext(p);
            printList(out_file, p);

            fprintf(out_file, "\n");
            
        }
        //Checking if distance G->distance[u] is == -1
        if(getDist(Graph, z) == -1){
            fprintf(out_file, "\n");
            fprintf(out_file, "The distance from %d to %d is ", y, z);
            fprintf(out_file, "infinity\n");
            fprintf(out_file, "No %d-%d path exists\n", y, z);
            fprintf(out_file, "\n");
        }

    

    //Freeing Graph and List
    freeGraph(&Graph);
    freeList(&p);

    //Closing input and output files
    fclose(in_file);
    fclose(out_file);

    return 0;

}