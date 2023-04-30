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
    int x = 0;
    int y = 0;
    int z = 0;
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

    //Read the first line
    fscanf(in_file, "%d\n", &count);
    Graph new = newGraph(count);
    fscanf(in_file, "%d%d\n", &x, &y);

    // while(x != 0 && y != 0){
    //     addArc(new, x, y);
    //     fscanf(in_file, "%d %d\n", &x, &y);
    // }

    while(fscanf(in_file, "%d %d\n", &x, &y) == 2){
        addArc(new, x, y);
        addArc(new, y, x);
    }

    //Printing Lable message
    fprintf(out_file, "Adjacency list representation of G:\n");
    printGraph(out_file, new);
    fprintf(out_file, "\n");

    //Creating Lits and graph to transpose
    List temp_list = newList();
    Graph tran;
    tran = transpose(new);
    for(int i = 1; i<= count; i++){
        append(temp_list, i);
    }

    //Calling DFS on graphs using temp_list
    DFS(new, temp_list);
    DFS(tran, temp_list);
    for(int i = 1; i <= count; i++){
        if(getParent(tran, i) == NIL){
            z++;
        }
    }
    fprintf(out_file, "G contains %d strongly connected components:\n", z);

    List *C = malloc(z * sizeof(List*));

    for(int i = 0; i < z; i++){
        C[i] = newList();
    }

    x = z;
    for(moveFront(temp_list); index(temp_list) >= 0; moveNext(temp_list)){
        int u = get(temp_list);
        if(getParent(tran, u) == NIL){
            x--;
        }
        append(C[x], u);
    }

    for(int i = 0; i < z; i++){
        fprintf(out_file, "Component %d: ", i+1);
        printList(out_file, C[i]);
        fprintf(out_file, "\n");
        freeList(&C[i]);
    }

    free(C);
    freeGraph(&new);
    freeGraph(&tran);
    freeList(&temp_list);
    fclose(in_file);
    fclose(out_file);    
}





/*
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
    int x = 0;
    int y = 0;

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

    //Read the first line
    fscanf(in_file, "%d\n", &count);
    Graph new = newGraph(count);
    fscanf(in_file, "%d%d\n", &x, &y);

    while(x != 0 && y != 0){
        addArc(new, x, y);
        fscanf(in_file, "%d %d\n", &x, &y);
    }

    //Printing Lable message
    fprintf(out_file, "Adjacency list representation of G:\n");
    printGraph(out_file, new);
    fprintf(out_file, "\n");

    //Creating list for DFS
    List graph= newList(); 
    int i = 1;
    while(i <= getOrder(new)){
        append(graph, i);
        i++; 
    }

    DFS(new, graph); 
    Graph graphT = transpose(new); 
    DFS(graphT, graph); 
    
    fprintf(out_file, "\n"); 

    count = 0; 
    moveBack(graph); 
    while (index(graph) != -1){
        if (getParent(graphT, get(graph)) == NIL){
            count++; 
        }
        movePrev(graph);
    }
    fprintf(out_file, "G contains %d strongly connected components:\n", count); 
    
    //O0O0O0O0O0O0O0O0O0O00O0O0O00
    int k = 1;
    while(index(graphT) >= 0){
        fprintf(out_file, "Component %d: ", k++);
        List components = newList();

        if(index(graph) < 0) moveBack(graph);
        while(index(graph) >= 0){
            if(getParent(graphT,get(graph)) == NIL){

                prepend(components, get(graph));
                movePrev(graph);
                break;
            }
            prepend(components, get(graph));

            movePrev(graph);
        }
        printList(out_file, components);
        fprintf(out_file, "\n");
        freeList(&components);
        moveNext(graph);
    }
    //oO0O0O0O0O0O0O0O0O0O0O0O0O0O0
    fclose(in_file);
    fclose(out_file);

    // Free Graph
    freeGraph(&graphT);
    freeGraph(&new);

    return(0);


    
}

*/