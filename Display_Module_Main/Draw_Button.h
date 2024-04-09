#ifndef DrawB
#define DrawB

#include <iostream>
#include <string>
#include <vector>
#include "..\Object\Materials.h"
#include "..\Display_Module_Class\Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Draw_Button
{
public:
    bool Testmod = 1;

public:
    int Draw_cost = 10;

private:
    int highlight_id = 0;

public:
    vector<int> st_xy{0, 0};
    vector<int> Size{9, 4};
    void Output();

private:
    string Layer_name = "Map";
};

void Draw_Button::Output()
{
    vector<Pixel> Output_Map;
    vector <int> en_xy{st_xy[0]+Size[0]-1,st_xy[1]+Size[1]-1};
    Pixel temp_pixel;
    temp_pixel.colour=B_White;
    string temp=string("                 ")+"    Draw Card    "+"                 "+"                 ";
    for (int id=0;id<temp.size();id++){
        temp_pixel.text=temp[id];
        Output_Map.push_back(temp_pixel);
    }
    temp_pixel.colour=B_Green;
    for (int id=1;id<Size[0]*2-2;id++){
        temp_pixel.text="━";
        Output_Map[id]=temp_pixel;
        Output_Map[51+id]=temp_pixel;
    }
    temp_pixel.text="┏";
    Output_Map[0]=temp_pixel;
    temp_pixel.text="┓";
    Output_Map[16]=temp_pixel;
    temp_pixel.text="┗";
    Output_Map[51]=temp_pixel;
    temp_pixel.text="┛";
    Output_Map[67]=temp_pixel;
    temp_pixel.text="┃";
    Output_Map[17]=temp_pixel;
    Output_Map[34]=temp_pixel;
    Output_Map[33]=temp_pixel;
    Output_Map[50]=temp_pixel;
    temp_pixel.colour=B_White;
    for (int id=0;id<to_string(Draw_cost).size();id++){
        temp_pixel.text=to_string(Draw_cost)[id];
        Output_Map[40+id]=temp_pixel;
    }
    Output_Map[44]=Materials_Graphic(16);
    highlight_id= R_Main.Add_Textbox(1, highlight_id, Layer_name, Output_Map, st_xy, en_xy, 0);
}

#endif