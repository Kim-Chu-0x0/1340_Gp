#ifndef UPG
#define UPG

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "..\Display_Module_Class\Class_Pixel.h"
#include "Materials.h"
#include "Class_Buildings.h"

using namespace std;

class Upgrade
{
    // testing
private:
    bool TestMod = 0;
    bool TestText = 0;

public:
    int type = 0;
    int subtype = 0;
    int level = 0;
    double value = 0;
    vector <Pixel> description;

public:
    void Input_type(int id);
    void Text_Formation(int id);
};

// Type:
//  0 : Extra Card per draw (Min3 Max5)
//  1 : Extend Map Horizontaly
//  2 : Extend Map Vertically
//  3 : Extra Resource Output (All)
//  4 : Extra Resource Output (Specific Building)
//  5 : Reduce Resource Intakes (All)
//  6 : Reduce Resource Intakes (Specific Building)
//  7 : Increase Duration (All)
//  8 : Increase Duration (Specific Building)
//  9 : Extra Inventory Slot
//  10 : Increase Luck
//  11 : Increase Energy Regeneration
//  12 : Increase Maximum Energy
//  13 : Longer Preperation Time Before Disaster
//  14 : Increase Resource Output (Specific Type)
//  15 : Reduce Resource Intakes (Specific Type)
//  16 : Gain Extra Life
//  17 : Less Draw Consumption
//  18 : Receive T1 Resource Every Turn
//  19 : Receive 2 Random Upgrades
//  20 : Increase Duration (Specific Type)
void Upgrade::Input_type(int id)
{
    type=id;
    int express = 0;
    double constant_1 = 0;
    double constant_2 = 0;
    level = Upgrade_List[id][0] + 1;
    switch (id)
    {
    case 0:
        express = 1;
        break;
    case 1:
        express = 1;
        break;
    case 2:
        express = 1;
        break;
    case 3:
        express = 2;
        constant_1 = 18;
        constant_2 = 1.16;
        break;
    case 4:
        express = 2;
        constant_1 = 30;
        constant_2 = 1.25;
        subtype = rand() % Production_Building_number;
        level = Upgrade_List[id][subtype * 2] + 1;
        break;
    case 5:
        express = 2;
        constant_1 = 10;
        constant_2 = 0.71;
        break;
    case 6:
        express = 2;
        constant_1 = 20;
        constant_2 = 0.766;
        subtype = rand() % Processing_Building_number;
        level = Upgrade_List[id][subtype * 2] + 1;
        break;
    case 7:
        express = 2;
        constant_1 = 18;
        constant_2 = 1.16;
        break;
    case 8:
        express = 2;
        constant_1 = 30;
        constant_2 = 1.25;
        subtype = rand() % All_Building_number;
        level = Upgrade_List[id][subtype * 2] + 1;
        break;
    case 9:
        express = 1;
        break;
    case 10:
        express = 2;
        constant_1 = 10;
        constant_2 = 0.945;
        break;
    case 11:
        express = 2;
        constant_1 = 5;
        constant_2 = 0.92;
        break;
    case 12:
        express = 20;
        break;
    case 13:
        express = 1;
        break;
    case 14:
        express = 2;
        constant_1 = 25;
        constant_2 = 1.16;
        subtype = rand() % Production_Building_type;
        level = Upgrade_List[id][subtype * 2] + 1;
        break;
    case 15:
        express = 2;
        constant_1 = 15;
        constant_2 = 0.73;
        subtype = rand() % Processing_Building_type;
        level = Upgrade_List[id][subtype * 2] + 1;
        break;
    case 16:
        express = 1;
        break;
    case 17:
        express = 2;
        constant_1 = 12;
        constant_2 = 0.77;
        break;
    case 18:
        express = 2;
        constant_1 = 3;
        constant_2 = 0.92;
        break;
    case 19:
        express = 3;
        break;
    case 20:
        express = 2;
        constant_1 = 25;
        constant_2 = 1.16;
        subtype = rand() % All_Building_type;
        level = Upgrade_List[id][subtype * 2] + 1;
        break;

    default:
        cout << "(Input_type)Error: Unknown Upgrade id" << '\n';
        exit(0);
    };
    int temp;
    switch (express)
    {
    case 1:
        value = 1;
        break;
    case 2:
        temp=30*Upgrade_List[10][1];
        value = constant_1 * (pow(constant_2, pow(level, 0.5)));
        value *= ((85+(rand()%(temp)))/100.0);
        break;
    case 3:
        value = 1;
        break;
    }
    if (TestMod){
        cout<<'\n'<<"Upgrade value generation completed"<<'\n';
        cout<<"Type: "<<type<<'\n';;
        cout<<"Subtype: "<<subtype<<'\n';;
        cout<<"Level: "<<level<<'\n';;
        cout<<"Value: "<<value<<'\n';;
    }
    Text_Formation(id);
}

