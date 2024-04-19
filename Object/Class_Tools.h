#ifndef TOOL
#define TOOL

#include <iostream>
#include <string>
#include <vector>
#include "..\Display_Module_Class\Class_Pixel.h"
#include "Materials.h"

using namespace std;

class Tool
{
    // testing
private:
    bool TestMod = 0;

public:
    int type = 0;
    int value = 0;
    void Input_Type(int id);
};

void Tool::Input_Type(int id){
    type = id;
    int temp;
    switch (id)
    {
    case 2:
        temp=20*Upgrade_List[10][1];
        value=20+rand()%(temp);
        break;
    case 5:
        temp=30*Upgrade_List[10][1];
        value=20+rand()%(temp);
        break;
    case 6:
        temp=22*Upgrade_List[10][1];
        value=12+rand()%(temp);
        break;
    case 7:
        temp=14*Upgrade_List[10][1];
        value=5+rand()%(temp);
        break;
    default:
        value=1;
        break;
    }
    switch (id)
    { 
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    }
}

#endif