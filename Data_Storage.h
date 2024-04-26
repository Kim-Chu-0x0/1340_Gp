#ifndef DataS
#define DataS

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Needs to be saved
//  Type:
//   0 : Extra Card per draw (Min3 Max5)
//   1 : Extend Map Horizontaly
//   2 : Extend Map Vertically
//   3 : Extra Resource Output (All)
//   4 : Extra Resource Output (Specific Building)
//   5 : Reduce Resource Intakes (All)
//   6 : Reduce Resource Intakes (Specific Building)
//   7 : Increase Duration (All)
//   8 : Increase Duration (Specific Building)
//   9 : Extra Inventory Slot
//   10 : Increase Luck
//   11 : Increase Energy Regeneration
//   12 : Increase Maximum Energy
//   13 : Longer Preperation Time Before Disaster
//   14 : Increase Resource Output (Specific Type)
//   15 : Reduce Resource Intakes (Specific Type)
//   16 : Gain Extra Life
//   17 : Less Draw Consumption
//   18 : Receive T1 Resource Every Turn
//   19 : Receive 2 Random Upgrades
//   20 : Increase Duration (Specific Type)
//  Format:
//{0:level,1:value 2:level,3:value......}
vector<vector<double>> Upgrade_List;

// 00:Draw
// 01:DUI
// 02:EGY
// 03:INV
// 04:Grid
// 05:Res
// 06:NTB
vector<bool> Selectable_List;

vector<int> Weighting_Tier_List{0, 4, 8, 12, 17, 25, 35, 45, 90};

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
    Weighting_Tier_List[6],
    // Tier 2 producer
    Weighting_Tier_List[4],
    // Tier 0 processor
    Weighting_Tier_List[7],
    // Tier 1 processor
    Weighting_Tier_List[6],
    // Tier 2 processor
    Weighting_Tier_List[4],
    // Tier 0 extractor
    Weighting_Tier_List[6],
    // Tier 1 extractor
    Weighting_Tier_List[5],
    // Tier 2 extractor
    Weighting_Tier_List[3],
    // Tier 0 dismantler
    Weighting_Tier_List[5],
    // Tier 1 dismantler
    Weighting_Tier_List[4],
    // Tier 2 dismantler
    Weighting_Tier_List[2],
    // Tier 0 generator
    Weighting_Tier_List[4],
    // Tier 1 generator
    Weighting_Tier_List[4],
    // Tier 2 generator
    Weighting_Tier_List[3]};

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
    Weighting_Tier_List[5],
    // 10 : Increase Luck
    Weighting_Tier_List[3],
    // 11 : Increase Energy Regeneration
    Weighting_Tier_List[3],
    // 12 : Increase Maximum Energy
    Weighting_Tier_List[3],
    // 13 : Longer Preperation Time Before Disaster
    Weighting_Tier_List[3],
    // 14 : Increase Resource Output (Specific Type)
    Weighting_Tier_List[2],
    // 15 : Reduce Resource Intakes (Specific Type)
    Weighting_Tier_List[3],
    // 16 : Gain Extra Life
    Weighting_Tier_List[1],
    // 17 : Less Draw Consumption
    Weighting_Tier_List[3],
    // 18 : Receive T1 Resource Every Turn
    Weighting_Tier_List[3],
    // 19 : Receive 2 Random Upgrades
    Weighting_Tier_List[0],
    // 20 : Increase Duration (Specific Type)
    Weighting_Tier_List[2]};

int Sum_Upgrade_Weighting, Sum_Building_Weighting, Sum_Tool_Weighting;

vector<int> Screen_Size{0, 0};

// Needs to be saved
//  00 Free Draw
//  01 Prevent 1 round corruption
//  02 Energy level bonus
vector<double> Other_Buffs{0, 0, 0};

bool End_turn_able = 0;

// Needs to be saved
int Turn_No = 0;

// Needs to be saved
int Corruption_gap;
// Needs to be saved
int turn_counter;

// 0:Draw_Button
// 1:Draw_UI
// 2:Energy_Bar
// 3:Inventory
// 4:Map_Grid
// 5:Resources_Display
// 6:Next_Turn_Button
// 7:Stat_Display
vector<bool> Visible{0, 0, 0, 0, 0, 0, 0, 0};

#include "Display_Module_Main/Draw_Button.h"
#include "Display_Module_Main/Map_Grid.h"
#include "Display_Module_Main/Resources_Display.h"
#include "Display_Module_Main/Energy_Bar.h"
#include "Display_Module_Main/Draw_UI.h"
#include "Display_Module_Main/Inventory.h"
#include "Display_Module_Main/Next_Turn_Button.h"
#include "Display_Module_Main/Stat_Display.h"

