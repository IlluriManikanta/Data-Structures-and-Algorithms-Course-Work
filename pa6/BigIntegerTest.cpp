/********************************************************************************* 
* Anish Shivamurthy, ashivamu
* 2023 Winter CSE101 PA6
* BigInteger.cpp
* Big Integer ADT implementation
*********************************************************************************/

#include<iostream>
#include<string>
#include<cmath>
#include<sstream>
#include<iomanip>
#include<ctype.h>
#include "List.h"
#include "BigInteger.h"

const ListElement base  = 1000000000;  
const int         power = 9;   


// Helper Functions ----------------------------------------

// negateList()
// Changes the sign of each integer in List L. 
void negateList(List& L){
	L.moveFront();
	while (L.position() < L.length()) {
		L.setAfter(L.peekNext()*-1);
		L.moveNext();
	}    
}


int normalizeList(List& L){
	int sgn = 0;
	if (L.length() == 0) {
		return sgn;
	}
	sgn = 1;
	L.moveFront();
	if (L.front() < 0) {
		negateList(L);
		sgn = -1;
	}
	ListElement carryIn = 0;
	L.moveBack();
	while (L.position() != 0) {
		ListElement data = L.peekPrev();
		L.setBefore(data + carryIn);
		carryIn = 0;
		ListElement d = L.peekPrev();
		if (d < 0){
			if ((d/base) != 0){
				carryIn = (d/base)-1;
			} else {
				carryIn = -1;;
			}
			L.setBefore(d + abs(base*carryIn));
		}
		else if (d >= base){
			carryIn = (d/base);
			ListElement q = d-(base*carryIn);
			L.setBefore(q);
		}
		L.movePrev();
	}
	
	if (carryIn > 0) {
		L.insertAfter(carryIn);
	}
	return sgn;
	
}


void sumList(List& S, List A, List B, int sgn){
	ListElement x, y;
    	S.clear();
    	A.moveFront();
    	B.moveFront();
    	if (A.length() != B.length()) {	
    		while (A.length() != B.length()) {
			x = A.moveNext();
			y = B.moveNext();
			S.insertBefore(x+(y*sgn));
		}
        }
	while (A.position() < A.length()) {
		x = A.moveNext();
		S.insertBefore(x);
	}
        while (B.position() < B.length()) {
        	y = B.moveNext();
        	S.insertBefore(y*sgn);
        }
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p.
void shiftList(List& L, int p){
	int i = 0;
	while (i < p) {
		L.insertAfter(0);
		i++;
	}
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. 
void scalarMultList(List& L, ListElement m){
	if (m != 1) {
		L.moveFront();
		while (L.position() < L.length()) {
			ListElement x = L.peekNext();
			if (x == 0) {
				L.eraseBefore();
				L.insertBefore(x*m);
			}
			L.moveNext();
		}
		L.moveFront();
	}
}


// Class constructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state:
// signum=0, digits=().
BigInteger::BigInteger(){
	signum = 0;
	digits = List();
}


// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
	int n = s.length();
	int i = 0;
	int x = 0;
	int y = 0;
	if (n == 0){
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	
	std::string d = "";

	if (s[0] == '+'){
		signum = 1;
		d = s.substr(1, n);
	}
	else if (s[0] == '-'){
		signum = -1;
		d = s.substr(1, n);
	}
	else{
		signum = 1;
		d = s;
	}
	
	while (d[i] != '\0') {
    		x++;
    		i++;
  	}

	int len = d.length() - 1;
	int data = ceil(x*1.0/power);	
	while (y < data) {
		std::string t = "";
		int p = 0;
		while (p < power){
			t = d[len] + t;
			len--;
			if (len == -1) {
				break;
			}
			p++;
		}
		digits.insertAfter(std::stol(t));
		y++;	
	}
	digits.moveFront();
	while (digits.peekNext() == 0) {
		digits.eraseAfter();
	}
}


BigInteger::BigInteger(const BigInteger& N){	
	signum = N.signum;
	digits = N.digits;
}




// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
	return signum;
}


// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
	int ret = 0;
	BigInteger a = *this;
	BigInteger b = N;
	List A = digits;
	List B = N.digits;
	if (a.signum == b.signum && A == B) {
		ret = 0;
	}
	if (a.signum > b.signum){
		ret = 1;
	}
	else if (a.signum < b.signum){
		ret = -1;
	}
	else {
		if (A.length() < B.length()){
			ret = -1;		
		}
		else if (A.length() > B.length()){
			ret = 1;
		}
		else {
			A.moveFront();
			B.moveFront();
			while (A.position() != A.length() && B.position() != B.length()) {
				ListElement elA = A.moveNext();
				ListElement elB = B.moveNext();
				if (elA < elB) {
					if (a.signum == 1) {
						ret = -1;
					} else {
						ret = 1;
					}
				}
				else if (elA > elB) {
					if (a.signum == 1) {
						ret = 1;
					} else {
						ret = 1;
					}
				} 
			}
		}
	}
	return ret;
}



// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void BigInteger::makeZero(){
	digits.clear();
	signum = 0; 
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative.
void BigInteger::negate(){
	if (signum != 0) {
		signum *= -1;
	}
}


// BigInteger Arithmetic operations ----------------------------------------


// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
	BigInteger Sum;
	Sum.signum = 1;
	BigInteger a = *this;
	BigInteger b = N;
	List A = digits;
	List B = N.digits;
	List& s = Sum.digits;
	A.moveBack();
	B.moveBack();
	while (A.position() > 0 && B.position() > 0) {
		if (B.position() > 0) {
			ListElement addA = a.signum*A.movePrev();
			ListElement addB = b.signum*B.movePrev();
			s.insertAfter(addA + addB);
		}
	}
	while (A.position() > 0) {
		ListElement addA = a.signum*A.movePrev();
		s.insertAfter(addA);
	}
	
	while (B.position() > 0) {
		ListElement addB = b.signum*B.movePrev();
		s.insertAfter(addB);
	}
	if (signum == -1) {
		negateList(A);
	}
	if (N.signum == -1) {
		negateList(B);
	}
	while (s.position() < s.length()) {
	    	if (s.moveNext() == 0) {
	    		s.eraseBefore();
	    	}
	    	else {
	    		break;
	    	}
	}
	Sum.signum = normalizeList(s);
    	return Sum;
}



// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
	BigInteger A = BigInteger(N);
	A.negate();
	return add(A);
}



// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
	BigInteger prod;
	prod.signum = 1;
	BigInteger A = *this;
	BigInteger B = N;
	int sigA = A.signum;
	int sigB = B.signum;
	List a = digits;
	List b = N.digits;
	if (sigA == 0) { 
		prod.signum = 0;
		return prod;
	}
	if (sigB == 0) {
		prod.signum = 0;
		return prod;
	}
	if (sigA == -1) {
		negateList(a);
	}
	if (sigB == -1) {
		negateList(b);
	}
	b.moveBack();
	int col = 0;
	while (B.digits.position() != 0){
		BigInteger calc;
		calc.signum = 1;
		shiftList(calc.digits, col);		
		A.digits.moveBack();
		ListElement bresult = B.digits.movePrev();
		while (A.digits.position() != 0) {
			ListElement mulvalue = A.digits.movePrev()*bresult;
			calc.digits.insertAfter(mulvalue);
		}
		normalizeList(calc.digits);
		prod = prod.add(calc);
		col++;
		
	}
	if (sigA == sigB){
		prod.signum = 1;
	} else {
		prod.signum = -1;
	}
		
	return prod;
}



// Other Functions ---------------------------------------------------------



// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
	std::string s = "";
	std::string sign = "";
	if (signum == -1){
		sign = "-";
	} else if (signum == 0) {
		s = "0";
		return s;
	}
  	digits.moveFront();
	while (digits.position() < digits.length()){
		std::string t = std::to_string(digits.moveNext());
		int size = t.length();
		int end = power - size;
		int i = 0;
		while (i < end) {
			t = "0" + t;
			i++;
		}
		s = s + t;
	}
	
	int j = 0;
	while (s[j]=='0') {
		j++;
	}
	std::string sub = s.substr(j, s.length());
	s = sign + sub;
  	return s;
}



// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
	return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B.. 
bool operator==( const BigInteger& A, const BigInteger& B ){
	if (A.compare(B) == 0) {
		return true;
	}
	return false;
}


// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
	if (A.compare(B) == -1) {
		return true;
	}
	return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
	if (A.compare(B) == -1 || A.compare(B) == 0) {
		return true;
	}
	return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
	if (A.compare(B) == 1 || A.compare(B) == 0) {
		return true;
	}
	return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
	if (A.compare(B) == 1 || A.compare(B) == 0) {
		return true;
	}
	return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
	A = A.add(B);
	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	A = A.sub(B);
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
	A = A.mult(B);
	return A;
}
























// // ========== Name ========== //
// // Manikantanagasai H. Illuri //
// // milluri@ucsc.edu           //
// // 2023 Spring CSE101         //
// // PA 6                       //
// // Testing BigInteger ADT     //
// // ========================== //

// //-----------------------------------------------------------------------------
// //  BigIntegerClient.cpp 
// //  A test client for the BigInteger ADT
// //-----------------------------------------------------------------------------
// #include<iostream>
// #include<string>
// #include<stdexcept>
// #include"BigInteger.h"

// using namespace std;

// int main(){

//    string s1 = "91287346670000043892345634563400005619187236478";
//    //string s2 = "-330293847502398475";
//    string s3 = "9876545439000000345634560000000002000034565430000000006543654365346534";
//    //string s4 = "9876545439000000000000000100000000000006543654365346534";
//    string s5 = "98765454390000034563456191872363456345619187236000456456345756780000065436543";
//    //string s6 = "9876545439000000000000000000000000000006543";

//    //BigInteger N;
//    BigInteger A = BigInteger(s1);
//    BigInteger B = BigInteger(s3);
//    BigInteger C = BigInteger(s5);

//    cout << endl;

//    cout << "A = " << A << endl;
//    cout << "B = " << B << endl;
//    cout << "C = " << C << endl;
//    cout << endl;

//    BigInteger D = A+B;
//    BigInteger E = B+A;
//    BigInteger F = D-E;
//    BigInteger G = 53234*A + 29384747*B + 928374*C;
//    BigInteger H = A*B;
//    BigInteger I = B*A;
//    BigInteger J = G*H*I;

//    cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
//    cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
//    cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
//    cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
//    cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

//    cout << "D = " << D << endl;
//    cout << "E = " << E << endl;
//    cout << "(D==E) = " << ((D==E)?"True":"False") << endl;
//    cout << "F = " << F << endl;
//    cout << "G = " << G << endl;
//    cout << "H = " << H << endl;
//    cout << "I = " << I << endl;
//    cout << "(H==I) = " << ((H==I)?"True":"False") << endl;
//    cout << "J = " << J << endl << endl;

//    cout << endl;

//    A += B;
//    B -= C;
//    C *= J;
//    cout << "A = " << A << endl;
//    cout << "B = " << B << endl;
//    cout << "C = " << C << endl;
//    cout << endl;

//    cout << A*B*C*D*E*G*H*I*J << endl << endl;

//    cout << endl;

//    // test exceptions
//    try{
//       BigInteger J = BigInteger("");
//    }catch( std::invalid_argument& e ){
//       cout << e.what() << endl;
//       cout << "   continuing without interruption" << endl;
//    }
//    try{
//       BigInteger J = BigInteger("+");
//    }catch( std::invalid_argument& e ){
//       cout << e.what() << endl;
//       cout << "   continuing without interruption" << endl;
//    }
//    try{
//       BigInteger J = BigInteger("12329837492387492837492$4982379487293847");
//    }catch( std::invalid_argument& e ){
//       cout << e.what() << endl;
//       cout << "   continuing without interruption" << endl;
//    }
//    try{
//       BigInteger J = BigInteger("5298374902837409+82734098729287349827398");
//    }catch( std::invalid_argument& e ){
//       cout << e.what() << endl;
//       cout << "   continuing without interruption" << endl;
//    }

//    cout << endl;

//    return EXIT_SUCCESS;
// }
