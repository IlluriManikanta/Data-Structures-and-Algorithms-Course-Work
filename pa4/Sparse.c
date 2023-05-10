// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 3                       //
// Running Matric.c here      //
// ========================== //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"

int main(int argc, char * argv[]){
    FILE *in_file = stdin;
    FILE *out_file = stdout;
    
    //Checking for correct number of arguments
    if(argc != 3){
        fprintf(stderr, " Sparce: ERROR: Unexpected number of arguments\n");
        fprintf(stderr, "Sparce: Please enter: ./Sparce <input file> <output file>\n");
        exit(1);
    }

    //Opening in and out files 
    in_file = fopen(argv[1], "r");
    out_file = fopen(argv[2], "w");
   
    //Checking if files are NULL or not
    if(in_file == NULL){
        fprintf(stderr, " Sparce: ERROR: Unable to open file to read\n");
        exit(1);
    } 
    if(out_file == NULL){
        fprintf(stderr, " Sparce: ERROR: Unable to open file to write\n");
        exit(1);
    }
    //Vartiables to store changes in the matrix ad size of matrix
    int x = 0; // n
    int y = 0; // a
    int z = 0; // b

    //Reading line 1 in file
    fscanf(in_file, "%d %d %d", &x, &y, &z);
    Matrix matrix_a = newMatrix(x);
    Matrix matrix_b = newMatrix(x);

    //Creating temp vairables for matrix data
    int rows = 0;
    int col = 0;
    double val = 0;

    //Scanning from matrix values from file
    for(int i = 0; i < y; i++){
        fscanf(in_file, "%d %d %lf", &rows, &col, &val);
        changeEntry(matrix_a, rows, col, val);
    }

    //Scanning from matrix values from file
    for(int i = 0; i < z; i++){
        fscanf(in_file, "%d %d %lf", &rows, &col, &val);
        changeEntry(matrix_b, rows, col, val);
    }
    
    //Calling each of the matrix functions on matrix_a and matrix_b

    //Printing as per sudo code
    fprintf(out_file, "A has %d non-zero entries:\n", NNZ(matrix_a)); 
    printMatrix(out_file, matrix_a); 
    fprintf(out_file, "\n"); 
    fprintf(out_file, "B has %d non-zero entries:\n", NNZ(matrix_b)); 
    printMatrix(out_file, matrix_b); 
    fprintf(out_file, "\n"); 

    fprintf(out_file, "(1.5)*A =\n"); 
    Matrix const_prod = scalarMult(1.5, matrix_a); 
    printMatrix(out_file, const_prod); 
    fprintf(out_file, "\n"); 
    makeZero(const_prod); 
    freeMatrix(&const_prod); 

    fprintf(out_file, "A+B =\n"); 
    Matrix add1 = sum(matrix_a, matrix_b); 
    printMatrix(out_file, add1); 
    fprintf(out_file, "\n");
    makeZero(add1); 
    freeMatrix(&add1); 

    fprintf(out_file, "A+A =\n"); 
    Matrix add2 = sum(matrix_a, matrix_a); 
    printMatrix(out_file, add2); 
    fprintf(out_file, "\n"); 
    makeZero(add2); 
    freeMatrix(&add2);

    fprintf(out_file, "B-A =\n"); 
    Matrix sub1 = diff(matrix_b, matrix_a); 
    printMatrix(out_file, sub1); 
    fprintf(out_file, "\n"); 
    makeZero(sub1); 
    freeMatrix(&sub1); 

    fprintf(out_file, "A-A =\n"); 
    Matrix sub2 = diff(matrix_a, matrix_a); 
    printMatrix(out_file, sub2); 
    fprintf(out_file, "\n");
    makeZero(sub2); 
    freeMatrix(&sub2); 

    fprintf(out_file, "Transpose(A) =\n"); 
    Matrix tr_A = transpose(matrix_a);
    printMatrix(out_file, tr_A); 
    fprintf(out_file, "\n"); 
    makeZero(tr_A); 
    freeMatrix(&tr_A);

    fprintf(out_file, "A*B =\n"); 
    Matrix prod1 = product(matrix_a, matrix_b); 
    printMatrix(out_file, prod1); 
    fprintf(out_file, "\n"); 
    makeZero(prod1); 
    freeMatrix(&prod1); 

    fprintf(out_file, "B*B =\n"); 
    Matrix prod2 = product(matrix_b, matrix_b); 
    printMatrix(out_file, prod2); 
    makeZero(prod2); 
    freeMatrix(&prod2); 
    
   
    // makeZero(matrix_a);
    freeMatrix(&matrix_a); 
    // makeZero(matrix_b); 
    freeMatrix(&matrix_b); 
    fclose(in_file); 
    fclose(out_file); 
}


