#ifndef STT_DIS
#define STT_DIS

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Object/Materials.h"
#include "Object/Display_Module_CLass/Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Stat_Display
{
private:
    bool Stat_TestMod = 0;

protected:
    void Stat_Output();
    vector<int> Stat_st_xy{0, 36};
    vector<int> Stat_Size{23, 2};

private:
    vector<int> Size_P1{23, 2};

protected:
    string Stat_Layer_name = "Map";

private:
    int Stat_selectable;
};

void Stat_Display::Stat_Output()
{
    Pixel space;
    space.text = "/s";
    Stat_selectable = Selectable_List[7];
    vector<Pixel> Output_Map, Temp_1, Temp_2;
    string Text = "Number/sof/sturns/sbefore/sthe/snext/sdisaster:/s";
    for (int length = 0; length < 3; length++)
    {
        if (to_string(Corruption_gap - turn_counter).size() > length)
        {
            Text += to_string(Corruption_gap - turn_counter)[length];
        }
        else
        {
            Text += "/s";
        }
    }
    Temp_2 = To_Pixel(Text);

    if (Corruption_gap - turn_counter > 14)
    {
        Temp_2[Temp_2.size() - 1].colour = H_Green;
        Temp_2[Temp_2.size() - 2].colour = H_Green;
        Temp_2[Temp_2.size() - 3].colour = H_Green;
    }
    else if (Corruption_gap - turn_counter > 11)
    {
        Temp_2[Temp_2.size() - 1].colour = Green;
        Temp_2[Temp_2.size() - 2].colour = Green;
        Temp_2[Temp_2.size() - 3].colour = Green;
    }
    else if (Corruption_gap - turn_counter > 8)
    {
        Temp_2[Temp_2.size() - 1].colour = H_Yellow;
        Temp_2[Temp_2.size() - 2].colour = H_Yellow;
        Temp_2[Temp_2.size() - 3].colour = H_Yellow;
    }
    else if (Corruption_gap - turn_counter > 5)
    {
        Temp_2[Temp_2.size() - 1].colour = Yellow;
        Temp_2[Temp_2.size() - 2].colour = Yellow;
        Temp_2[Temp_2.size() - 3].colour = Yellow;
    }
    else if (Corruption_gap - turn_counter > 3)
    {
        Temp_2[Temp_2.size() - 1].colour = Red;
        Temp_2[Temp_2.size() - 2].colour = Red;
        Temp_2[Temp_2.size() - 3].colour = Red;
    }
    else
    {
        Temp_2[Temp_2.size() - 1].colour = B_Red;
        Temp_2[Temp_2.size() - 2].colour = B_Red;
        Temp_2[Temp_2.size() - 3].colour = B_Red;
    }

    for (int id = Temp_2.size(); id < (Size_P1[0] * 2) - 1; id++)
    {
        Temp_2.push_back(space);
    }
    Text = "Energy/slevel/sbouns:/s";
    if ((Other_Buffs[2] - 1) > 0)
    {
        Text += "+";
    }
    else if ((Other_Buffs[2] - 1) != 0)
    {
        Text += "-";
    }
    for (int length = 0; length < 4; length++)
    {
        if (to_string(abs(Other_Buffs[2] - 1) * 100).size() > length)
        {
            Text += to_string(abs(Other_Buffs[2] - 1) * 100)[length];
        }
        else
        {
            Text += "/s";
        }
    }
    Text += "%/s/s(to resources)";
    Temp_1 = To_Pixel(Text);
    for (int id = Temp_1.size(); id < (Size_P1[0] * 2) - 1; id++)
    {
        Temp_1.push_back(space);
    }

    if ((Other_Buffs[2] - 1) > 0)
    {
        Temp_1[20].colour = Green;
        Temp_1[21].colour = Green;
        Temp_1[22].colour = Green;
        Temp_1[23].colour = Green;
        Temp_1[24].colour = Green;
        Temp_1[25].colour = Green;
    }
    else if ((Other_Buffs[2] - 1) != 0)
    {
        Temp_1[20].colour = Red;
        Temp_1[21].colour = Red;
        Temp_1[22].colour = Red;
        Temp_1[23].colour = Red;
        Temp_1[24].colour = Red;
        Temp_1[25].colour = Red;
    }

    for (int id = 0; id < Temp_1.size(); id++)
    {
        Output_Map.push_back(Temp_1[id]);
    }
    for (int id = 0; id < Temp_2.size(); id++)
    {
        Output_Map.push_back(Temp_2[id]);
    }
    vector<int> en_xy{Stat_st_xy[0] + Size_P1[0] - 1, Stat_st_xy[1] + Size_P1[1] - 1};
    R_Main.Add_Textbox("", 0, 0, Stat_Layer_name, Output_Map, Stat_st_xy, en_xy, 0);
}
#endif