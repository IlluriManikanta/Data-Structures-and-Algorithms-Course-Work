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
#include "List.h"

#define Maxlen 100

int main(int argc, char * argv[]){
    int line_cnt = 0;
    FILE *in_file;
    FILE *out_file;
    char n[Maxlen];
    int buffer_size = 512;

    //Checking for correct number of arguments
    if(argc != 2){
        fprintf(stderr, " Lex: ERROR: Unexpected number of arguments");
        exit(1);
    }
    
    //Opening in and out files 
    in_file = fopen(argv[1], "r");
    out_file = fopen(argv[2], "w");
   
    //Checking if files are NULL or not
    if(in_file == NULL){
        fprintf(stderr, " Lex: ERROR: Unable to open file to read");
        exit(1);
    } 
    if(out_file == NULL){
        fprintf(stderr, " Lex: ERROR: Unable to open file to write");
        exit(1);
    }

    //Counting lines in Inputfile
    while(fgets(n, Maxlen, in_file) != NULL){
        line_cnt += 1;
    }

    //Reading lines from infile into array of strings
    moveFront(in_file);
    char** list_of_strings = (char**)malloc(sizeof(line_cnt)); //allocating memeory for list of strings
    int list_of_strings_index = 0;

    while(fgets(n, Maxlen, in_file) != NULL){
      list_of_strings[list_of_strings_index] = strdup(n); 
      list_of_strings_index++;
   }




}

