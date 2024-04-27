// for testing input module
#include <iostream>
#include <string>
#include <vector> 
#include <ctime> 
#include "Action_Process.h"
Action_Processor R_Main;

#include "Data_Storage.h"
Data_Storage D_Main;

#include "Input.h"
Input I_Main;

using namespace std;

int main()
{
    srand(time(0));
    I_Main.Call_Start_Interface();
    //D_Main.Test_Specific_Card(12);
    for (int ff = 0;; ff++)
    {
        I_Main.Read_input();
        I_Main.Execute_Command();
    }
}