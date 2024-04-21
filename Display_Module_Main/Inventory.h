#ifndef INV
#define INV

#include <iostream>
#include <string>
#include <vector>
#include "..\Object\Class_Card.h"
#include "..\Display_Module_Class\Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Inventory
{
    // testing
private:
    bool INV_Testmod = 1;

    // item access
protected:
    void INV_Fill_Item(int pos, Card item);
    void INV_Reset();
    void INV_Output();
    void INV_Discard();
    Card INV_Slot_Output();

    // Formating Data
protected:
    vector<int> INV_st_xy{0, 5};
    vector<int> INV_Size{0, 4};
    int INV_Max_Size = 11;

    // Other Data
protected:
    int INV_selection;
    int INV_selection_id;
    vector<Card> INV_item_list;
    vector<int> INV_highlight_id;
    int INV_button_highlight_id;
    string INV_Layer_name = "Map";
    string INV_Popup_Layer_Name = "PopUp_Map";
    int INV_Phase = 0;

private:
    int INV_selectable;
};

void Inventory::INV_Discard(){
    Card temp;
    temp.Blank();
    INV_item_list[INV_selection]=temp;
}

Card Inventory::INV_Slot_Output(){
    return INV_item_list[INV_selection];
}

void Inventory::INV_Fill_Item(int pos, Card item)
{
    if (pos == -1)
    {
        bool Found = 0;
        for (int id = 0; (id < Upgrade_List[9][1]) && (!Found); id++)
        {
            if (INV_item_list[id].Type == 0)
            {
                INV_item_list[id] = item;
                Found = 1;
            }
        }
    }
    else
    {
        INV_item_list[pos] = item;
    }
}

void Inventory::INV_Reset()
{
    Card temp;
    temp.Blank();
    for (int id = 0; id < INV_Max_Size; id++)
    {
        INV_item_list.push_back(temp);
        INV_highlight_id.push_back(0);
    }
}

