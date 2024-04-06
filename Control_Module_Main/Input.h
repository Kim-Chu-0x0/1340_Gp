#ifndef INPUT
#define INPUT

#include <iostream>
#include <string>
#include <vector>
#include "Action_Process.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Input{
    private:
        bool I_TestMod=0;
    public:
        void Read_input();
        vector <char> input_stack;
};

void Input::Read_input(){
    const vector <char> Available_char{'w','W','a','A','s','S','d','D'};
    string input;
    getline(cin,input);
    for (int id=0;id<input.size();id++){
        for (int id_2=0;id_2<input.size();id_2++){
            if (input[id]==Available_char[id_2]){
                input_stack.push_back(input[id]);
                if(I_TestMod){
                    cout<<"Stack: "<<input[id]<<'\n';
                }
            }
        }
    }
}

#endif