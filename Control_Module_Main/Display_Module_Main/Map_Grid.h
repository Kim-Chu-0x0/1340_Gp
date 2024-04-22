#ifndef M_GRID
#define M_GRID

#include <iostream>
#include <string>
#include <vector>
#include "Object/Class_Buildings.h"
#include "Object/Display_Module_CLass/Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Map_Grid
{
    // testing
private:
    bool Grid_TestMod = 0;

    // item access
protected:
    // change a single grid
    // xy can be in form of{x_id,y_id} or {id}
    void Grid_Set_Building(vector<int> xy, Building item);
    // re-input all building object
    // previous data will be covered
    void Grid_CoverAll_Biulding(vector<Building> item_list);
    void Grid_Reset();
    vector <vector <int>> Cal_Building_req();
    void Grid_Place_Building(Building item);
    void Grid_Restore_Building(double value);
    void Grid_Building_On_Off();

protected:
    vector<Building> Grid_Building_list;
    vector<int> Grid_Highlight_Data;
    int Grid_Phase = 0;
    Building cache;
private:
    int Grid_selectable;

    // size control
protected:
    void Grid_Set_Size(int x, int y)
    {
        if (!((Grid_Grid_Size[0] == 0) && (Grid_Grid_Size[1] == 0)))
        {
            cout << '\n'
                 << "(Grid_Set_Size)Error: Grid_Size can not be changed" << '\n';
            exit(0);
        }
        Grid_Grid_Size[0] = x;
        Grid_Grid_Size[1] = y;
        Building temp;
        for (int x = 0; x < Grid_Grid_Size[0] * Grid_Grid_Size[1]; x++)
        {
            Grid_Building_list.push_back(temp);
            Grid_Highlight_Data.push_back(0);
        }
        Grid_Size[1] = Grid_Grid_Size[1] * 7 - 1;
    }
    void Grid_Expand(int x, int y);
    void Check_Size();

    // output control
protected:
    void Grid_Output();
    void Grid_Refresh_stat();
    vector<int> Grid_st_xy{0, 0};
    vector<int> Grid_Maximum_Size{8, 5};
    vector<int> Grid_Size{Grid_Maximum_Size[0] * 7 - 1, 0};
    string Grid_Layer_name = "Map";
    string Grid_Popup_Layer_name = "PopUp_Map";
    void Grid_Pass_Turn();
    vector<int> Get_Disaster_Req();
    void Grid_Plant_Disaster(int level);
    Building Grid_Take_Building();
    void Grid_Demolish_Building();
    int Grid_Get_pos();

private:
    vector<int> Grid_Grid_Size{0, 0};
    int selection;
    void Grid_Popup();
    int Grid_Disaster_Fix_Highlight_Data;
};

int Map_Grid::Grid_Get_pos(){
    return selection;
}

void Map_Grid::Grid_Demolish_Building(){
    Building temp;
    temp.Input_type(6);
    Grid_Place_Building(temp);
}

Building Map_Grid::Grid_Take_Building(){
    Building temp = Grid_Building_list[selection];
    Grid_Demolish_Building();
    return temp;
}

void Map_Grid::Grid_Restore_Building(double value){
    Grid_Building_list[selection].Restore_Lifespan(value);
}

vector<int> Map_Grid::Get_Disaster_Req(){
    return (Grid_Building_list[selection].Get_Disaster_Req());
}

void Map_Grid::Grid_Building_On_Off(){
    if (Grid_Building_list[selection].On_Off==0){
        Grid_Building_list[selection].On_Off=1;
    }
    else{
        Grid_Building_list[selection].On_Off=0;
    }
}

