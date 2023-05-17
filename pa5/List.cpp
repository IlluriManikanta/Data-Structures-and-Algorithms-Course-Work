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
    frontDummy = new Node(-11);
	backDummy = new Node(-11);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

List::List(const List& L) {
	    frontDummy = new Node(-11);
        backDummy = new Node(-11);
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        beforeCursor = frontDummy;
        afterCursor = backDummy;
        pos_cursor = 0;
        num_elements = 0;
	Node *N = L.frontDummy->next;
	while(N != L.backDummy) {
		this->insertBefore(N->data);
		N = N->next;
	}		
}

List::~List() {
	this->clear();
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
    return frontDummy->next->data;
   }

   // back()
   // Returns the back element in this List.
   // pre: length()>0
   ListElement List::back() const{
    if(length() < -1){
        throw std::length_error("List ADT: ERROR in back(): Calling back on Empty List");
    }
    return backDummy->prev->data;
   }

   // position()
   // Returns the position of cursor in this List: 0 <= position() <= length().
   int List::position() const{
    return pos_cursor;
   }

   // peekNext()
   // Returns the element after the cursor.
   // pre: position()<length()
   ListElement List::peekNext() const{
    if(position() >= length()){
        throw std::range_error("List ADT: ERROR in peekNext(): Cursor position out of range");
    }
    return afterCursor->data;
   }

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
   ListElement List::peekPrev() const{
    if(position() <= 0){
        throw std::range_error("List ADT: ERROR in peekPrev(): Cursor position out of range");
    }
    return beforeCursor->data;
   }
 


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
   void List::clear(){
    moveFront();
    while(length() > 0){
        eraseAfter();
    }
   }

   // moveFront()
   // Moves cursor to position 0 in this List.
   void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
   }

   // moveBack()
   // Moves cursor to position length() in this List.
   void List::moveBack(){
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = length();
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
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
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
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
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
        Node *temp = new Node(x);
        temp->prev = beforeCursor;
        temp->next = afterCursor;
        beforeCursor->next = temp;
        afterCursor->prev = temp;
        beforeCursor = temp;
        num_elements++;
        pos_cursor++;
   }

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
   void List::setAfter(ListElement x){
    if(pos_cursor >= length()){
        throw std::range_error("List ADT: ERROR in setAfter(): Cursor position out of range");
    }
    afterCursor->data = x;
   }

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
   void List::setBefore(ListElement x){
    if(pos_cursor <= 0){
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

    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
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
    Node *N = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete N;
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
    while(position() < length()){
        if(afterCursor->data == x){
            moveNext();
            return position();
        }
        moveNext();
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
    while(position() > 0){
        if(beforeCursor->data == x){
            movePrev();
            return position();
        }
        movePrev();
    }
    return -1;
   }
void List::cleanup() {
    Node* current = frontDummy->next;
    while (current != backDummy) {
        Node* checker = current->next;
        while (checker != backDummy) {
            Node* nextNode = checker->next;  // Store next node before potential deletion
            if (current->data == checker->data) {
                if (checker == beforeCursor) {
                    beforeCursor = beforeCursor->prev;
                    afterCursor = beforeCursor->next;
                    if (num_elements > pos_cursor) {
                        pos_cursor--;
                    }
                }
                if (checker == afterCursor) {
                    afterCursor = afterCursor->next;
                    beforeCursor = afterCursor->prev;
                    if (num_elements > pos_cursor) {
                        pos_cursor--;
                    }
                }
                checker->prev->next = checker->next;
                checker->next->prev = checker->prev;
                delete checker;
                num_elements--;
            }
            checker = nextNode;  // Move to the next node
        }
        current = current->next;
    }
    if (pos_cursor == num_elements) {
        afterCursor = backDummy;
        beforeCursor = backDummy->prev;
    }
}

// void List::cleanup() {
//     Node* current = frontDummy->next;
    
//     while (current != backDummy) {
//         Node* checker = current->next;

//         while (checker != backDummy) {
//             if (current->data == checker->data) {
//                 Node* toDelete = checker;

//                 checker = checker->next;
//                 toDelete->prev->next = toDelete->next;
//                 toDelete->next->prev = toDelete->prev;
//                 if (toDelete == beforeCursor) {
//                     beforeCursor = toDelete->prev;
//                     afterCursor = beforeCursor->next;
//                     if (num_elements > pos_cursor) {
//                         pos_cursor--;
//                     }
//                 }
//                 if (toDelete == afterCursor) {
//                     afterCursor = toDelete->next;
//                     beforeCursor = afterCursor->prev;
//                     if (num_elements > pos_cursor) {
//                         pos_cursor--;
//                     }
//                 }
//                 delete toDelete;
//                 num_elements--;
//             } else {
//                 checker = checker->next;
//             }
//         }
//         current = current->next;
//     }
//     if (pos_cursor == num_elements) {
//         afterCursor = backDummy;
//         beforeCursor = backDummy->prev;
//     }
// }

   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
   List List::concat(const List& L) const{
        List K = List();
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
        K.moveFront();
        return K;
   }

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
   std::string List::to_string() const{
        Node* N = nullptr;
        std::string s = "(";
        for(N=frontDummy->next; N!=backDummy->prev; N=N->next){
            s += std::to_string(N->data)+", ";
        }
        s += std::to_string(N->data)+")";

        return s;
   }

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   bool List::equals(const List& R) const{
    if (num_elements != R.num_elements) {
        return false;
    }
    bool eq = false;
    Node* N = frontDummy->next;
    Node* M = R.frontDummy->next;
    eq = ( this->length() == R.length());
    while (eq && N != backDummy->prev) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;

    }
    return eq;
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

