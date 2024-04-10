#ifndef RES_DIS
#define RES_DIS

#include <iostream>
#include <string>
#include <vector>
#include "..\Object\Materials.h"
#include "..\Display_Module_Class\Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Resources_Display
{
private:
    bool Res_TestMod = 0;

protected:
    // quantity can be negative
    void Res_Add_Resources(int type, int quantity);

protected:
    vector<int> Res_Resource_List{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int Res_Energy;

protected:
    void Res_Output();
    vector<int> Res_st_xy{0, 0};
    vector<int> Res_Size{9, 8};

private:
    string Res_Layer_name = "Map";
};

void Resources_Display::Res_Add_Resources(int type, int quantity)
{
    Res_Resource_List[type] += quantity;
}

void Resources_Display::Res_Output()
{
    vector<Pixel> Output_Map;
    Pixel Space, Semicolon;
    Space.text = " ";
    Semicolon.text = ":";
    int Y_Size = (Res_Size[1]) + (Res_Resource_List.size() % 2);
    if (Res_TestMod)
    {
        cout << '\n'
             << "Y_Size: " << Y_Size << '\n';
    }
    for (int id = 0; id < Y_Size; id++)
    {
        Pixel temp;
        Output_Map.push_back(Materials_Graphic(id));
        Output_Map.push_back(Space);
        Output_Map.push_back(Semicolon);
        Output_Map.push_back(Space);
        for (int length = 0; length < 4; length++)
        {
            if (to_string(Res_Resource_List[id]).size() - 2 < length)
            {
                temp.text = to_string(Res_Resource_List[id])[length];
                Output_Map.push_back(temp);
            }
            else
            {
                Output_Map.push_back(Space);
            }
        }
        if (!(Res_Resource_List.size() % 2 == 1 && id + 1 == Y_Size))
        {
            Output_Map.push_back(Space);
            Output_Map.push_back(Materials_Graphic(id + Y_Size));
            Output_Map.push_back(Space);
            Output_Map.push_back(Semicolon);
            Output_Map.push_back(Space);
            for (int length = 0; length < 4; length++)
            {
                if (to_string(Res_Resource_List[id + Y_Size]).size() - 2 < length)
                {
                    temp.text = to_string(Res_Resource_List[id + Y_Size])[length];
                    Output_Map.push_back(temp);
                }
                else
                {
                    Output_Map.push_back(Space);
                }
            }
        }
        else
        {
            Output_Map.push_back(Space);
            Output_Map.push_back(Space);
            Output_Map.push_back(Space);
            Output_Map.push_back(Space);
            Output_Map.push_back(Space);
            Output_Map.push_back(Space);
            Output_Map.push_back(Space);
            Output_Map.push_back(Space);
        }
    }
    if (Res_TestMod)
    {
        cout << '\n'
             << "MapSize: " << Output_Map.size() << '\n';
    }
    vector<int> en_xy{Res_st_xy[0] + Res_Size[0] - 1, Res_st_xy[1] + Res_Size[1] - 1};
    R_Main.Add_Textbox("",0, 0, Res_Layer_name, Output_Map, Res_st_xy, en_xy, 0);
}
#endif