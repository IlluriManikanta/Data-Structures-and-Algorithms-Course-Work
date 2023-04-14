
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LINE_LENGTH 1000

int main(int argc, char* argv[]) {
    // Check command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open input file
    FILE* input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error: cannot open input file %s\n", argv[1]);
        exit(1);
    }

    // Count number of lines in input file
    int num_lines = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        num_lines++;
    }
    rewind(input_file);

    // Allocate array of strings
    char** string_array = calloc(num_lines, sizeof(char*));
    if (string_array == NULL) {
        fprintf(stderr, "Error: cannot allocate memory for string array\n");
        exit(1);
    }

    // Read lines into string array
    int i = 0;
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        // Remove newline character from end of line
        line[strcspn(line, "\n")] = '\0';
        // Allocate memory for string and copy it
        string_array[i] = malloc(strlen(line) + 1);
        if (string_array[i] == NULL) {
            fprintf(stderr, "Error: cannot allocate memory for string %d\n", i);
            exit(1);
        }
        strcpy(string_array[i], line);
        i++;
    }

    // Close input file
    fclose(input_file);

    // Create list of indices
    List list = newList();
    append(list, 0);
    for (int j = 1; j < num_lines; j++) {
        int curr_index = j;
        moveBack(list);
        while (index(list) >= 0 && strcmp(string_array[curr_index], string_array[get(list)]) <= 0) {
            movePrev(list);
        }
        if (index(list) >= 0) {
            insertAfter(list, curr_index);
        } else {
            prepend(list, curr_index);
        }
    }

    // Open output file
    FILE* output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error: cannot open output file %s\n", argv[2]);
        exit(1);
    }

    // Print strings in alphabetical order
    moveFront(list);
    while (index(list) >= 0) {
        fprintf(output_file, "%s\n", string_array[get(list)]);
        moveNext(list);
    }

    // Close output file
    fclose(output_file);

    // Free memory
    for (int j = 0; j < num_lines; j++) {
        free(string_array[j]);
    }
    free(string_array);
    freeList(&list);

    return 0;
}
// // ========== Name ========== //
// // Manikantanagasai H. Illuri //
// // milluri@ucsc.edu           //
// // 2023 Spring CSE101         //
// // PA 1                       //
// // Implementing alphabetizat  //
// // -ion method                //
// // ========================== //


// //to test make lex.c
// //./lex in_file out_file 

// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include "List.h"

// #define Maxlen 100

// int strcmp(const char* str1, const char* str2);
// char *strdup(const char *string);
// size_t strlen(const char *string);
// char *strcpy(char *string1, const char *string2);


// int main(int argc, char * argv[]){
//     int line_cnt = 0;
//     FILE *in_file;
//     FILE *out_file;
//     char num[Maxlen];
//     int buffer_size = 512;

//     //Checking for correct number of arguments
//     if(argc != 3){
//         fprintf(stderr, " Lex: ERROR: Unexpected number of arguments");
//         exit(1);
//     }
    
//     //Opening in and out files 
//     in_file = fopen(argv[1], "r");
//     out_file = fopen(argv[2], "w");
   
//     //Checking if files are NULL or not
//     if(in_file == NULL){
//         fprintf(stderr, " Lex: ERROR: Unable to open file to read");
//         exit(1);
//     } 
//     if(out_file == NULL){
//         fprintf(stderr, " Lex: ERROR: Unable to open file to write");
//         exit(1);
//     }

//     // Count the number of lines in the input file
//     while(fgets(num, Maxlen, in_file) != NULL)  {
//         line_cnt += 1;
//     }

//     fseek(in_file, buffer_size, SEEK_SET); // To set the file pointer to the start of the file
    
//     char** str_array = calloc(line_cnt, sizeof(char*));
    
//     int array_indx = 0;
//     while(fgets(num, Maxlen, in_file) != NULL)  {
//         str_array[array_indx] = malloc(strlen(num) + 1); 
//         strcpy(str_array[array_indx], num);
//         array_indx += 1;
//     }

//     //creating new list to append compared strings
//     List out_list = newList();
//     append(out_list, 0);

//     //Loop to iterate through string array and cmp
//     for(int i = 1; i < line_cnt; i++){
//         moveFront(out_list);
//         while(index(out_list) >= 0 && strcmp(str_array[i], str_array[get(out_list)]) >= 0){
//             moveNext(out_list);
//         }
//         if(index(out_list) <= 0){
//             insertBefore(out_list, i);   
//         } else {
//             append(out_list, i);
//         }
//     }

//     //Writing to out file
//     while (index(out_list) >= 0) {
//         fprintf(out_file, "%s\n", str_array[get(out_list)]);
//         moveNext(out_list);
//     }

//     //Freeing Memory
//     freeList(&out_list);
//     for (int i = 0; i < line_cnt + 1; i++) {
//         free(str_array[i]);
//     }

//     free(str_array);
//     fclose(in_file);
//     fclose(out_file);
//     return 0;

//     //close inputfile
//     //iterate through arraty of strings and use string cmp and order them
//     //open outfile and print it to out file
//     // close out file 
//     //free memory

// }



