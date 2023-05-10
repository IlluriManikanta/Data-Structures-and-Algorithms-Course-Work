// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 4                       //
// Testing ADT Functions      //
// ========================== //
// I have added more of my own tests to 


//-----------------------------------------------------------------------------
// ListClient.c
// Test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = newList();
   List D = newList();
   List E = newList();
   List F = newList();
   int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
   int i, u=-1, v=-2, w=-3; 
   bool equal = false;

   for(i=1; i<=20; i++){
      append(A, &X[i]);
      prepend(B, &X[i]);
      append(A, &X[i]);
      prepend(B, &X[i]);

   }

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

      for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   moveFront(A);
   while( index(A)>=0 ){
      append(C, get(A));
      moveNext(A);
   }
   moveFront(B);
   while( index(B)>=0 ){
      append(D, get(B));
      moveNext(B);
   }
   for(moveFront(C); index(C)>=0; moveNext(C)){
      printf("%d ", *(int*)get(C));
   }
   printf("\n");

   
   equal = (length(A)==length(C));
   moveFront(A);
   moveFront(C);
   while( index(A)>=0 && equal){
      equal = ( get(A)==get(C) );
      moveNext(A);
      moveNext(C);
   }
   printf("A equals C is %s\n", (equal?"true":"false") );

   moveFront(A);
   for(i=0; i<5; i++) moveNext(A);    
   printf("index(A)=%d\n", index(A));
   insertBefore(A, &u);              
   printf("index(A)=%d\n", index(A));
   for(i=0; i<9; i++) moveNext(A);    
   printf("index(A)=%d\n", index(A));
   insertAfter(A, &v);               
   printf("index(A)=%d\n", index(A));
   for(i=0; i<5; i++) movePrev(A);   
   printf("index(A)=%d\n", index(A));
   delete(A);                         
   printf("index(A)=%d\n", index(A));
   moveBack(A);                       
   printf("index(A)=%d\n", index(A));
   for(i=0; i<10; i++) movePrev(A); 
   printf("index(A)=%d\n", index(A));
   set(A, &w);
   for(i=0; i<10; i++) movePrev(A); 
   printf("index(A)=%d\n", index(A));
   set(D, &w);
   for(i=0; i<10; i++) movePrev(A); 
   printf("index(A)=%d\n", index(A));
   set(E, &w);
   for(i=0; i<10; i++) movePrev(A); 
   printf("index(A)=%d\n", index(A));
   set(F, &w);

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");

   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");

   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);
   freeList(&D);
   freeList(&E);
   freeList(&F);

   return(0);
}


