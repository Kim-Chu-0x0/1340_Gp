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
//  19 : Receive 2 Random Upgrades
//  20 : Increase Duration (Specific Type)
// Format:
//{0:level,1:value 2:level,3:value......}
vector<vector<double>> Upgrade_List;

//00:Draw
//01:DUI
//02:EGY
//03:INV
//04:Grid
//05:Res
vector <bool> Selectable_List;

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
    Weighting_Tier_List[2]};

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
    Weighting_Tier_List[4]};

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
    Weighting_Tier_List[2]};

int Sum_Upgrade_Weighting, Sum_Building_Weighting, Sum_Tool_Weighting;

vector<int> Screen_Size{0, 0};

// 0:Draw_Button
// 1:Draw_UI
// 2:Energy_Bar
// 3:Inventory
// 4:Map_Grid
// 5:Resources_Display
vector<bool> Visible{0, 0, 0, 0, 0, 0};

#include "..\Display_Module_Main\Draw_Button.h"
#include "..\Display_Module_Main\Map_Grid.h"
#include "..\Display_Module_Main\Resources_Display.h"
#include "..\Display_Module_Main\Energy_Bar.h"
#include "..\Display_Module_Main\Draw_UI.h"
#include "..\Display_Module_Main\Inventory.h"

using namespace std;

class Data_Storage : public Map_Grid, public Resources_Display, public Draw_Button, public Energy_Bar, public Draw_UI, public Inventory
{
public:
    void Test_Specific_Card(int id);
private:
    bool Testmod = 0;

public:
    void Initialize();
    void Refresh();
    void Refresh_Layer(string id);

public:
    void Draw(int id);
    void Discard(int id);
    void Use_INV_item(int id);
    int Building_Grid_Selection_Result(int id);

private:
    void Upgrade_Apply(Upgrade input);
    void Relocate();
    void Upgrade_Max_Check();
    void D_Phase_Switch(int id);

public:
    int slot_id_cache;
private:
    int slot_pos_cache;
    int Situation;
    Card Card_cache;
};

void Data_Storage ::Upgrade_Apply(Upgrade input)
{
    Upgrade_List[input.type][input.subtype * 2] += 1;
    Upgrade_List[input.type][input.subtype * 2 + 1] += input.value;
    if(input.type==1||input.type==2){
        Check_Size();
    }
}

void Data_Storage::Discard(int id){
    if(id==0){
        INV_Phase=1;
    }
    else if(id==1){
        INV_Phase=0;
    }
    else if(id==2){
        INV_Phase=0;
        INV_Discard();
    }
}

void Data_Storage::Use_INV_item(int id){
    if(id==0){
        INV_Phase=2;
    }
    else if(id==1){
        INV_Phase=0;
    }
    else if(id==2){
        INV_Phase=0;
        Card_cache=INV_Slot_Output();
        slot_id_cache=INV_selection_id;
        slot_pos_cache=INV_selection;
        INV_Discard();
        D_Phase_Switch(1);
        if (Card_cache.Type==2){
            Situation=1;
        }
        else if (Card_cache.Type==3){
            Situation=0;
        }
    }
}

