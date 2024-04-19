#ifndef CARD
#define CARD

#include <iostream>
#include <string>
#include <vector>
#include "Class_Buildings.h"
#include "Class_Upgrade.h"
#include "Class_Tools.h"

using namespace std;

const vector <int> Size_of_icon{5,4};

class Card
{
    // testing
private:
    bool TestMod = 0;

public:
    void Random();
    void Blank();

public:
    vector <Pixel> Graphic,Description,Detail_in_Inv;
    vector <int> Size_of_Description{17,0};
    int Type = 0;
private:
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
            if (temp_vector[id]=="0"){
                temp.text="/s";
            }
            else{
            temp.text=temp_vector[id];
            }
            Graphic.push_back(temp);
        }
        Description=U_Data.description;
        Size_of_Description[1]=U_Data.description.size()/33;
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
            if (temp_vector[id]=="0"){
                temp.text="/s";
            }
            else{
            temp.text=temp_vector[id];
            }
            Graphic.push_back(temp);
        }
        Size_of_Description[1]=0;
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
            if (temp_vector[id]=="0"){
                temp.text="/s";
            }
            else{
            temp.text=temp_vector[id];
            }
            Graphic.push_back(temp);
        }
        Description=B_Data.description;
        Size_of_Description[1]=B_Data.description.size()/33;
    }
    if (TestMod){
        cout<<'\n'<<"Card type "<<Type<<" generated"<<'\n';
        cout<<"Description Size: "<<Size_of_Description[0]<<' '<<Size_of_Description[1]<<'\n';
    }
}

void Card::Blank()
{
    Pixel space;
    space.text="/s";
    Graphic.clear();
    for (int id=0;id<(((Size_of_icon[0]*2)-1)*Size_of_icon[1]);id++){
        Graphic.push_back(space);
    }
}

#endif