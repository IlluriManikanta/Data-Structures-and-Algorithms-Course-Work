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
#include <assert.h>
#include "List.h"

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
    Node cursor;
} ListObj;

// Node constructor
Node makeNode (int data){
    Node n = (Node)malloc(sizeof(NodeObj));
    assert(n != NULL);
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

// Node Destructor
void freeNode(Node* pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

// Constructors
List newList(void){
    List l = (List)malloc(sizeof(ListObj));
    assert (l != NULL);
    l->length = 0;
    l->index = -1;
    l->front = NULL;
    l->back = NULL;
    l->cursor = NULL;
    return l;
}

// Destructors
void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        free(*pL);
        *pL = NULL;
    }
}

// Access Function
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

int index(List L){
    if(L){
        if(L->length <= 0){
            fprintf(stderr, " List ADT; ERROR in index(): Empty list");
            exit(1);
        }
        if(L->index < -1){
            fprintf(stderr, " List ADT; ERROR in index(): Index less than -1");
            exit(1);  
        }
        return L->index;
    } else {
        fprintf(stderr, " List ADT; ERROR in index(): NULL pointer");
        exit(1);
    }
}

bool equals(List A, List B){
    if(A && B){
        if(A->length != B->length){
            return false;
        }
        Node val1;
        Node val2;
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

// Manipulation Functions
// TA More helped me with wrtiting this function. 
void clear(List L){	
    if(L){
        Node t = L->front;
    	Node temp = t;
    	while (t != NULL) {
        	temp = t->next;
        	freeNode(&t);
        	t = temp;
   	    }
    	L->front = NULL;
   	    L->back = NULL;
    	L->cursor = NULL;
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
            L->cursor = L->front; 
            L->index = 0;
            
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
            L->cursor = L->back; 
            L->index = L->length - 1;
        }
    } else {
        fprintf(stderr, " List ADT; ERROR in moveBack(): NULL pointer");
        exit(1);
    }
}

void movePrev(List L){
    if(L){
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
        Node new_pre = makeNode(x);
        //TA Arka helped me tacke the edge case where the List is empty. Will set front and back to new_prev.
        if(L->length == 0){
            L->front = L->back = new_pre;
            L->length += 1;
        } else if(L->length > 0){
            L->front->prev = new_pre;
            new_pre->next = L->front;
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
        Node new_app = makeNode(x);
        //TA Arka helped me tacke the edge case where the List is empty.Will set front and back to new_app. 
        if(L->length == 0){
            L->front = L->back = new_app;
            L->length += 1;
        } else if(L->length > 0){ 
            L->back->next = new_app;
            new_app->prev = L->back;
            L->back = new_app;
            L->index += 1;
            L->length += 1;
        } 
    } else {
       fprintf(stderr, " List ADT; ERROR in append(): NULL pointer");
        exit(1); 
    }
}

void insertBefore(List L, int x){
    if(L){
        if(L->front == L->cursor){
            prepend(L, x);
            return;
        } else {
            Node new_insertB = makeNode(x);
            Node node_bc = L->cursor->prev;

            if(L->length > 0 && L->index >= 0){
                new_insertB->next = L->cursor;
                new_insertB->prev = node_bc;
                L->cursor->prev = new_insertB;
                node_bc->next = new_insertB;

                L->length += 1;
                L->index += 1;}
        }  
    } else {
        fprintf(stderr, " List ADT; ERROR in insertBefore(): NULL pointer");
        exit(1);  
    }
}

void insertAfter(List L, int x){
    if(L){
        if(L->front == L->cursor){
            append(L, x);
            return;
        } else {
             Node new_insertA = makeNode(x);
            Node node_after_cursor = L->cursor->next;
            if(L->length > 0 && L->index >=0){
                new_insertA->prev = L->cursor;
                new_insertA->next = node_after_cursor;
                L->cursor->next = new_insertA;
                node_after_cursor->prev = new_insertA;
                L->length += 1;
            }
        }
    } else {
        fprintf(stderr, " List ADT; ERROR in insertAfter(): NULL pointer");
        exit(1);  
    }
}
//TA Arka helped me with this function
void deleteFront(List L){
    if(L){
        if (length(L) == 0) {
            printf("List ADT; ERROR in deletFront(): Empty List");
            exit(1);
        }
        Node o = L->front;
        if(L->cursor == o){
            L->cursor = NULL;
        }
        if(o->next != NULL){
            L->front = o->next;
        }
        
        freeNode(&o);
        L->length -= 1;

    } else {
        fprintf(stderr, " List ADT; ERROR in deleteFront(): NULL pointer");
        exit(1);    
    }
}

void deleteBack(List L){
    	if (L == NULL) {
		printf("List Error: calling deleteFront() on NULL list reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) == 0) {
		printf("List Error: calling deleteFront() on an empty list\n");
		exit(EXIT_FAILURE);
	}
	Node N = L->back; 
	L->back = N->prev;
	if (L->cursor == N) {
		L->index = -1;
		L->cursor = NULL;
	}
	freeNode(&N);
	L->length--;
    // if(L){
    //     if(L->length == 0){
    //         printf("List ADT; ERROR in deletBack(): Empty List");
    //         exit(1);
    //     }
    //     if(L->back == L->cursor){
    //         L->index = -1;
    //         L->cursor = NULL;
    //     }

    //     Node end = L->back;
    //     L->back = end->prev;
    //     freeNode(&end);

    //     L->length -= 1;

    // } else {
    //     fprintf(stderr, " List ADT; ERROR in deleteBack(): NULL pointer");
    //     exit(1); 
    // }
}

void delete(List L){
    if(L){
        if(L->back == L->cursor){
            deleteBack(L);
            return;
        }       
        if(L->front == L->cursor){
            deleteFront(L);
            return;
        }

        Node cursor = L->cursor;
        Node node_bc = cursor->prev;
        Node node_ac = cursor->next;
        
        if(node_bc){
            node_bc->next = node_ac;
        }
        if(node_ac){
            node_ac->prev = node_bc;
        }

        L->cursor = NULL;
        L->index = -1;
        freeNode(&cursor);
        L->length -= 1;
 
    } else {
        fprintf(stderr, " List ADT; ERROR in delete(): NULL pointer");
        exit(1); 
    }
}

List copyList(List L){
    if(L){
        List new_list = newList();
        if(L->length != 0){
            Node N = L->front; 
            while (N != NULL) {
                append(new_list, N->data);
                N = N->next;
            }
            if(new_list->cursor != NULL){
                new_list->cursor = NULL;
                return new_list;
            } else {
                return new_list;
            }
        } else {
            return new_list;    
        }
    } else {
        fprintf(stderr, " List ADT; ERROR in List copyList(): NULL pointer");
        exit(1);         
    }
}

List concatList(List A, List B);                            // will finish this later not needed for this pa

void printList(FILE* output, List L){
    if(L){
        if(L->length != 0){
            moveFront(L);
            while(index(L) >= 0){
                fprintf(output, "%d ", get(L));
                moveNext(L);
            }
        }
    } else {
        fprintf(stderr, " List ADT; ERROR in List printList(): NULL pointer");
        exit(1);
    }
}