int Data_Storage ::Building_Grid_Selection_Result(int id){
    //Place Building
    if (Situation==0){
        //Hv building Q
        if(id==0){
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        //Hv building E
        else if(id==1){
            return 0;
        }
        //No building Q
        else if(id==2){
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        //No building E
        else if(id==3){
            Card_cache.B_Data.Countdown_St();
            Grid_Place_Building(Card_cache.B_Data);
            D_Phase_Switch(0);
            return 0;
        }
    }
    else if (Situation==1){
        //Hv building Q
        if(id==0){
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        //Hv building E
        else if(id==1){
            D_Phase_Switch(0);
            return 0;
        }
        //No building Q
        else if(id==2){
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        //No building E
        else if(id==3){
            return 2;
        }
    }
    return 0;
}

void Data_Storage ::D_Phase_Switch(int id){
    //Reset
    if (id==0){
        Selectable_List[0]=1;
        Selectable_List[1]=1;
        Selectable_List[2]=1;
        Selectable_List[3]=1;
        Selectable_List[4]=1;
        Selectable_List[5]=1;
        Grid_Phase=0;
    }
    //Building Grid Selection
    else if(id==1){
        Selectable_List[0]=0;
        Selectable_List[1]=0;
        Selectable_List[2]=0;
        Selectable_List[3]=0;
        Selectable_List[4]=1;
        Selectable_List[5]=0;
        Grid_Phase=1;
    }
}

void Data_Storage ::Upgrade_Max_Check(){
    if (Upgrade_List[0][1]==5){
        Upgrade_Weighting[0]=0;
    }
    if (Upgrade_List[1][1]==Grid_Maximum_Size[0]){
        Upgrade_Weighting[1]=0;
    }
    if (Upgrade_List[2][1]==Grid_Maximum_Size[1]){
        Upgrade_Weighting[2]=0;
    }
    if (Upgrade_List[9][1]==INV_Max_Size){
        Upgrade_Weighting[9]=0;
    }
    if (Upgrade_List[16][0]==1){
        Upgrade_Weighting[16]=0;
    }
}

void Data_Storage::Draw(int id)
{
    if (id == 0)
    {
        Upgrade_Max_Check();
        Sum_Upgrade_Weighting = Sum_Building_Weighting = Sum_Tool_Weighting = 0;
        for (int id = 0; id < Upgrade_Weighting.size(); id++)
        {
            Sum_Upgrade_Weighting += Upgrade_Weighting[id];
        }
        for (int id = 0; id < Building_Weighting.size(); id++)
        {
            Sum_Building_Weighting += Building_Weighting[id];
        }
        for (int id = 0; id < Tool_Weighting.size(); id++)
        {
            Sum_Tool_Weighting += Tool_Weighting[id];
        }
        if (Testmod){
            cout <<'\n'<<"Sum_Upgrade_Weighting= "<<Sum_Upgrade_Weighting<<'\n';
            cout <<"Sum_Tool_Weighting= "<<Sum_Tool_Weighting<<'\n';
            cout <<"Sum_Building_Weighting= "<<Sum_Building_Weighting<<'\n';
            cout <<"RNG MAX= "<<(Sum_Upgrade_Weighting + Sum_Tool_Weighting + Sum_Building_Weighting)<<'\n';
        }
        DUI_Draw_Card();
        Visible[1] = 1;
    }
    else if (id == 1)
    {
        DUI_Phase = 0;
    }
    else if (id == 2)
    {
        DUI_Phase = 1;
    }
    else if (id == 3)
    {
        Card temp=DUI_Draw_Output();
        if (temp.Type == 1)
        {
            Upgrade_Apply(temp.U_Data);
        }
        else
        {
            INV_Fill_Item(-1, temp);
        }
        DUI_Clear();
        Visible[1] = 0;
    }
}

void Data_Storage::Test_Specific_Card(int id)
{
    for (int no = 0;no<Upgrade_Weighting.size();no++){
        if (id != no){
            Upgrade_Weighting[no]=0;
        }
    }
    id-=Upgrade_Weighting.size();
    for (int no = 0;no<Tool_Weighting.size();no++){
        if (id != no){
            Tool_Weighting[no]=0;
        }
    }
    id-=Tool_Weighting.size();
    for (int no = 0;no<Building_Weighting.size();no++){
        if (id != no){
            Building_Weighting[no]=0;
        }
    }
}

void Data_Storage::Refresh_Layer(string id)
{
    Relocate();
    if (Draw_Layer_name == id)
    {
        if (Visible[0])
        {
            Draw_Output();
        }
    }
    if (DUI_Layer_name == id)
    {
        if (Visible[1])
        {
            DUI_Output();
        }
    }
    if (EGY_Layer_name == id)
    {
        if (Visible[2])
        {
            EGY_Output();
        }
    }
    if ((INV_Layer_name == id)||(INV_Popup_Layer_Name == id))
    {
        if (Visible[3])
        {
            INV_Output();
        }
    }
    if (Grid_Layer_name == id)
    {
        if (Visible[4])
        {
            Grid_Output();
        }
    }
    if (Res_Layer_name == id)
    {
        if (Visible[5])
        {
            Res_Output();
        }
    }
}

void Data_Storage::Refresh()
{
    Relocate();
    if (Visible[0])
    {
        Draw_Output();
    }
    if (Visible[1])
    {
        DUI_Output();
    }
    if (Visible[2])
    {
        EGY_Output();
    }
    if (Visible[3])
    {
        INV_Output();
    }
    if (Visible[4])
    {
        Grid_Output();
    }
    if (Visible[5])
    {
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
    INV_st_xy[0] = Res_st_xy[0];
    INV_st_xy[1] = EGY_st_xy[1] + EGY_Size[1] + 1;
    Screen_Size[0] = EGY_Size[0];
    Screen_Size[1] = INV_st_xy[1] + INV_Size[1];
}

void Data_Storage::Initialize()
{
    for (int id = 0;id<6;id++){
        Selectable_List.push_back(1);
    }
    Visible[0] = 1;
    Visible[2] = 1;
    Visible[3] = 1;
    Visible[4] = 1;
    Visible[5] = 1;
    if (Testmod){
        cout<<'\n'<<"Visual&Selectable_Date initialized"<<'\n';
    }
    // Upgrade Data Initialize
    vector<double> temp{0, 0};
    for (int id = 0;id<21;id++){
        Upgrade_List.push_back(temp);
    }
    Upgrade_List[0][1] = 3;
    Upgrade_List[1][1] = 4;
    Upgrade_List[2][1] = 4;
    Upgrade_List[9][1] = 4;
    Upgrade_List[10][1] = 100;
    Upgrade_List[12][1] = 100;
    for (int id = 1; id < Production_Building_type; id++)
    {
        Upgrade_List[14].push_back(0);
        Upgrade_List[14].push_back(0);
    }
    for (int id = 1; id < Production_Building_number; id++)
    {
        Upgrade_List[4].push_back(0);
        Upgrade_List[4].push_back(0);
    }
    for (int id = 1; id < Processing_Building_type; id++)
    {
        Upgrade_List[15].push_back(0);
        Upgrade_List[15].push_back(0);
    }
    for (int id = 1; id < Processing_Building_number; id++)
    {
        Upgrade_List[6].push_back(0);
        Upgrade_List[6].push_back(0);
    }
    for (int id = 1; id < All_Building_type; id++)
    {
        Upgrade_List[20].push_back(0);
        Upgrade_List[20].push_back(0);
    }
    for (int id = 1; id < All_Building_number; id++)
    {
        Upgrade_List[7].push_back(0);
        Upgrade_List[7].push_back(0);
    }
    if (Testmod){
        cout<<"Upgrade_Date initialized"<<'\n';
    }
    // UI Setup
    Grid_Set_Size(Upgrade_List[1][1], Upgrade_List[2][1]);
    Res_Future_List[0] = 10;
    Res_Future_List[5] = -999;
    EGY_Energy = 70;
    EGY_Future_Energy = 30;
    Grid_Reset();
    INV_Reset();
    if (Testmod){
        cout<<'\n';
        cout<<"R_Main initialized"<<'\n';
    }
    Relocate();
}

#endif