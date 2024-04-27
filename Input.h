#ifndef INPUT
#define INPUT

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "Action_Process.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Input
{
private:
    bool I_TestMod = 1;

public:
    void Read_input();
    void Execute_Command();
    void Initialize();
    void Call_Start_Interface();
    int Key_to_Action(string type, char Input_Key);

private:
    void I_Refresh();
    void I_Output();
    void Switch_Layer(string id);
    void Refresh_Layer(string id);
    vector<char> input_stack;
};

int Input::Key_to_Action(string type, char Input_Key)
{
    if (I_TestMod)
    {
        cout << '\n'
             << "Selecting type: " << type << '\n';
    }
    int Command;
    switch (Input_Key)
    {
    case 'W':
        Command = 0;
        break;
    case 'S':
        Command = 2;
        break;
    case 'A':
        Command = 1;
        break;
    case 'D':
        Command = 3;
        break;
    case 'Q':
        Command = 4;
        break;
    case 'E':
        Command = 5;
        break;
    default:
        if (I_TestMod)
        {
            cout << '\n'
                 << "Command not found" << '\n';
        }
        break;
    }
    int W = 1;
    int S = 2;
    int A = 3;
    int D = 4;
    int Q = 0;
    int E = 0;
    //*****************Edit what action to be taken after a key is pressed here***************************
    if (type == "Building")
    {
        E = 5;
    }
    else if (type == "Draw_T")
    {
        E = 6;
    }
    else if (type == "Card_Draw")
    {
        E = 7;
    }
    else if (type == "Card_Draw_CFM")
    {
        W = 0;
        S = 0;
        A = 0;
        D = 0;
        Q = 8;
        E = 9;
    }
    else if (type == "INV_Slot")
    {
        Q = 10;
        E = 11;
    }
    else if (type == "INV_Discard_CFM")
    {
        W = 0;
        S = 0;
        A = 0;
        D = 0;
        Q = 12;
        E = 13;
    }
    else if (type == "INV_Use_CFM")
    {
        W = 0;
        S = 0;
        A = 0;
        D = 0;
        Q = 14;
        E = 15;
    }
    else if (type == "Building_NULL_F")
    {
        Q = 16;
        E = 17;
    }
    else if (type == "Building_NULL_T")
    {
        Q = 18;
        E = 19;
    }
    else if (type == "NTB_T")
    {
        E = 20;
    }
    else if (type == "Disaster")
    {
        E = 21;
    }
    else if (type == "Disaster_Fix_F")
    {
        W = 22;
        S = 22;
        A = 22;
        D = 22;
        Q = 22;
        E = 22;
    }
    else if (type == "Disaster_Fix_T")
    {
        W = 0;
        S = 0;
        A = 0;
        D = 0;
        Q = 22;
        E = 23;
    }
    else if (type == "New_Game")
    {
        E = 24;
    }
    else if (type == "Load_Save")
    {
        E = 25;
    }
    else if (type == "Save_Left_0")
    {
        Q = 26;
        A = 27;
        E = 27;
    }
    else if (type == "Save_Right_0")
    {
        Q = 26;
        D = 28;
        E = 28;
    }
    else if (type == "Save_Left_1")
    {
        Q = 35;
        A = 36;
        E = 36;
    }
    else if (type == "Save_Right_1")
    {
        Q = 35;
        D = 37;
        E = 37;
    }
    else if (type == "Clear_Save")
    {
        Q = 26;
        E = 29;
    }
    else if(type == "Save_Game"){
        Q = 35;
        E = 38;
    }
    else if (type == "Setting"){
        E = 30;
    }
    else if (type == "Setting_ANSI"){
        Q = 31;
        E = 32;
    }
    else if (type == "Setting_Save"){
        Q = 31;
        E = 34;
    }
    else if (type == "Setting_Quit"){
        Q = 31;
        E = 33;
    }
    vector<int> Key{W, A, S, D, Q, E};
    if (I_TestMod)
    {
        cout << "Selecting Command: " << Key[Command] << '\n';
    }
    return Key[Command];
}

void Input::Call_Start_Interface(){
    R_Main.Initialize();
    R_Main.Set_Move_const(5,30);
    if (I_TestMod)
    {
        cout << '\n';
        cout << "R_Main initialized" << '\n';
    }
    D_Main.Call_Start_Interface();
    if (I_TestMod)
    {
        cout << "D_Main initialized" << '\n';
    }
    I_Refresh();
    I_Output();
}

