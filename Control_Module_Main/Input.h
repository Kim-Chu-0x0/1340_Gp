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
    else if (type == "Draw")
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
    vector<int> Key{W, A, S, D, Q, E};
    if (I_TestMod)
    {
        cout << "Selecting Command: " << Key[Command] << '\n';
    }
    return Key[Command];
}

void Input::Initialize()
{
    R_Main.Initialize();
    if (I_TestMod)
    {
        cout << '\n';
        cout << "R_Main initialized" << '\n';
    }
    D_Main.Initialize();
    if (I_TestMod)
    {
        cout << "D_Main initialized" << '\n';
    }
    I_Refresh();
    I_Output();
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
        if (Ref){
            R_Main.Refresh_Current_Name();
        }
        //*****************Edit action here***************************
        switch (Key_to_Action(R_Main.Current_Item_Name, input_stack[id]))
        {
        case 0:
            Ref = 0;
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