void Map_Grid::Grid_Popup(){
    if (((Grid_Phase == 0)||(Grid_Phase == 1)) && (selection != -1))
    {
        if (Grid_Building_list[selection].name != "Empty/sSpace")
        {
            vector<int> temp_St{Grid_st_xy[0]+((selection%Grid_Grid_Size[0])*7)-6, Grid_st_xy[1]+((selection/Grid_Grid_Size[0])*7)+7};
            if (selection%Grid_Grid_Size[0] == Grid_Maximum_Size[0] - 1)
            {
                temp_St[0] -= 5;
            }
            int temp_size=(Grid_Building_list[selection].description.size()/33);
            vector<int> temp_En{temp_St[0] + 16, temp_St[1] + temp_size - 1};
            R_Main.Add_Textbox("", 0, 0, Grid_Popup_Layer_name, Grid_Building_list[selection].description, temp_St, temp_En, 0);
        }
    }
    if (Grid_Phase == 2){
        string Text = "000000000000000000000000Press0E0to0Fix0000000000000000000000000";
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
        vector<int> temp_St{Grid_st_xy[0]+((selection%Grid_Grid_Size[0])*7)-2, Grid_st_xy[1]+((selection/Grid_Grid_Size[0])*7)+7};
        if (selection%Grid_Grid_Size[0] == Grid_Maximum_Size[0] - 1)
        {
            temp_St[0] -= 3;
        }
        vector<int> temp_En{temp_St[0] + 10, temp_St[1] + 2};
        Grid_Disaster_Fix_Highlight_Data = R_Main.Add_Textbox("Disaster_Fix_T", 1, Grid_Disaster_Fix_Highlight_Data, Grid_Popup_Layer_name, T_Pixel_List, temp_St, temp_En, 0);
    }
    if (Grid_Phase == 3){
        string Text = "0000000000000000000000Not0Enough0Materials000000000000000000000";
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
        vector<int> temp_St{Grid_st_xy[0]+((selection%Grid_Grid_Size[0])*7)-2, Grid_st_xy[1]+((selection/Grid_Grid_Size[0])*7)+7};
        if (selection%Grid_Grid_Size[0] == Grid_Maximum_Size[0] - 1)
        {
            temp_St[0] -= 3;
        }
        vector<int> temp_En{temp_St[0] + 10, temp_St[1] + 2};
        Grid_Disaster_Fix_Highlight_Data = R_Main.Add_Textbox("Disaster_Fix_F", 1, Grid_Disaster_Fix_Highlight_Data, Grid_Popup_Layer_name, T_Pixel_List, temp_St, temp_En, 0);
    }
}

//Start at lv 0
void Map_Grid::Grid_Plant_Disaster(int level){
    for (int no = 0;no<level+1;no++){
        int choice=rand()%Grid_Building_list.size();
        Building Dis;
        Dis.Input_type(7);
        vector<int> temp{choice};
        Grid_Set_Building(temp, Dis);
    }
}

void Map_Grid::Grid_Pass_Turn(){
    Building Null;
    Null.Input_type(6);
    for (int id = 0; id < Grid_Building_list.size(); id++){
        if (Grid_Building_list[id].Pass_Turn()){
            vector<int> temp{id};
            Grid_Set_Building(temp, Null);
        }
    }
}

void Map_Grid::Grid_Refresh_stat(){
    for (int id = 0; id < Grid_Building_list.size(); id++){
        Grid_Building_list[id].Refresh_stat();
    }
}

vector <vector <int>> Map_Grid::Cal_Building_req(){
    vector <int> temp (17,0);
    vector <vector <int>> Output{temp,temp};
    for (int id = 0; id < Grid_Grid_Size[0] * Grid_Grid_Size[1]; id++){
        if (Grid_Building_list[id].name!="Empty/sSpace"){
            vector <vector <int>> T_Output=Grid_Building_list[id].Return_Req();
            for (int no = 0;no<T_Output[0].size();no++){
                Output[0][no]+=T_Output[0][no];
            }
            for (int no = 0;no<T_Output[1].size();no++){
                Output[1][no]+=T_Output[1][no];
            }
        }
    }
    return Output;
}

void Map_Grid::Grid_Reset()
{
    Building Null;
    Null.Input_type(6);
    for (int id = 0; id < Grid_Grid_Size[0] * Grid_Grid_Size[1]; id++)
    {
        vector<int> temp{id};
        Grid_Set_Building(temp, Null);
    }
}

void Map_Grid::Grid_Place_Building(Building item){
    vector <int> temp{selection};
    Grid_Set_Building(temp,item);
}

void Map_Grid::Grid_Expand(int x, int y)
{
    if (!((x >= 0) && (y >= 0)))
    {
        cout << '\n'
             << "(Grid_Expand)Error: Size can not be negative number" << '\n';
        cout << '\n'
             << "Your input: x=" << x << " y=" << y << '\n';
        exit(0);
    }
    if ((Grid_Grid_Size[0] == 0) && (Grid_Grid_Size[1] == 0))
    {
        cout << '\n'
             << "(Grid_Expand)Error: Set the size first" << '\n';
        exit(0);
    }
    // rightward
    Building temp;
    temp.Input_type(6);
    for (int id_y = Grid_Grid_Size[1] - 1; id_y >= 0; id_y--)
    {
        for (int id_x = 0; id_x < x; id_x++)
        {
            Grid_Building_list.insert(Grid_Building_list.begin() + id_y * Grid_Grid_Size[0] + Grid_Grid_Size[0], temp);
            Grid_Highlight_Data.insert(Grid_Highlight_Data.begin() + id_y * Grid_Grid_Size[0] + Grid_Grid_Size[0], 0);
        }
    }
    Grid_Grid_Size[0] += x;
    // downward
    for (int id_y = 0; id_y < y; id_y++)
    {
        for (int id_x = 0; id_x < Grid_Grid_Size[0]; id_x++)
        {
            Grid_Building_list.push_back(temp);
            Grid_Highlight_Data.push_back(0);
        }
    }
    Grid_Grid_Size[1] += y;
    Grid_Size[1] = Grid_Grid_Size[1] * 7 - 1;
}

