// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 6                       //
// Implementing List ADT C++  //
// ========================== //

//Added own test cases to test my code 

//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------


#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
   printf("%s\n", "Beginning the Tests\n");
		
		printf("%s\n", "Your code is working fine if it matches the output at the bottom\n");

   int i, n=10;
   List A, B, C, D;

   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
   }

   //cleanup position check
   printf("%s\n", "Cleanup Position check");

   A.insertBefore(1);
    cout << "A pos = " << A.position() << endl;
    A.insertBefore(2);
    cout << "A pos = " << A.position() << endl;
    A.insertBefore(2);
    cout << "A pos = " << A.position() << endl;
    A.insertBefore(1);
    cout << "A pos = " << A.position() << endl;
    A.insertBefore(2);
    cout << "A pos = " << A.position() << endl;
    A.insertBefore(3);
    cout << "A pos = " << A.position() << endl;
    A.insertBefore(1);
    cout << "A pos = " << A.position() << endl;
    A.findPrev(3);
    cout << "A pos before cleanup() = " << A.position() << endl;
    A.cleanup();
    cout << "A = " << A << endl;
    cout << "A pos here = " << A.position() << endl;
    if (A.position() != 2) cout << "A.pos = 2\n" << endl;

   //cleanup position check
    cout << "Start: B pos = " << B.position() << endl;
   B.insertBefore(1);
   cout << "B pos = " << B.position() << endl;
      B.insertBefore(2);
         cout << "B pos = " << B.position() << endl;
      B.insertBefore(2);
         cout << "B pos = " << B.position() << endl;
      B.insertBefore(1);
         cout << "B pos = " << B.position() << endl;
      B.insertBefore(2);
         cout << "B pos = " << B.position() << endl;
      B.insertBefore(3);
         cout << "B pos = " << B.position() << endl;
      B.insertBefore(1);
         cout << "B pos = " << B.position() << endl;
      B.findPrev(3);
         cout << "B pos = " << B.position() << endl;
      B.movePrev();
         cout << "B pos = " << B.position() << endl;
      B.cleanup();
      cout << "B = " << B << endl;
      cout << "B pos here = " << B.position() << endl;
      if (B.position() != 2) cout << "B.pos = 2" << endl;

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

printf("%s\n", "testing movePrev");
		

   cout << endl << "B: ";
   for(i=1; i<=9; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;
   printf("%s\n", "testing moveNext");
   cout << endl << "C: ";
   for(i=1; i<=7; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

printf("%s\n", "testing equals, true or false");
   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==D is " << (C==D?"true":"false") << endl;
   cout << "D==A is " << (D==A?"true":"false") << endl;
   cout << endl;
printf("%s\n", "testing findNext");
   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;

   cout << B.findPrev(2) << endl;

   B.eraseBefore();
   cout << "after erase before" << B << endl;
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findNext(30) << endl; 
   cout << B.position() << endl;
   cout << B.findPrev(30) << endl;
   cout << B.position() << endl;
   cout << endl;

printf("%s\n", "testing insertafter");
   for( i=101; i>=1; i--){
      A.insertAfter(i);
      A.movePrev();
   }
   printf("%s\n", "testing movenext");
   cout << "A = " << A << endl;
   for( i=1; i<=110; i++){
      A.moveNext();
   }
   cout << A.position() << endl;
   A.cleanup();
   cout << "A = " << A << endl;
   cout << A.position() << endl;
   cout << endl;

   List E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;

   cout << endl;

   List F = A.concat(B);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position: " << F.position() << endl;
   for( i=1; i<=7; i++){
      cout << "peekNext: " << F.peekNext() << endl;
      F.insertBefore(-i);
      cout << F.moveNext() << endl; 
   }
   cout << "F = " << F << endl;

   cout << endl;

   cout << "test exceptions: " << endl;
   cout << "A = " << A << endl;
   A.moveFront();
   try{
      A.peekPrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.movePrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setBefore(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseBefore();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.moveBack();
   try{
      A.peekNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.moveNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setAfter(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseAfter();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.clear();
   try{
      A.front();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.back();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;
   
   return( 0 );
}
