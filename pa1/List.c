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
typedef struct Nodeobj* Node;


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
} ListObj;

// Node constructor
Node makeNode (int data){
    Node n = (Node)malloc(sizeof(NodeObj));
    assert (n != NULL);
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

//Node Destructor
void freeNode(Node* pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

// ========= Constructors =========
List newList(void){
    List l = (List)mallco(sizeof(ListObj));
    assert (l != NULL);
    l->length = 0;
    l->index = -1;
    l->front = NULL;
    l->back = NULL;
    l->cursor = NULL;
    return l;
}

// ========= Destructors =========
void freelist(List* pL){
    if(pL != NULL && *pL != NULL){
        free(*pL);
        *pL = NULL;
    }
}

// ========= Access Function =========

int length(List L){
    if(L){
        return L->length;
    } else {
        fprintf(stderr, " List ADT; ERROR in Length(): NULL pointer");
        exit(1);
    }
}

int front(List L){
    if(L){
        if(L->length <= 0){
            fprintf(stderr, " List ADT; ERROR in front(): Empty list");
            exit(1);
        }
        return L->front->data;
    } else {
        fprintf(stderr, " List ADT; ERROR in front(): NULL pointer");
        exit(1);
    }
}

int back(List L){
    if(L){
        if(L->length <= 0){
            fprintf(stderr, " List ADT; ERROR in back(): Empty list");
            exit(1);
        }
        return L->back->data;
    } else {
        fprintf(stderr, " List ADT; ERROR in back(): NULL pointer");
        exit(1);
    } 
}

int get(List L){
    if(L){
        if(L->index < 0){
            fprintf(stderr, " List ADT; ERROR in get(): Cursor is NULL");
            exit(1);
        } else if(L->length <= 0){
            fprintf(stderr, " List ADT; ERROR in get(): Empty list");
            exit(1);
        }
        return L->cursor->data;
    } else {
        fprintf(stderr, " List ADT; ERROR in get(): NULL pointer");
        exit(1);
    } 
}

int index (List L){
    if(L){
        if(L->length <= 0){
            fprintf(stderr, " List ADT; ERROR in index(): Empty list");
            exit(1);
        }
        if(L->index < -1){
            fprintf(stderr, " List ADT; ERROR in index(): Index less than -1");
            exit(1);  
        }
        return L->front->data;
    } else {
        fprintf(stderr, " List ADT; ERROR in index(): NULL pointer");
        exit(1);
    }
}

bool equals(List A, List B){

    if(A && B){
        if(A->length != B->length){
            fprintf(stderr, " List ADT; ERROR in equals(): Empty list");
            exit(1);
        }
        Node val1, val2;
        val1 = A->front;
        val2 = B->front;

        while(val1 != NULL && val2 != NULL){
            if (val1->data != val2->data)
            {
                return false;
            }
            else
            {
                val1 = val1->next;
                val2 = val2->next;
            }
        }
        return true;
    } else {
        fprintf(stderr, " List ADT; ERROR in equals(): NULL pointer");
        exit(1);
    }
}

// ========= Manipulation Functions =========
// TA More helped me with wrtiting this function. 
void clear(List L){
    if(L){
        if(L->length <= 0){
            fprintf(stderr, " List ADT; ERROR in clear(): Empty list");
            exit(1);
        }
        Node temp_n;
        Node fnode = L->front;
        while(fnode != L->back){
            // temp_n = fnode->next;
            // free(&fnode);
            // fnode = temp_n;
            deleteFront(L);
        }
        //free(L->back);
        deleteBack(L);
        L->cursor = NULL;
        L->front = NULL;
        L->back = NULL;
        L->length = 0;
        L->index = -1;
    } else {
        fprintf(stderr, " List ADT; ERROR in clear(): NULL pointer");
        exit(1);
    }
}

void set(List L, int x){
    if(L){
        if(L->length <= 0){
            fprintf(stderr, " List ADT; ERROR in set(): Empty list");
            exit(1);
        }
        if(L->index < -1){
            fprintf(stderr, " List ADT; ERROR in set(): Index less than -1");
            exit(1);
        }
        L->cursor->data = x;
    } else {
        fprintf(stderr, " List ADT; ERROR in set(): NULL pointer");
        exit(1);
    }
}

void moveFront(List L){
    if(L){
        if(L->length <= 0){
            fprintf(stderr, " List ADT; ERROR in moveFront(): Empty list");
            exit(1);
        } else {
            L->index = 0;
            L->cursor = L->front; 
        }
    } else {
        fprintf(stderr, " List ADT; ERROR in moveFront(): NULL pointer");
        exit(1);
    }
}

void moveBack(List L){
    if(L){
        if(L->length <= 0){
            fprintf(stderr, " List ADT; ERROR in moveBack(): Empty list");
            exit(1);
        } else {
            L->index = L->length - 1;
            L->cursor = L->back; 
        }
    } else {
        fprintf(stderr, " List ADT; ERROR in moveBack(): NULL pointer");
        exit(1);
    }
}

void movePrev(List L){
    if(L){
        // could use this --------------
        // if(L->cursor != NULL){
        //     if(L->cursor != L->front){
        //         L->index -= 1;
        //         L->cursor = L->cursor->prev;
        //     }else{
        //         L->cursor = NULL;
        //         L->index = -1;
        //     }
        // } 
        //-------------------------------
        // or 
        if(L->cursor != NULL && L->cursor != L->front){
            L->index -= 1;
            L->cursor = L->cursor->prev;
        } else if(L->cursor == L->front){
            L->cursor = NULL;
            L->index = -1;
        }
    } else {
        fprintf(stderr, " List ADT; ERROR in movePrev(): NULL pointer");
        exit(1);
    }
}

void moveNext(List L){
    if(L){
        // you can rewire this in the same way that is commented for the movePrev function. 
        if(L->cursor != NULL && L->cursor != L->back){
            L->index += 1;
            L->cursor = L->cursor->next;
        } else if(L->cursor == L->back){
            L->cursor   = NULL;
            L->index = -1;
        }
    } else {
        fprintf(stderr, " List ADT; ERROR in moveNext(): NULL pointer");
        exit(1); 
    }
}

void prepend(List L, int x){
    if(L){
        Node new_pre = newNode(x);
        //TA Arka helped me tacke the edge case where the List is empty. Will set front and back to new_prev.
        if(L->length == 0){
            L->front = L->back = new_pre;
        }
        if(L->length > 0){
            new_pre->next = L->front;
            L->front->prev = new_pre;
            L->front = new_pre;
            L->index += 1;
            L->length += 1;
        } 
    } else {
       fprintf(stderr, " List ADT; ERROR in prepend(): NULL pointer");
        exit(1); 
    }
}

void append(List L, int x){
     if(L){
        Node new_app = newNode(x);
        //TA Arka helped me tacke the edge case where the List is empty.Will set front and back to new_app. 
        if(L->length == 0){
            L->front = L->back = new_app;
        }
        if(L->length > 0){
            new_app->prev = L->back;
            L->back->next = new_app;
            L->back = new_app;
        } 
    } else {
       fprintf(stderr, " List ADT; ERROR in prepend(): NULL pointer");
        exit(1); 
    }
}

void insertBefore(List L, int x);  

void insertAfter(List L, int x); 

void deleteFront(List L);  

void deleteBack(List L);

void delete(List L);

List copyList(List L);

List concatList(List A, List B);

void printList(FILE* output, List L);
