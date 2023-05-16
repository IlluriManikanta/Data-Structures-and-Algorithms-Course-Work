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
	cursorPosition = 0;
	number_ele = 0;
}

List::List(const List& L) {
	frontDummy = new Node(-100);
        backDummy = new Node(-100);
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        beforeCursor = frontDummy;
        afterCursor = backDummy;
        cursorPosition = 0;
        number_ele = 0;
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
        return number_ele;
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
    if(cursorPosition > length()){
        throw std::range_error("List ADT: ERROR in position(): Cursor position out of range");
    }
    return cursorPosition;
   }

   // peekNext()
   // Returns the element after the cursor.
   // pre: position()<length()
   ListElement List::peekNext() const{
    if(cursorPosition >= length()){
        throw std::range_error("List ADT: ERROR in peekNext(): Cursor position out of range");
    }
    return afterCursor->data;
   }

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
   ListElement List::peekPrev() const{
    if(cursorPosition <= 0){
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
    cursorPosition = 0;
    beforeCursor = frontDummy;
    afterCursor = beforeCursor->next;
   }

   // moveBack()
   // Moves cursor to position length() in this List.
   void List::moveBack(){
    cursorPosition = length();
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
   }

   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 
   ListElement List::moveNext(){
    if(cursorPosition >= length()){
        throw std::range_error("List ADT: ERROR in moveNext(): Cursor position out of range");
    }

    beforeCursor = afterCursor;
    afterCursor = beforeCursor->next;
    cursorPosition++;

    return afterCursor->data;
    
   }

   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
   ListElement List::movePrev(){
    if(cursorPosition <= 0){
        throw std::range_error("List ADT: ERROR in movePrev(): Cursor position out of range");
    }

    afterCursor = beforeCursor;
    beforeCursor = afterCursor->prev;
    cursorPosition--;

    return beforeCursor->data;
   }

   // insertAfter()
   // Inserts x after cursor.
   void List::insertAfter(ListElement x){
    
   }

   // insertBefore()
   // Inserts x before cursor.
   void List::insertBefore(ListElement x){

   }

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
   void List::setAfter(ListElement x){
    if(cursorPosition > length()){
        throw std::("List ADT: ERROR in setAfter(): Cursor position out of range");
    }
    afterCursor->data = x;
   }

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
   void List::setBefore(ListElement x){
    if(cursorPosition < 0){
        throw std::("List ADT: ERROR in setAfter(): Cursor position out of range");
    }
    beforeCursor->data = x;
   }

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
   void List::eraseAfter(){

   }

   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
   void List::eraseBefore(){

   }


   // Other Functions ---------------------------------------------------------

   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 
   int List::findNext(ListElement x){
    while(cursorPosition < length()){
        if(moveNext() == x){
            return cursorPosition;
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
   int findPrev(ListElement x){
    while(cursorPosition > 0){
        if(movePrev() == x){
            return cursorPosition;
        }
    }
    return -1;
   }

   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
   void cleanup(){

   }
 
   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
   List concat(const List& L) const{

   }

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
   std::string to_string() const{

   }

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   bool equals(const List& R) const{

   }


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
   friend std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
   }

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
   friend bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
   }

   // operator=()
   // Overwrites the state of this List with state of L.
   List& operator=( const List& L ){

   }