void Input::Initialize()
{
    R_Main.Set_Move_const(-1,-1);
    D_Main.Initialize();
    if (I_TestMod)
    {
        cout << "D_Main initialized" << '\n';
    }
    I_Refresh();
}

// Clear all temp data stored in Main
// Then re-input all needed data
void Input::I_Refresh()
{
    R_Main.Clear();
    D_Main.Refresh();
    if (I_TestMod)
    {
        cout << '\n'
             << "Refreshed" << '\n';
    }
}

void Input::Refresh_Layer(string id)
{
    R_Main.Refresh_Layer(id);
    D_Main.Refresh_Layer(id);
}

void Input::I_Output()
{
    R_Main.Render_Output();
    if (!I_TestMod)
    {
        cout << "\x1B[2J\x1B[H" << flush;
    }
    R_Main.Render_Print();
    if (I_TestMod)
    {
        cout << '\n'
             << "Outputed" << '\n';
    }
}

void Input::Switch_Layer(string id)
{
    R_Main.Switch_Layer(id);
    Refresh_Layer(R_Main.Highlight_Choice_Layer);
    R_Main.Refresh_Current_Name();
}

void Input::Execute_Command()
{
    bool Sus = 0;
    bool Ref = 1;
    int Temp;
    for (int id = 0; id < input_stack.size(); id++)
    {
        if (Ref)
        {
            R_Main.Refresh_Current_Name();
        }
        Ref = 0;
        //*****************Edit action here***************************
        switch (Key_to_Action(R_Main.Current_Item_Name, input_stack[id]))
        {
        case 0:
            Sus = 0;
            break;
        // UP
        case 1:
            Ref = 1;
            Sus = 1;
            Refresh_Layer(R_Main.Highlight_Choice_Layer);
            R_Main.Move(1);
            I_Refresh();
            break;
        // DOWN
        case 2:
            Ref = 1;
            Sus = 1;
            Refresh_Layer(R_Main.Highlight_Choice_Layer);
            R_Main.Move(2);
            I_Refresh();
            break;
        // LEFT
        case 3:
            Ref = 1;
            Sus = 1;
            Refresh_Layer(R_Main.Highlight_Choice_Layer);
            R_Main.Move(3);
            I_Refresh();
            break;
        // RIGHT
        case 4:
            Ref = 1;
            Sus = 1;
            Refresh_Layer(R_Main.Highlight_Choice_Layer);
            R_Main.Move(4);
            I_Refresh();
            break;
        // Building On/Off
        case 5:
            Ref = 1;
            Sus = 1;
            D_Main.Building_On_Off();
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // DRAW CARD
        case 6:
            Ref = 1;
            Sus = 1;
            D_Main.Draw(0);
            Switch_Layer("PopUp_Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // DRAW CARD Confirm Selection
        case 7:
            Ref = 1;
            Sus = 1;
            D_Main.Draw(2);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // DRAW CARD Reverse Selection
        case 8:
            Ref = 1;
            Sus = 1;
            D_Main.Draw(1);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // DRAW CARD DONE
        case 9:
            Ref = 1;
            Sus = 1;
            D_Main.Draw(3);
            Switch_Layer("Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Discard_Inventory_Item
        case 10:
            Ref = 1;
            Sus = 1;
            D_Main.Discard(0);
            Switch_Layer("PopUp_Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Use_Inventory_Item
        case 11:
            Ref = 1;
            Sus = 1;
            D_Main.Use_INV_item(0);
            Switch_Layer("PopUp_Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Discard_Inventory_Item Reverse
        case 12:
            Ref = 1;
            Sus = 1;
            D_Main.Discard(1);
            Switch_Layer("Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Discard_Inventory_Item Confirm
        case 13:
            Ref = 1;
            Sus = 1;
            D_Main.Discard(2);
            Switch_Layer("Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Use_Inventory_Item Reverse
        case 14:
            Ref = 1;
            Sus = 1;
            D_Main.Use_INV_item(1);
            Switch_Layer("Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Use_Inventory_Item Confirm
        case 15:
            Ref = 1;
            Sus = 1;
            D_Main.Use_INV_item(2);
            Switch_Layer("Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Hv Building Q
        case 16:
            Ref = 1;
            Sus = 1;
            Temp = D_Main.Building_Grid_Selection_Result(0);
            if (Temp == 1)
            {
                R_Main.Restore_Textbox_id(D_Main.slot_id_cache);
            }
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Hv Building E
        case 17:
            Ref = 1;
            Sus = 1;
            Temp = D_Main.Building_Grid_Selection_Result(1);
            if (Temp == 1)
            {
                R_Main.Restore_Textbox_id(D_Main.slot_id_cache);
            }
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // No Building Q
        case 18:
            Ref = 1;
            Sus = 1;
            Temp = D_Main.Building_Grid_Selection_Result(2);
            if (Temp == 1)
            {
                R_Main.Restore_Textbox_id(D_Main.slot_id_cache);
            }
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // No Building E
        case 19:
            Ref = 1;
            Sus = 1;
            Temp = D_Main.Building_Grid_Selection_Result(3);
            if (Temp == 1)
            {
                R_Main.Restore_Textbox_id(D_Main.slot_id_cache);
            }
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Next_Turn
        case 20:
            Ref = 1;
            Sus = 1;
            D_Main.Next_turn();
            I_Refresh();
            break;
        // Fix
        case 21:
            Ref = 1;
            Sus = 1;
            D_Main.Fix(0);
            Switch_Layer("PopUp_Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Fix Reverse
        case 22:
            Ref = 1;
            Sus = 1;
            D_Main.Fix(1);
            Switch_Layer("Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Fix Reverse
        case 23:
            Ref = 1;
            Sus = 1;
            D_Main.Fix(2);
            Switch_Layer("Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Start_New_Game
        case 24:
            Ref = 1;
            Sus = 1;
            Initialize();
            id = input_stack.size() - 1;
            break;
        // Select_Save
        case 25:
            Ref = 1;
            Sus = 1;
            D_Main.Save_Selection(0);
            Switch_Layer("Setting");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Quit Select_Save
        case 26:
            Ref = 1;
            Sus = 1;
            D_Main.Save_Selection(1);
            Switch_Layer("Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Select_Save Left
        case 27:
            Ref = 1;
            Sus = 1;
            D_Main.Save_Selection(2);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Select_Save Right
        case 28:
            Ref = 1;
            Sus = 1;
            D_Main.Save_Selection(3);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Select_Save Delete
        case 29:
            Ref = 1;
            Sus = 1;
            D_Main.Save_Selection(4);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Open Setting Page
        case 30:
            Ref = 1;
            Sus = 1;
            D_Main.Setting(0);
            Switch_Layer("Setting");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Close Setting Page
        case 31:
            Ref = 1;
            Sus = 1;
            D_Main.Setting(1);
            Switch_Layer("Map");
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Setting Simple ANSI
        case 32:
            Ref = 1;
            Sus = 1;
            D_Main.Setting(2);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Setting S_Quit
        case 33:
            Ref = 1;
            Sus = 1;
            D_Main.Setting(3);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Setting Save
        case 34:
            Ref = 1;
            Sus = 1;
            D_Main.Setting(4);
            R_Main.Set_Move_const(5,30);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Setting Save Return
        case 35:
            Ref = 1;
            Sus = 1;
            D_Main.Setting(5);
            R_Main.Set_Move_const(-1,-1);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Setting Select_Save Left
        case 36:
            Ref = 1;
            Sus = 1;
            D_Main.Save_Selection(5);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Setting Select_Save Right
        case 37:
            Ref = 1;
            Sus = 1;
            D_Main.Save_Selection(6);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        // Setting Select_Save Save
        case 38:
            Ref = 1;
            Sus = 1;
            D_Main.Save_Selection(7);
            I_Refresh();
            id = input_stack.size() - 1;
            break;
        }
    }
    input_stack.clear();
    if (Sus == 0)
    {
        I_Refresh();
    }
    I_Output();
}

void Input::Read_input()
{
    const vector<char> Available_char{'w', 'W', 'a', 'A', 's', 'S', 'd', 'D', 'q', 'Q', 'e', 'E'};
    string input;
    getline(cin, input);
    if (I_TestMod)
    {
        cout << '\n'
             << "Input length: " << input.size() << '\n';
    }
    for (int id = 0; id < input.size(); id++)
    {
        for (int id_2 = 0; id_2 < Available_char.size(); id_2++)
        {
            if (input[id] == Available_char[id_2])
            {
                input_stack.push_back(toupper(input[id]));
                if (I_TestMod)
                {
                    cout << "Stack: " << input[id] << '\n';
                }
            }
        }
    }
}

#endif