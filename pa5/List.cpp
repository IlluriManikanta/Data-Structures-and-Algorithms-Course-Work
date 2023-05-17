// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 5                       //
// Implementing List ADT C++  //
// ========================== //
#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

List::Node::Node(int x) {
    next = nullptr;
	prev = nullptr;
	data = x;
}

List::List() {
    frontDummy = new Node(-100);
	backDummy = new Node(-100);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

List::List(const List& L) {
	frontDummy = new Node(-100);
        backDummy = new Node(-100);
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        beforeCursor = frontDummy;
        afterCursor = backDummy;
        pos_cursor = 0;
        num_elements = 0;
	Node *t = L.frontDummy->next;
	while(t != L.backDummy) {
		this->insertBefore(t->data);
		t = t->next;
	}		
}

List::~List() {
	clear();
	delete frontDummy;
	delete backDummy;
}


   // Access functions --------------------------------------------------------

   // length()
   // Returns the length of this List.
   int List::length() const{
        return num_elements;
   }

   // front()
   // Returns the front element in this List.
   // pre: length()>0
   ListElement List::front() const{
    if(length() < -1){
        throw std::length_error("List ADT: ERROR in front(): Calling front on Empty List");
    }
    return frontDummy->data;
   }

   // back()
   // Returns the back element in this List.
   // pre: length()>0
   ListElement List::back() const{
    if(length() < -1){
        throw std::length_error("List ADT: ERROR in back(): Calling back on Empty List");
    }
    return backDummy->data;
   }

   // position()
   // Returns the position of cursor in this List: 0 <= position() <= length().
   int List::position() const{
    if(length() < -1){
        throw std::length_error("List ADT: ERROR in position(): Calling position on Empty List");
    }
    if(pos_cursor > length()){
        throw std::range_error("List ADT: ERROR in position(): Cursor position out of range");
    }
    return pos_cursor;
   }

   // peekNext()
   // Returns the element after the cursor.
   // pre: position()<length()
   ListElement List::peekNext() const{
    if(pos_cursor >= length()){
        throw std::range_error("List ADT: ERROR in peekNext(): Cursor position out of range");
    }
    return afterCursor->data;
   }

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
   ListElement List::peekPrev() const{
    if(pos_cursor <= 0){
        throw std::range_error("List ADT: ERROR in peekPrev(): Cursor position out of range");
    }
    return beforeCursor->data;
   }
 


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
   void List::clear(){
    moveFront();
    while(length() != 0){
        eraseAfter();
    }
   }

   // moveFront()
   // Moves cursor to position 0 in this List.
   void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = beforeCursor->next;
   }

   // moveBack()
   // Moves cursor to position length() in this List.
   void List::moveBack(){
    pos_cursor = length();
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
   }

   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 
   ListElement List::moveNext(){
    if(pos_cursor >= length()){
        throw std::range_error("List ADT: ERROR in moveNext(): Cursor position out of range");
    }

    beforeCursor = afterCursor;
    afterCursor = beforeCursor->next;
    pos_cursor++;

    return afterCursor->data;
    
   }

   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
   ListElement List::movePrev(){
    if(pos_cursor <= 0){
        throw std::range_error("List ADT: ERROR in movePrev(): Cursor position out of range");
    }

    afterCursor = beforeCursor;
    beforeCursor = afterCursor->prev;
    pos_cursor--;

    return beforeCursor->data;
   }

   // insertAfter()
   // Inserts x after cursor.
   void List::insertAfter(ListElement x){
        Node *temp = new Node(x);
        temp->prev = beforeCursor;
        temp->next = afterCursor;
        beforeCursor->next = temp;
        afterCursor->prev = temp;
        afterCursor = temp;
        num_elements++;
   }

   // insertBefore()
   // Inserts x before cursor.
   void List::insertBefore(ListElement x){
        Node *n = new Node(x);
        n->prev = beforeCursor;
        n->next = afterCursor;
        beforeCursor->next = n;
        afterCursor->prev = n;
        beforeCursor = n;
        num_elements++;
        pos_cursor++;
   }

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
   void List::setAfter(ListElement x){
    if(pos_cursor > length()){
        throw std::range_error("List ADT: ERROR in setAfter(): Cursor position out of range");
    }
    afterCursor->data = x;
   }

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
   void List::setBefore(ListElement x){
    if(pos_cursor < 0){
        throw std::range_error("List ADT: ERROR in setAfter(): Cursor position out of range");
    }
    beforeCursor->data = x;
   }

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
   void List::eraseAfter(){
    if (position() >= length()) {
        throw std::range_error("List ADT: ERROR in setAfter(): Cursor position out of range"); 
    }
    Node *N = afterCursor;
    beforeCursor->next = N->next; 
    afterCursor->next->prev = beforeCursor; 
    afterCursor = N->next; 
    delete N; 
    num_elements--; 
   }

   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
   void List::eraseBefore(){
    if (position() <= 0) {
        throw std::range_error("List ADT: ERROR in setAfter(): Cursor position out of range"); 
    }
    Node *n = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete n;
    pos_cursor--;
    num_elements--;
   }


   // Other Functions ---------------------------------------------------------

   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 
   int List::findNext(ListElement x){
    while(pos_cursor < length()){
        if(moveNext() == x){
            return pos_cursor;
        }
    }
    return -1;
   }

   // findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 
   int List::findPrev(ListElement x){
    while(pos_cursor > 0){
        if(movePrev() == x){
            return pos_cursor;
        }
    }
    return -1;
   }

    //SM
   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
   void List::cleanup(){
     moveFront();
    Node *check = nullptr;
    for(Node *i = frontDummy; i != backDummy; i = i->next){
        //helps check previous element again.
        if(check != i){
            moveNext();
        }
        // int posi = position()-1;
        // int F = findNext(i->data);
        if(findNext(i->data) == -1){
            //resets position
            while (position() != (position()-1)){
                // printf("position = %d\n", position());
                // printf("posi = %d\n", posi);
                movePrev();
            }
            moveNext();
        }else{
            //erases the element and moves to front 
           eraseBefore();
            moveFront();
            i = frontDummy;
            check = i;
        }
    }
    // Node *n = frontDummy->next;
    // int size = 0;
    // int pos = 0;
    // while (n != backDummy) {
    //     Node *t = n->next;
    //     while (t != backDummy) {
    //         if (n->data != t->data) {
    //             t = t->next;
    //         } else {
    //             if (t == afterCursor) {
    //                 eraseAfter();
    //             } else if (t == beforeCursor) {
    //                 eraseBefore();
    //             } else {
    //                 Node *d = t;
    //                 t->next->prev = t->prev;
    //                 t->prev->next = t->next;
    //                 t = t->next;
    //                 delete d;
    //             }
    //         }
    //     }
    //     n = n->next;
    // }
    // Node *t2 = frontDummy->next;
    // Node *t3 = frontDummy->next;
    // while (t2 != afterCursor) {
    //     pos++;
    //     t2 = t2->next;
    // }
    // while (t3 != backDummy) {
    //     size++;
    //     t3 = t3->next;
    // }
    // num_elements = size;
    // pos_cursor = pos;

}

   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
   List List::concat(const List& L) const{
        List K;
        Node* N = this->frontDummy->next;

        while (N != this->backDummy) {
            K.insertBefore(N->data);
            N = N->next;
        }

        Node* M = L.frontDummy->next;

        while (M != L.backDummy) {
            K.insertBefore(M->data);
            M = M->next;
        }

        return K;
   }

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
   std::string List::to_string() const{
        std::string str = "(";

        for (Node* N = frontDummy; N != nullptr; N = N->next) {
            str += std::to_string(N->data);
            str += (N->next != nullptr) ? ", " : "";
        }

        str += ")";
        return str;
   }

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   bool List::equals(const List& R) const{
    if (num_elements != R.num_elements) {
        return false;
    }

    Node* N = frontDummy;
    Node* M = R.frontDummy;

    while (N != nullptr) {
        if (N->data != M->data) {
            return false;
        }
        N = N->next;
        M = M->next;
    }

    return true;
   }


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
   std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
   }

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
   bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
   }

    //SM
   // operator=()
   // Overwrites the state of this List with state of L.
   List& List::operator=( const List& L ){
        if (this != &L) {
            List tmp = L;
            std::swap(frontDummy, tmp.frontDummy);
            std::swap(backDummy, tmp.backDummy);
            std::swap(beforeCursor, tmp.beforeCursor);
            std::swap(afterCursor, tmp.afterCursor);
            std::swap(num_elements, tmp.num_elements);
            std::swap(pos_cursor, tmp.pos_cursor);
        }
        return *this;
   }

