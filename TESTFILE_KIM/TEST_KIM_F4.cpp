//for testing input module
#include <iostream>
#include <string>
#include <vector>
#include "..\Control_Module_Main\Action_Process.h"
Action_Processor R_Main;
#include "..\Display_Module_Main\Map_Grid.h"
Map_Grid Grid;
#include "..\Control_Module_Main\Input.h"
Input I_Main;

using namespace std;

int main(){
    R_Main.Set_Size(50,50);
    R_Main.Add_Layer_object("Map",2);
    R_Main.Add_Layer_object("PopUp",1);
    R_Main.Add_Layer_object("Setting",0);
    int x=1+rand()%4;
    int y=1+rand()%4;
    Building TEMP;
    vector <Building> Item;
    for (int id=0;id<x*y;id++){
        TEMP.type(rand()%6);
        Item.push_back(TEMP);
    }
    Grid.Set_Size(x,y);
    Grid.CoverAll_Biulding(Item);
    cout<<"\e[A";
    for (int ff=0;ff<20;ff++){
        I_Main.Read_input();
        I_Main.Execute_Command();
    }
}