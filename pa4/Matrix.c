// // ========== Name ========== //
// // Manikantanagasai H. Illuri //
// // milluri@ucsc.edu           //
// // 2023 Spring CSE101         //
// // PA 4                       //
// // Matrix ADT                 //
// // ========================== //


// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <assert.h>

// #include "Matrix.h"
// #include "List.h"

// typedef struct EntryObj* Entry;

// typedef struct EntryObj{
//     int column;
//     double value;
// } EntryObj;

// typedef struct MatrixObj{
//     int size;
//     int NNZ;
//     List *rows;
// }MatrixObj;

// // newEntry()
// Entry newEntry(int col, double val){
//     Entry E = malloc(sizeof(EntryObj));
//     assert(E != NULL);
//     E->column = col;
//     E->value = val;
//     return E;
// }

// // deleteEntry()
// void deleteEntry(Entry *pE){
//     if(pE != NULL && *pE != NULL){
//         free(*pE);
//         *pE = NULL;
//     }
// }

// // newMatrix()
// // Returns a reference to a new nXn Matrix object in the zero state.
// Matrix newMatrix(int n){
//     Matrix M = malloc(sizeof(MatrixObj));
//     assert(M != NULL);
//     M->size = n;
//     M->NNZ = 0;
//     M->rows = calloc(n+1, sizeof(List));
//     for (int i = 1; i <= n; i++) {
//         M->rows[i] = newList();
//     }
//     return M;
// }

// // freeMatrix()
// // Frees heap memory associated with *pM, sets *pM to NULL.
// void freeMatrix(Matrix* pM){
//     if (*pM != NULL && pM != NULL) {
//         for (int i = 1; i <= (*pM)->size; i++){
//             freeList(&((*pM)->rows[i]));
//         }
//         free((*pM)->rows);
//         free((*pM));
//         *pM = NULL;
//     }
// }

// // Access functions
// // size()
// // Return the size of square Matrix M.
// int size(Matrix M){
//     if(M){
//         return M->size;
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in size(): NULL pointer\n");
//         exit(1);
//     }
// }

// // NNZ()
// // Return the number of non-zero elements in M.
// int NNZ(Matrix M){
//     if(M){
//         return M->NNZ;
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in NNZ(): NULL pointer\n");
//         exit(1);
//     }

// }

// // equals()
// // Return true (1) if matrices A and B are equal, false (0) otherwise.
// int equals(Matrix A, Matrix B){
//     if(A != NULL || B != NULL){
//         if(A->NNZ != B->NNZ || A->size != B->size){
//             return 0;
//         } else {
//             List c, d;
//             int i;
//             for(i = 1; i <= A->NNZ; i++){
//             //      set "c" and "d" to the rows of "A" and "B"
//                 c = A->rows[i];
//                 d = B->rows[i];
//                 moveFront(c);
//                 moveFront(d);
//                 while(index(c) == index(d)){
//                     Entry x = (Entry)get(A->rows[i]);
//                     Entry y = (Entry)get(B->rows[i]);
//                     if(x->column != y->column || x->value != y->value){
//                         return 0;
//                     }
//                     if(index(c) != index(d)){
//                         return false;
//                     } else {
//                         moveNext(c);
//                         moveNext(d);
//                     }
//                 }
//             }
//             return 1;
//         } 
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in equal(): NULL pointer\n");
//         exit(1);
//     }  
// }

// // Manipulation procedures
// // makeZero()
// // Re-sets M to the zero Matrix state.
// void makeZero(Matrix M){
//     if(M){
//         M->NNZ = 0;
//         for(int i = 1; i <= size(M); i++){
//             List row = M->rows[i];
//             for(moveFront(row); index(row) >= 0; moveNext(row)){
//                 Entry val = (Entry)get(row);
//                 deleteEntry(&val);
//             }
//             clear(row);
//         }
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in makeZero(): NULL pointer\n");
//         exit(1);
//     }
// }

// // changeEntry()
// // Changes the ith row, jth column of M to the value x.
// // Pre: 1<=i<=size(M), 1<=j<=size(M)
// void changeEntry(Matrix M, int i, int j, double x){
//     if(M){
//         if(i < 1 || i > size(M) || j < 1 || j > size(M)){
//             fprintf(stderr, " Matrix ADT; ERROR in changeEntry(): index out of range\n");
//             exit(1);
//         }
//         List l = M->rows[i];
//         Entry e = NULL;

