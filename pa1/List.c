// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 1                       //
// Implementing List ADT      //
// ========================== //

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

//type casting structure pointer(nodeobj*) to a different type
typedef struct NodeObj* Node;


//defining structure for Nodeobj
typedef struct Nodeobj{
    int data;
    Node next;
    Node prev;
} NodeObj;

//defining structure for List
typedef struct Listobj{
    int length;
    int index;
    Node front;
    Node back;
    Node cursor
} Listobj;

// Node constructor
Node makeNode (int data){
    Node n = (Node)malloc(sizeof(NodeObj));
    assert (n != NULL);
}

//Node Destructor


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
