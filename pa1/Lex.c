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

int strcmp(const char* str1, const char* str2);
char *strdup(const char *string);
size_t strlen(const char *string);
char *strcpy(char *string1, const char *string2);


int main(int argc, char * argv[]){
    int line_cnt = 0;
    FILE *in_file;
    FILE *out_file;
    char num[Maxlen];
    int buffer_size = 512;

    //Checking for correct number of arguments
    if(argc != 3){
        fprintf(stderr, " Lex: ERROR: Unexpected number of arguments\n");
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

    fseek(in_file, buffer_size, SEEK_SET); // To set the file pointer to the start of the file
    
    char** str_array = calloc(line_cnt, sizeof(char*));
    
    int array_indx = 0;
    while(fgets(num, Maxlen, in_file) != NULL)  {
        str_array[array_indx] = malloc(strlen(num) + 1); 
        strcpy(str_array[array_indx], num);
        array_indx += 1;
    }

    //creating new list to append compared strings
    List out_list = newList();
    append(out_list, 0);

    //Loop to iterate through string array and cmp
    for(int i = 1; i < line_cnt; i++){
        moveFront(out_list);
        int cnt = i;
        while(index(out_list) >= 0 && strcmp(str_array[cnt], str_array[get(out_list)]) >= 0){
            moveNext(out_list);
        }
        if(index(out_list) <= 0){
            insertBefore(out_list, cnt);   
        } else {
            append(out_list, cnt);
        }
    }

    //Writing to out file
    while (index(out_list) >= 0) {
        fprintf(out_file, "%s\n", str_array[get(out_list)]);
        moveNext(out_list);
    }

    //Freeing Memory
    freeList(&out_list);
    for (int i = 0; i < line_cnt + 1; i++) {
        free(str_array[i]);
    }

    free(str_array);
    fclose(in_file);
    fclose(out_file);
    return 0;

    //close inputfile
    //iterate through arraty of strings and use string cmp and order them
    //open outfile and print it to out file
    // close out file 
    //free memory

}



