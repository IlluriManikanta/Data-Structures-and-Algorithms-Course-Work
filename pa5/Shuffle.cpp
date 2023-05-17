// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 5                       //
// Running List.cpp here      //
// ========================== //

#include <iostream>
#include "List.h"

using namespace std;

//Implemented accoding to the instructions porvided and TA guidance from TA office hours. 
void shuffle(List &D){
    List temp;
    int d_half = D.length() / 2;

    D.moveFront();
    int i = 0;
    while(i < d_half){
        temp.insertBefore(D.moveNext());
        D.eraseBefore();
        i++;
    }
    // for (int i = 0; i < d_half; i++) {
    //     temp.insertBefore(D.moveNext());
    //     D.eraseBefore();
    // }

    temp.moveFront();
    int j = 0;
    while(j < temp.length()){
        D.moveNext();
        D.insertBefore(temp.moveNext());
        j++;
    }
    // for (int i = 0; i < temp.length(); i++) {
    //     D.moveNext();
    //     D.insertBefore(temp.moveNext());
    // }

}

int main(int argc, char* argv[]){
    //Checking for correct number of arguments
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " <deck size>" << endl;
        return 1;
    }

    int decksize = atoi(argv[1]);
    if(decksize <=0){
        cerr << "Deck size must be a positive integer" << endl;
        return 1;
    }

    cout << "deck size\t\tshuffle count\n------------------------------" << endl;

    for(int i = 1; i <= decksize; i++){
        List d;


        for(int j = 1; j <= i; j++){
            d.insertBefore(j);
        }

        List copydeck = d;
        int cnt = 0;
        while(true){
            shuffle(d);
            // List temp;
            // int d_half = d.length() / 2;

            // d.moveFront();
            // for (int i = 0; i < d_half; i++) {
            //     temp.insertBefore(d.moveNext());
            //     d.eraseBefore();
            // }

            // temp.moveFront();
            // for (int i = 0; i < temp.length(); i++) {
            //     d.moveNext();
            //     d.insertBefore(temp.moveNext());
            // }
            cnt++;
            if(d.equals(copydeck)){
                break;
            }

        }
        cout << i << "\t\t\t\t" << cnt << endl;
    }
    return 1;
}




    

