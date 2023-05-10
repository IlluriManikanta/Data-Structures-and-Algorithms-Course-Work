// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 4                       //
// Testing ADT Functions      //
// ========================== //
// I have added more of my own tests to 
//-----------------------------------------------------------------------------
//  MatrixClient.c 
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n=10;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H;
   printf("%s\n", "ChangeENtry test");
   changeEntry(A, 4, 1, 4);
    changeEntry(A, 2, 1, 5);
    changeEntry(A, 1, 6, 2);
    changeEntry(A, 1, 7, 5);
    changeEntry(A, 8, 1, 4);
    changeEntry(A, 2, 2, 9);
    changeEntry(A, 2, 5, 0);
    changeEntry(A, 24, 3, 1);
    changeEntry(A, 2, 3, 0);
   
    changeEntry(A, 5, 3, 0);
    changeEntry(A, 3, 1, 4);
    changeEntry(A, 3, 2, 0);
    
    changeEntry(A, 7, 0, 222);
    changeEntry(A, 80, 1, 2434);
    
    changeEntry(A, 7, 0, 0);

   printf("%s\n", "makezero test");
    makeZero(A);
    changeEntry(A, 3, 5, 5);

   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");
   printf("%s\n", "ScalarMut test");
   C = scalarMult(1.9, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");
   printf("%s\n", "sum test");
   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");
   printf("%s\n", "diff test");
   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");
   printf("%s\n", "transpose test");
   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");
   printf("%s\n", "product test");
   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");
   printf("%s\n", "copy test");
   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", "equals test");
   printf("%s\n", equals(H, A)?"true":"false" );
   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );
   printf("%s\n", equals(B, A)?"true":"false" );
   printf("%s\n", equals(C, A)?"true":"false" );
   printf("%s\n", "make zero test");
   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("%s\n", "freeing test");
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   
   freeMatrix(&A);
   freeMatrix(&B);
   return EXIT_SUCCESS;
}