void Map_Grid::Check_Size()
{
    for (; Grid_Grid_Size[0] < Upgrade_List[1][1];)
    {
        Grid_Expand(1, 0);
    }
    for (; Grid_Grid_Size[1] < Upgrade_List[2][1];)
    {
        Grid_Expand(0, 1);
    }
}

void Map_Grid::Grid_Output()
{
    Grid_selectable=Selectable_List[4];
    if (Grid_Phase==0||Grid_Phase==1){
        selection = -1;
        if ((R_Main.Highlight_Choice_Layer == Grid_Layer_name) && (Grid_Highlight_Data[0] != 0))
        {
            for (int id = 0; id < Grid_Highlight_Data.size(); id++)
            {
                if (R_Main.Highlight_Choice_Textbox_id[R_Main.AP_Layer_Location] == Grid_Highlight_Data[id])
                {
                    selection = id;
                }
            }
        }
    }
    if (Grid_TestMod)
    {
        cout << '\n'
             << "Building ID: " << '\n';
        for (int x = 0; x < Grid_Highlight_Data.size(); x++)
        {
            cout << Grid_Highlight_Data[x] << " ";
        }
        cout << '\n';
    }
    for (int y = 0; y < Grid_Grid_Size[1]; y++)
    {
        int y1 = Grid_st_xy[1] + ((Grid_Building_list[0].output_graphic_size_S[1] + 1) * y);
        int y2 = Grid_st_xy[1] + ((Grid_Building_list[0].output_graphic_size_S[1] + 1) * y) + (Grid_Building_list[0].output_graphic_size_S[1] - 1);
        for (int x = 0; x < Grid_Grid_Size[0]; x++)
        {
            int x1 = Grid_st_xy[0] + ((Grid_Building_list[0].output_graphic_size_S[0] + 1) * x);
            int x2 = Grid_st_xy[0] + ((Grid_Building_list[0].output_graphic_size_S[0] + 1) * x) + (Grid_Building_list[0].output_graphic_size_S[0] - 1);
            vector<int> temp_St{x1, y1};
            vector<int> temp_En{x2, y2};
            if(Grid_Phase==0){
                if (Grid_Building_list[x + y * Grid_Grid_Size[0]].name=="Empty/sSpace"){
                    Grid_Highlight_Data[x + y * Grid_Grid_Size[0]] = R_Main.Add_Textbox("Building_NULL", Grid_selectable, Grid_Highlight_Data[x + y * Grid_Grid_Size[0]], Grid_Layer_name, Grid_Building_list[x + y * Grid_Grid_Size[0]].graphic_S, temp_St, temp_En, 0);
                }
                else if (Grid_Building_list[x + y * Grid_Grid_Size[0]].name=="Disaster"){
                    Grid_Highlight_Data[x + y * Grid_Grid_Size[0]] = R_Main.Add_Textbox("Disaster", Grid_selectable, Grid_Highlight_Data[x + y * Grid_Grid_Size[0]], Grid_Layer_name, Grid_Building_list[x + y * Grid_Grid_Size[0]].graphic_S, temp_St, temp_En, 0);
                }
                else {
                    Grid_Highlight_Data[x + y * Grid_Grid_Size[0]] = R_Main.Add_Textbox("Building", Grid_selectable, Grid_Highlight_Data[x + y * Grid_Grid_Size[0]], Grid_Layer_name, Grid_Building_list[x + y * Grid_Grid_Size[0]].graphic_S, temp_St, temp_En, 0);
                }
            }
            else if(Grid_Phase==1){
                if (Grid_Building_list[x + y * Grid_Grid_Size[0]].name=="Empty/sSpace"){
                    Grid_Highlight_Data[x + y * Grid_Grid_Size[0]] = R_Main.Add_Textbox("Building_NULL_T", Grid_selectable, Grid_Highlight_Data[x + y * Grid_Grid_Size[0]], Grid_Layer_name, Grid_Building_list[x + y * Grid_Grid_Size[0]].graphic_S, temp_St, temp_En, 0);
                }
                else if (Grid_Building_list[x + y * Grid_Grid_Size[0]].name=="Disaster"){
                    Grid_Highlight_Data[x + y * Grid_Grid_Size[0]] = R_Main.Add_Textbox("Disaster_", Grid_selectable, Grid_Highlight_Data[x + y * Grid_Grid_Size[0]], Grid_Layer_name, Grid_Building_list[x + y * Grid_Grid_Size[0]].graphic_S, temp_St, temp_En, 0);
                }
                else {
                    Grid_Highlight_Data[x + y * Grid_Grid_Size[0]] = R_Main.Add_Textbox("Building_NULL_F", Grid_selectable, Grid_Highlight_Data[x + y * Grid_Grid_Size[0]], Grid_Layer_name, Grid_Building_list[x + y * Grid_Grid_Size[0]].graphic_S, temp_St, temp_En, 0);
                }
            }
            else{
                Grid_Highlight_Data[x + y * Grid_Grid_Size[0]] = R_Main.Add_Textbox("", 0, Grid_Highlight_Data[x + y * Grid_Grid_Size[0]], Grid_Layer_name, Grid_Building_list[x + y * Grid_Grid_Size[0]].graphic_S, temp_St, temp_En, 0);
            }
        }
    }
    if (Grid_Grid_Size[0] != Grid_Maximum_Size[0])
    {
        int y1 = Grid_st_xy[1];
        int y2 = Grid_st_xy[1] + ((Grid_Building_list[0].output_graphic_size_S[1] + 1) * (Grid_Grid_Size[1] - 1)) + (Grid_Building_list[0].output_graphic_size_S[1] - 1);
        int x1 = Grid_st_xy[0] + ((Grid_Building_list[0].output_graphic_size_S[0] + 1) * (Grid_Grid_Size[0]));
        int x2 = Grid_st_xy[0] + ((Grid_Building_list[0].output_graphic_size_S[0] + 1) * (Grid_Maximum_Size[0] - 1)) + (Grid_Building_list[0].output_graphic_size_S[0] - 1);
        vector<Pixel> Temp;
        Pixel temp_P;
        temp_P.text = "/s";
        for (int id = 0; id < (y2 - y1 + 1) * (((x2 - x1 + 1) * 2) - 1); id++)
        {
            Temp.push_back(temp_P);
        }
        vector<int> temp_St{x1, y1};
        vector<int> temp_En{x2, y2};
        R_Main.Add_Textbox("", 0, 0, Grid_Layer_name, Temp, temp_St, temp_En, 0);
    }

    Grid_Popup();

    if (Grid_TestMod)
    {
        cout << "Output done" << '\n';
        cout << '\n'
             << "Building ID: " << '\n';
        for (int x = 0; x < Grid_Highlight_Data.size(); x++)
        {
            cout << Grid_Highlight_Data[x] << " ";
        }
        cout << '\n';
    }
}