//         if(length(l) == 0){
//             if(x != 0){
//                 e = newEntry(j, x);
//                 append(l, e);
//                 M->NNZ++;
//             }
//         } else {
//             moveFront(l);
//             while(index(l) != -1 && ((Entry)get(l))->column < j){
//                 moveNext(l);
//             }
//             if(index(l) == -1){
//                 if(x != 0){
//                     e = newEntry(j, x);
//                     append(l, e);
//                     M->NNZ++;
//                 }
//             } else {
//                 if(((Entry)get(l))->column == j){
//                     if(x == 0){
//                         delete(l);
//                         M->NNZ--;
//                     } else {
//                         ((Entry)get(l))->value = x;
//                     }
//                 } else {
//                     if(x != 0){
//                         e = newEntry(j, x);
//                         insertBefore(l, e);
//                         M->NNZ++;
//                     }
//                 }
//             }
//         }
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in changeEntry(): NULL pointer\n");
//         exit(1);
//     }
// }

// // Matrix Arithmetic operations
// // copy()
// // Returns a reference to a new Matrix object having the same entries as A.
// //NEED TO CHECK
// Matrix copy(Matrix A){
//     if(A){
//         Matrix copyA = newMatrix(size(A));
//         copyA->NNZ = NNZ(A);
//         for(int i = 1; i <= size(A); i++){
//             List r = A->rows[i];
//             for(moveFront(r); index(r) >= 0; moveNext(r)){
//                 Entry val = get(r);
//                 append(copyA->rows[i], newEntry(val->column, val->value));
//             }
//         }
//         return copyA;
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in copy(): NULL pointer\n");
//         exit(1);
//     }
// }

// // transpose()
// // Returns a reference to a new Matrix object representing the transpose
// // of A.
// Matrix transpose(Matrix A){
//     if(A){
//         Matrix T = newMatrix(size(A));
//         T->NNZ = NNZ(A);
//         for(int i = 1; i <= size(A); i++){
//             List row = A->rows[i];
//             moveFront(row);
//             while(index(row) >= 0){
//                 Entry E = get(row);
//                 append(T->rows[E->column], newEntry(E->value, i));
//                 moveNext(row);
//             }
//         }
//         return T;
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in transpose(): NULL pointer\n");
//         exit(1);
//     }
// }

// // scalarMult()
// // Returns a reference to a new Matrix object representing xA.
// Matrix scalarMult(double x, Matrix A){
//     if(A){
//         Matrix s_matrix = newMatrix(size(A));
//         for(int i = 1; i <= size(A); i++){
//             List list_of_ele = A->rows[i];
//             moveFront(list_of_ele);
//             while(index(list_of_ele) >= 0){
//                 Entry E = (Entry)get(list_of_ele);
//                 append((s_matrix->rows)[i], newEntry(x * E->value, E->column));
//                 s_matrix->NNZ++;
//                 moveNext(list_of_ele);
//             }
//         }
//         return s_matrix;
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in scalarMult(): NULL pointer\n");
//         exit(1);
//     }
// }

// // sum()
// // Returns a reference to a new Matrix object representing A+B.
// // pre: size(A)==size(B)
// Matrix sum(Matrix A, Matrix B){
//     if(A != NULL || B != NULL){
//         if(size(A) != size(B)){
//             fprintf(stderr, " Matrix ADT; ERROR in sum(): size(A) != size(B)\n");
//             exit(1);
//         }
//         if(equals(A, B)){
//             return scalarMult(2.0, A);
//         }
//         Matrix s_matrix = newMatrix(size(A));
//         for(int i = 1; i <= size(A); i++){
//             int count = 0;
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

//                 if(matrix_a && matrix_b && (matrix_a->column == matrix_b->column)){
//                     if(matrix_a->value + matrix_b->value != 0){
//                         Entry sum_val = newEntry(matrix_a->value + matrix_b->value, matrix_a->column);
//                         append(s_matrix->rows[i], sum_val);
//                         count++;
//                     }
//                     moveNext(A->rows[i]);
//                     moveNext(B->rows[i]);
//                 } else if((matrix_a && (matrix_a->column < matrix_b->column)) || matrix_b == NULL){
//                     Entry sum_val = newEntry(matrix_a->value, matrix_a->column);
//                     append((s_matrix->rows)[i], sum_val);
//                     count++;
//                     moveNext(A->rows[i]);
//                 } else {
//                     Entry sum_val = newEntry(matrix_b->value, matrix_b->column);
//                     append(s_matrix->rows[i], sum_val);
//                     count++;
//                     moveNext(B->rows[i]);
//                 }

//             }
//             s_matrix->NNZ += count;
//         }
//         return s_matrix;
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in sum(): NULL pointer\n");
//         exit(1);
//     }
// }

