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
    vector <Pixel> Graphic,Description,Detail_in_Inv;
    vector <int> Size_of_Description{0,0};
private:
    int Type = 0;
    Building B_Data;
    Tool T_Data;
    Upgrade U_Data;
};

//Locate in Class_Card.h
void Card::Random(){
    Graphic.clear();
    int RNG=rand()%(Sum_Upgrade_Weighting+Sum_Tool_Weighting+Sum_Building_Weighting);
    int Choice;
    if (RNG<Sum_Upgrade_Weighting){//Upgrade
        Type=1;
        for (Choice=0;RNG>=0;Choice++){
            RNG-=Upgrade_Weighting[Choice];
        }
        U_Data.Input_type(Choice);
        vector<string> temp_vector{
            "0","0","0","╔","═","╗","0","0","0",
            "0","╔","═","╝","0","╚","═","╗","0",
            "0","╚","═","╗","0","╔","═","╝","0",
            "0","0","0","╚","═","╝","0","0","0"
        };
        Pixel temp;
        temp.colour=Green;
        for (int id=0;id<temp_vector.size();id++){
            temp.text=temp_vector[id];
            Graphic.push_back(temp);
        }
    }
    else if(RNG<(Sum_Upgrade_Weighting+Sum_Tool_Weighting)){//Tool
        RNG-=Sum_Upgrade_Weighting;
        Type=2;
        for (Choice=0;RNG>=0;Choice++){
            RNG-=Tool_Weighting[Choice];
        }
        T_Data.Input_Type(Choice);
        vector<string> temp_vector{
            "0","╔","═","═","═","═","═","╗","0",
            "0","║","0","═","╦","═","0","║","0",
            "0","║","0","═","╩","═","0","║","0",
            "0","╚","═","═","═","═","═","╝","0"
        };
        Pixel temp;
        temp.colour=Blue;
        for (int id=0;id<temp_vector.size();id++){
            temp.text=temp_vector[id];
            Graphic.push_back(temp);
        }
    }
    else{//Building
        RNG-=Sum_Upgrade_Weighting;
        RNG-=Sum_Tool_Weighting;
        Type=3;
        for (Choice=0;RNG>=0;Choice++){
            RNG-=Building_Weighting[Choice];
        }
        B_Data.Input_type(Choice);
        vector<string> temp_vector{
            "0","╦","0","0","╦","0","0","╦","0",
            "0","║","0","0","║","0","0","║","0",
            "0","║","0","0","║","0","0","║","0",
            "0","╩","0","0","╩","0","0","╩","0"
        };
        Pixel temp;
        temp.colour=Yellow;
        for (int id=0;id<temp_vector.size();id++){
            temp.text=temp_vector[id];
            Graphic.push_back(temp);
        }
    }
}

#endif