void Inventory::INV_Output()
{
    for (int id = 0; id < Upgrade_List[9][1]; id++){
        if(INV_item_list[id].Type==3){
            INV_item_list[id].Refresh_stat();
        }
    }
    INV_selectable = Selectable_List[3];
    if (INV_Phase == 0)
    {
        INV_selection = -1;
        INV_selection_id = 1;
        if ((R_Main.Highlight_Choice_Layer == INV_Layer_name) && (INV_highlight_id[0] != 0))
        {
            for (int id = 0; id < INV_highlight_id.size(); id++)
            {
                if (R_Main.Highlight_Choice_Textbox_id[R_Main.AP_Layer_Location] == INV_highlight_id[id])
                {
                    INV_selection = id;
                    INV_selection_id = INV_highlight_id[id];
                }
            }
        }
        if (INV_Testmod){
            cout<<'\n'<<"Select: "<<INV_selection<<'\n';
        }
    }
    for (int id = 0; id < Upgrade_List[9][1]; id++)
    {
        vector<int> temp_St{INV_st_xy[0] + (id * (Size_of_icon[0] + 1)), INV_st_xy[1]};
        vector<int> temp_En{temp_St[0] + (Size_of_icon[0] - 1), temp_St[1] + (Size_of_icon[1] - 1)};
        if (INV_Phase == 0)
        {
            if (INV_selection == id)
            {
                if (INV_item_list[INV_selection].Type != 0)
                {
                    INV_highlight_id[id] = R_Main.Add_Textbox("INV_Slot", INV_selectable, INV_highlight_id[id], INV_Layer_name, INV_item_list[id].Graphic, temp_St, temp_En, 0);
                }
                else
                {
                    INV_highlight_id[id] = R_Main.Add_Textbox("INV_Slot_NULL", INV_selectable, INV_highlight_id[id], INV_Layer_name, INV_item_list[id].Graphic, temp_St, temp_En, 0);
                }
            }
            else
            {
                INV_highlight_id[id] = R_Main.Add_Textbox("INV_Slot", INV_selectable, INV_highlight_id[id], INV_Layer_name, INV_item_list[id].Graphic, temp_St, temp_En, 0);
            }
            if (INV_Testmod)
            {
                cout << '\n'
                     << "Item " << id << " id: " << INV_highlight_id[id] << '\n';
            }
        }
        else if ((INV_Phase == 1)||(INV_Phase == 2))
        {
            R_Main.Add_Textbox("", 0, 0, INV_Layer_name, INV_item_list[id].Graphic, temp_St, temp_En, 0);
        }
    }
    vector<int> St{INV_st_xy[0] + (int(Upgrade_List[9][1]) * (Size_of_icon[0] + 1)), INV_st_xy[1]};
    vector<int> En{Screen_Size[0] - 1, St[1] + (Size_of_icon[1] - 1)};
    Pixel temp_P;
    temp_P.text = "/s";
    vector<Pixel> blank_des;
    for (int id = 0; id < ((((En[0] - St[0] + 1) * 2) - 1) * (En[1] - St[1] + 1)); id++)
    {
        blank_des.push_back(temp_P);
    }
    R_Main.Add_Textbox("", 0, 0, INV_Layer_name, blank_des, St, En, 0);
    if ((INV_Phase == 0) && (INV_selection != -1))
    {
        if (INV_item_list[INV_selection].Type != 0)
        {
            vector<int> temp_St{INV_st_xy[0] + ((INV_selection - 1) * (Size_of_icon[0] + 1)), INV_st_xy[1] - INV_item_list[INV_selection].Size_of_Description[1] - 1};
            if (INV_selection == 0)
            {
                temp_St[0] += (Size_of_icon[0] + 1);
            }
            else if (INV_selection == INV_item_list.size() - 1)
            {
                temp_St[0] -= (Size_of_icon[0] + 1);
            }
            vector<int> temp_En{temp_St[0] + INV_item_list[INV_selection].Size_of_Description[0] - 1, temp_St[1] + INV_item_list[INV_selection].Size_of_Description[1] - 1};
            R_Main.Add_Textbox("", 0, 0, INV_Popup_Layer_Name, INV_item_list[INV_selection].Description, temp_St, temp_En, 0);
        }
    }
    if (INV_Phase == 1)
    {
        if (INV_Testmod)
        {
            cout << '\n'
                 << "Pop_up button generation" << '\n';
        }
        string Text = "0000000000000000000Press0E0to0discard00000000000000000000";
        vector<Pixel> T_Pixel_List;
        Pixel T_Pixel;
        T_Pixel.colour = Red;
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
        vector<int> temp_St{INV_st_xy[0] + ((INV_selection) * (Size_of_icon[0] + 1)) - 3, INV_st_xy[1] - 4};
        if (INV_selection == 0)
        {
            temp_St[0] += 3;
        }
        else if (INV_selection == INV_item_list.size() - 1)
        {
            temp_St[0] -= 2;
        }
        vector<int> temp_En{temp_St[0] + 9, temp_St[1] + 2};
        INV_button_highlight_id = R_Main.Add_Textbox("INV_Discard_CFM", INV_selectable, INV_button_highlight_id, INV_Popup_Layer_Name, T_Pixel_List, temp_St, temp_En, 0);
    }
    else if (INV_Phase == 2)
    {
        if (INV_Testmod)
        {
            cout << '\n'
                 << "Pop_up button generation" << '\n';
        }
        string Text = "000000000000000000000Press0E0to0Use0000000000000000000000";
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
        vector<int> temp_St{INV_st_xy[0] + ((INV_selection) * (Size_of_icon[0] + 1)) - 3, INV_st_xy[1] - 4};
        if (INV_selection == 0)
        {
            temp_St[0] += 3;
        }
        else if (INV_selection == INV_item_list.size() - 1)
        {
            temp_St[0] -= 2;
        }
        vector<int> temp_En{temp_St[0] + 9, temp_St[1] + 2};
        INV_button_highlight_id = R_Main.Add_Textbox("INV_Use_CFM", INV_selectable, INV_button_highlight_id, INV_Popup_Layer_Name, T_Pixel_List, temp_St, temp_En, 0);
    }
}

#endif