// // diff()
// // Returns a reference to a new Matrix object representing A-B.
// // pre: size(A)==size(B)
// Matrix diff(Matrix A, Matrix B){
//     if(A != NULL || B != NULL){
//         if(size(A) != size(B)){
//             fprintf(stderr, " Matrix ADT; ERROR in sum(): size(A) != size(B)\n");
//             exit(1);
//         }
//         if(equals(A, B)){
//             return newMatrix(size(A));
//         }
//         return sum(A, scalarMult(-1.0, B));
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in diff(): NULL pointer\n");
//         exit(1);
//     }
// }

// double vectorDot(List P, List Q){
//     double sum = 0;
//     moveFront(P);
//     moveFront(Q);
//     while (index(P) >= 0 && index(Q) >= 0){
//         Entry entry_p = (Entry)get(P);
//         Entry entry_q = (Entry)get(Q);
//         if (entry_p->column == entry_q->column){
//             sum += (entry_p->value * entry_q->value);
//             moveNext(P);
//             moveNext(Q);
//         } else if (entry_p->column < entry_q->column){
//             moveNext(P);
//         } else {
//             moveNext(Q);
//         }    
//     }
//     return sum;
// }

// // product()
// // Returns a reference to a new Matrix object representing AB
// // pre: size(A)==size(B)
// Matrix product(Matrix A, Matrix B){
//     if(A != NULL || B != NULL){
//         Matrix trans = transpose(B);
//         Matrix prod = newMatrix(size(A));
//         for(int i = 1; i <= size(prod); i++){
//             if(length(A->rows[i]) != 0){
//                 for(int j = 1; j <= size(prod); j++){
//                     if(length(trans->rows[j]) != 0){
//                         double val = vectorDot(A->rows[i], trans->rows[j]);
//                         if(val != 0){
//                             Entry product_val = newEntry(val, j);
//                             append(prod->rows[i], product_val);
//                             prod->NNZ += j;
//                         }
//                     }
//                 }
//             }
//         }
//         freeMatrix(&trans);
//         return prod;
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in product(): NULL pointer\n");
//         exit(1);
//     }
// }

// // printMatrix()
// // Prints a string representation of Matrix M to filestream out. Zero rows
// // are not printed. Each non-zero row is represented as one line consisting
// // of the row number, followed by a colon, a space, then a space separated
// // list of pairs "(col, val)" giving the column numbers and non-zero values
// // in that row. The double val will be rounded to 1 decimal point.
// void printMatrix(FILE* out, Matrix M){
//     if(M){
//         for (int i = 1; i <= size(M); i++){
//             if (length(M->rows[i]) != 0){
//                 fprintf(out, "%i:", i);
//                 for (moveFront((M->rows)[i]); index((M->rows)[i]) >= 0; moveNext((M->rows)[i])){
//                     Entry E = (Entry)get((M->rows)[i]);
//                     fprintf(out, " (%i, %.1lf)", E->column, E->value);
//                 }
//                 fprintf(out, "\n");
//             }
//         }
//     } else {
//         fprintf(stderr, " Matrix ADT; ERROR in printMatrix(): NULL pointer\n");
//         exit(1);
//     }
// }



#include "List.h"
#include "Matrix.h"
#include "stdlib.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj{
    double data;
    int index;
} EntryObj;

// Create a entry of data d, and index i.
Entry newEntry(double d, int i){
    Entry E = malloc(sizeof(EntryObj));
    E->data = d;
    E->index = i;
    return E;
}

void freeEntry(Entry* pE){
    if(pE != NULL && *pE != NULL){
        free(*pE);
        *pE = NULL;
        pE = NULL;
    }
}

typedef struct MatrixObj{
    // Rows in matrix, each row is a List ADT which contains sevral entrys.
    List* rows;
    // The size of square Matrix
    int size;
    // The Number of None Zero element
    int nnz;        
}MatrixObj;

Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));
    M->rows = calloc(n + 1, sizeof(List));
    for(int i = 0; i <= n; i++){
        M->rows[i] = newList();
        // for(int j = 0; j <= n; j++){
        //     Entry E = newEntry(0, j);
        //     append(M->rows[i], E);
        // }
    }
    M->size = n;
    M->nnz = 0;
    return M;
}

// Move the cursor in the List to index ith position
// Precondition:
//      0 <= i <= length(L);
//      List L contains Entry which index = i;
void moveCursor(List L, int i){
    while(((Entry)get(L))->index != i){
        if(index(L) == -1) moveFront(L);
        if(((Entry)get(L))->index < i) moveNext(L);
        if(((Entry)get(L))->index > i) movePrev(L);
    }
}
Entry getEntry(Matrix M ,int i, int j){
    List row = M->rows[i];
    for(moveFront(row); index(row) >= 0; moveNext(row)){
        Entry E = get(row);
        if(E->index == j){
            return E;
        }
    }
    return NULL;
}

