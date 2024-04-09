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

private:
    void I_Refresh();
    void I_Output();
    vector<char> input_stack;
};

// Clear all temp data stored in Main
// Then re-input all needed data
void Input::I_Refresh()
{
    if (I_TestMod)
    {
        cout << '\n'
             << "Refreshed" << '\n';
    }
    R_Main.Clear();
    D_Main.Refresh();
}

void Input::I_Output()
{
    if (I_TestMod)
    {
        cout << '\n'
             << "Outputed" << '\n';
    }
    R_Main.Render_Output();
    cout << "\x1B[2J\x1B[H" << flush;
    R_Main.Render_Print();
}

void Input::Execute_Command()
{
    for (int id = 0; id < input_stack.size(); id++)
    {
        switch (toupper(input_stack[id]))
        {
        case 'W':
            I_Refresh();
            R_Main.Move(1);
            break;
        case 'S':
            I_Refresh();
            R_Main.Move(2);
            break;
        case 'A':
            I_Refresh();
            R_Main.Move(3);
            break;
        case 'D':
            I_Refresh();
            R_Main.Move(4);
            break;
        default:
            if (I_TestMod)
            {
                cout << '\n'
                     << "Command not found" << '\n';
            }
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
    const vector<char> Available_char{'w', 'W', 'a', 'A', 's', 'S', 'd', 'D'};
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
                input_stack.push_back(input[id]);
                if (I_TestMod)
                {
                    cout << "Stack: " << input[id] << '\n';
                }
            }
        }
    }
}

#endif