/****************************************************************************************
*  ListClient.c
*  Test client for List ADT
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   }

   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");

   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");


   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10

   delete(A);
   printList(stdout,A);

   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));



    // List newlisttest = newList();
    // if(index(newlisttest) == -1){
    //     printf("%s", "HERE");
    // } else {
    //     printf("%s", "NOT HERE");
    // }
    // List D = newList();
    printf("%s", "0");
    append(A, 5);
    printf("%s", "0");
    append(A, 6);
    printf("%s", "0");
    append(A, 4);
    printf("%s", "0");
    append(A, 33);
    printf("%s", "0");
    append(A, 2);
    printf("%s", "0");
    append(A, 1);
    printf("%s", "0");
    moveBack(A);
    printf("%s", "0");
    insertAfter(A, 75);
    printf("%s", "0");
    moveNext(A);
    printf("%s", "0");
    if (index(A) != 6)
        printf("%s", "0");
        printf("%s", "iii");
    //   return 1;
    insertAfter(A, 345);
    printf("%s", "0");
    moveBack(A);
    printf("%s", "0");
    if (index(A) != 7)
      printf("%s", "jjj");
    
    freeList(&A);
    freeList(&B);
    freeList(&C);



   return(0);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
21
0
*/



