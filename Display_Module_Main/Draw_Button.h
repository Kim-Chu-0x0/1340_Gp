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
private:
    bool Draw_Testmod = 0;

protected:
    int Draw_Draw_cost = 10;

private:
    int Draw_highlight_id = 0;

protected:
    vector<int> Draw_st_xy{0, 0};
    vector<int> Draw_Size{9, 4};
    void Draw_Output();

private:
    string Draw_Layer_name = "Map";
};

void Draw_Button::Draw_Output()
{
    vector<Pixel> Output_Map;
    vector<int> en_xy{Draw_st_xy[0] + Draw_Size[0] - 1, Draw_st_xy[1] + Draw_Size[1] - 1};
    Pixel temp_pixel;
    temp_pixel.colour = B_White;
    string temp = string("                 ") + "    Draw Card    " + "                 " + "                 ";
    for (int id = 0; id < temp.size(); id++)
    {
        temp_pixel.text = temp[id];
        Output_Map.push_back(temp_pixel);
    }
    temp_pixel.colour = B_Green;
    for (int id = 1; id < Draw_Size[0] * 2 - 2; id++)
    {
        temp_pixel.text = "━";
        Output_Map[id] = temp_pixel;
        Output_Map[51 + id] = temp_pixel;
    }
    temp_pixel.text = "┏";
    Output_Map[0] = temp_pixel;
    temp_pixel.text = "┓";
    Output_Map[16] = temp_pixel;
    temp_pixel.text = "┗";
    Output_Map[51] = temp_pixel;
    temp_pixel.text = "┛";
    Output_Map[67] = temp_pixel;
    temp_pixel.text = "┃";
    Output_Map[17] = temp_pixel;
    Output_Map[34] = temp_pixel;
    Output_Map[33] = temp_pixel;
    Output_Map[50] = temp_pixel;
    temp_pixel.colour = B_White;
    for (int id = 0; id < to_string(Draw_Draw_cost).size(); id++)
    {
        temp_pixel.text = to_string(Draw_Draw_cost)[id];
        Output_Map[40 + id] = temp_pixel;
    }
    Output_Map[44] = Materials_Graphic(16);
    Draw_highlight_id = R_Main.Add_Textbox("Draw", 1, Draw_highlight_id, Draw_Layer_name, Output_Map, Draw_st_xy, en_xy, 0);
}

#endif