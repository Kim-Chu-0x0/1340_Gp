//for testing output module
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include "..\Display_Module_Class\Class_Render.h"
Render R_Main;
#include "..\Display_Module_Main\Map_Grid.h"

using namespace std;

void test();

int main(){
    R_Main.Set_Size(30,30);
    R_Main.Add_Layer_object("Map",0);
    for (int x=0;x<99;x++){
        srand(x);
        test();
    }
    return 0;
}

void test(){
    int x=1+rand()%4;
    int y=1+rand()%4;
    Map_Grid Grid;
    Grid.Set_Size(x,y);
    vector <Building> Item;
    Building TEMP;
    for (int id=0;id<x*y;id++){
        TEMP.type(rand()%6);
        Item.push_back(TEMP);
    }
    Grid.CoverAll_Biulding(Item);
    cout<<"\x1B[2J\x1B[H"<<flush;
    Grid.Output();
    R_Main.Render_Output();
    R_Main.Render_Print();
    cin.get();
    cin.get();
    //for(int x=0;x<22;x++){
    //    cout<<"\e[A";
    //}
    //cout<<flush;
}