void Upgrade::Text_Formation(int id)
{
    vector <string> insert_list;
    string raw_text=",Level:-"+to_string(level)+",";
    string value_string =to_string(value).substr(0,4);
    switch (id)
    {
    case 0:
        raw_text+="when-you-draw-cards,Gain-a-extra-choice";
        break;
    case 1:
        raw_text+="extend-the-map-horizontally-by-1";
        break;
    case 2:
        raw_text+="extend-the-map-vertically-by-1";
        break;
    case 3:
        insert_list.push_back(value_string);
        raw_text+="Gain-//%-resource-boost,(Apply-to-all-buildings)";
        break;
    case 4:
        insert_list.push_back(Processing_Building_name_list[subtype]);
        insert_list.push_back(value_string);
        raw_text+="//-gain-//%,resource-boost";
        break;
    case 5:
        insert_list.push_back(value_string);
        raw_text+="Gain-//%-input-discount,(Apply-to-all-buildings)";
        break;
    case 6:
        insert_list.push_back(Production_Building_name_list[subtype]);
        insert_list.push_back(value_string);
        raw_text+="//-gain-//%,input-discount";
        break;
    case 7:
        insert_list.push_back(value_string);
        raw_text+="Gain-//%-lifespan,(Apply-to-all-buildings)";
        break;
    case 8:
        insert_list.push_back(All_Building_name_list[subtype]);
        insert_list.push_back(value_string);
        raw_text+="//-gain-//%,lifespan";
        break;
    case 9:
        raw_text+="Gain-an-extra-inventory-slot";
        break;
    case 10:
        insert_list.push_back(value_string);
        raw_text+="Luck-increase-by-//%";
        break;
    case 11:
        insert_list.push_back(value_string);
        raw_text+="Energy-regen-increase-by-//%";
        break;
    case 12:
        insert_list.push_back(value_string);
        raw_text+="Maximum-energy-increase-by-//";
        break;
    case 13:
        raw_text+="Longer-delay-between-disasters";
        break;
    case 14:
        insert_list.push_back(Production_Building_type_list[subtype]);
        insert_list.push_back(value_string);
        raw_text+="All-//-gain-//%,resource-boost";
        break;
    case 15:
        insert_list.push_back(Processing_Building_type_list[subtype]);
        insert_list.push_back(value_string);
        raw_text+="All-//-gain-//%,input-discount";
        break;
    case 16:
        raw_text+="Gain-one-extra-life,(once-per-game)";
        break;
    case 17:
        insert_list.push_back(value_string);
        raw_text+="Reduce-draw-cost-by-//%";
        break;
    case 18:
        insert_list.push_back(value_string);
        raw_text+="Receive-//-Tier-1,-resources-per-turn";
        break;
    case 19:
        raw_text+="Receive-2-Random-upgrades";
        break;
    case 20:
        insert_list.push_back(All_Building_type_list[subtype]);
        insert_list.push_back(value_string);
        raw_text+="All-//-gain-//%,lifespan";
        break;
    }
    int text_pos=0;
    string pros_text1,pros_text2;
    for (int id=0;id<insert_list.size();id++){
        for (;!(raw_text[text_pos]=='/'&&raw_text[text_pos+1]=='/');text_pos++){
            pros_text1+=raw_text[text_pos];
        }
        pros_text1+=insert_list[id];
        text_pos++;
        text_pos++;
    }
    for (;text_pos<raw_text.size();text_pos++){
        pros_text1+=raw_text[text_pos];
    }
    if (insert_list.size()==0){
        pros_text1=raw_text;
    }
    if (TestText){
        cout<<'\n'<<"pros_text1: "<<pros_text1<<'\n';
    }
    for (int id=0;id<pros_text1.size();id++){
        if (pros_text1[id]=='-'){
            pros_text2+="/s";
        }
        else{
            pros_text2+=pros_text1[id];
        }
    }
    if (TestText){
        cout<<'\n'<<"pros_text2: "<<pros_text2<<'\n';
    }
    pros_text1="";
    vector <Pixel> Output=To_Pixel(pros_text2);
    Pixel space;
    space.text="/s";
    int counter=0;
    for (int id=Output.size()-1;id>=0;id--){
        counter++;
        if (Output[id].text==","){
            Output[id]=space;
            for (int time = counter;time<33;time++){
                Output.insert(Output.begin()+id+counter,space);
            }
            counter=0;
        }
    }
    Output.erase(Output.begin());
    Output.push_back(space);
    description = Output;
    if (TestMod){
        cout<<'\n'<<"Upgrade description generation completed"<<'\n';
    }
    if (TestText){
        cout<<'\n'<<"Size: "<<Output.size()<<'\n';
    }
}

#endif