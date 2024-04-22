#ifndef ACTION_P
#define ACTION_P

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Display_Module_Main/Object/Display_Module_CLass/Class_Render.h"

using namespace std;

class Action_Processor : public Render
{
private:
    bool A_P_TestMod = 0;
    bool A_P_TestMod_detail = 0;

public:
    int Move(int direction);
    int Switch_Layer(string name);
    void Restore_Textbox_id(int id);

public:
    void Initialize();
    string Current_Item_Name;
    void Refresh_Current_Name()
    {
        if (A_P_TestMod){
            cout<<'\n'<<"Refresh_Current_Name"<<'\n';
        }
        Highlight_Refresh();
        AP_Layer_Location = Layer_id_search(Highlight_Choice_Layer);
        Textbox_Location = Textbox_id_search(Highlight_Choice_Textbox_id[AP_Layer_Location], AP_Layer_Location);
        Current_Item_Name = Layer_Textbox_name[AP_Layer_Location][Textbox_Location];
        for (int id = 0; id < Layer_no; id++)
        {
            Layer_Textbox_id[id].clear();
            Layer_Textbox_position[id].clear();
            Layer_Textbox_name[id].clear();
        }
    }

public:
    int AP_Layer_Location;
private:
    int Textbox_Location;
};

void Action_Processor::Initialize()
{
    Set_Size(80, 42);
    Add_Layer_object("Map", 2);
    Add_Layer_object("PopUp_Map", 1);
    Add_Layer_object("Setting", 0);
}

void Action_Processor::Restore_Textbox_id(int id){
    Highlight_Choice_Textbox_id[AP_Layer_Location]=id;
}

