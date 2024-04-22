#ifndef DrawB
#define DrawB

#include <iostream>
#include <string>
#include <vector>
#include "Object/Materials.h"
#include "Object/Display_Module_CLass/Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Draw_Button
{
private:
    bool Draw_Testmod = 0;

protected:
    int Draw_Draw_cost;
    bool Draw_Availability = 1;

private:
    int Draw_Draw_cost_base=20;
    int Draw_selectable;
    int Draw_highlight_id = 0;

protected:
    vector<int> Draw_st_xy{0, 0};
    vector<int> Draw_Size{9, 4};
    void Draw_Output();
    void Draw_Refresh_stat();
    string Draw_Layer_name = "Map";
};

void Draw_Button::Draw_Refresh_stat(){
    Draw_Draw_cost=Draw_Draw_cost_base*100/Upgrade_List[17][1];
}

void Draw_Button::Draw_Output()
{
    Draw_selectable=Selectable_List[0];
    vector<Pixel> Output_Map;
    vector<int> en_xy{Draw_st_xy[0] + Draw_Size[0] - 1, Draw_st_xy[1] + Draw_Size[1] - 1};
    Pixel temp_pixel;
    if (Draw_Availability){
        temp_pixel.colour = B_White;
    }
    else{
        temp_pixel.colour = B_Red;
    }
    string temp = string("00000000000000000") + "0000Draw0Card0000" + "00000000000000000" + "00000000000000000";
    for (int id = 0; id < temp.size(); id++)
    {
        if (temp[id] == '0')
        {
            temp_pixel.text = "/s";
        }
        else
        {
            temp_pixel.text = temp[id];
        }
        Output_Map.push_back(temp_pixel);
    }
    if (Draw_Availability){
        temp_pixel.colour = B_Green;
    }
    else{
        temp_pixel.colour = B_Yellow;
    }
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
    if (Draw_Availability){
        Draw_highlight_id = R_Main.Add_Textbox("Draw_T", Draw_selectable, Draw_highlight_id, Draw_Layer_name, Output_Map, Draw_st_xy, en_xy, 0);
    }
    else{
        Draw_highlight_id = R_Main.Add_Textbox("Draw_F", Draw_selectable, Draw_highlight_id, Draw_Layer_name, Output_Map, Draw_st_xy, en_xy, 0);
    }
}

#endif