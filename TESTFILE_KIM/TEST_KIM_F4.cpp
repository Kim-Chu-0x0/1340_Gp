//for testing input module
#include <iostream>
#include <string>
#include <vector>
#include "..\Control_Module_Main\Input.h"

using namespace std;

Input I_Main;

int main(){
    cout<<"\e[A";
    I_Main.Read_input();
    for (int id =0;id<I_Main.input_stack.size();id++){
        cout<<"Stack: "<<I_Main.input_stack[id]<<'\n';
    }
}