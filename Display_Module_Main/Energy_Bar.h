#ifndef EGY_BAR
#define EGY_BAR

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "..\Object\Materials.h"
#include "..\Display_Module_Class\Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Energy_Bar
{
private:
    bool EGY_TestMod = 0;

protected:
    double EGY_Energy = 100;
    double EGY_Future_Energy = 0;

protected:
    void EGY_Output();
    vector<int> EGY_st_xy{0, 0};
    vector<int> EGY_Size{0, 2};
    string EGY_Layer_name = "Map";
private:
    int EGY_selectable;

private:
    int Text_Width = 4;
};

void Energy_Bar::EGY_Output()
{
    EGY_selectable=Selectable_List[2];
    vector<Pixel> Output_Map;
    string temp_s = "Energy:0000000";
    Pixel temp_P;
    temp_P.colour = B_White;
    for (int id = 0; id < EGY_Size[1] * ((Text_Width * 2) - 1); id++)
    {
        if (temp_s[id] == '0')
        {
            temp_P.text = "/s";
        }
        else
        {
            temp_P.text = temp_s[id];
        }
        Output_Map.push_back(temp_P);
    }
    Output_Map[10] = Materials_Graphic(16);
    vector<int> Textbox_en_xy{EGY_st_xy[0] + Text_Width - 1, EGY_st_xy[1] + EGY_Size[1] - 1};
    R_Main.Add_Textbox("", 0, 0, EGY_Layer_name, Output_Map, EGY_st_xy, Textbox_en_xy, 0);
    Output_Map.clear();
    Pixel P1_Pix, P2_Pix, P3_Pix;
    P1_Pix.text = P2_Pix.text = P3_Pix.text = "█";
    P1_Pix.colour = Yellow;
    int Bar_Size = EGY_Size[0] - Text_Width - 1;
    double P1 = (EGY_Energy / Upgrade_List[12][1]) * ((2 * (Bar_Size)) - 1);
    double P2;
    if (EGY_Future_Energy < 0)
    {
        P2 = P1;
        P1 -= (abs(EGY_Future_Energy) / Upgrade_List[12][1]) * ((2 * (Bar_Size)) - 1);
        P2_Pix.colour = H_Red;
    }
    else
    {
        P2 = ((EGY_Future_Energy / Upgrade_List[12][1]) * ((2 * (Bar_Size)) - 1)) + P1;
        P2_Pix.colour = H_Green;
    }
    P3_Pix.colour = Black;
    for (int y = 0; y < EGY_Size[1]; y++)
    {
        for (int x = 0; x < (2 * (Bar_Size)) - 1; x++)
        {
            if (x > P2)
            {
                Output_Map.push_back(P3_Pix);
            }
            else if (x > P1)
            {
                Output_Map.push_back(P2_Pix);
            }
            else
            {
                Output_Map.push_back(P1_Pix);
            }
        }
    }
    vector<int> st_xy{EGY_st_xy[0] + Text_Width + 1, EGY_st_xy[1]};
    vector<int> en_xy{EGY_st_xy[0] + EGY_Size[0] - 1, EGY_st_xy[1] + EGY_Size[1] - 1};
    R_Main.Add_Textbox("", 0, 0, EGY_Layer_name, Output_Map, st_xy, en_xy, 0);
}
#endif