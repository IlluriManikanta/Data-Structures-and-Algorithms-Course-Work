// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 7                       //
// WordFrequency              //
// ========================== //

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }

    ifstream in(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return EXIT_FAILURE;
    }

    ofstream out(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return EXIT_FAILURE;
    }

    Dictionary D;

    int line_count = 0;
    string line;
    string tokenBuffer;
    string token;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    size_t begin, end, len;

    while (getline(in, line)) {
        line_count++;
        len = line.length();

        int token_count = 0;
        tokenBuffer = "";

        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end - begin);

        while (!token.empty()) {
            token_count++;

            for (char& c : token) {
                c = tolower(c);
            }

            if (D.contains(token)) {
                D.setValue(token, D.getValue(token) + 1);
            } else {
                D.setValue(token, 1);
            }

            begin = min(line.find_first_not_of(delim, end + 1), len);
            end = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end - begin);
        }
    }

    out << D << "\n";
    in.close();
    out.close();

    return EXIT_SUCCESS;
}
