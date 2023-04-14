// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 1                       //
// Implementing alphabetizat  //
// -ion method                //
// ========================== //


//to test make lex.c
//./lex in_file out_file 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "List.h"

#define Maxlen 1000

int main(int argc, char * argv[]){
    int line_cnt = 0;
    FILE *in_file;
    FILE *out_file;
    char num[Maxlen];

    //Checking for correct number of arguments
    if(argc != 3){
        fprintf(stderr, " Lex: ERROR: Unexpected number of arguments\n");
        fprintf(stderr, "Lex: Please enter: ./Lex <input file> <output file>\n");
        exit(1);
    }
    
    //Opening in and out files 
    in_file = fopen(argv[1], "r");
    out_file = fopen(argv[2], "w");
   
    //Checking if files are NULL or not
    if(in_file == NULL){
        fprintf(stderr, " Lex: ERROR: Unable to open file to read\n");
        exit(1);
    } 
    if(out_file == NULL){
        fprintf(stderr, " Lex: ERROR: Unable to open file to write\n");
        exit(1);
    }

    // Count the number of lines in the input file
    while(fgets(num, Maxlen, in_file) != NULL)  {
        line_cnt += 1;
    }
    if(line_cnt < 0){
        fprintf(stderr, " Lex: ERROR: Inputfile is Empty\n");
        exit(1);
    }

    // Writing strings to array of strings using 2D array
    rewind(in_file); // To set the file pointer to the start of the file
    char str_array[line_cnt][Maxlen]; // Using a 2D array for array of strings. 
    int array_indx = 0;
    while(fgets(num, Maxlen, in_file) != NULL){
        strcat(num, "\0");
        strcpy(str_array[array_indx], num);
        array_indx += 1;
    }

    //Creating new list to append compared strings using nexted for loop and method mentioned in class
    List out_list = newList();
    prepend(out_list, 0);

    //Loop to iterate through string array and cmp
    for(int i = 1; i < line_cnt; i++){
        
    // TA Arka helped me with this section
        for(moveFront(out_list); index(out_list) >= 0; moveNext(out_list)){
            if(strcmp(&str_array[i][0], &str_array[get(out_list)][0]) < 0){
                insertBefore(out_list, i);
                break;
            }
        }
        if(index(out_list) < 0){
            append(out_list, i);
        } 

    }
        
    //Writing to out file
    for(moveFront(out_list); index(out_list) >= 0; moveNext(out_list)) {
        fprintf(out_file, "%s\n", str_array[get(out_list)]);
    }

    //Freeing Memory
    freeList(&out_list);
    fclose(in_file);
    fclose(out_file);
    return 0;

}



