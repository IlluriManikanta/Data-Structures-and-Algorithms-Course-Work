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
    Graph G = newGraph(x);

    //Reading inputfile and storing adjacent pair values
    fscanf(in_file, "%d %d\n", &y, &z);
    while(y != 0 || z != 0){
        //adding edge if pair is correct and exists
        addEdge(G, y, z); 
        fscanf(in_file, "%d %d", &y, &z);
    }
 
    //Calling printGraph Function to print Adjacency list representation
    printGraph(out_file, G);
    


    fscanf(in_file, "%d %d", &y, &z);

    //Sourcing & Destination pair Checks
    while(y != 0 || z != 0){
        //Checking if pair is present and if pair is "0,0" dummy pair
        if(y == z){
            fprintf(out_file, "\n");
            fprintf(out_file, "The distance from %d to %d is 0\n", y, z);
            fprintf(out_file, "A shortest %d-%d path is: ", y, z);
            fscanf(in_file, "%d %d\n", &y, &z);
            continue;
        }
        //Calling BFS on graph "Graph"
        BFS(G, y);
        int d = getDist(G, z);
        
        if(d = INF){
            //Printing output in specified format
            fprintf(out_file, "The distance from %d to %d is infinity\n", y, z);
        } else {
            //Printing output in specified format
            fprintf(out_file, "The distance from %d to %d is ", y, z);
            fprintf(out_file, "%d\n", d);
        }
        
        List p = newList();

        getPath(p, G, z);

        if(front(p) == NIL){
            //Printing output in specified format
            fprintf(out_file, "No %d-%d path exists\n", y, z);
        } else {
            //Printing output in specified format
            fprintf(out_file, "A shortest %d-%d path is ", y, z);
            printList(out_file, p);
        }
        freeList(&p);
        fscanf(in_file, "%d %d\n", &y, &z);
    }
    //Freeing Graph and List
        freeGraph(&G);

    //Closing input and output files
    fclose(in_file);
    fclose(out_file);

    return 0;


}