using namespace std;

class Data_Storage : public Map_Grid, public Resources_Display, public Draw_Button, public Energy_Bar, public Draw_UI, public Inventory, public Next_Turn_Button, public Stat_Display
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
    void Next_turn();

public:
    void Draw(int id);
    void Discard(int id);
    void Fix(int id);
    void Use_INV_item(int id);
    void Building_On_Off();
    int Building_Grid_Selection_Result(int id);

private:
    void Upgrade_Apply(Upgrade input);
    void Relocate();
    void Upgrade_Max_Check();
    void D_Phase_Switch(int id);
    void Availability_Check();
    void Refresh_stat();
    void Restart_Game();

public:
    int slot_id_cache;

private:
    int slot_pos_cache;
    int Situation;
    int Grid_pos_cache;
    Card Card_cache;
    Building Building_cache;

private:
    // Needs to be saved
    int Corruption_no;

    // SL module
public:
    void Save(int id);
    void Load(int id);

private:
    int Auto_Save_counter = 0;
};

void Data_Storage::Restart_Game()
{
    EGY_Energy = 100;
    Grid_Clear_Disasters();
}

void Data_Storage::Building_On_Off()
{
    Grid_Building_On_Off();
}

void Data_Storage::Refresh_stat()
{
    // Energy level bonus
    Other_Buffs[2] = 0.75 + (EGY_Energy_Level() * 0.15);
    INV_Refresh_stat();
    Draw_Refresh_stat();
    Grid_Refresh_stat();
}

void Data_Storage::Availability_Check()
{
    Refresh_stat();
    End_turn_able = 1;
    vector<vector<int>> Result = Cal_Building_req();
    for (int id = 0; id < Res_Future_List.size(); id++)
    {
        Res_Future_List[id] = 0;
        Res_Future_List[id] -= Result[0][id];
    }
    for (int id = 0; id < Res_Resource_List.size(); id++)
    {
        if ((Res_Resource_List[id] + Res_Future_List[id]) >= 0)
        {
            Res_Issue[id] = 0;
        }
        else
        {
            End_turn_able = 0;
            Res_Issue[id] = 1;
        }
    }
    for (int id = 0; id < Res_Future_List.size(); id++)
    {
        Res_Future_List[id] += Result[1][id];
    }
    for (int id = 0; id < 4; id++)
    {
        Res_Future_List[id] += Upgrade_List[18][1];
    }
    EGY_Future_Energy = 0;
    EGY_Future_Energy -= Result[0][16];
    EGY_Future_Energy += Result[1][16];
    EGY_Future_Energy += Upgrade_List[11][1];
    bool blank = 0;
    for (int id = 0; id < Upgrade_List[9][1]; id++)
    {
        if (INV_item_list[id].Type == 0)
        {
            blank = 1;
        }
    }
    if (blank)
    {
        if (EGY_Energy > Draw_Draw_cost)
        {
            Draw_Availability = 1;
        }
        else if (Other_Buffs[0] != 0)
        {
            Draw_Availability = 1;
        }
        else
        {
            Draw_Availability = 0;
        }
    }
    else
    {
        Draw_Availability = 0;
    }
}

void Data_Storage::Next_turn()
{
    if (Corruption_no > 0)
    {
        if (Other_Buffs[1] > 0)
        {
            Other_Buffs[1] -= 1;
        }
    }
    EGY_Energy += EGY_Future_Energy;
    if (EGY_Energy > Upgrade_List[12][1])
    {
        EGY_Energy = Upgrade_List[12][1];
    }
    if (EGY_Energy < 0)
    {
        // Game over
        if (Upgrade_List[16][1] != 0)
        {
            Upgrade_List[16][1] = 0;
            Restart_Game();
        }
        else
        {
            cout << '\n'
                 << "Game Over" << '\n';
            exit(0);
        }
    }
    for (int id = 0; id < Res_Resource_List.size(); id++)
    {
        Res_Resource_List[id] += Res_Future_List[id];
    }
    Grid_Pass_Turn();
    turn_counter += 1;
    if (turn_counter == Corruption_gap)
    {
        turn_counter = 1;
        Corruption_gap = Upgrade_List[13][1] + rand() % 4;
        Turn_No += 1;
        Grid_Plant_Disaster(0);
        Corruption_no += 1;
    }
    Auto_Save_counter++;
    if (Auto_Save_counter > 4)
    {
        Save(0);
        Auto_Save_counter = 0;
    }
}

