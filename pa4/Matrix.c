// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 4                       //
// Matrix ADT                 //
// ========================== //


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Matrix.h"
#include "List.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj{
    int column;
    double value;
} EntryObj;

typedef struct MatrixObj{
    int size;
    int NNZ;
    List *rows;
}MatrixObj;

// newEntry()
Entry newEntry(int col, double val){
    Entry E = malloc(sizeof(EntryObj));
    assert(E != NULL);
    E->column = col;
    E->value = val;
    return E;
}

// deleteEntry()
void deleteEntry(Entry *pE){
    if(pE != NULL && *pE != NULL){
        free(*pE);
        *pE = NULL;
        pE = NULL;
    }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));
    assert(M != NULL);
    M->size = n;
    M->NNZ = 0;
    M->rows = calloc(n+1, sizeof(List));
    for (int i = 1; i <= n; i++) {
        M->rows[i] = newList();
    }
    return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if (pM != NULL && pM != NULL) {
        Matrix M =pM;
        for (int i = 1; i <= M->size; i++){
            freeList(&(M->rows[i]));
        }
        free(M->rows);
        free(M);
        *pM = NULL;
    }
}

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
    if(M){
        return M->size;
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in size(): NULL pointer\n");
        exit(1);
    }
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if(M){
        return M->NNZ;
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in NNZ(): NULL pointer\n");
        exit(1);
    }

}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if(A != NULL || B != NULL){
        if(A->NNZ != B->NNZ || A->size != B->size){
            return 0;
        } else {
            Entry x, y;
            List c, d;
            int i;
            for(i = 1; i <= A->NNZ; i++){
            //      set "c" and "d" to the rows of "A" and "B"
                c = &(A->rows[i]);
                d = &(B->rows[i]);
                moveFront(c);
                moveFront(d);
                while(index(c) == index(d)){
                    x = (Entry)get(A->rows[i]);
                    y = (Entry)get(B->rows[i]);
                    if(index(c) != index(d)){
                        return false;
                    } else {
                        moveNext(c);
                        moveNext(d);
                    }
                }
            }
            return 1;
        } 
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in equal(): NULL pointer\n");
        exit(1);
    }  
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    if(M){
        M->NNZ = 0;
        for(int i = 0; i < size(M); i++){
            List row = M->rows[i];
            while(length(row) > 0){
                deleteFront(row);
                moveNext(row); // UNSURE
            }
        }
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in makeZero(): NULL pointer\n");
        exit(1);
    }
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if(M){

    } else {
        fprintf(stderr, " Matrix ADT; ERROR in changeEntry(): NULL pointer\n");
        exit(1);
    }
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if(A){
        
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in copy(): NULL pointer\n");
        exit(1);
    }
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    if(A){

    } else {
        fprintf(stderr, " Matrix ADT; ERROR in transpose(): NULL pointer\n");
        exit(1);
    }
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if(A){

    } else {
        fprintf(stderr, " Matrix ADT; ERROR in scalarMult(): NULL pointer\n");
        exit(1);
    }
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if(A != NULL || B != NULL){

    } else {
        fprintf(stderr, " Matrix ADT; ERROR in sum(): NULL pointer\n");
        exit(1);
    }
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if(A != NULL || B != NULL){

    } else {
        fprintf(stderr, " Matrix ADT; ERROR in diff(): NULL pointer\n");
        exit(1);
    }
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if(A != NULL || B != NULL){

    } else {
        fprintf(stderr, " Matrix ADT; ERROR in product(): NULL pointer\n");
        exit(1);
    }
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    if(M){

    } else {
        fprintf(stderr, " Matrix ADT; ERROR in printMatrix(): NULL pointer\n");
        exit(1);
    }
}