void freeMatrix(Matrix* pM){
    if(pM != NULL && *pM != NULL){
        for(int i = 0; i <= size(*pM); i++){
            List row = (*pM)->rows[i];
            for(moveFront(row); index(row) >= 0; moveNext(row)){
                Entry E = get(row);
                freeEntry(&E);
            }
            freeList(&((*pM)->rows[i]));
        }
        free((*pM)->rows);
        free((*pM));
        *pM = NULL;
        pM = NULL;
    }
}

int size(Matrix M){
    return M->size;
}

int NNZ(Matrix M){
    return M->nnz;
}

bool equalsEntry(Entry A, Entry B){
    return A->data == B->data && A->index == B->index;
}

bool equalsRow(List A, List B){
    for(moveFront(A), moveFront(B); index(A) >=0 && index(B) >= 0; moveNext(A), moveNext(B)){
        Entry a = get(A);
        Entry b = get(B);
        if(!equalsEntry(a, b)){
            return false;
        }
    }
    return true;
}

int equals(Matrix A, Matrix B){
    if(A->size != B->size || A->nnz != B->nnz){
        return 0;
    }
    for(int i = 0; i <= size(A); i++){
        if(!equalsRow(A->rows[i], A->rows[i])){
            return 0;
        }
    }
    return 1;
}

void makeZero(Matrix M){
    for(int i = 0; i < size(M); i++){
        List row = M->rows[i];
        while(length(row) > 0){
            deleteFront(row);
        }
    }
    M->nnz = 0;
}

// If M doesn't have ith row, jth column Entry, create a new Entry and insert it into the proper position
// If M have ith row, jth column Entry, then change the value of such Entry.
void changeEntry(Matrix M, int i, int j, double x){
    Entry E = getEntry(M, i, j);
    if(E == NULL){  // M_ij doesn't exist.
        if(x == 0){
            return;
        }
        List row = M->rows[i];
        // move cursor of ith row to a proper position for inserting a new Entry.
        for(moveFront(row); index(row) >= 0; moveNext(row)){
            if(((Entry)get(row))->index > j){
                break;
            }
        }
        // append a new Entry to a proper position in ith row.
        if(index(row) >= 0){
            insertBefore(row, newEntry(x, j));
        }else{
            append(M->rows[i], newEntry(x, j));
        }
        // Change NNZ field
        M->nnz ++;
    }else{  // M_ij exist.
        // Change NNZ field
        if(x == 0){
            moveCursor(M->rows[i], j);
            freeEntry(&E);
            delete(M->rows[i]);
            M->nnz -= 1;
            return;
        }
        E->data = x;
    }
}

Matrix copy(Matrix A){
    Matrix copyA = newMatrix(size(A));
    copyA->nnz = NNZ(A);
    for(int i = 0; i <= size(A); i++){
        List row = A->rows[i];
        for(moveFront(row); index(row) >= 0; moveNext(row)){
            Entry E = get(row);
            append(copyA->rows[i], newEntry(E->data, E->index));
        }
    }
    return copyA;
}

Matrix transpose(Matrix A){
    Matrix T = newMatrix(size(A));
    T->nnz = NNZ(A);
    for(int i = 0; i <= size(A); i++){
        List row = A->rows[i];
        for(moveFront(row); index(row) >= 0; moveNext(row)){
            Entry E = get(row);
            append(T->rows[E->index], newEntry(E->data, i));
        }
    }
    return T;
}

Matrix scalarMult(double x, Matrix A){
    Matrix scalarA = newMatrix(size(A));
    scalarA->nnz = NNZ(A);
    for(int i = 0; i <= size(A); i++){
        List row = A->rows[i];
        for(moveFront(row); index(row) >= 0; moveNext(row)){
            Entry E = get(row);
            append(scalarA->rows[i], newEntry(x * E->data, E->index));
            if(x == 0){
                scalarA->nnz -= 1;
            }
        }
    }
    return scalarA;
}

