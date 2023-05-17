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
    D.moveFront();
    int i = 0;
    int h = (D.length() / 2);
    while(i < h){
        temp.insertBefore(D.moveNext());
        D.eraseBefore();
        i++;
    }

    temp.moveFront();
    int j = 0;
    while(j < temp.length()){
        D.moveNext();
        D.insertBefore(temp.moveNext());
        j++;
    }

}

int main(int argc, char* argv[]){
    //Checking for correct number of arguments
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " <deck size>" << endl;
        return 1;
    }

    //Setting to the deck
    int decksize = atoi(argv[1]);
    //Check to see if the argument is a positive value or not
    if(decksize < 1){
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
            cnt++;
            if(d.equals(copydeck)){
                break;
            }
        }
        cout << i << "\t\t\t\t" << cnt << endl;
    }
    return 1;
}




    

