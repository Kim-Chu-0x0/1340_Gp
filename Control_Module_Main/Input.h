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
    bool I_TestMod = 0;

public:
    void Read_input();
    void Execute_Command();
    void Initialize();
    int Key_to_Action(string type, char Input_Key);

private:
    void I_Refresh();
    void I_Output();
    vector<char> input_stack;
};

int Input::Key_to_Action(string type, char Input_Key)
{
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

void Input::I_Output()
{
    R_Main.Render_Output();
    if (!I_TestMod){
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
    for (int id = 0; id < input_stack.size(); id++)
    {
        R_Main.Refresh_Current_Name();
        //*****************Edit action here***************************
        switch (Key_to_Action(R_Main.Current_Item_Name, input_stack[id]))
        {
        case 0:
            break;
        // UP
        case 1:
            I_Refresh();
            R_Main.Move(1);
            break;
        // DOWN
        case 2:
            I_Refresh();
            R_Main.Move(2);
            break;
        // LEFT
        case 3:
            I_Refresh();
            R_Main.Move(3);
            break;
        // RIGHT
        case 4:
            I_Refresh();
            R_Main.Move(4);
            break;
        // DRAW CARD
        case 6:
            D_Main.Draw();
            I_Refresh();
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