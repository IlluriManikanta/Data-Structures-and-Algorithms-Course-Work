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
   
   changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 5);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 5);
    changeEntry(A, 1, 1, 4);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 2, 5, 0);
    changeEntry(A, 2, 3, 0);
    changeEntry(A, 3, 3, 5);
   
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 3, 3, 0);
    
    changeEntry(A, 7, 6, 42);
    changeEntry(A, 10, 1, 24);
    
    changeEntry(A, 7, 6, 0);
   
   //  makeZero(A);
   //  changeEntry(A, 5, 5, 5);
   
   freeMatrix(&A);
   freeMatrix(&B);
   return EXIT_SUCCESS;
}

/*
Output of this program:
9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

0

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

true
false
true
0
*/