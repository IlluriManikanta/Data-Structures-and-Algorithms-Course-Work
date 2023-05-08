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
#include <assert.h>

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
    if (*pM != NULL && pM != NULL) {
        for (int i = 1; i <= (*pM)->size; i++){
            freeList(&((*pM)->rows[i]));
        }
        free((*pM)->rows);
        free((*pM));
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
            List c, d;
            int i;
            for(i = 1; i <= A->NNZ; i++){
            //      set "c" and "d" to the rows of "A" and "B"
                c = A->rows[i];
                d = B->rows[i];
                moveFront(c);
                moveFront(d);
                while(index(c) == index(d)){
                    Entry x = (Entry)get(A->rows[i]);
                    Entry y = (Entry)get(B->rows[i]);
                    if(x->column != y->column || x->value != y->value){
                        return 0;
                    }
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
        for(int i = 1; i <= size(M); i++){
            List row = M->rows[i];
            for(moveFront(row); index(row) >= 0; moveNext(row)){
                Entry val = (Entry)get(row);
                deleteEntry(&val);
            }
            clear(row);
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
        if(i < 1 || i > size(M) || j < 1 || j > size(M)){
            fprintf(stderr, " Matrix ADT; ERROR in changeEntry(): index out of range\n");
            exit(1);
        }
        List l = M->rows[i];
        Entry e = NULL;

        if(length(l) == 0){
            if(x != 0){
                e = newEntry(j, x);
                append(l, e);
                M->NNZ++;
            }
        } else {
            moveFront(l);
            while(index(l) != -1 && ((Entry)get(l))->column < j){
                moveNext(l);
            }
            if(index(l) == -1){
                if(x != 0){
                    e = newEntry(j, x);
                    append(l, e);
                    M->NNZ++;
                }
            } else {
                if(((Entry)get(l))->column == j){
                    if(x == 0){
                        delete(l);
                        M->NNZ--;
                    } else {
                        ((Entry)get(l))->value = x;
                    }
                } else {
                    if(x != 0){
                        e = newEntry(j, x);
                        insertBefore(l, e);
                        M->NNZ++;
                    }
                }
            }
        }
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in changeEntry(): NULL pointer\n");
        exit(1);
    }
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
//NEED TO CHECK
Matrix copy(Matrix A){
    if(A){
        Matrix copyA = newMatrix(size(A));
        copyA->NNZ = NNZ(A);
        for(int i = 0; i <= size(A); i++){
            List row = A->rows[i];
            for(moveFront(row); index(row) >= 0; moveNext(row)){
                Entry E = get(row);
                append(copyA->rows[i], newEntry(E->value, E->column));
            }
        }
        return copyA;
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
        Matrix T = newMatrix(size(A));
        T->NNZ = NNZ(A);
        for(int i = 0; i <= size(A); i++){
            List row = A->rows[i];
            moveFront(row);
            while(index(row) >= 0){
                Entry E = get(row);
                append(T->rows[E->column], newEntry(E->value, i));
                moveNext(row);
            }
        }
        return T;
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in transpose(): NULL pointer\n");
        exit(1);
    }
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if(A){
        Matrix s_matrix = newMatrix(size(A));
        for(int i = 1; i <= size(A); i++){
            List list_of_ele = A->rows[i];
            moveFront(list_of_ele);
            while(index(list_of_ele) >= 0){
                Entry E = (Entry)get(list_of_ele);
                append((s_matrix->rows)[i], newEntry(x * E->value, E->column));
                s_matrix->NNZ++;
                moveNext(list_of_ele);
            }
        }
        return s_matrix;
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
        if(size(A) != size(B)){
            fprintf(stderr, " Matrix ADT; ERROR in sum(): size(A) != size(B)\n");
            exit(1);
        }
        if(equals(A, B)){
            return scalarMult(2.0, A);
        }
        Matrix s_matrix = newMatrix(size(A));
        for(int i = 1; i <= size(A); i++){
            int count = 0;
            moveFront(A->rows[i]);
            moveFront(B->rows[i]);
            while(index(A->rows[i]) >= 0 || index(B->rows[i]) >= 0){
                Entry matrix_a = (index(A->rows[i]) >= 0) ? (Entry)get(A->rows[i]) : NULL;
                Entry matrix_b = (index(B->rows[i]) >= 0) ? (Entry)get(B->rows[i]) : NULL;
                // if(index(A->rows[i]) >= 0){
                //     matrix_a = (Entry)get(A->rows[i]);
                // } else {
                //     matrix_a = NULL;
                // }
                // if(index(B->rows[i]) >= 0){
                //     matrix_b = (Entry)get(B->rows[i]);
                // } else {
                //     matrix_b = NULL;
                // }
                if(matrix_a && matrix_b && matrix_a->column == matrix_b->column){
                    double val = matrix_a->value + matrix_b->value;
                    if(val != 0){
                        Entry sum_val = newEntry(val, matrix_a->column);
                        append((s_matrix->rows)[i], sum_val);
                        count++;
                    }
                    moveNext(A->rows[i]);
                    moveNext(B->rows[i]);
                } else if((matrix_a && matrix_a->column < matrix_b->column) || matrix_b == NULL){
                    Entry sum_val = newEntry(matrix_a->value, matrix_a->column);
                    append((s_matrix->rows)[i], sum_val);
                    count++;
                    moveNext(A->rows[i]);
                } else {
                    Entry sum_val = newEntry(matrix_b->value, matrix_b->column);
                    append(s_matrix->rows[i], sum_val);
                    count++;
                    moveNext(B->rows[i]);
                }

            }
            s_matrix->NNZ += count;
        }
        return s_matrix;
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
        if(size(A) != size(B)){
            fprintf(stderr, " Matrix ADT; ERROR in sum(): size(A) != size(B)\n");
            exit(1);
        }
        if(equals(A, B)){
            return newMatrix(size(A));
        }
        return sum(A, scalarMult(-1.0, B));
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in diff(): NULL pointer\n");
        exit(1);
    }
}

double vectorDot(List P, List Q){
    double sum = 0;
    moveFront(P);
    moveFront(Q);
    while (index(P) >= 0 && index(Q) >= 0){
        Entry entry_p = (Entry)get(P);
        Entry entry_q = (Entry)get(Q);
        if (entry_p->column == entry_q->column){
            sum += (entry_p->value * entry_q->value);
            moveNext(P);
            moveNext(Q);
        } else if (entry_p->column < entry_q->column){
            moveNext(P);
        } else {
            moveNext(Q);
        }    
    }
    return sum;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if(A != NULL || B != NULL){
        Matrix trans = transpose(B);
        Matrix prod = newMatrix(size(A));
        for(int i = 1; i <= size(prod); i++){
            if(length(A->rows[i]) != 0){
                for(int j = 1; j <= size(prod); j++){
                    if(length(trans->rows[j]) != 0){
                        double val = vectorDot(A->rows[i], trans->rows[j]);
                        if(val != 0){
                            Entry product_val = newEntry(val, j);
                            append(prod->rows[i], product_val);
                            prod->NNZ += j;
                        }
                    }
                }
            }
        }
        freeMatrix(&trans);
        return prod;
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
        for (int i = 1; i <= size(M); i++){
            if (length(M->rows[i]) != 0){
                fprintf(out, "%i:", i);
                for (moveFront((M->rows)[i]); index((M->rows)[i]) >= 0; moveNext((M->rows)[i])){
                    Entry E = (Entry)get((M->rows)[i]);
                    fprintf(out, " (%i, %.1lf)", E->column, E->value);
                }
                fprintf(out, "\n");
            }
        }
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in printMatrix(): NULL pointer\n");
        exit(1);
    }
}