void Map_Grid::Grid_Set_Building(vector<int> xy, Building item)
{
    if (xy.size() == 2)
    {
        int x = xy[0];
        int y = xy[1];
        if ((x >= Grid_Grid_Size[0]) || (y >= Grid_Grid_Size[1]))
        {
            cout << '\n'
                 << "(Grid_Set_Building)Error: x and y should locate within the grid system" << '\n';
            cout << "input x: " << x << " y: " << y << '\n';
            cout << "Grid size x: " << Grid_Grid_Size[0] << " y: " << Grid_Grid_Size[1] << '\n';
            exit(0);
        }
        Grid_Building_list[Grid_Grid_Size[0] * y + x] = item;
    }
    else
    {
        Grid_Building_list[xy[0]] = item;
    }
}

void Map_Grid::Grid_CoverAll_Biulding(vector<Building> item_list)
{
    if (item_list.size() != Grid_Grid_Size[0] * Grid_Grid_Size[1])
    {
        cout << '\n'
             << "(Grid_CoverAll_Biulding)Error: Size of input vector should equal to the size of the grid" << '\n';
        cout << "input size: " << item_list.size() << '\n';
        cout << "Grid size : " << Grid_Grid_Size[0] * Grid_Grid_Size[1] << '\n';
        exit(0);
    }
    for (int id = 0; id < item_list.size(); id++)
    {
        vector<int> temp{id};
        Grid_Set_Building(temp, item_list[id]);
    }
}

#endif