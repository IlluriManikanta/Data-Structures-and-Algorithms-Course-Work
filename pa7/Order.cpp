// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 7                       //
// Order                      //
// ========================== //
#include <iostream>
#include<fstream>
#include<string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream in;
    ofstream out;

    //Checking number of argumnets passed
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // Counting and printing tokens 
    Dictionary D;
    string s;
    for (int i = 1; getline(in, s); i++) {
        D.setValue(s, i);
    }

    out << D << '\n' << D.pre_string() << '\n';

    // close files
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
