
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"


int main (int argc, char * argv[]) {
	int buffer_size = 512;
	if (argc != 3) {
		fprintf(stderr, "Number of arguments is invalid.");
		exit(EXIT_FAILURE);
	}
	FILE *infile = fopen(argv[1], "r");           
  	FILE *outfile = fopen(argv[2], "w"); 
  	
  	if (infile == NULL) {         
    		fprintf(stderr, "Cannot open the input file"); 
    	}
    	if (outfile == NULL) {         
    		fprintf(stderr, "Cannot open the output file"); 
    	}
    	int count = 0;
    	char lines[buffer_size];
    	while (fgets(lines, buffer_size, infile) != NULL) {
    		count++;
    	}
    	rewind(infile);
    	char** arraystring = malloc((count) * sizeof(char*));
    	int i = 0;
    	while (i < count) {
    		arraystring[i] = malloc((buffer_size * sizeof(char)));
    		fgets(arraystring[i], buffer_size, infile);
    		i++;
    	}
    
    	List list = newList();
    	append(list, 0);
    	
    	for (int i = 1; i < count; i++) {
    		moveFront(list);
    		int k = i;
    		while (index(list) != -1 && k > 0 && strcmp(arraystring[i], arraystring[get(list)]) > 0) {
    			moveNext(list);
    			k--;
    		}
    		if (index(list) >= 0) {
    			insertBefore(list, i);
    		}	
    		else {
    			append(list, i);
    		}
    	}
    	moveFront(list);
    	
    	while (index(list) < length(list)) {
    		fprintf(outfile, "%s", arraystring[get(list)]);
    		moveNext(list);
    	}
    	
    	freeList(&list);
    	for (int i = 0; i < count; i++) {
    		free(arraystring[i]);
    	}
    	free(arraystring);
    	fclose(infile);
    	fclose(outfile);
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



