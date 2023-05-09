// // ========== Name ========== //
// // Manikantanagasai H. Illuri //
// // milluri@ucsc.edu           //
// // 2023 Spring CSE101         //
// // PA 4                       //
// // Implementing List ADT      //
// // ========================== //



// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include <assert.h>
// #include "List.h"

// //type casting structure pointer(nodeobj*) to a different type
// typedef struct Nodeobj* Node;


// //defining structure for Nodeobj
// typedef struct Nodeobj{
//     void* data;
//     Node next;
//     Node prev;
// } NodeObj;

// //defining structure for List
// typedef struct Listobj{
//     int length;
//     int index;
//     Node front;
//     Node back;
//     Node cursor;
// } ListObj;

// // Node constructor
// Node makeNode (void* data){
//     Node n = malloc(sizeof(NodeObj));
//     assert(n != NULL);
//     n->data = data;
//     n->next = NULL;
//     n->prev = NULL;
//     return n;
// }

// // Node Destructor
// void freeNode(Node* pN){
//     if(pN != NULL && *pN != NULL){
//         free(*pN);
//         *pN = NULL;
//     }
// }

// // Constructors
// List newList(void){
//     List l = (List)malloc(sizeof(ListObj));
//     assert (l != NULL);
//     l->length = 0;
//     l->index = -1;
//     l->front = NULL;
//     l->back = NULL;
//     l->cursor = NULL;
//     return l;
// }

// // Destructors
// void freeList(List* pL){
//     if(pL != NULL && *pL != NULL){
//         while((*pL)->length != 0){
//             deleteBack(*pL);
//         }
//         free(*pL);
//         *pL = NULL;
//     }
// }

// // Access Function
// int length(List L){
//     if(L){
//         return L->length;
//     } else {
//         fprintf(stderr, " List ADT; ERROR in Length(): NULL pointer\n");
//         exit(1);
//     }
// }

// void* front(List L){
//     if(L){
//         if(L->length <= 0){
//             fprintf(stderr, " List ADT; ERROR in front(): Empty list\n");
//             exit(1);
//         }
//         return L->front->data;
//     } else {
//         fprintf(stderr, " List ADT; ERROR in front(): NULL pointer\n");
//         exit(1);
//     }
// }

// void* back(List L){
//     if(L){
//         if(L->length <= 0){
//             fprintf(stderr, " List ADT; ERROR in back(): Empty list\n");
//             exit(1);
//         }
//         return L->back->data;
//     } else {
//         fprintf(stderr, " List ADT; ERROR in back(): NULL pointer\n");
//         exit(1);
//     } 
// }

// void* get(List L){
//     if(L){
//         if(L->index < 0){
//             fprintf(stderr, " List ADT; ERROR in get(): Cursor is NULL\n");
//             exit(1);
//         } else if(L->length <= 0){
//             fprintf(stderr, " List ADT; ERROR in get(): Empty list\n");
//             exit(1);
//         }
//         return L->cursor->data;
//     } else {
//         fprintf(stderr, " List ADT; ERROR in get(): NULL point\n");
//         exit(1);
//     } 
// }

// int index(List L){
//     if(L){
//         if(L->cursor){
//             return L->index;
//         } else {
//             return -1;
//         }
//     } else {
//         fprintf(stderr, " List ADT; ERROR in index(): NULL pointer\n");
//         exit(1);
//     }
// }

// // Manipulation Functions
// // TA More helped me with wrtiting this function. 
// void clear(List L){	
//     if(L){
//         Node t = L->front;
//     	Node temp = t;
//     	while (L->length > 0) {
//             temp = t->next;
//             deleteFront(L);
//         	// freeNode(&t);
//         	t = temp;
//    	    }
//     	L->front = NULL;
//    	    L->back = NULL;
//     	L->cursor = NULL;
//     	L->length = 0;
//     	L->index = -1;
//     } else {
//         fprintf(stderr, " List ADT; ERROR in clear(): NULL pointer\n");
//         exit(1);
//     }
// }