void Data_Storage ::Upgrade_Apply(Upgrade input)
{
    Upgrade_List[input.type][input.subtype * 2] += 1;
    Upgrade_List[input.type][input.subtype * 2 + 1] += input.value;
    if (input.type == 1 || input.type == 2)
    {
        Check_Size();
    }
    if (input.type == 12)
    {
        EGY_Energy += input.value;
    }
}

void Data_Storage::Discard(int id)
{
    if (id == 0)
    {
        INV_Phase = 1;
    }
    else if (id == 1)
    {
        INV_Phase = 0;
    }
    else if (id == 2)
    {
        INV_Phase = 0;
        INV_Discard();
    }
}

void Data_Storage::Fix(int id)
{
    if (id == 0)
    {
        bool Sus = 1;
        vector<int> Result = Get_Disaster_Req();
        for (int id = 0; id < Res_Resource_List.size(); id++)
        {
            if ((Res_Resource_List[id] - Result[id]) < 0)
            {
                Sus = 0;
            }
        }
        if (Sus)
        {
            Grid_Phase = 2;
        }
        else
        {
            Grid_Phase = 3;
        }
    }
    else if (id == 1)
    {
        Grid_Phase = 0;
    }
    else if (id == 2)
    {
        Grid_Phase = 0;
        vector<int> Result = Get_Disaster_Req();
        for (int id = 0; id < Res_Resource_List.size(); id++)
        {
            Res_Resource_List[id] -= Result[id];
        }
        Grid_Demolish_Building();
        Corruption_no -= 1;
    }
}

void Data_Storage::Use_INV_item(int id)
{
    if (id == 0)
    {
        INV_Phase = 2;
    }
    else if (id == 1)
    {
        INV_Phase = 0;
    }
    else if (id == 2)
    {
        INV_Phase = 0;
        Card_cache = INV_Slot_Output();
        slot_id_cache = INV_selection_id;
        slot_pos_cache = INV_selection;
        INV_Discard();
        if (Card_cache.Type == 2)
        {
            if (Card_cache.T_Data.type == 0)
            {
                Situation = 1;
                D_Phase_Switch(1);
            }
            else if (Card_cache.T_Data.type == 1)
            {
                Situation = 2;
                D_Phase_Switch(1);
            }
            else if (Card_cache.T_Data.type == 2)
            {
                Situation = 3;
                D_Phase_Switch(1);
            }
            else if (Card_cache.T_Data.type == 3)
            {
                Other_Buffs[1] = 1;
            }
            else if (Card_cache.T_Data.type == 4)
            {
                Other_Buffs[0] = 1;
            }
            else if (Card_cache.T_Data.type == 5)
            {
                for (int id = 0; id < 4; id++)
                {
                    Res_Resource_List[id] += Card_cache.T_Data.value;
                }
            }
            else if (Card_cache.T_Data.type == 6)
            {
                for (int id = 0; id < 4; id++)
                {
                    Res_Resource_List[4 + id] += Card_cache.T_Data.value;
                }
            }
            else if (Card_cache.T_Data.type == 7)
            {
                for (int id = 0; id < 4; id++)
                {
                    Res_Resource_List[8 + id] += Card_cache.T_Data.value;
                }
            }
        }
        else if (Card_cache.Type == 3)
        {
            Situation = 0;
            D_Phase_Switch(1);
        }
    }
}