// Move between selectable textboxes
// 1:Up 2:Down 3:Left 4:Right
int Action_Processor::Move(int direction)
{
    if (A_P_TestMod)
    {
        switch (direction)
        {
        case 1:
            cout << '\n'
                 << "Action: Up" << '\n';
            break;
        case 2:
            cout << '\n'
                 << "Action: Down" << '\n';
            break;
        case 3:
            cout << '\n'
                 << "Action: Left" << '\n';
            break;
        case 4:
            cout << '\n'
                 << "Action: Right" << '\n';
            break;
        }
        cout << '\n'
             << "Layer name: " << Highlight_Choice_Layer << '\n';
        cout << "Current Item id: " << Highlight_Choice_Textbox_id[AP_Layer_Location] << '\n';
    }
    const int Distance_threshold_1 = 0;
    const int Distance_threshold_2 = 10;
    // fetch all required data

    // This list is not in order, plz do not use id to access it
    // To get the correct item, plz use A_P_Textbox_position[id]
    vector<vector<int>> A_P_st_pt = Layer_list[Layer_position[AP_Layer_Location]].Textbox_St;
    // This list is not in order, plz do not use id to access it
    // To get the correct item, plz use A_P_Textbox_position[id]
    vector<vector<int>> A_P_en_pt = Layer_list[Layer_position[AP_Layer_Location]].Textbox_En;
    vector<int> A_P_Layer_Textbox_id = Layer_Textbox_id[AP_Layer_Location];
    vector<int> A_P_Textbox_position = Layer_Textbox_position[AP_Layer_Location];
    vector<int> Present_st_pt = A_P_st_pt[A_P_Textbox_position[Textbox_Location]];
    vector<int> Present_en_pt = A_P_en_pt[A_P_Textbox_position[Textbox_Location]];
    if (A_P_TestMod)
    {
        cout << "Stpt: " << Present_st_pt[0] << " " << Present_st_pt[1] << '\n';
        cout << "Enpt: " << Present_en_pt[0] << " " << Present_en_pt[1] << '\n';
    }
    A_P_Layer_Textbox_id.erase(A_P_Layer_Textbox_id.begin() + Textbox_Location);
    A_P_Textbox_position.erase(A_P_Textbox_position.begin() + Textbox_Location);
    if (A_P_TestMod_detail)
    {
        for (int id = 0; id < A_P_Textbox_position.size(); id++)
        {
            cout << '\n'
                 << "Item id: " << A_P_Layer_Textbox_id[id] << '\n';
            cout << "Position: " << A_P_Textbox_position[id] << '\n';
            cout << "Stpt: " << Layer_list[Layer_position[AP_Layer_Location]].Textbox_St[A_P_Textbox_position[id]][0] << " " << Layer_list[Layer_position[AP_Layer_Location]].Textbox_St[A_P_Textbox_position[id]][1] << '\n';
            cout << "Enpt: " << Layer_list[Layer_position[AP_Layer_Location]].Textbox_En[A_P_Textbox_position[id]][0] << " " << Layer_list[Layer_position[AP_Layer_Location]].Textbox_En[A_P_Textbox_position[id]][1] << '\n';
        }
    }
    // Filter unavalible textbox
    vector<int> perpendicular_distance, parallel_distance;
    vector<bool> pass(A_P_Layer_Textbox_id.size(), 1);
    switch (direction)
    {
    // Up
    case 1:
        for (int id = 0; id < A_P_Layer_Textbox_id.size(); id++)
        {
            if (A_P_st_pt[A_P_Textbox_position[id]][1] > Present_en_pt[1])
            {
                if (A_P_TestMod_detail)
                {
                    cout << '\n'
                         << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step1" << '\n';
                }
                pass[id] = 0;
            }
            else if (!((A_P_st_pt[A_P_Textbox_position[id]][0] < Present_en_pt[0] + Distance_threshold_1) && (A_P_en_pt[A_P_Textbox_position[id]][0] + Distance_threshold_1 > Present_st_pt[0])))
            {
                if (A_P_TestMod_detail)
                {
                    cout << '\n'
                         << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step2" << '\n';
                }
                pass[id] = 0;
            }
            else
            {
                if (Present_st_pt[1] - A_P_en_pt[A_P_Textbox_position[id]][1] > Distance_threshold_2)
                {
                    if (A_P_TestMod_detail)
                    {
                        cout << '\n'
                             << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step3" << '\n';
                    }
                    pass[id] = 0;
                }
                else
                {
                    perpendicular_distance.push_back(Present_st_pt[1] - A_P_en_pt[A_P_Textbox_position[id]][1]);
                    if (A_P_st_pt[A_P_Textbox_position[id]][0] > (Present_st_pt[0] + Present_en_pt[0]) / 2)
                    {
                        parallel_distance.push_back(A_P_st_pt[A_P_Textbox_position[id]][0] - ((Present_st_pt[0] + Present_en_pt[0]) / 2));
                    }
                    else
                    {
                        parallel_distance.push_back(((Present_st_pt[0] + Present_en_pt[0]) / 2) - A_P_en_pt[A_P_Textbox_position[id]][0]);
                    }
                }
            }
        }
        break;
    // Down
    case 2:
        for (int id = 0; id < A_P_Layer_Textbox_id.size(); id++)
        {
            if (A_P_en_pt[A_P_Textbox_position[id]][1] < Present_st_pt[1])
            {
                if (A_P_TestMod_detail)
                {
                    cout << '\n'
                         << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step1" << '\n';
                }
                pass[id] = 0;
            }
            else if (!((A_P_st_pt[A_P_Textbox_position[id]][0] < Present_en_pt[0] + Distance_threshold_1) && (A_P_en_pt[A_P_Textbox_position[id]][0] + Distance_threshold_1 > Present_st_pt[0])))
            {
                if (A_P_TestMod_detail)
                {
                    cout << '\n'
                         << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step2" << '\n';
                }
                pass[id] = 0;
            }
            else
            {
                if (A_P_st_pt[A_P_Textbox_position[id]][1] - Present_en_pt[1] > Distance_threshold_2)
                {
                    if (A_P_TestMod_detail)
                    {
                        cout << '\n'
                             << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step3" << '\n';
                    }
                    pass[id] = 0;
                }
                else
                {
                    perpendicular_distance.push_back(A_P_st_pt[A_P_Textbox_position[id]][1] - Present_en_pt[1]);
                    if (A_P_st_pt[A_P_Textbox_position[id]][0] > (Present_st_pt[0] + Present_en_pt[0]) / 2)
                    {
                        parallel_distance.push_back(A_P_st_pt[A_P_Textbox_position[id]][0] - ((Present_st_pt[0] + Present_en_pt[0]) / 2));
                    }
                    else
                    {
                        parallel_distance.push_back(((Present_st_pt[0] + Present_en_pt[0]) / 2) - A_P_en_pt[A_P_Textbox_position[id]][0]);
                    }
                }
            }
        }
        break;
    // Left
    case 3:
        for (int id = 0; id < A_P_Layer_Textbox_id.size(); id++)
        {
            if (A_P_st_pt[A_P_Textbox_position[id]][0] > Present_en_pt[0])
            {
                if (A_P_TestMod_detail)
                {
                    cout << '\n'
                         << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step1" << '\n';
                }
                pass[id] = 0;
            }
            else if (!((A_P_st_pt[A_P_Textbox_position[id]][1] < Present_en_pt[1] + Distance_threshold_1) && (A_P_en_pt[A_P_Textbox_position[id]][1] + Distance_threshold_1 > Present_st_pt[1])))
            {
                if (A_P_TestMod_detail)
                {
                    cout << '\n'
                         << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step2" << '\n';
                }
                pass[id] = 0;
            }
            else
            {
                if (Present_st_pt[0] - A_P_en_pt[A_P_Textbox_position[id]][0] > Distance_threshold_2)
                {
                    if (A_P_TestMod_detail)
                    {
                        cout << '\n'
                             << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step3" << '\n';
                    }
                    pass[id] = 0;
                }
                else
                {
                    perpendicular_distance.push_back(Present_st_pt[0] - A_P_en_pt[A_P_Textbox_position[id]][0]);
                    if (A_P_st_pt[A_P_Textbox_position[id]][1] > (Present_st_pt[1] + Present_en_pt[1]) / 2)
                    {
                        parallel_distance.push_back(A_P_st_pt[A_P_Textbox_position[id]][1] - ((Present_st_pt[1] + Present_en_pt[1]) / 2));
                    }
                    else
                    {
                        parallel_distance.push_back(((Present_st_pt[1] + Present_en_pt[1]) / 2) - A_P_en_pt[A_P_Textbox_position[id]][1]);
                    }
                }
            }
        }
        break;
    // Right
    case 4:
        for (int id = 0; id < A_P_Layer_Textbox_id.size(); id++)
        {
            if (A_P_en_pt[A_P_Textbox_position[id]][0] < Present_st_pt[0])
            {
                if (A_P_TestMod_detail)
                {
                    cout << '\n'
                         << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step1" << '\n';
                }
                pass[id] = 0;
            }
            else if (!((A_P_st_pt[A_P_Textbox_position[id]][1] < Present_en_pt[1] + Distance_threshold_1) && (A_P_en_pt[A_P_Textbox_position[id]][1] + Distance_threshold_1 > Present_st_pt[1])))
            {
                if (A_P_TestMod_detail)
                {
                    cout << '\n'
                         << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step2" << '\n';
                }
                pass[id] = 0;
            }
            else
            {
                if (A_P_st_pt[A_P_Textbox_position[id]][0] - Present_en_pt[0] > Distance_threshold_2)
                {
                    if (A_P_TestMod_detail)
                    {
                        cout << '\n'
                             << "Item id: " << A_P_Layer_Textbox_id[id] << " was removed in step3" << '\n';
                    }
                    pass[id] = 0;
                }
                else
                {
                    perpendicular_distance.push_back(A_P_st_pt[A_P_Textbox_position[id]][0] - Present_en_pt[0]);
                    if (A_P_st_pt[A_P_Textbox_position[id]][1] > (Present_st_pt[1] + Present_en_pt[1]) / 2)
                    {
                        parallel_distance.push_back(A_P_st_pt[A_P_Textbox_position[id]][1] - ((Present_st_pt[1] + Present_en_pt[1]) / 2));
                    }
                    else
                    {
                        parallel_distance.push_back(((Present_st_pt[1] + Present_en_pt[1]) / 2) - A_P_en_pt[A_P_Textbox_position[id]][1]);
                    }
                }
            }
        }
        break;
    }
    for (int id = pass.size() - 1; id >= 0; id--)
    {
        if (!pass[id])
        {
            A_P_Layer_Textbox_id.erase(A_P_Layer_Textbox_id.begin() + id);
            A_P_st_pt.erase(A_P_st_pt.begin() + A_P_Textbox_position[id]);
            A_P_en_pt.erase(A_P_en_pt.begin() + A_P_Textbox_position[id]);
        }
    }
    if (A_P_Layer_Textbox_id.size() == 0)
    {
        if (A_P_TestMod)
        {
            cout << '\n'
                 << "Movement " << direction << " invalid" << '\n';
        }
        return 0;
    }
    int min_id = 0;
    for (int id = 0; id < A_P_Layer_Textbox_id.size(); id++)
    {
        if (perpendicular_distance[id] < perpendicular_distance[min_id])
        {
            min_id = id;
        }
    }
    int min_value = perpendicular_distance[min_id];
    for (int id = A_P_Layer_Textbox_id.size() - 1; id >= 0; id--)
    {
        if (perpendicular_distance[id] > min_value)
        {
            A_P_Layer_Textbox_id.erase(A_P_Layer_Textbox_id.begin() + id);
            A_P_st_pt.erase(A_P_st_pt.begin() + A_P_Textbox_position[id]);
            A_P_en_pt.erase(A_P_en_pt.begin() + A_P_Textbox_position[id]);
            parallel_distance.erase(parallel_distance.begin() + id);
            perpendicular_distance.erase(perpendicular_distance.begin() + id);
        }
    }
    min_id = 0;
    for (int id = 0; id < A_P_Layer_Textbox_id.size(); id++)
    {
        if (parallel_distance[id] < parallel_distance[min_id])
        {
            min_id = id;
        }
    }
    Highlight_Choice_Textbox_id[AP_Layer_Location] = A_P_Layer_Textbox_id[min_id];
    if (A_P_TestMod)
    {
        cout << '\n'
             << "Result id: " << A_P_Layer_Textbox_id[min_id] << '\n';
    }
    return 0;
}

int Action_Processor::Switch_Layer(string name)
{
    for (int id = 0; id < Layer_id.size(); id++)
    {
        if (Layer_id[id] == name)
        {
            Highlight_Choice_Layer = name;
            if (A_P_TestMod)
            {
                cout << '\n'
                     << "Layer switch to " << name << '\n';
            }
            return 0;
        }
    }
    cout << '\n'
         << "(Switch_Layer)Error: Layer " << name << " not found" << '\n';
    exit(0);
}

#endif