// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 8                       //
// Dictionary ADT Testing File//
// ========================== //

//-----------------------------------------------------------------------------
// DictionaryTest.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
//Added my own test cases
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main() {
   string S[] = { 
      "plaices",
      "ambusher",
      "crosby",
      "wattles",
      "pardoner",
      "pythons",
      "second",
      "forms",
      "impales",
      "pic",
      "verticals",
      "recriminator",
      "depressants",
      "cul",
      "potables",
      "norm",
      "reinsurer",
      "deschooler",
      "recoining",
      "dissocialised",
      "cohabit",
      "hemiolia",
      "cantling",
      "glamorized",
      "millesimal",
      "glagolitic"
   };
   string T[] = { // words to delete
      "second",
      "forms",
      "impales",
      "pic",
      "verticals",
      "recriminator",
      "depressants",
      "cul",
      "potables",
      "norm",
      "reinsurer",
      "deschooler",
      "recoining",
   };

   Dictionary A;
   Dictionary B;

   cout << endl;

   // insert some pairs into A
   for (int i = 0; i < 26; i++) {
      A.setValue(S[i], i + 1);
   }

   // call operator=()
   B = A;

   cout << "A.size() = " << A.size() << endl << A << endl;
   cout << "B.size() = " << B.size() << endl << B << endl;

   B.setValue("deschooler", 101);
   B.setValue("reinsurer", 102);
   B.setValue("glagolitic", 103);
   B.setValue("cul", 104);
   B.setValue("ambusher", 105);

   // call copy constructor
   Dictionary C = B;

   cout << "B.size() = " << B.size() << endl << B << endl;
   cout << "C.size() = " << C.size() << endl << C << endl;

   // check operator==()
   cout << "A == B is " << (A == B ? "true" : "false") << endl;
   cout << "B == C is " << (B == C ? "true" : "false") << endl;
   cout << "C == A is " << (C == A ? "true" : "false") << endl << endl;

   // perform alterations on A
   // cout to check if value is associated with hemiolia
   cout << "Value associated with 'hemiolia': " << A.getValue("hemiolia") << endl;
   A.setValue("hemiolia", A.getValue("hemiolia") * 10); // change the value associated with "hemiolia"
   cout << "New value associated with 'hemiolia': " << A.getValue("hemiolia") << endl << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // remove some pairs from A
   for (int i = 0; i < 13; i++) {
      A.remove(T[i]);
   }

   // check state of A
   cout << "A.size() = " << A.size() << endl << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // do forward iteration on B
   cout << "Forward iteration on B, changing values:" << endl;
   for (B.begin(); B.hasCurrent(); B.next()) {
      cout << "(" + B.currentKey() + ", " << B.currentVal() << ") ";
      B.currentVal()++;  // change value
      cout << "(" + B.currentKey() + ", " << B.currentVal() << ")\n";
   }
   cout << endl;

   // do reverse iteration on C
   cout << "Reverse iteration on C, changing values" << endl;
   for (C.end(); C.hasCurrent(); C.prev()) {
      cout << "(" + C.currentKey() + ", " << C.currentVal() << ") ";
      C.currentVal()++;  // change value
      cout << "(" + C.currentKey() + ", " << C.currentVal() << ")\n";
   }
   cout << endl;

   // check exceptions
   cout << "Testing pre-condition errors:" << endl;
   try {
      cout << "A.getValue(\"blah\"): " << A.getValue("blah") << endl;
   } catch (logic_error& e) {
      cout << "Exception caught: " << e.what() << endl;
      cout << "Continuing without interruption" << endl;
   }
   try {
      A.remove("blah");
   } catch (logic_error& e) {
      cout << "Exception caught: " << e.what() << endl;
      cout << "Continuing without interruption" << endl;
   }
   try {
      cout << "A.currentKey(): " << A.currentKey() << endl;
   } catch (logic_error& e) {
      cout << "Exception caught: " << e.what() << endl;
      cout << "Continuing without interruption" << endl;
   }
   try {
      cout << "A.currentVal(): " << A.currentVal() << endl;
   } catch (logic_error& e) {
      cout << "Exception caught: " << e.what() << endl;
      cout << "Continuing without interruption" << endl;
   }
   try {
      A.next();
   } catch (logic_error& e) {
      cout << "Exception caught: " << e.what() << endl;
      cout << "Continuing without interruption" << endl;
   }
   try {
      A.prev();
   } catch (logic_error& e) {
      cout << "Exception caught: " << e.what() << endl;
      cout << "Continuing without interruption" << endl;
   }
   cout << endl;

   return EXIT_SUCCESS;
}
