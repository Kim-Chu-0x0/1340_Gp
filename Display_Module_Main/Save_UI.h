#ifndef SUI
#define SUI

#include <iostream>
#include <string>
#include <vector>
#include "Object/Display_Module_CLass/Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Save_UI
{
private:
    bool SUI_Testmod = 1;

private:
    vector<int> SUI_highlight_id{0, 0, 0, 0};
    int SUI_selectable = 1;

protected:
    vector<int> SUI_st_xy{0, 0};
    vector<int> SUI_Size{80, 40};
    void SUI_Output();
    int SUI_Phase;

protected:
    string SUI_Layer_name = "Setting";
};

void Save_UI::SUI_Output()
{
    if (SUI_Testmod){
        cout<<'\n'<<"Save number: "<<Save_no<<'\n';
        cout<<'\n'<<"Save Existence: "<<Save_Existence[Save_no]<<'\n';
    }
    string temp_string = string("000000000000000") + "0Save0Selected0" + "000000000000000";
    vector<Pixel> Output_Map;
    Pixel temp;
    for (int id = 0; id < temp_string.size(); id++)
    {
        if (temp_string[id] == '0')
        {
            temp.text = "/s";
        }
        else
        {
            temp.text = temp_string[id];
        }
        Output_Map.push_back(temp);
    }
    vector<int> st_xy{SUI_st_xy[0] + (SUI_Size[0] / 2) - 4, 12};
    vector<int> en_xy{st_xy[0] + 7, st_xy[1] + 2};
    R_Main.Add_Textbox("", 0, 0, SUI_Layer_name, Output_Map, st_xy, en_xy, 0);
    Output_Map.clear();
    if (SUI_Phase == 0)
    {
        if (Save_no == -1)
        {
            temp_string = string("000000000000000") + "000000000000000" + "0000New0Game000" + "000000000000000" + "000000000000000";
        }
        else if (Save_no == 0)
        {
            temp_string = string("000000000000000") + "000Auto0Save000" + "0000State:00000";
            if (Save_Existence[0])
            {
                temp_string += "00000Exist00000";
                temp_string += "000000000000000";
            }
            else
            {
                temp_string += "00000Empty00000";
                temp_string += "000000000000000";
            }
        }
        else
        {
            string Text = to_string(Save_no);
            temp_string = string("000000000000000") + "000Save0No0" + Text + "000" + "0000State:00000";
            if (Save_Existence[Save_no])
            {
                temp_string += "00000Exist00000";
                temp_string += "000000000000000";
            }
            else
            {
                temp_string += "00000Empty00000";
                temp_string += "000000000000000";
            }
        }
    }
    if (SUI_Phase == 1)
    {
        string Text = to_string(Save_no);
        temp_string = string("000000000000000") + "000Save0No0" + Text + "000" + "0000State:00000";
        if (Save_Existence[Save_no])
        {
            temp_string += "0000Occupied000";
            temp_string += "000000000000000";
        }
        else
        {
            temp_string += "00000Empty00000";
            temp_string += "000000000000000";
        }
    }
    for (int id = 0; id < temp_string.size(); id++)
    {
        if (temp_string[id] == '0')
        {
            temp.text = "/s";
        }
        else
        {
            temp.text = temp_string[id];
        }
        if (id > 44 && id < 60)
        {
            if (SUI_Phase == 0)
            {
                if (Save_Existence[Save_no])
                {
                    temp.colour = Green;
                }
                else
                {
                    temp.colour = Yellow;
                }
            }
            else if (SUI_Phase == 1)
            {
                if (Save_Existence[Save_no])
                {
                    temp.colour = Yellow;
                }
                else
                {
                    temp.colour = Green;
                }
            }
        }
        else
        {
            temp.colour = White;
        }
        Output_Map.push_back(temp);
    }
    st_xy[1] += 4;
    en_xy[1] += 6;
    R_Main.Add_Textbox("", 0, 0, SUI_Layer_name, Output_Map, st_xy, en_xy, 0);

    temp.colour = White;
    temp_string = string("000") + "000" + "0<0" + "000" + "000";
    Output_Map.clear();
    for (int id = 0; id < temp_string.size(); id++)
    {
        if (temp_string[id] == '0')
        {
            temp.text = "/s";
        }
        else
        {
            temp.text = temp_string[id];
        }
        Output_Map.push_back(temp);
    }
    st_xy[0] -= 3;
    en_xy[0] = st_xy[0] + 1;
    SUI_highlight_id[0] = R_Main.Add_Textbox(string("Save_Left_") + to_string(SUI_Phase), SUI_selectable, SUI_highlight_id[0], SUI_Layer_name, Output_Map, st_xy, en_xy, 0);
    temp_string = string("000") + "000" + "0>0" + "000" + "000";
    Output_Map.clear();
    for (int id = 0; id < temp_string.size(); id++)
    {
        if (temp_string[id] == '0')
        {
            temp.text = "/s";
        }
        else
        {
            temp.text = temp_string[id];
        }
        Output_Map.push_back(temp);
    }
    st_xy[0] += 12;
    en_xy[0] = st_xy[0] + 1;
    SUI_highlight_id[1] = R_Main.Add_Textbox(string("Save_Right_") + to_string(SUI_Phase), SUI_selectable, SUI_highlight_id[1], SUI_Layer_name, Output_Map, st_xy, en_xy, 0);

    if ((SUI_Phase == 1)||((Save_no != -1) && (Save_Existence[Save_no] && SUI_Phase == 0)))
    {
        if (SUI_Phase == 0)
        {
            temp_string = string("000000000000000") + "00Delete0Save00" + "000000000000000";
        }
        else if (SUI_Phase == 1)
        {
            if (Save_Existence[Save_no])
            {
                temp_string = string("000000000000000") + "00000Cover00000" + "000000000000000";
            }
            else
            {
                temp_string = string("000000000000000") + "000Save0Game000" + "000000000000000";
            }
        }
        Output_Map.clear();
        for (int id = 0; id < temp_string.size(); id++)
        {
            if (temp_string[id] == '0')
            {
                temp.text = "/s";
            }
            else
            {
                temp.text = temp_string[id];
            }
            Output_Map.push_back(temp);
        }
        st_xy[0] -= 9;
        en_xy[0] = st_xy[0] + 7;
        st_xy[1] += 6;
        en_xy[1] = st_xy[1] + 2;
        if (SUI_Phase == 0)
        {
            SUI_highlight_id[2] = R_Main.Add_Textbox("Clear_Save", SUI_selectable, SUI_highlight_id[2], SUI_Layer_name, Output_Map, st_xy, en_xy, 0);
        }
        else if (SUI_Phase == 1)
        {
            SUI_highlight_id[2] = R_Main.Add_Textbox("Save_Game", SUI_selectable, SUI_highlight_id[2], SUI_Layer_name, Output_Map, st_xy, en_xy, 0);
        }
        if (SUI_Phase == 0)
        {
        }
    }
}

#endif