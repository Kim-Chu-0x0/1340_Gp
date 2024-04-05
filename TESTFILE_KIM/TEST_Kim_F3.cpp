//for testing output module
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include "..\Display_Module_Class\Class_Render.h"
#include "..\Control_Module_Main\Action_Process.h"
Action_Processor R_Main;
#include "..\Display_Module_Main\Map_Grid.h"

using namespace std;

void test(int x,int y);

Map_Grid Grid;

int main(){
    R_Main.Set_Size(50,50);
    R_Main.Add_Layer_object("Map",0);
    int x=1+rand()%4;
    int y=1+rand()%4;
    Grid.Set_Size(x,y);
    for (int A=0;A<99;A++){
        srand(A);
        test(x,y);
        int C=rand()%2;
        int D=rand()%2;
        Grid.Expand(C,D);
        x+=C;
        y+=D;
    }
    return 0;
}

void test(int x,int y){
    cout<<"\x1B[2J\x1B[H"<<flush;
    cout<<"\x1B[2J\x1B[H"<<flush;
    cout<<"\x1B[2J\x1B[H"<<flush;
    cout<<"\x1B[2J\x1B[H"<<flush;
    vector <Building> Item;
    Building TEMP;
    for (int id=0;id<x*y;id++){
        TEMP.type(rand()%6);
        Item.push_back(TEMP);
    }
    Grid.CoverAll_Biulding(Item);
    Grid.Output();
    R_Main.Move(1+rand()%4);
    R_Main.Render_Output();
    R_Main.Render_Print();
    cin.get();
    cin.get();
    //for(int x=0;x<22;x++){
    //    cout<<"\e[A";
    //}
    //cout<<flush;
}