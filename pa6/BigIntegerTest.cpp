// // ========== Name ========== //
// // Manikantanagasai H. Illuri //
// // milluri@ucsc.edu           //
// // 2023 Spring CSE101         //
// // PA 6                       //
// // Testing BigInteger ADT     //
// // ========================== //


// #include<iostream>
// #include<string>
// #include<stdexcept>
// #include"BigInteger.h"

// using namespace std;

// int main(){
// 		printf("%s\n", "Beginning the Tests\n");
		
// 		printf("%s\n", "Your code is working fine if it matches the output at the bottom\n");

//    string s1 = "91287346670000043892345634563400005619187236478";
//    string s2 = "-330293847502398475";
//    string s3 = "9876545439000000345634560000000002000034565430000000006543654365346534";
//    string s4 = "9876545439000000000000000100000000000006543654365346534";
//    string s5 = "98765454390000034563456191872363456345619187236000456456345756780000065436543";
//    string s6 = "9876545439000000000000000000000000000006543";

//    BigInteger N;
//    BigInteger A = BigInteger(s1);
//    BigInteger B = BigInteger(s3);
//    BigInteger C = BigInteger(s5);

//    cout << endl;

//    cout << "A = " << A << endl;
//    cout << "B = " << B << endl;
//    cout << "C = " << C << endl;
//    cout << endl;

// 	printf("%s\n", "Testing addition\n");
//    BigInteger D = A+B;
//    BigInteger E = B+A;
//    	printf("%s\n", "Testing subtraction\n");
//    BigInteger F = D-E;
//    BigInteger F = A-B;
//    	printf("%s\n", "Testing addition and multiplication\n");
//    BigInteger G = 53527*A + 593247447*B + 8482474*C;
//     	printf("%s\n", "Testing multiplication\n");
//    BigInteger H = A*B;
//    BigInteger F = A*A;
//    BigInteger I = B*A;
//    	printf("%s\n", "Testing multiplication on three values\n");
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
//    	printf("%s\n", "Testing exceptions");
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

// 	printf("%s\n", "Testing Ended\n");
//    cout << endl;

//    return 0;
// }
