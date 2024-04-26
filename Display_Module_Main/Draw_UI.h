#ifndef DrawUI
#define DrawUI

#include <iostream>
#include <string>
#include <vector>
#include "Object/Materials.h"
#include "Object/Display_Module_CLass/Class_Render.h"
#include "Object/Class_Card.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Draw_UI
{
private:
    bool DUI_Testmod = 0;

private:
    vector<int> DUI_highlight_id;
    int DUI_selectable;

protected:
    int DUI_Phase = 0;
    vector<int> DUI_st_xy{0, 0};
    vector<int> DUI_Size{0, 0};
    vector<Card> DUI_item_list;
    void DUI_Output();
    void DUI_Draw_Card();
    Card DUI_Draw_Output();
    void DUI_Clear()
    {
        DUI_Phase = 0;
        DUI_item_list.clear();
    }

private:
    int selection = 0;
    void DUI_Refresh_Pos();

protected:
    string DUI_Layer_name = "PopUp_Map";
};

Card Draw_UI::DUI_Draw_Output()
{
    return DUI_item_list[selection];
}

void Draw_UI::DUI_Draw_Card()
{
    DUI_Clear();
    for (int no = 0; no < Upgrade_List[0][1]; no++)
    {
        Card temp;
        temp.Random();
        DUI_item_list.push_back(temp);
        DUI_highlight_id.push_back(0);
    }
}

void Draw_UI::DUI_Refresh_Pos()
{
    DUI_Size[0] = (DUI_item_list.size() * (Size_of_icon[0] + 1)) - 1;
    DUI_Size[1] = 5 + DUI_item_list[selection].Size_of_Description[1];
    DUI_st_xy[0] = (Screen_Size[0] / 2) - (DUI_Size[0] / 2);
    DUI_st_xy[1] = (Screen_Size[1] / 2) - (DUI_Size[1] / 2);
}

void Draw_UI::DUI_Output()
{
    if (DUI_Phase == 0)
    {
        if (DUI_Testmod)
        {
            cout << '\n'
                 << "DUI Phase 0" << '\n';
        }
        selection = 0;
        if (DUI_highlight_id[0] != 0)
        {
            for (int id = 0; id < DUI_highlight_id.size(); id++)
            {
                if (R_Main.Highlight_Choice_Textbox_id[R_Main.AP_Layer_Location] == DUI_highlight_id[id])
                {
                    selection = id;
                }
            }
        }
    }
    else if (DUI_Phase == 1)
    {
        if (DUI_Testmod)
        {
            cout << '\n'
                 << "DUI Phase 1" << '\n';
        }
    }

    DUI_selectable = Selectable_List[1];
    DUI_Refresh_Pos();

    for (int id = 0; id < DUI_item_list.size(); id++)
    {
        vector<int> temp_St{DUI_st_xy[0] + (id * (Size_of_icon[0] + 1)), DUI_st_xy[1]};
        vector<int> temp_En{temp_St[0] + (Size_of_icon[0] - 1), temp_St[1] + (Size_of_icon[1] - 1)};
        if (DUI_Phase == 0)
        {
            DUI_highlight_id[id] = R_Main.Add_Textbox("Card_Draw", DUI_selectable, DUI_highlight_id[id], DUI_Layer_name, DUI_item_list[id].Graphic, temp_St, temp_En, 0);
            if (DUI_Testmod)
            {
                cout << '\n'
                     << "Item " << id << " id: " << DUI_highlight_id[id] << '\n';
            }
        }
        else if (DUI_Phase == 1)
        {
            R_Main.Add_Textbox("", 0, 0, DUI_Layer_name, DUI_item_list[id].Graphic, temp_St, temp_En, 0);
        }
    }

    if (DUI_Testmod)
    {
        cout << '\n'
             << "DUI first part Outputed" << '\n';
    }
    vector<int> temp_St{DUI_st_xy[0] + ((selection - 1) * (Size_of_icon[0] + 1)), DUI_st_xy[1] + (Size_of_icon[1] + 1)};
    if (selection == 0)
    {
        temp_St[0] += (Size_of_icon[0] + 1);
    }
    else if (selection == DUI_item_list.size() - 1)
    {
        temp_St[0] -= (Size_of_icon[0] + 1);
    }
    vector<int> temp_En{temp_St[0] + DUI_item_list[selection].Size_of_Description[0] - 1, temp_St[1] + DUI_item_list[selection].Size_of_Description[1] - 1};
    R_Main.Add_Textbox("", 0, 0, DUI_Layer_name, DUI_item_list[selection].Description, temp_St, temp_En, 0);
    if (DUI_Testmod)
    {
        cout << '\n'
             << "DUI Output completed" << '\n';
    }

    if (DUI_Phase == 1)
    {
        string Text = "0000000000000000000Press0E0to0confirm00000000000000000000";
        vector<Pixel> T_Pixel_List;
        Pixel T_Pixel;
        T_Pixel.colour = Green;
        for (int id = 0; id < Text.size(); id++)
        {
            if (Text[id] == '0')
            {
                T_Pixel.text = "/s";
            }
            else
            {
                T_Pixel.text = Text[id];
            }
            T_Pixel_List.push_back(T_Pixel);
        }
        temp_St[0] = (Screen_Size[0] / 2) - 4;
        temp_En[0] = temp_St[0] + 9;
        temp_En[1] = DUI_st_xy[1] - 3;
        temp_St[1] = temp_En[1] - 2;
        R_Main.Add_Textbox("Card_Draw_CFM", DUI_selectable, 0, DUI_Layer_name, T_Pixel_List, temp_St, temp_En, 0);
    }
}

#endif