// void set(List L, void* x){
//     if(L){
//         if(L->length <= 0){
//             fprintf(stderr, " List ADT; ERROR in set(): Empty list\n");
//             exit(1);
//         }
//         if(L->index < -1){
//             fprintf(stderr, " List ADT; ERROR in set(): Index less than -1\n");
//             exit(1);
//         }
//         L->cursor->data = x;
//     } else {
//         fprintf(stderr, " List ADT; ERROR in set(): NULL pointer\n");
//         exit(1);
//     }
// }

// void moveFront(List L){
//     if(L){
//         if(L->length > 0){
//             L->cursor = L->front; 
//             L->index = 0;
//         }
//     } else {
//         fprintf(stderr, " List ADT; ERROR in moveFront(): NULL pointer\n");
//         exit(1);
//     }
// }

// void moveBack(List L){
//    if(L){
//         if(L->length > 0){
//             L->cursor = L->back; 
//             L->index = L->length - 1;
//         }   
//     } else {
//         fprintf(stderr, " List ADT; ERROR in moveBack(): NULL pointer\n");
//         exit(1);
//     }
// }

// void movePrev(List L){
//     if(L){
//         if(L->cursor != NULL && L->cursor != L->front){
//             L->index -= 1;
//             L->cursor = L->cursor->prev;
//         } else if(L->cursor == L->front){
//             L->cursor = NULL;
//             L->index = -1;
//         }
//     } else {
//         fprintf(stderr, " List ADT; ERROR in movePrev(): NULL pointer\n");
//         exit(1);
//     }
// }

// void moveNext(List L){
//     if(L){ 
//         if(L->cursor != NULL && L->cursor != L->back){
//             L->index += 1;
//             L->cursor = L->cursor->next;
//         } else if(L->cursor == L->back){
//             L->cursor   = NULL;
//             L->index = -1;
//         }
//     } else {
//         fprintf(stderr, " List ADT; ERROR in moveNext(): NULL pointer\n");
//         exit(1); 
//     }
// }

// void prepend(List L, void* x){
//     if(L){
//         Node new_pre = makeNode(x);
//         //TA Arka helped me tackle the edge case where the List is empty. Will set front and back to new_prev.
//         if(L->length == 0){
//             L->front = L->back = new_pre;
//             L->length += 1;
//         } else {
//             L->front->prev = new_pre;
//             new_pre->next = L->front;
//             L->front = new_pre;
//             L->index += 1;
//             L->length += 1;
//         } 
//     } else {
//        fprintf(stderr, " List ADT; ERROR in prepend(): NULL pointer\n");
//         exit(1); 
//     }
// }

// void append(List L, void* x){

//      if(L){
        
//         Node new_app = makeNode(x);
//         //TA Arka helped me tackle the edge case where the List is empty. Will set front and back to new_app. 
       
//         if(L->length == 0){
            
//             L->front = new_app;
//             L->back = new_app;
//             L->length += 1;
//         } else { 
           
//             L->back->next = new_app;
//             new_app->prev = L->back;
//             L->back = new_app;

//             L->length += 1;
//         } 
//     } else {
//        fprintf(stderr, " List ADT; ERROR in append(): NULL pointer\n");
//         exit(1); 
//     }
// }

// void insertBefore(List L, void* x){
//     if(L){
//         if(L->front == L->cursor){
//             prepend(L, x);
//             return;
//         } else {
//             Node new_insertB = makeNode(x);
//             Node node_bc = L->cursor->prev;

//             if(L->index >= 0){
                
//                 node_bc->next = new_insertB;
//                 new_insertB->prev = node_bc;
//                 L->cursor->prev = new_insertB;
//                 new_insertB->next = L->cursor;

//                 L->length += 1;
//                 L->index += 1;
//             }
//         }  
//     } else {
//         fprintf(stderr, " List ADT; ERROR in insertBefore(): NULL pointer\n");
//         exit(1);  
//     }
// }