int Data_Storage ::Building_Grid_Selection_Result(int id)
{
    // Place Building
    if (Situation == 0)
    {
        // Hv building Q
        if (id == 0)
        {
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        // Hv building E
        else if (id == 1)
        {
            return 0;
        }
        // No building Q
        else if (id == 2)
        {
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        // No building E
        else if (id == 3)
        {
            Card_cache.B_Data.Countdown_St();
            Grid_Place_Building(Card_cache.B_Data);
            D_Phase_Switch(0);
            return 0;
        }
    }
    // Move Building(1)
    else if (Situation == 1)
    {
        // Hv building Q
        if (id == 0)
        {
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        // Hv building E
        else if (id == 1)
        {
            Grid_pos_cache = Grid_Get_pos();
            Building_cache = Grid_Take_Building();
            Situation = 4;
            return 0;
        }
        // No building Q
        else if (id == 2)
        {
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        // No building E
        else if (id == 3)
        {
            return 0;
        }
    }
    // Demolish Building
    else if (Situation == 2)
    {
        // Hv building Q
        if (id == 0)
        {
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        // Hv building E
        else if (id == 1)
        {
            Grid_Demolish_Building();
            D_Phase_Switch(0);
            return 0;
        }
        // No building Q
        else if (id == 2)
        {
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        // No building E
        else if (id == 3)
        {
            return 0;
        }
    }
    // Restore Building lifespan
    else if (Situation == 3)
    {
        // Hv building Q
        if (id == 0)
        {
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        // Hv building E
        else if (id == 1)
        {
            Grid_Restore_Building(Card_cache.T_Data.value);
            D_Phase_Switch(0);
            return 0;
        }
        // No building Q
        else if (id == 2)
        {
            INV_Fill_Item(slot_pos_cache, Card_cache);
            D_Phase_Switch(0);
            return 1;
        }
        // No building E
        else if (id == 3)
        {
            return 0;
        }
    }
    // Move Building(2)
    else if (Situation == 4)
    {
        // Hv building Q
        if (id == 0)
        {
            vector<int> temp{Grid_pos_cache};
            Grid_Set_Building(temp, Building_cache);
            Situation = 1;
            return 0;
        }
        // Hv building E
        else if (id == 1)
        {
            return 0;
        }
        // No building Q
        else if (id == 2)
        {
            vector<int> temp{Grid_pos_cache};
            Grid_Set_Building(temp, Building_cache);
            Situation = 1;
            return 0;
        }
        // No building E
        else if (id == 3)
        {
            Grid_Place_Building(Building_cache);
            D_Phase_Switch(0);
            return 0;
        }
    }
    return 0;
}

void Data_Storage ::D_Phase_Switch(int id)
{
    // Reset
    if (id == 0)
    {
        Selectable_List[0] = 1;
        Selectable_List[1] = 1;
        Selectable_List[2] = 1;
        Selectable_List[3] = 1;
        Selectable_List[4] = 1;
        Selectable_List[5] = 1;
        Selectable_List[6] = 1;
        Grid_Phase = 0;
    }
    // Building Grid Selection
    else if (id == 1)
    {
        Selectable_List[0] = 0;
        Selectable_List[1] = 0;
        Selectable_List[2] = 0;
        Selectable_List[3] = 0;
        Selectable_List[4] = 1;
        Selectable_List[5] = 0;
        Selectable_List[6] = 0;
        Grid_Phase = 1;
    }
}

void Data_Storage ::Upgrade_Max_Check()
{
    if (Upgrade_List[0][1] == 5)
    {
        Upgrade_Weighting[0] = Weighting_Tier_List[0];
    }
    if (Upgrade_List[1][1] == Grid_Maximum_Size[0])
    {
        Upgrade_Weighting[1] = Weighting_Tier_List[0];
    }
    if (Upgrade_List[2][1] == Grid_Maximum_Size[1])
    {
        Upgrade_Weighting[2] = Weighting_Tier_List[0];
    }
    if (Upgrade_List[9][1] == INV_Max_Size)
    {
        Upgrade_Weighting[9] = Weighting_Tier_List[0];
    }
    if (Upgrade_List[16][0] == 1)
    {
        Upgrade_Weighting[16] = Weighting_Tier_List[0];
    }
}

void Data_Storage::Draw(int id)
{
    if (id == 0)
    {
        if (Other_Buffs[0] != 0)
        {
            Other_Buffs[0] -= 1;
        }
        else
        {
            EGY_Energy -= Draw_Draw_cost;
        }
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
        if (Testmod)
        {
            cout << '\n'
                 << "Sum_Upgrade_Weighting= " << Sum_Upgrade_Weighting << '\n';
            cout << "Sum_Tool_Weighting= " << Sum_Tool_Weighting << '\n';
            cout << "Sum_Building_Weighting= " << Sum_Building_Weighting << '\n';
            cout << "RNG MAX= " << (Sum_Upgrade_Weighting + Sum_Tool_Weighting + Sum_Building_Weighting) << '\n';
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
        Card temp = DUI_Draw_Output();
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
    for (int no = 0; no < Upgrade_Weighting.size(); no++)
    {
        if (id != no)
        {
            Upgrade_Weighting[no] = 0;
        }
    }
    id -= Upgrade_Weighting.size();
    for (int no = 0; no < Tool_Weighting.size(); no++)
    {
        if (id != no)
        {
            Tool_Weighting[no] = 0;
        }
    }
    id -= Tool_Weighting.size();
    for (int no = 0; no < Building_Weighting.size(); no++)
    {
        if (id != no)
        {
            Building_Weighting[no] = 0;
        }
    }
}

void Data_Storage::Refresh_Layer(string id)
{
    Availability_Check();
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
    if ((INV_Layer_name == id) || (INV_Popup_Layer_Name == id))
    {
        if (Visible[3])
        {
            INV_Output();
        }
    }
    if ((Grid_Layer_name == id) || (Grid_Popup_Layer_name == id))
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
    if (Res_Layer_name == id)
    {
        if (Visible[6])
        {
            NTB_Output();
        }
    }
    if (Stat_Layer_name == id)
    {
        if (Visible[7])
        {
            Stat_Output();
        }
    }
}

void Data_Storage::Refresh()
{
    Availability_Check();
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
    if (Visible[6])
    {
        NTB_Output();
    }
    if (Visible[7])
    {
        Stat_Output();
    }

    if (Testmod)
    {
        cout << '\n'
             << "D_Main refreshed" << '\n';
    }
}

void Data_Storage::Relocate()
{
    Stat_st_xy[0] = 0;
    Stat_st_xy[1] = 0;

    Res_st_xy[0] = Stat_st_xy[0];
    Res_st_xy[1] = Stat_st_xy[1] + Stat_Size[1] + 1;

    Grid_st_xy[0] = Res_Size[0] + Res_st_xy[0] + 1;
    Grid_st_xy[1] = Res_st_xy[1];

    Draw_st_xy[0] = Res_st_xy[0];
    Draw_st_xy[1] = Grid_st_xy[1] + Grid_Size[1] - Draw_Size[1];

    NTB_st_xy[0] = Res_st_xy[0];
    NTB_st_xy[1] = Res_st_xy[1] + Res_Size[1] + 1;
    NTB_Size[1] = Draw_st_xy[1] - NTB_st_xy[1] - 1;

    EGY_st_xy[0] = Res_st_xy[0];
    EGY_st_xy[1] = Grid_st_xy[1] + Grid_Size[1] + 1;
    EGY_Size[0] = Grid_st_xy[0] + Grid_Size[0] - EGY_st_xy[0];

    INV_st_xy[0] = Res_st_xy[0];
    INV_st_xy[1] = EGY_st_xy[1] + EGY_Size[1] + 1;

    Screen_Size[0] = EGY_Size[0];
    Screen_Size[1] = INV_st_xy[1] + INV_Size[1];

    R_Main.Set_Size(Screen_Size[0] + 1, Screen_Size[1]);
}

void Data_Storage::Initialize()
{
    for (int id = 0; id < 8; id++)
    {
        Selectable_List.push_back(1);
    }
    Visible[0] = 1;
    Visible[2] = 1;
    Visible[3] = 1;
    Visible[4] = 1;
    Visible[5] = 1;
    Visible[6] = 1;
    Visible[7] = 1;
    if (Testmod)
    {
        cout << '\n'
             << "Visual&Selectable_Date initialized" << '\n';
    }
    // Upgrade Data Initialize
    vector<double> temp{0, 0};
    for (int id = 0; id < 21; id++)
    {
        Upgrade_List.push_back(temp);
    }
    Upgrade_List[0][1] = 3;
    Upgrade_List[1][1] = 4;
    Upgrade_List[2][1] = 4;
    Upgrade_List[9][1] = 4;
    Upgrade_List[10][1] = 100;
    Upgrade_List[11][1] = 20;
    Upgrade_List[12][1] = 100;
    Upgrade_List[13][1] = 14;
    Upgrade_List[17][1] = 100;
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
        Upgrade_List[8].push_back(0);
        Upgrade_List[8].push_back(0);
    }
    if (Testmod)
    {
        cout << "Upgrade_Date initialized" << '\n';
    }
    // Corruption Setup
    Corruption_gap = Upgrade_List[13][1] + rand() % 4;
    turn_counter += 1;
    // UI Setup
    Grid_Set_Size(Upgrade_List[1][1], Upgrade_List[2][1]);
    EGY_Energy = 70;
    Grid_Reset();
    INV_Reset();
    if (Testmod)
    {
        cout << '\n';
        cout << "R_Main initialized" << '\n';
    }
    Relocate();
    Load(0);
}

// Order:
// int Turn_No
// int Corruption_gap
// int turn_counter
// int Corruption_no
// int EGY_Energy
// vector<vector<double>> Upgrade_List
// vector<double> Other_Buffs
// Grid Building Data
// INV Card Data
void Data_Storage::Save(int id)
{
    string file_name = string("Save") + to_string(id) + ".txt";
    ofstream File(file_name);
    File << Turn_No << '\n'
         << '\n';
    File << Corruption_gap << '\n'
         << '\n';
    File << turn_counter << '\n'
         << '\n';
    File << Corruption_no << '\n'
         << '\n';
    File << EGY_Energy << '\n'
         << '\n';
    for (int y = 0; y < Upgrade_List.size(); y++)
    {
        File << Upgrade_List[y].size() << '\n';
        for (int x = 0; x < Upgrade_List[y].size(); x++)
        {
            File << Upgrade_List[y][x] << '\n';
        }
    }
    File << '\n';
    for (int y = 0; y < Other_Buffs.size(); y++)
    {
        File << Other_Buffs[y] << '\n';
    }
    File << '\n';
    vector<string> temp = Grid_Save();
    for (int y = 0; y < temp.size(); y++)
    {
        File << temp[y] << '\n';
    }
    File << '\n';
    temp = INV_Save();
    for (int y = 0; y < temp.size(); y++)
    {
        File << temp[y] << '\n';
    }
    File << '\n';
    temp.clear();
    File.close();
}

void Data_Storage::Load(int id)
{
    string file_name = string("Save") + to_string(id) + ".txt";
    ifstream File(file_name);
    string Line;
    vector <string> temp;
    int counter, subcounter, gap, phase, subcounter2;
    counter = subcounter = gap = phase = subcounter2 = 0;
    while (getline(File, Line))
    {
        // int Turn_No
        if (Line == "")
        {
            phase++;
            counter = 0;
            subcounter = 0;
            subcounter2 = 0;
            gap = 0;
            temp.clear();
        }
        else if (phase == 0)
        {
            Turn_No = stoi(Line);
        }
        // int Corruption_gap
        else if (phase == 1)
        {
            Corruption_gap = stoi(Line);
        }
        // int turn_counter
        else if (phase == 2)
        {
            turn_counter = stoi(Line);
        }
        // int Corruption_no
        else if (phase == 3)
        {
            Corruption_no = stoi(Line);
        }
        // int EGY_Energy
        else if (phase == 4)
        {
            EGY_Energy = stoi(Line);
        }
        // vector<vector<double>> Upgrade_List
        else if (phase == 5)
        {
            if (subcounter == 0)
            {
                gap = stoi(Line);
                subcounter++;
            }
            else if (subcounter == gap+1)
            {
                counter++;
                gap = stoi(Line);
                subcounter = 1;
            }
            else
            {
                Upgrade_List[counter][subcounter - 1] = stod(Line);
                subcounter++;
            }
            //cout<<'\n'<<"counter: "<<counter<<"  subcounter: "<<subcounter<<'\n';
        }
        // vector<double> Other_Buffs
        else if (phase == 6)
        {
            Other_Buffs[counter] = stod(Line);
            counter++;
        }
        // Grid Building Data
        else if (phase == 7)
        {
            cout<<'\n'<<"counter: "<<counter<<"  subcounter: "<<subcounter<<"  subcounter2: "<<subcounter2<<'\n';
            cout<<Line<<'\n';
            if (gap == 0)
            {
                temp.push_back(Line);
                gap = stoi(Line);
                subcounter=1;
                counter++;
            }
            else if (subcounter==gap){
                temp.push_back(Line);
                Grid_Set_Building(temp,counter-1);
                gap=0;
                temp.clear();
            }
            else{
                temp.push_back(Line);
                subcounter++;
            }
        }
        // INV Card Data
        else if (phase == 8)
        {
            cout<<'\n'<<"counter: "<<counter<<"  subcounter: "<<subcounter<<"  subcounter2: "<<subcounter2<<'\n';
            cout<<Line<<'\n';
            if (subcounter == 0)
            {
                subcounter = stoi(Line);
                if (subcounter!=0){
                    temp.push_back(Line);
                }
            }
            else if (subcounter2==0&&subcounter != 0)
            {
                gap=stoi(Line);
                temp.push_back(Line);
                subcounter2=1;
                counter++;
            }
            else if (subcounter2==gap){
                temp.push_back(Line);
                INV_item_list[counter-1].Load_Card(temp);
                subcounter=0;
                subcounter2=0;
                temp.clear();
            }
            else{
                temp.push_back(Line);
                subcounter2++;
            }
        }
    }
    File.close();
}

#endif