Matrix sum(Matrix A, Matrix B){
    B = copy(B);
    Matrix sumAB = newMatrix(size(A));
    for(int i = 0; i <= size(A); i++){
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        for(moveFront(rowA), moveFront(rowB); index(rowA) >= 0 && index(rowB) >= 0; ){
            Entry E_A = get(rowA);
            Entry E_B = get(rowB);
            if(E_A->index == E_B->index){
                append(sumAB->rows[i], newEntry(E_A->data + E_B->data, E_A->index));
                if(E_A->data + E_B->data == 0){
                    deleteBack(sumAB->rows[i]);
                    sumAB->nnz -= 1;
                }
                moveNext(rowA);
                moveNext(rowB);
            }else if (E_A->index < E_B->index){
                append(sumAB->rows[i], newEntry(E_A->data, E_A->index));
                moveNext(rowA);
            }else if (E_A->index > E_B->index){
                append(sumAB->rows[i], newEntry(E_B->data, E_B->index));
                moveNext(rowB);
            }
            sumAB->nnz += 1;
        }
        while (index(rowA) >= 0){
            Entry E_A = get(rowA);
            append(sumAB->rows[i], newEntry(E_A->data, E_A->index));
            sumAB->nnz += 1;
            moveNext(rowA);
        }
        while (index(rowB) >= 0){
            Entry E_B = get(rowB);
            append(sumAB->rows[i], newEntry(E_B->data, E_B->index));
            sumAB->nnz += 1;
            moveNext(rowB);
        }
    }
    freeMatrix(&B);
    return sumAB;
}

Matrix diff(Matrix A, Matrix B){
    B = copy(B);
    Matrix diffAB = newMatrix(size(A));
    for(int i = 0; i <= size(A); i++){
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        for(moveFront(rowA), moveFront(rowB); index(rowA) >= 0 && index(rowB) >= 0; ){
            Entry E_A = get(rowA);
            Entry E_B = get(rowB);
            if(E_A->index == E_B->index){
                append(diffAB->rows[i], newEntry(E_A->data - E_B->data, E_A->index));
                if(E_A->data - E_B->data == 0){
                    deleteBack(diffAB->rows[i]);
                    diffAB->nnz -= 1;
                }
                moveNext(rowA);
                moveNext(rowB);
            }else if (E_A->index < E_B->index){
                append(diffAB->rows[i], newEntry(E_A->data, E_A->index));
                moveNext(rowA);
            }else if (E_A->index > E_B->index){
                append(diffAB->rows[i], newEntry(0 - E_B->data, E_B->index));
                moveNext(rowB);
            }
            diffAB->nnz += 1;
        }
        // Append the rest Entry in rowA or rowB
        while (index(rowA) >= 0){
            Entry E_A = get(rowA);
            append(diffAB->rows[i], newEntry(E_A->data, E_A->index));
            diffAB->nnz += 1;
            moveNext(rowA);
        }
        while (index(rowB) >= 0){
            Entry E_B = get(rowB);
            append(diffAB->rows[i], newEntry(0 - E_B->data, E_B->index));
            diffAB->nnz += 1;
            moveNext(rowB);
        }
    }
    freeMatrix(&B);
    return diffAB;
}

// Helper function
double vectorDot(List P, List Q){
    double result = 0.0;
    for(moveFront(P), moveFront(Q); index(P) >= 0 && index(Q) >= 0; ){
        Entry p = get(P);
        Entry q = get(Q);
        if(p->index == q->index){
            result += p->data * q->data;
            moveNext(P);
            moveNext(Q);
        }else if (p->index < q->index){
            moveNext(P);
        }else if(p->index > q->index){
            moveNext(Q);
        }
    }
    return result;
}

Matrix product(Matrix A, Matrix B){
    Matrix newB = transpose(B);
    Matrix productAB = newMatrix(size(A));
    for(int i = 1; i <= size(A); i++){
        for(int j = 1; j <= size(A); j++){
            // moveCursor(A->rows[i], j);
            // moveCursor(B->rows[i], j);
            // Entry aEntry = get(A->rows[i]);
            // Entry bEntry = get(B->rows[i]);
            double product = vectorDot(A->rows[i], newB->rows[j]);
            if(product != 0.0){
                append(productAB->rows[i], newEntry(product, j));
                productAB->nnz += 1;
            }
        }
    }
    freeMatrix(&newB);
    return productAB;
}

// Helper function for printMatrix
void cat(FILE* out, List L){
    moveFront(L);
    while(index(L) >= 0){
        Entry E = get(L);
        if(E->data != 0) fprintf(out, "(%d, %.1lf) ", E->index, E->data);
        moveNext(L);
    }
}

void printMatrix(FILE* out, Matrix M){
    for(int i = 0; i <= size(M); i++){
        moveFront(M->rows[i]);
        while(index(M->rows[i]) >= 0){
            if(((Entry)get(M->rows[i]))->data != 0.0){
                fprintf(out, "%d: ", i);
                cat(out, M->rows[i]);
                fprintf(out, "\n");
                break;
            }
            moveNext(M->rows[i]);
        }
    }
    fprintf(out, "\n");
}







