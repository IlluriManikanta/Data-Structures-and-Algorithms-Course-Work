// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 1                       //
// Header file for List ADT   //
// ========================== //

#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include <stdio.h>
#include <stdbool.h>

typedef struct Listobj* List;

// ========= Constructors =========
List newList(void);

// ========= Destructors =========
void freelist(List* pL);

// ========= Access Function =========

int length(List L);

int front(List L);

int back(List L); 

int get(List L);

int index (List L);

bool equals(List A, List B);

// ========= Manipulation Functions =========

void clear(List L);

void set(List L, int x);

void moveFront(List L);  

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, int x);

void append(List L, int x);

void insertBefore(List L, int x);  

void insertAfter(List L, int x); 

void deleteFront(List L);  

void deleteBack(List L);

void delete(List L);

List copyList(List L);

List concatList(List A, List B);

void printList(FILE* output, List L);

#endif