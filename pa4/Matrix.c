// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 4                       //
// Matrix ADT                 //
// ========================== //

//Got code checked by TA's in session and used TA Mike's sudo code form google drive to implement some functions
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
Entry newEntry(double val, int col){
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
//TA Sheel helped me with corner case handling and memory leak correction
void freeMatrix(Matrix* pM){
    if (*pM != NULL && pM != NULL) {
        for (int i = 1; i <= (*pM)->size; i++){
            List l = (*pM)->rows[i];
            for (moveFront(l); index(l) >= 0; moveNext(l)){
                    Entry E = get(l);
                    deleteEntry(&E);
                }
            freeList(&l);
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
//Done as per sudo code
//TA Sheel helped me with corner case handling and memory leak correction
int equals(Matrix A, Matrix B){
    if(A != NULL || B != NULL){
        if(size(A) == 0 && size(B) == 0){
                return 1;
        }
        Entry x, y;
        List c, d;
        if(size(A) != size(B)){
            return 0;
        }
        if(A->NNZ != B->NNZ){
            return 0;
        }

        for(int i = 1; i <= size(A); i++) {
            if(length(A->rows[i]) != length(B->rows[i])){
                return 0;
            }
            
            c = A->rows[i];
            d = B->rows[i];
            moveFront(c);
            moveFront(d);
            while((index(c) >= 0 && index(d) >= 0)){
                x = (Entry)get(c);
                y = (Entry)get(d); 
                if(x->value != y->value || x->column != y->column){
                    return 0;
                } else {
                    moveNext(c);
                    moveNext(d);
                }
            }
        }
        return 1;
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in equals(): NULL pointer\n");
        exit(1);
    }
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
//Done as per sudo code
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
//TA Sheel helped me with corner case handling and memory leak correction
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
                e = newEntry(x, j);
                append(l, e);
                M->NNZ++;
            }
        } else {
            moveFront(l);
            while(index(l) >= 0){
                e = (Entry)get(l);
                if(e->column >= j){
                    break;
                }
                moveNext(l);
            }
            if(index(l) == -1){
                if(x != 0){
                    e = newEntry(x, j);
                    append(l, e);
                    M->NNZ++;
                }
            } else {
                if(((Entry)get(l))->column == j){
                    if(x == 0){
                        deleteEntry(&e);
                        delete(l);
                        M->NNZ--;
                    } else {
                        ((Entry)get(l))->value = x;
                    }
                } else {
                    if(x != 0){
                        e = newEntry(x, j);
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
//Done as per sudo code
Matrix copy(Matrix A){
    if(A){
        Matrix copyA = newMatrix(size(A));
        copyA->NNZ = NNZ(A);
        for(int i = 1; i <= size(A); i++){
            List r = A->rows[i];
            for(moveFront(r); index(r) >= 0; moveNext(r)){
                Entry val = get(r);
                append(copyA->rows[i], newEntry(val->value, val->column));
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
//Done as per sudo code
//TA Sheel helped me with corner case handling and memory leak correction
Matrix transpose(Matrix A){
    if(A){
        Matrix T = newMatrix(size(A));
        Entry E;
        int i;
        int col;
        double val;

        T->NNZ = NNZ(A);
        for(i = 1; i <= size(A); i++){
            moveFront(A->rows[i]);
            while(index(A->rows[i]) >= 0){
                E = get(A->rows[i]);
                col = E->column;
                val = E->value;
                append(T->rows[col], newEntry(val, i)); 
                moveNext(A->rows[i]);
            }

        }
        return T;
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in transpose(): NULL pointer\n");
        exit(1);
    }
}

// // sum()
// // OLD SUM: was seg faulting
// // Returns a reference to a new Matrix object representing A+B.
// // pre: size(A)==size(B)
// Matrix sum(Matrix A, Matrix B){
//     if(A != NULL || B != NULL){
//         // printf("Before size");
//         if(size(A) != size(B)){
//             fprintf(stderr, " Matrix ADT; ERROR in sum(): size(A) != size(B)\n");
//             exit(1);
//         }
//         // printf("Before equals");
//         if(equals(A, B)){
//             return scalarMult(2.0, A);
//         }
//         Matrix s_matrix = newMatrix(size(A));
//         for(int i = 1; i <= size(A); i++){
//             int nnz_count = 0;
//             moveFront(A->rows[i]);
//             moveFront(B->rows[i]);
//             while(index(A->rows[i]) >= 0 || index(B->rows[i]) >= 0){
//                 Entry matrix_a = NULL;
//                 Entry matrix_b = NULL;

//                 if(index(A->rows[i]) >= 0){
//                     matrix_a = (Entry)get(A->rows[i]);
//                 } else {
//                     matrix_a = NULL;
//                 }
//                 if(index(B->rows[i]) >= 0){
//                     matrix_b = (Entry)get(B->rows[i]);
//                 } else {
//                     matrix_b = NULL;
//                 }

//                 if(matrix_a->column == matrix_b->column){
//                     if((matrix_a->value + matrix_b->value) != 0){
//                         Entry sum_val = newEntry(matrix_a->value + matrix_b->value, matrix_a->column);
//                         append(s_matrix->rows[i], sum_val);
//                         nnz_count += 1;
//                     }
//                     moveNext(A->rows[i]);
//                     moveNext(B->rows[i]);
//                 }
//                 if((matrix_a->column < matrix_b->column) || matrix_b == NULL){
//                     Entry sum_val = newEntry(matrix_a->value, matrix_a->column);
//                     append((s_matrix->rows)[i], sum_val);
//                     nnz_count++;
//                     moveNext(A->rows[i]);
//                 } else {
//                     Entry sum_val = newEntry(matrix_b->value, matrix_b->column);
//                     append(s_matrix->rows[i], sum_val);
//                     nnz_count++;
//                     moveNext(B->rows[i]);
//                 }

//             }
//         }
//         return s_matrix;
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in sum(): NULL pointer\n");
//         exit(1);
//     }
// }

//new sum mine
//Done as per sudo code
//TA Sheel helped me with corner case handling, memory leak correction, and logic checking
Matrix sum(Matrix A, Matrix B){
    if(A != NULL && B != NULL){
        if(A == B){
            return scalarMult(2.0, A);
        }
        Matrix s_matrix = newMatrix(size(A));
        Entry a, b;
        for(int i = 1; i <= size(A); i++){
            moveFront(A->rows[i]);
            moveFront(B->rows[i]);
            while(index(A->rows[i]) >= 0 && index(B->rows[i]) >= 0){

                if(index(A->rows[i]) >= 0){
                    a = (Entry)get(A->rows[i]);
                } else {
                    a = NULL;
                }
                if(index(B->rows[i]) >= 0){
                    b = (Entry)get(B->rows[i]);
                } else {
                    b = NULL;
                }

                if(a->column == b->column){
                    if((a->value + b->value) != 0){
                        Entry temp = newEntry(a->value + b->value, a->column); 
                        
                        append(s_matrix->rows[i], temp);
                        s_matrix->NNZ++;
                        //changeEntry(s_matrix, i, a->column, a->value + b->value);
                    }
                    moveNext(A->rows[i]);
                    moveNext(B->rows[i]);
                } else if(a->column < b->column){
                    Entry temp = newEntry(a->value, a->column); 
                    append(s_matrix->rows[i], temp);
                    s_matrix->NNZ++;
                    //changeEntry(s_matrix, i, a->column, a->value);
                    moveNext(A->rows[i]);
                } else {
                    Entry temp = newEntry(b->value, b->column); 
                    append(s_matrix->rows[i], temp);
                    s_matrix->NNZ++;
                    moveNext(B->rows[i]);
                }
            }

            while(index(A->rows[i]) >= 0){

                Entry a = (Entry)get(A->rows[i]);
                Entry temp = newEntry(a->value, a->column); 
                append(s_matrix->rows[i], temp);
                s_matrix->NNZ++;
                //changeEntry(s_matrix, i, a->column, a->value);
                moveNext(A->rows[i]);
            }

            while(index(B->rows[i]) >= 0){

                Entry b = (Entry)get(B->rows[i]);
                Entry temp = newEntry(b->value, b->column); 
                append(s_matrix->rows[i], temp);
                s_matrix->NNZ++;
                //changeEntry(s_matrix, i, b->column, b->value);
                moveNext(B->rows[i]);
            }
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
//Done as per sudo code
//TA Sheel helped me with corner case handling and simplification 
Matrix diff(Matrix A, Matrix B){
    if(A != NULL || B != NULL){
        if(A == B){
            return newMatrix(size(A));
        }
        Matrix temp = scalarMult(-1.0, B);
        Matrix fnl = sum(A, temp);

        freeMatrix(&temp);
        return fnl;
        
        // Matrix s_matrix = newMatrix(size(A));

        // for(int i = 1; i <= size(A); i++){
        //    List a_row;
        //    List b_row;
        //    List sum_list;

        //    a_row = A->rows[i];
        //    b_row = B->rows[i];
        //    sum_list = s_matrix->rows[i];

        //    moveFront(a_row);
        //    moveFront(b_row);
        //     while(index(a_row) >= 0 && index(b_row) >= 0){
                
        //         Entry a = (Entry)get(a_row);
        //         Entry b = (Entry)get(b_row);

        //         if(a->column == b->column){  
        //             if((a->value - b->value) != 0){
        //                 Entry temp = newEntry(a->value - b->value, a->column); 
                        
        //                 append(sum_list, temp);
        //                 s_matrix->NNZ++;
        //                 //changeEntry(s_matrix, i, a->column, a->value + b->value);
        //                 moveNext(a_row);
        //                 moveNext(b_row);
        //             } else {
        //                 moveNext(a_row);
        //                 moveNext(b_row);  
        //             }
        //         } else if(a->column < b->column){
        //             Entry temp = newEntry(a->value, a->column); 
        //             append(sum_list, temp);
        //             s_matrix->NNZ++;
        //             //changeEntry(s_matrix, i, a->column, a->value);
        //             moveNext(a_row);
        //         } else {
        //             Entry temp = newEntry(b->value, b->column); 
        //             append(sum_list, temp);
        //             s_matrix->NNZ++;
        //             moveNext(b_row);
        //         }
        //     }

        //     while(index(a_row) >= 0){

        //         Entry a = (Entry)get(a_row);
        //         Entry temp = newEntry(a->value, a->column); 
        //         append(sum_list, temp);
        //         s_matrix->NNZ++;
        //         //changeEntry(s_matrix, i, a->column, a->value);
        //         moveNext(a_row);
        //     }

        //     while(index(b_row) >= 0){

        //         Entry b = (Entry)get(b_row);
        //         Entry temp = newEntry(b->value, b->column); 
        //         append(sum_list, temp);
        //         s_matrix->NNZ++;
        //         //changeEntry(s_matrix, i, b->column, b->value);
        //         moveNext(b_row);
        //     }
        // }
        // return s_matrix;
    } else {
        fprintf(stderr, " Matrix ADT; ERROR in diff(): NULL pointer\n");
        exit(1);
    }
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
//Done as per sudo code
//TA Sheel helped me with corner case handling, memory leak correction, and logical checking
Matrix scalarMult(double x, Matrix A){
    if(A){
        Matrix s_matrix = newMatrix(size(A));
        for(int i = 1; i <= size(A); i++){
            List list_of_ele = A->rows[i];
            moveFront(list_of_ele);
            while(index(list_of_ele) >= 0){
                Entry E = (Entry)get(list_of_ele);
                append((s_matrix->rows)[i], newEntry( x * E->value, E->column));
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

//Done as per sudo code
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
//Done as per sudo code
//TA Sheel helped me with corner case handling, memory leak correction, logical correction, and simplification of logic
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
                            prod->NNZ += 1;
                        }
                    }
                }
            }
        }
        freeMatrix(&trans);
        return prod;
    return NULL;
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
//Done as per sudo code
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


