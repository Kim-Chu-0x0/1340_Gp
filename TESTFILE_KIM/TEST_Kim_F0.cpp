//for random testing
#include <string>
#include <iostream>
#include "../Object/Materials.h"

using namespace std;

int main(){
    string TT="88whxbdawhbuiduau78987654/01/08/07uuu/s";
    vector <Pixel> temp=To_Pixel(TT);
    for (int id=0;id<temp.size();id++){
        temp[id].print();
    }
}

