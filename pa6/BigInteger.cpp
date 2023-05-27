// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 6                       //
// Implementing BigInteger ADT//
// ========================== //

#include "BigInteger.h"

ListElement base = 1000000000;  
int power = 9;

// Helper Functions below ---------------------------------------------------------------------------------------------------
void scalarMultiply(List& L, ListElement m){
    L.moveFront();
    while(L.position() < L.length()){
        ListElement v = L.peekNext() * m;
        L.setAfter(v);
        L.moveNext();
    }
}

//TA George helped me implement this function(05/22/2023) 
int normalizeList(List& L){
    int signval = 1;
    if(L.front() == 0){
        return 0;
    } else if(L.front() < 0){
        signval = -1;
        scalarMultiply(L, -1);
    }

    L.moveBack();
    int carry = 0;
    ListElement hold = 0;
    while(L.position() > 0){
        hold = L.peekPrev() + carry;
        carry = 0;
        if(hold < 0){
            carry = -1;
            hold += base;
        }
        L.setBefore(hold % base);
        carry += (hold / base);
        L.movePrev();
    }

    if(carry > 0){
        L.moveFront();
        L.insertAfter(carry);
    }

    return signval;
}

//TA George helped me implement this function(05/22/2023) 
void sumList(List& S, List A, List B, int sgn){
    S.clear();
    scalarMultiply(B, sgn);
    A.moveBack();
    B.moveBack();
    
    while (A.position() > 0 || B.position() > 0) {  

        ListElement x = 0;
        if(A.position() > 0){
            x = A.peekPrev();
        } else {
            x = 0;
        }
        
        ListElement y = 0;
        if(B.position() > 0){
            y = B.peekPrev();
        } else {
            y = 0;
        }

        ListElement sumofele = x + y;
        S.insertAfter(sumofele);
        if(A.position() > 0){
            A.movePrev();
        }

        if(B.position() > 0){
            B.movePrev();
        }
    }

    S.moveFront();
    while(S.front() == 0 && S.length() > 1){
        S.eraseAfter();
    }
}

void shiftList(List& L, int p){
    L.moveBack();
    for(int i = 0; i < p; i++){
        L.insertAfter(0);
    }
}

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    if(x < 0){
        signum = -1;
    } else if(x > 0){
        signum = 1;
    } else {
        signum = 0;
    }

    long absval = 0;
    if(x < 0){
        absval = -x;
    } else {
        absval = x;
    }

    while(absval > 0){
        digits.insertAfter(absval % base);
        absval /= base;
    }

    digits.moveFront();
}

// BigInteger()
//NEED TO CHANGE
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    if (s.size() == 0){                                                                        
        throw std::invalid_argument("BigInteger: ERROR in Constructor: empty string"); 
    }

    signum = 1;
    if (s[0] == '-') {
        signum = -1;
        s = s.substr(1);
    } else if (s[0] == '+') {
        s = s.substr(1);
    }

    if (s.size() >= 1){                     
        for (char const &c : s) {
            if (!isdigit(c)){                                                                               
                throw std::invalid_argument("BigInteger: ERROR in Constructor: non-numeric string"); 
            }
        }
    } else {                                                                               
        throw std::invalid_argument("BigInteger: ERROR in Constructor: non-numeric string"); 
    }

    int position = s.length() % power; 

    if (position){                                                    
        digits.insertBefore(stol(s.substr(0, position))); 
    }

    while(position < (int)s.length()){
        digits.insertBefore(stol(s.substr(position, power))); 
        position += power;
    }
}

// BigInteger()
// Constructor that creates a copy of N.
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
    List A = digits;
    List B = N.digits;

    if (signum > N.signum) {
        ret = 1;
    } else if (signum < N.signum) {
        ret = -1;
    } else {

        if (A.length() < B.length()) {
            ret = -1;
        } else if (A.length() > B.length()) {
            ret = 1;
        } else {

            A.moveFront();
            B.moveFront();

            while (A.position() < A.length() && ret == 0) { 
                if (A.peekNext() < B.peekNext()) {
                    ret = -1;
                } else if (A.peekNext() > B.peekNext()) {
                    ret = 1;
                } else {
                    ret = 0;
                }
                A.moveNext();
                B.moveNext();
            }
        }
    }
    return ret;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    signum *= -1;
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger copya = *this;
    BigInteger copyb = N;
    BigInteger sum;
    int sgn = 1;
    if(this->signum == -1){
        scalarMultiply(copya.digits, -1); // negates the list 
    }
    if(N.signum == -1){
        sgn = -1;
    }

    sumList(sum.digits, copya.digits, copyb.digits, sgn); // adding all list values togather
    sum.signum = normalizeList(sum.digits);
    if(normalizeList(sum.digits) == -1){
        scalarMultiply(sum.digits, -1);
    }

    return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger A = BigInteger(N);
    scalarMultiply(A.digits, -1); // negates list A
    return add(A);
}

// mult()
// Returns a BigInteger representing the product of this and N. 
//TA Amaan assisted me in tackeling corner cases and fixing logical errors in loop(05/24/2023)
BigInteger BigInteger::mult(const BigInteger& N) const{ 
    BigInteger fnl;
    if (this->signum == 0 || N.signum == 0) {
        return fnl;
    }

    List tot;
    List Ntemp = N.digits;  
    List tmp;

    Ntemp.moveBack();
    int move = 0;
    while (Ntemp.position() != 0) {
        ListElement now = Ntemp.peekPrev();
        
        tmp = this->digits;
        scalarMultiply(tmp, now);
        shiftList(tmp, move);

        List tempsum = tot;
        sumList(tot, tempsum, tmp, 1);

        normalizeList(tot);
        move++;
        Ntemp.movePrev();
    }

    fnl.digits = tot;
    if(this->signum == N.signum){
        fnl.signum = 1;
    } else {
        fnl.signum = -1;
    }
    return fnl;
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
    if (signum == -1) {
        sign = "-";
    } else if (signum == 0) {
        s = "0";
        return s;
    }
    
    digits.moveFront();
    while (digits.position() < digits.length()) {
        std::string st = "";
        ListElement element = digits.moveNext();
        if (element == 0) {
            st = "0";
        } else {
            int tmp = element;
            while (tmp > 0) {
                st = char('0' + (tmp % 10)) + st; 
                tmp /= 10;
            }
        }
        int size = st.length();
        int i = 0;
        while (i < (power - size)) {
            st = "0" + st;
            i++;
        }
        s = s + st;
    }
    
    int j = 0;
    while (s[j] == '0') {
        j++;
    }
    
    std::string sub = "";
    for (int k = j; k < s.length(); k++) {
        sub += s[k];
    }
    
    s = sign + sub;
    return s;

}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 0){
        return true;
    } else {
        return false;
    }
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == -1){
        return true;
    } else {
        return false;
    }
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 0 || A.compare(B) == -1){
        return true;
    } else {
        return false;
    }
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 1){
        return true;
    } else {
        return false;
    }
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 0 || A.compare(B) == 1){
        return true;
    } else {
        return false;
    }
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
