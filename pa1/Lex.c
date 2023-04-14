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
#include "List.h"

#define Maxlen 100

int main(int argc, char * argv[]){
    int line_cnt = 0;
    FILE *in_file;
    FILE *out_file;
    char num[Maxlen];
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

    // Count the number of lines in the input file
    int line_cnt = 0;
    while( fgets(num, Maxlen, in_file) != NULL )  {
        line_cnt += 1;
    }

    fseek(in_file, buffer_size, SEEK_SET); // To set the file pointer to the start of the file
    
    char** string_array = malloc(sizeof(line_cnt) * sizeof(char*));
    int array_indx = 0;

    while(fgets(num, Maxlen, in_file) != NULL)  {
        string_array[array_indx] = strdup(num); 
        array_indx += 1;
    }

    //creating new list to append compared strings
    List out_list = newList();
    append(out_list, 0);

    //Loop to iterate through string array and cmp
    for(int i = 1; i < line_cnt; i++){
        moveFront(out_list);
        while(index(out_list) >= 0 && strcmp(string_array[i], string_array[get(num)]) > 0){
            moveNext(out_list);
        }
        if(index(out_list) < 0){
            append(out_list, i);
        }else{
            insertBefore(out_list, i);
        }
    }

    //Writing to out file
    while (index(out_list) < length(out_list)) {
        fprintf(out_file, "%s", string_array[get(out_list)]);
        moveNext(out_list);
    }

    //Freeing Memory
    freeList(&out_list);
    for (int i = 0; i < line_cnt + 1; i++) {
        free(string_array[i]);
    }

    free(string_array);
    fclose(in_file);
    fclose(out_file);
    return 0;

    //close inputfile
    //iterate through arraty of strings and use string cmp and order them
    //open outfile and print it to out file
    // close out file 
    //free memory

}