// void insertAfter(List L, void* x){
//     if(L){
//         if(L->back == L->cursor){
//             append(L, x);
//             return;
//         } else {
//             Node new_insertA = makeNode(x);
//             Node node_after_cursor = L->cursor->next;
//             if(L->index >= 0){
//                 node_after_cursor->prev = new_insertA;
//                 new_insertA->next = node_after_cursor;
//                 L->cursor->next = new_insertA;
//                 new_insertA->prev = L->cursor;
//                 L->length += 1;
//             }
//         }
//     } else {
//         fprintf(stderr, " List ADT; ERROR in insertAfter(): NULL pointer\n");
//         exit(1);  
//     }
// }
// //TA Arka helped me with this function
// void deleteFront(List L){
//     if(L){
//         if(L->length == 0){
//             fprintf(stderr,"List ADT; ERROR in deletBack(): Empty List\n");
//             exit(1);
//         }
//         if(L->front == L->cursor){
//             L->cursor = NULL;
//             L->index = -1;
//         } 
//         if(L->length == 1){
//             freeNode(&L->front);
//             L->front = NULL;
//             L->back = NULL;
//         } else { 
//             Node o = L->front;
//             Node fn = L->front->next;
//             if(o->next != NULL){
//                 o->next->prev = NULL;
//                 freeNode(&o);
//                 L->front = fn;
//             }
//         } 
//         L->length -= 1;
//         L->index -= 1;

//     } else {
//         fprintf(stderr, " List ADT; ERROR in deleteFront(): NULL pointer\n");
//         exit(1);    
//     }
// }

// void deleteBack(List L){
//     if(L){
//         if(L->length == 0){
//             fprintf(stderr, "List ADT; ERROR in deletBack(): Empty List\n");
//             exit(1);
//         }
        
//         if(L->back == L->cursor){
//             L->index = -1;
//             L->cursor = NULL;
            
//         } 

//         if(L->length == 1){
//             freeNode(&L->back);
//             L->front = NULL;
//             L->back = NULL;
//         } else { 
//             Node o = L->back;
//             Node fn = L->back->prev;
//             if(o->prev != NULL){
//                 o->prev->next = NULL;
//                 freeNode(&o);
//                 L->back = fn;
//             }
//         }
//         L->length -= 1;
//     } else {
//         fprintf(stderr, " List ADT; ERROR in deleteBack(): NULL pointer\n");
//         exit(1); 
//     }
// }

// void delete(List L){
//     if(L){
//         if(L->back == L->cursor){
//             deleteBack(L);
//             return;
//         }       
//         if(L->front == L->cursor){
//             deleteFront(L);
//             return;
//         }

//         Node node_bc = L->cursor->prev;
//         Node node_ac = L->cursor->next;
        
//         if(node_bc){
//             node_bc->next = node_ac;
//         }
//         if(node_ac){
//             node_ac->prev = node_bc;
//         }

//         L->cursor = NULL;
//         L->index = -1;
//         freeNode(&L->cursor);
//         L->length -= 1;
 
//     } else {
//         fprintf(stderr, " List ADT; ERROR in delete(): NULL pointer\n");
//         exit(1); 
//     }
// }

// List copyList(List L){
//     if(L){
//         List new_list = newList();
//         if(L->length != 0){
//             Node N = L->front; 
//             while (N != NULL) {
//                 append(new_list, N->data);
//                 N = N->next;
//             }
//             if(new_list->cursor != NULL){
//                 new_list->cursor = NULL;
//                 return new_list;
//             } else {
//                 return new_list;
//             }
//         } else {
//             return new_list;    
//         }
//     } else {
//         fprintf(stderr, " List ADT; ERROR in List copyList(): NULL pointer\n");
//         exit(1);         
//     }
// }

// List concatList(List A, List B); // will finish this later not needed for this pa

// void printList(FILE* output, List L){
//     if(L){
//         if(L->length != 0){
//             moveFront(L);
//             while(index(L) >= 0){
//                 fprintf(output, "%p ", get(L));
//                 moveNext(L);
//             }
//         }
//     } else {
//         fprintf(stderr, " List ADT; ERROR in List printList(): NULL pointer\n");
//         exit(1);
//     }
// }


#include <stdlib.h>
#include "List.h"

typedef struct NodeObj *Node;

typedef struct NodeObj
{
    void *data;
    Node prev;
    Node next;
} NodeObj;

typedef struct ListObj
{
    Node front;
    Node cursor;
    Node back;
    int index;
    int length;
} ListObj;

