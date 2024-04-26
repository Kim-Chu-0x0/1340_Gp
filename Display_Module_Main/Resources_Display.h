#ifndef RES_DIS
#define RES_DIS

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Object/Materials.h"
#include "Object/Display_Module_CLass/Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Resources_Display
{
private:
    bool Res_TestMod = 0;

protected:
    //Needs to be saved
    vector<int> Res_Resource_List{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<int> Res_Future_List{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<bool> Res_Issue{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

protected:
    void Res_Output();
    vector<int> Res_st_xy{0, 0};
    vector<int> Res_Size{9, 16};

protected:
    void Res_PsssTurn();
    string Res_Layer_name = "Map";
private:
    int Res_selectable;
};

void Resources_Display::Res_PsssTurn()
{
    for (int id = 0; id < Res_Resource_List.size(); id++)
    {
        Res_Resource_List[id] += Res_Future_List[id];
        Res_Future_List[id] = 0;
    }
}

void Resources_Display::Res_Output()
{
    Res_selectable=Selectable_List[5];
    vector<Pixel> Output_Map;
    Pixel Space, Semicolon;
    Space.text = "/s";
    Semicolon.text = ":";
    int Y_Size = (Res_Size[1] / 2) + (Res_Resource_List.size() % 2);
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
            if (to_string(Res_Resource_List[id]).size() > length)
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
                if (to_string(Res_Resource_List[id + Y_Size]).size() > length)
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
            for (int id_temp = 0; id_temp < 9; id_temp++)
            {
                Output_Map.push_back(Space);
            }
        }

        if (Res_Future_List[id] == 0)
        {
            for (int id_temp = 0; id_temp < 8; id_temp++)
            {
                Output_Map.push_back(Space);
            }
        }
        else
        {
            Output_Map.push_back(Space);
            if (Res_Future_List[id] > 0)
            {
                temp.colour = H_Green;
                temp.text = "+";
            }
            else
            {
                temp.colour = H_Red;
                temp.text = "-";
            }
            if (Res_Issue[id]){
                temp.colour = H_Yellow;
            }
            Output_Map.push_back(temp);
            for (int length = 0; length < 6; length++)
            {
                if (to_string(abs(Res_Future_List[id])).size() > length)
                {
                    temp.text = to_string(abs(Res_Future_List[id]))[length];
                    Output_Map.push_back(temp);
                }
                else
                {
                    Output_Map.push_back(Space);
                }
            }
        }
        if (!(Res_Resource_List.size() % 2 == 1 && id + 1 == Y_Size))
        {
            Output_Map.push_back(Space);
            if (Res_Future_List[id + Y_Size] == 0)
            {
                for (int id_temp = 0; id_temp < 8; id_temp++)
                {
                    Output_Map.push_back(Space);
                }
            }
            else
            {
                Output_Map.push_back(Space);
                if (Res_Future_List[id + Y_Size] > 0)
                {
                    temp.colour = H_Green;
                    temp.text = "+";
                }
                else
                {
                    temp.colour = H_Red;
                    temp.text = "-";
                }
                if (Res_Issue[id + Y_Size]){
                    temp.colour = H_Yellow;
                }
                Output_Map.push_back(temp);
                for (int length = 0; length < 6; length++)
                {
                    if (to_string(abs(Res_Future_List[id + Y_Size])).size() > length)
                    {
                        temp.text = to_string(abs(Res_Future_List[id + Y_Size]))[length];
                        Output_Map.push_back(temp);
                    }
                    else
                    {
                        Output_Map.push_back(Space);
                    }
                }
            }
        }
        else
        {
            for (int id_temp = 0; id_temp < 9; id_temp++)
            {
                Output_Map.push_back(Space);
            }
        }
    }
    if (Res_TestMod)
    {
        cout << '\n'
             << "MapSize: " << Output_Map.size() << '\n';
    }
    vector<int> en_xy{Res_st_xy[0] + Res_Size[0] - 1, Res_st_xy[1] + Res_Size[1] - 1};
    R_Main.Add_Textbox("", 0, 0, Res_Layer_name, Output_Map, Res_st_xy, en_xy, 0);
}
#endif