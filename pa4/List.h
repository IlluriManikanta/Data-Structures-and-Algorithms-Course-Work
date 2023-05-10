// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 4                       //
// Header file for List ADT   //
// ========================== //

#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include <stdio.h>
#include <stdbool.h>


typedef struct Listobj* List;


// Constructors 
List newList(void);


// Destructors
void freeList(List* pL);


// Access Functions

int length(List L);

void* front(List L);

void* back(List L); 

void* get(List L);

int index(List L);


// Manipulation Functions

void clear(List L);

void set(List L, void* x);

void moveFront(List L);  

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, void* x);

void append(List L, void* x);

void insertBefore(List L, void* x);  

void insertAfter(List L, void* x); 

void deleteFront(List L);  

void deleteBack(List L);

void delete(List L);

List copyList(List L);

void printList(FILE* output, List L);

#endif

