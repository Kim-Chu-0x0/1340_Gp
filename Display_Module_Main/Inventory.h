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
    bool INV_Testmod = 0;

    // item access
protected:
    void INV_Fill_Item(int pos, Card item);
    void INV_Reset();
    void INV_Output();

    // Formating Data
protected:
    vector<int> INV_st_xy{0, 5};
    vector<int> INV_Size{0, 4};
    int INV_Max_Size = 11;

    // Other Data
protected:
    int selection;
    vector<Card> INV_item_list;
    vector<int> INV_highlight_id;
    string INV_Layer_name = "Map";
};

void Inventory::INV_Fill_Item(int pos, Card item){
    if (pos==-1){
        bool Found = 0;
        for (int id = 0; (id < Upgrade_List[9][1]) && (!Found); id++){
            if (INV_item_list[id].Type==0){
                INV_item_list[id]=item;
                Found = 1;
            }
        }
    }
    else{
        INV_item_list[pos]=item;
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
    selection = -1;
    if (INV_highlight_id[0] != 0)
    {
        for (int id = 0; id < INV_highlight_id.size(); id++)
        {
            if (R_Main.Highlight_Choice_Textbox_id == INV_highlight_id[id])
            {
                selection = id;
            }
        }
    }
    for (int id = 0; id < Upgrade_List[9][1]; id++)
    {
        vector<int> temp_St{INV_st_xy[0] + (id * (Size_of_icon[0] + 1)), INV_st_xy[1]};
        vector<int> temp_En{temp_St[0] + (Size_of_icon[0] - 1), temp_St[1] + (Size_of_icon[1] - 1)};
        INV_highlight_id[id] = R_Main.Add_Textbox("INV_Slot", 1, INV_highlight_id[id], INV_Layer_name, INV_item_list[id].Graphic, temp_St, temp_En, 0);
        if (INV_Testmod)
        {
            cout << '\n'
                 << "Item " << id << " id: " << INV_highlight_id[id] << '\n';
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
    if (selection != -1)
    {
        if(INV_item_list[selection].Type!=0){
            vector<int> temp_St{INV_st_xy[0] + ((selection - 1) * (Size_of_icon[0] + 1)), INV_st_xy[1] + (Size_of_icon[1] + 1)};
            if (selection == 0)
            {
                temp_St[0] += (Size_of_icon[0] + 1);
            }
            else if (selection == INV_item_list.size() - 1)
            {
                temp_St[0] -= (Size_of_icon[0] + 1);
            }
            vector<int> temp_En{temp_St[0] + INV_item_list[selection].Size_of_Description[0] - 1, temp_St[1] + INV_item_list[selection].Size_of_Description[1] - 1};
            R_Main.Add_Textbox("", 0, 0, INV_Layer_name, INV_item_list[selection].Description, temp_St, temp_En, 0);
        }
    }
}

#endif