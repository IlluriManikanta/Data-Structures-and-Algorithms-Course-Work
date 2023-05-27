// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 5                       //
// Implementing Arithmetic    //
// ========================== //

#include<fstream>
#include"BigInteger.h"

using namespace std;

int main(int argc, char* argv[]){
    //declaring in and out files
    ifstream in_file;
    ofstream out_file;

    //Checking for correct number of arguments
    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <deck size>" << endl;
        return 1;
    }

    //Opening read and write files
    in_file.open(argv[1]);
    if(!in_file.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(1);
    }
    
    out_file.open(argv[2]);
    if( !out_file.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(1);
    }

    //Reading lines input file
    string tmp_A;
    string tmp_B;
    in_file >> tmp_A >> tmp_B;

    BigInteger A(tmp_A);
    BigInteger B(tmp_B);

    //Conducting arithmetic operations here
    out_file << A << endl << endl;
    out_file << B << endl << endl;
    out_file << A + B << endl << endl;
    out_file << A - B << endl << endl;
    out_file << A - A << endl << endl;
    out_file << A.mult(BigInteger("3")) - B.mult(BigInteger("2")) << endl << endl;
    out_file << A * B << endl << endl;
    out_file << A * A << endl << endl;
    out_file << B * B << endl << endl;
    out_file << (A * A * A * A).mult(BigInteger("9")) + (B * B * B * B * B).mult(BigInteger("16")) << endl << endl;

    //Closing files
    in_file.close();
    out_file.close();

    return(0);

}