Node newNode(void *data)
{
    Node new_node = (Node)malloc(sizeof(NodeObj));
    if (new_node)
    {
        new_node->data = data;
        new_node->prev = NULL;
        new_node->next = NULL;
        return new_node;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. Node newNode(void *data).\n3. Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
}

void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

List newList(void)
{
    List L = (List)malloc(sizeof(ListObj));
    if (L != NULL)
    {
        L->front = NULL;
        L->cursor = NULL;
        L->back = NULL;
        L->index = -1;
        L->length = 0;
        return L;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. List newList(void).\n3. Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
}

void freeList(List *pL)
{
    if (pL != NULL && *pL != NULL)
    {
        while (length(*pL) != 0)
        {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

int length(List L)
{
    if (L)
    {
        return L->length;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. int length(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

int index(List L)
{
    if (L)
    {
        if (L->cursor == NULL)
        {
            return -1;
        }
        return L->index;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. int index(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void *front(List L)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void *front(List L).\n 3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        return L->front->data;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void *front(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void *back(List L)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void *back(List L).\n 3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        return L->back->data;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void *back(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void *get(List L)
{
    if (L)
    {
        if (L->cursor == NULL)
        {
            fprintf(stderr, "1. List Error.\n 2. void *get(List L).\n3. Error the cursor is undefined.\n");
            exit(EXIT_FAILURE);
        }
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void *get(List L).\n 3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        if (L->index < 0)
        {
            fprintf(stderr, "1. List Error.\n2. void *get(List L).\n 3. Error the index is undefined.\n");
            exit(EXIT_FAILURE);
        }
        return L->cursor->data;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void *get(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

bool ListEqual(List A, List B)
{
    if (A == NULL || B == NULL)
    {                                                                                                  // checking if pointers are not equal to null
        fprintf(stderr, "1. List Error\n2. Function equals()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE);                                                                            // Exiting
    }
    if (A->length != B->length)
    {                 
        return false;
    }
    if (A->length == 0 && B->length == 0)
    {           
        return true;
    }
    Node temp_1 = A->front; 
    Node temp_2 = B->front;
    while (temp_1 != NULL && temp_2 != NULL)
    { 
        if (temp_1->data != temp_2->data)
        {                
            free(temp_1);
            free(temp_2);
            return false;
        }
        temp_1 = temp_1->next; 
        temp_2 = temp_2->next; 
    }
    free(temp_1); 
    free(temp_2); 
    return true;
}

void clear(List L)
{
    if (L)
    {
        while (L->length > 0)
        {
            deleteFront(L);
        }
        L->front = L->cursor = L->back = NULL;
        L->index = -1;
        L->length = 0;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void clear(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void set(List L, void *x)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void set(List L, void *x).\n 3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        if (L->index < 0)
        {
            fprintf(stderr, "1. List Error.\n2. void set(List L, void *x).\n 3. Error the index is undefined.\n");
            exit(EXIT_FAILURE);
        }
        L->cursor->data = x;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void set(List L, void *x).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void moveFront(List L)
{
    if (L)
    {
        if (L->length > 0)
        {
            L->cursor = L->front;
            L->index = 0;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void moveFront(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void moveBack(List L)
{
    if (L)
    {

        if (L->length > 0)
        {
            L->cursor = L->back;
            L->index = L->length - 1;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void moveBack(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void movePrev(List L)
{
    if (L)
    {
        if (L->cursor != NULL && L->cursor == L->front)
        {
            L->cursor = NULL;
            L->index = -1;
        }
        else if (L->cursor != NULL)
        {
            L->cursor = L->cursor->prev;
            L->index--;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void movePrev(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void moveNext(List L)
{
    if (L)
    {
        if (L->cursor != NULL && L->cursor == L->back)
        {
            L->cursor = NULL;
            L->index = -1;
        }
        else if (L->cursor != NULL)
        {
            L->cursor = L->cursor->next;
            L->index++;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void moveNext(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void prepend(List L, void *x)
{
    if (L)
    {
        Node new = newNode(x);
        if (L->length == 0)
        {
            L->front = L->back = new;
            L->length++;
        }
        else if (L->length >= 1)
        {
            new->next = L->front;
            L->front->prev = new;
            L->front = new;
            if (L->cursor != NULL)
            {
                L->index++;
            }
            L->length++;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void prepend(List L, void *x).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void append(List L, void *x)
{
    if (L)
    {
        Node new = newNode(x);
        if (L->length == 0)
        {
            L->front = L->back = new;
            L->length++;
        }
        else if (L->length >= 1)
        {
            new->prev = L->back;
            L->back->next = new;
            L->back = new;
            L->length++;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void append(List L, void *x).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void insertBefore(List L, void *x)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void insertBefore(List L, void *x).\n 3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        if (L->index < 0)
        {
            fprintf(stderr, "1. List Error.\n2. void insertBefore(List L, void *x).\n 3. Error the index is undefined.\n");
            exit(EXIT_FAILURE);
        }
        if (L->cursor != NULL)
        {
            Node N = newNode(x);
            N->prev = L->cursor->prev;
            L->cursor->prev = N;
            N->next = L->cursor;
            if (L->cursor == L->front)
            {
                L->front = N;
            }
            else if (N->prev != NULL && L->cursor != L->front)
            {
                N->prev->next = N;
            }
            L->index++;
            L->length++;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void insertBefore(List L, void *x).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void insertAfter(List L, void *x)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void insertAfter(List L, void *x).\n 3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        if (L->index < 0)
        {
            fprintf(stderr, "1. List Error.\n2. void insertAfter(List L, void *x).\n 3. Error the index is undefined.\n");
            exit(EXIT_FAILURE);
        }
        if (L->cursor != NULL)
        {
            Node N = newNode(x);
            if (L->cursor == L->back)
            {
                N->prev = L->back;
                L->back->next = N;
                L->back = N;
            }
            else
            {
                N->next = L->cursor->next;
                N->prev = L->cursor;
                L->cursor->next = N;
            }
            L->length++;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void insertAfter(List L, void *x).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void deleteFront(List L)
{
    if (L)
    {

        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void deleteFront(List L).\n3. Error the list is empty.\n");
            exit(EXIT_FAILURE);
        }
        Node N = NULL;
        if (L->length > 1)
        {
            N = L->front;
            L->front = L->front->next;
            freeNode(&N);
            L->front->prev = NULL;
            if (L->cursor != NULL)
            {
                L->index--;
            }
            else if (L->index == 0)
            {
                L->cursor = NULL;
                L->index = -1;
            }
        }
        else if (L->length == 1)
        {
            freeNode(&L->front);
            L->front = L->back = L->cursor = NULL;
            L->index = -1;
        }
        L->length--;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void deleteFront(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void deleteBack(List L)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void deleteBack(List L).\n3. Error calling function on empty list\n");
            exit(EXIT_FAILURE);
        }
        Node N = NULL;
        if (L->length > 1)
        {
            N = L->back;
            if (L->cursor == L->back)
            {
                L->cursor = NULL;
                L->index = -1;
            }
            L->back = L->back->prev;
            freeNode(&N);
            L->back->next = NULL;
            L->length--;
        }
        else if (L->length == 1)
        {
            freeNode(&L->front);
            L->back = L->front = L->cursor = NULL;
            L->index = -1;
            L->length = 0;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void deleteBack(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void delete(List L)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void delete(List L).\n3. Error calling function on empty list\n");
        }
        if (L->index < 0)
        {
            fprintf(stderr, "1. List Error.\n2. void delete(List L).\n3. Error the index is undefined.\n");
            exit(EXIT_FAILURE);
        }
        if (L->length == 1)
        {
            freeNode(&L->front);
            L->front = L->back = NULL;
        }
        else if (L->front == L->cursor)
        {
            L->front = L->front->next;
            freeNode(&L->cursor);
            L->front->prev = NULL;
        }
        else if (L->back == L->cursor)
        {
            L->back = L->back->prev;
            freeNode(&L->cursor);
            L->back->next = NULL;
        }
        else
        {
            L->cursor->prev->next = L->cursor->next;
            L->cursor->next->prev = L->cursor->prev;
            freeNode(&L->cursor);
        }
        L->index = -1;
        L->length--;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void delete(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void printList(FILE *out, List L)
{
    if (L)
    {
        Node N = NULL;
        for (N = L->front; N != NULL; N = N->next)
        {
            fprintf(out, "%p ", N->data);
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void printList(FILE *out, List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

List copyList(List L)
{
    if (L)
    {
        Node N = NULL;
        List copy = newList();
        N = L->front;
        while (N != NULL)
        {
            append(copy, N->data);
            N = N->next;
        }
        return copy;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. List copyList(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}