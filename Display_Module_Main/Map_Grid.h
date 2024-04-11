#ifndef M_GRID
#define M_GRID

#include <iostream>
#include <string>
#include <vector>
#include "..\Object\Class_Buildings.h"
#include "..\Display_Module_Class\Class_Render.h"

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
    // xy can be in form of{x_id,y_id} orF {id}
    void Grid_Set_Building(vector<int> xy, Building item);
    // re-input all building object
    // previous data will be covered
    void Grid_CoverAll_Biulding(vector<Building> item_list);
    void Grid_Reset();

protected:
    vector<Building> Grid_Building_list;
    vector<int> Grid_Highlight_Data;

    // size control
protected:
    void Grid_Set_Size(int x, int y)
    {
        if (!((Grid_Grid_Size[0] == 0) && (Grid_Grid_Size[1] == 0)))
        {
            cout << '\n'
                 << "Error: Grid_Size can not be changed" << '\n';
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
        Grid_Size[0] = Grid_Grid_Size[0] * 7 - 1;
        Grid_Size[1] = Grid_Grid_Size[1] * 7 - 1;
    }
    void Grid_Expand(int x, int y);

    // output control
protected:
    void Grid_Output();
    vector<int> Grid_st_xy{0, 0};
    vector<int> Grid_Size{0, 0};
    vector<int> Grid_Maximum_Size{8, 5};

private:
    string Grid_Layer_name = "Map";
    vector<int> Grid_Grid_Size{0, 0};
};

void Map_Grid::Grid_Reset()
{
    Building Null;
    Null.type(6);
    for (int id = 0; id < Grid_Grid_Size[0] * Grid_Grid_Size[1]; id++)
    {
        vector<int> temp{id};
        Grid_Set_Building(temp, Null);
    }
}

void Map_Grid::Grid_Expand(int x, int y)
{
    if (!((x >= 0) && (y >= 0)))
    {
        cout << '\n'
             << "Error: Size can not be negative number" << '\n';
        cout << '\n'
             << "Your input: x=" << x << " y=" << y << '\n';
        exit(0);
    }
    if ((Grid_Grid_Size[0] == 0) && (Grid_Grid_Size[1] == 0))
    {
        cout << '\n'
             << "Error: Set the size first" << '\n';
        exit(0);
    }
    // rightward
    Building temp;
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
    Grid_Size[0] = Grid_Grid_Size[0] * 7 - 1;
    Grid_Size[1] = Grid_Grid_Size[1] * 7 - 1;
}

void Map_Grid::Grid_Output()
{
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
            Grid_Highlight_Data[x + y * Grid_Grid_Size[0]] = R_Main.Add_Textbox("Building", 1, Grid_Highlight_Data[x + y * Grid_Grid_Size[0]], Grid_Layer_name, Grid_Building_list[x + y * Grid_Grid_Size[0]].graphic_S, temp_St, temp_En, 0);
        }
    }
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
                 << "Coordinates Error: x and y should locate within the grid system" << '\n';
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
             << "Input Error: Size of input vector should equal to the size of the grid" << '\n';
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