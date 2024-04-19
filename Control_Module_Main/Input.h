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
    void Refresh_Layer(string id);
    vector<char> input_stack;
};

int Input::Key_to_Action(string type, char Input_Key)
{
    if (I_TestMod)
    {
        cout << '\n'
             << "Selecting type: " <<type<< '\n';
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
        Q = 8;
        E = 9;
    }
    vector<int> Key{W, A, S, D, Q, E};
    return Key[Command];
}

void Input::Initialize()
{
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

void Input::Execute_Command()
{
    R_Main.Refresh_Current_Name();
    for (int id = 0; id < input_stack.size(); id++)
    {
        //*****************Edit action here***************************
        switch (Key_to_Action(R_Main.Current_Item_Name, input_stack[id]))
        {
        case 0:
            break;
        // UP
        case 1:
            I_Refresh();
            R_Main.Move(1);
            Refresh_Layer(R_Main.Highlight_Choice_Layer);
            break;
        // DOWN
        case 2:
            I_Refresh();
            R_Main.Move(2);
            Refresh_Layer(R_Main.Highlight_Choice_Layer);
            break;
        // LEFT
        case 3:
            I_Refresh();
            R_Main.Move(3);
            Refresh_Layer(R_Main.Highlight_Choice_Layer);
            break;
        // RIGHT
        case 4:
            I_Refresh();
            R_Main.Move(4);
            Refresh_Layer(R_Main.Highlight_Choice_Layer);
            break;
        // DRAW CARD
        case 6:
            D_Main.Draw(0);
            R_Main.Switch_Layer("PopUp_1");
            I_Refresh();
            id=input_stack.size()-1;
            break;
        // DRAW CARD Confirm Selection
        case 7:
            D_Main.Draw(2);
            I_Refresh();
            id=input_stack.size()-1;
            break;
        // DRAW CARD Reverse Selection
        case 8:
            D_Main.Draw(1);
            I_Refresh();
            id=input_stack.size()-1;
            break;
        // DRAW CARD DONE
        case 9:
            D_Main.Draw(3);
            R_Main.Switch_Layer("Map");
            I_Refresh();
            id=input_stack.size()-1;
            break;
        }
        if (id == input_stack.size() - 1)
        {
            I_Output();
        }
    }
    input_stack.clear();
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