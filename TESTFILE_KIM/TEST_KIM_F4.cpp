//for testing input module
#include <iostream>
#include <string>
#include <vector>
#include "..\Control_Module_Main\Action_Process.h"
Action_Processor R_Main;

#include "..\Display_Module_Main\Data_Storage.h"
Data_Storage D_Main;

#include "..\Control_Module_Main\Input.h"
Input I_Main;

using namespace std;

int main(){
    R_Main.Set_Size(50,30);
    R_Main.Add_Layer_object("Map",2);
    R_Main.Add_Layer_object("PopUp",1);
    R_Main.Add_Layer_object("Setting",0);
    D_Main.Initialize();
    for (int ff=0;ff<200;ff++){
        I_Main.Read_input();
        I_Main.Execute_Command();
    }
}