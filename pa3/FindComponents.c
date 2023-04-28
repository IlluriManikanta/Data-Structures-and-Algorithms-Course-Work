// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 3                       //
// Implementing FindComponents//
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
    int val1 = 0;
    int val2 = 0;
    int count = 0;

    //Checking for correct number of arguments
    if(argc != 3){
        fprintf(stderr, " FindComponents: ERROR: Unexpected number of arguments\n");
        fprintf(stderr, "FindComponents: Please enter: ./FindComponents <input file> <output file>\n");
        exit(1);
    }

    //Opening in and out files 
    in_file = fopen(argv[1], "r");
    out_file = fopen(argv[2], "w");
   
    //Checking if files are NULL or not
    if(in_file == NULL){
        fprintf(stderr, " FindComponents: ERROR: Unable to open file to read\n");
        exit(1);
    } 
    if(out_file == NULL){
        fprintf(stderr, " FindComponents: ERROR: Unable to open file to write\n");
        exit(1);
    }

    //NEED TO FINISH
    





}