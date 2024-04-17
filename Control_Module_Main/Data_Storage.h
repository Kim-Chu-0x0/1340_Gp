#ifndef DataS
#define DataS

#include <iostream>
#include <string>
#include <vector>

// Type:
//  0 : Extra Card per draw (Min3 Max5)
//  1 : Extend Map Horizontaly
//  2 : Extend Map Vertically
//  3 : Extra Resource Output (All)
//  4 : Extra Resource Output (Specific Building)
//  5 : Reduce Resource Intakes (All)
//  6 : Reduce Resource Intakes (Specific Building)
//  7 : Increase Duration (All)
//  8 : Increase Duration (Specific Building)
//  9 : Extra Inventory Slot
//  10 : Increase Luck
//  11 : Increase Energy Regeneration
//  12 : Increase Maximum Energy
//  13 : Longer Preperation Time Before Disaster
//  14 : Increase Resource Output (Specific Type)
//  15 : Reduce Resource Intakes (Specific Type)
//  16 : Gain Extra Life
//  17 : Less Draw Consumption
//  18 : Receive T1 Resource Every Turn
//  19 : Increase Duration (Specific Type)
// Format:
//{0:level,1:value 2:level,3:value......}
vector<vector<int>> Upgrade_List;

vector<int> Weighting_Tier_List{0, 1, 4, 6, 10, 15, 30, 50, 90};

vector<int> Tool_Weighting{
    // Move Building
    Weighting_Tier_List[4],
    // Demolish Building
    Weighting_Tier_List[4],
    // Extend Life span
    Weighting_Tier_List[3],
    // Prevent 1 round corruption
    Weighting_Tier_List[3],
    // Free Draw
    Weighting_Tier_List[4],
    // Gain T1 Resources
    Weighting_Tier_List[3],
    // Gain T2 Resources
    Weighting_Tier_List[3],
    // Gain T3 Resources
    Weighting_Tier_List[2]
};

vector<int> Building_Weighting{
    // Tier 0 producer
    Weighting_Tier_List[8],
    // Tier 1 producer
    Weighting_Tier_List[4],
    // Tier 2 producer
    Weighting_Tier_List[2],
    // Tier 0 processor
    Weighting_Tier_List[7],
    // Tier 1 processor
    Weighting_Tier_List[6],
    // Tier 2 processor
    Weighting_Tier_List[4]
};

vector<int> Upgrade_Weighting{
    // 0 : Extra Card per draw (Min3 Max5)
    Weighting_Tier_List[3],
    // 1 : Extend Map Horizontaly
    Weighting_Tier_List[3],
    // 2 : Extend Map Vertically
    Weighting_Tier_List[3],
    // 3 : Extra Resource Output (All)
    Weighting_Tier_List[2],
    // 4 : Extra Resource Output (Specific Building)
    Weighting_Tier_List[3],
    // 5 : Reduce Resource Intakes (All)
    Weighting_Tier_List[1],
    // 6 : Reduce Resource Intakes (Specific Building)
    Weighting_Tier_List[2],
    // 7 : Increase Duration (All)
    Weighting_Tier_List[2],
    // 8 : Increase Duration (Specific Building)
    Weighting_Tier_List[3],
    // 9 : Extra Inventory Slot
    Weighting_Tier_List[3],
    // 10 : Increase Luck
    Weighting_Tier_List[3],
    // 11 : Increase Energy Regeneration
    Weighting_Tier_List[2],
    // 12 : Increase Maximum Energy
    Weighting_Tier_List[3],
    // 13 : Longer Preperation Time Before Disaster
    Weighting_Tier_List[1],
    // 14 : Increase Resource Output (Specific Type)
    Weighting_Tier_List[2],
    // 15 : Reduce Resource Intakes (Specific Type)
    Weighting_Tier_List[1],
    // 16 : Gain Extra Life
    Weighting_Tier_List[0],
    // 17 : Less Draw Consumption
    Weighting_Tier_List[3],
    // 18 : Receive T1 Resource Every Turn
    Weighting_Tier_List[1],
    // 19 : Receive 2 Random Upgrades
    Weighting_Tier_List[2],
    // 20 : Increase Duration (Specific Type)
    Weighting_Tier_List[2]
};

int Sum_Upgrade_Weighting,Sum_Building_Weighting,Sum_Tool_Weighting;

vector <int> Screen_Size{0,0};

