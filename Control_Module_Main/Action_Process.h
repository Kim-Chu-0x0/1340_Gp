#ifndef ACTION_P
#define ACTION_P

#include <iostream>
#include <string>
#include <vector>
#include "..\Control_Module_Class\Class_Action.h"
#include "..\Display_Module_Class\Class_Render.h"

using namespace std;

class Action_Processor: public Render{
    private:
        bool A_P_TestMod=1;

    private:
        void Move(int direction){
            int Layer_Location=Layer_id_search(Highlight_Choice_Layer);
            int Textbox_Location=Textbox_id_search(Highlight_Choice_Textbox_id,Layer_Location);
        }
};

#endif