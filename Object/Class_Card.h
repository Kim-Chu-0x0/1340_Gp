#ifndef CARD
#define CARD

#include <iostream>
#include <string>
#include <vector>
#include "Class_Buildings.h"
#include "Class_Upgrade.h"
#include "Class_Tools.h"

using namespace std;

class Card
{
    // testing
private:
    bool TestMod = 0;

public:
    void Random();

public:
    vector <Pixel> Graphic;
    vector <Pixel> Description;
    vector <Pixel> Detail_in_Inv;
private:
    int Type = 0;
    Building B_Data;
    Tool T_Data;
    Upgrade U_Data;
};

//Locate in Class_Card.h
void Card::Random(){
    int RNG=rand()%(Sum_Upgrade_Weighting+Sum_Tool_Weighting+Sum_Building_Weighting);
    int Choice;
    for (Choice=0;RNG>=0;Choice++){
        RNG-=Upgrade_Weighting[Choice];
    }
    for (Choice=0;RNG>=0;Choice++){
        RNG-=Tool_Weighting[Choice];
    }
    for (Choice=0;RNG>=0;Choice++){
        RNG-=Building_Weighting[Choice];
    }
}

#endif