//0:Draw_Button
//1:Draw_UI
//2:Energy_Bar
//3:Inventory
//4:Map_Grid
//5:Resources_Display
vector <vector <bool>> Accessable{{0},{0},{0},{0},{0},{0}};
vector <bool> Visible{0,0,0,0,0,0};

#include "..\Display_Module_Main\Draw_Button.h"
#include "..\Display_Module_Main\Map_Grid.h"
#include "..\Display_Module_Main\Resources_Display.h"
#include "..\Display_Module_Main\Energy_Bar.h"
#include "..\Display_Module_Main\Draw_UI.h"

using namespace std;

class Data_Storage : public Map_Grid, public Resources_Display, public Draw_Button, public Energy_Bar, public Draw_UI
{
private:
    bool Testmod = 0;

public:
    void Initialize();
    void Refresh();

public:
    void Draw();

private:
    void Relocate();
};

void Data_Storage::Draw()
{
    Sum_Upgrade_Weighting=Sum_Building_Weighting=Sum_Tool_Weighting=0;
    for (int id = 0;id<Upgrade_Weighting.size();id++){
        Sum_Upgrade_Weighting+=Upgrade_Weighting[id];
    }
    for (int id = 0;id<Building_Weighting.size();id++){
        Sum_Building_Weighting+=Building_Weighting[id];
    }
    for (int id = 0;id<Tool_Weighting.size();id++){
        Sum_Tool_Weighting+=Tool_Weighting[id];
    }
    DUI_Draw_Card();
    Visible[1]=1;
}

void Data_Storage::Refresh()
{
    if ( Visible[0] ){
        Draw_Output();
    }
    if ( Visible[1] ){
        DUI_Output();
    }
    if ( Visible[2] ){
        EGY_Output();
    }
    if ( Visible[3] ){
        //;
    }
    if ( Visible[4] ){
        Grid_Output();
    }
    if ( Visible[5] ){
        Res_Output();
    }
    
    
    if (Testmod)
    {
        cout << '\n'
             << "D_Main refreshed" << '\n';
    }
}

void Data_Storage::Relocate()
{
    Res_st_xy[0] = 0;
    Res_st_xy[1] = 0;
    Grid_st_xy[0] = Res_Size[0] + Res_st_xy[0] + 1;
    Grid_st_xy[1] = Res_st_xy[1];
    Draw_st_xy[0] = Res_st_xy[0];
    Draw_st_xy[1] = Grid_st_xy[1] + Grid_Size[1] - Draw_Size[1];
    EGY_st_xy[0] = Res_st_xy[0];
    EGY_st_xy[1] = Grid_st_xy[1] + Grid_Size[1] + 1;
    EGY_Size[0] = Grid_st_xy[0] + Grid_Size[0] - EGY_st_xy[0];
    Screen_Size[0]=EGY_Size[0];
    Screen_Size[1]=EGY_st_xy[1]+EGY_Size[1];
}

void Data_Storage::Initialize()
{
    Visible[0]=1;
    Visible[2]=1;
    Visible[4]=1;
    Visible[5]=1;
    // Upgrade Data Initialize
    vector <int> temp{0,0};
    for (int id;id<20;id++){
        Upgrade_List.push_back(temp);
    }
    Upgrade_List[0][1]=3;
    for (int id=1;id<Production_Building_type;id++){
        Upgrade_List[14].push_back(0);
        Upgrade_List[14].push_back(0);
    }
    for (int id=1;id<Production_Building_number;id++){
        Upgrade_List[4].push_back(0);
        Upgrade_List[4].push_back(0);
    }
    for (int id=1;id<Processing_Building_type;id++){
        Upgrade_List[15].push_back(0);
        Upgrade_List[15].push_back(0);
    }
    for (int id=1;id<Processing_Building_number;id++){
        Upgrade_List[6].push_back(0);
        Upgrade_List[6].push_back(0);
    }
    for (int id=1;id<All_Building_type;id++){
        Upgrade_List[19].push_back(0);
        Upgrade_List[19].push_back(0);
    }
    for (int id=1;id<All_Building_number;id++){
        Upgrade_List[7].push_back(0);
        Upgrade_List[7].push_back(0);
    }
    // UI Setup
    Grid_Set_Size(4, 4);
    Res_Future_List[0] = 10;
    Res_Future_List[5] = -999;
    EGY_Energy = 50;
    EGY_Future_Energy = 30;
    Grid_Reset();
    Relocate();
}

#endif