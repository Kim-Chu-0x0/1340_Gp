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
    bool TestMod = 0;

public:
    // quantity can be negative
    void Add_Resources(int type, int quantity);

private:
    vector<int> Resource_List{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

public:
    void Output();
    vector<int> st_xy{0, 0};
    vector<int> Size{9, 8};

private:
    string Layer_name = "Map";
};

void Resources_Display::Add_Resources(int type, int quantity)
{
    Resource_List[type] += quantity;
}

void Resources_Display::Output()
{
    vector<Pixel> Output_Map;
    Pixel Space, Semicolon;
    Space.text = " ";
    Semicolon.text = ":";
    int Y_Size = (Size[1]) + (Resource_List.size() % 2);
    if (TestMod)
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
            if (to_string(Resource_List[id]).size() - 2 < length)
            {
                temp.text = to_string(Resource_List[id])[length];
                Output_Map.push_back(temp);
            }
            else
            {
                Output_Map.push_back(Space);
            }
        }
        if (!(Resource_List.size() % 2 == 1 && id + 1 == Y_Size))
        {
            Output_Map.push_back(Space);
            Output_Map.push_back(Materials_Graphic(id + Y_Size));
            Output_Map.push_back(Space);
            Output_Map.push_back(Semicolon);
            Output_Map.push_back(Space);
            for (int length = 0; length < 4; length++)
            {
                if (to_string(Resource_List[id + Y_Size]).size() - 2 < length)
                {
                    temp.text = to_string(Resource_List[id + Y_Size])[length];
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
    if (TestMod)
    {
        cout << '\n'
             << "MapSize: " << Output_Map.size() << '\n';
    }
    vector<int> en_xy{st_xy[0] + Size[0] - 1, st_xy[1] + Size[1] - 1};
    R_Main.Add_Textbox(0, 0, Layer_name, Output_Map, st_xy, en_xy, 0);
}
#endif