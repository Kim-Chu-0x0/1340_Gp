#ifndef ACTION_P
#define ACTION_P

#include <iostream>
#include <string>
#include <vector>
#include "..\Control_Module_Class\Class_Action.h"
#include "..\Display_Module_Class\Class_Render.h"

using namespace std;

//a render object R_Main must be created before this headfile is called
//Render R_Main;

//store the action to be performed when player input (e.g.WASD)
class Action_Processor{
    private:
        bool TestMod=1;

    public:
        int Add_Textbox(int Textbox_id,string Layer_id,vector <int>St_pt,vector <int>En_pt);
    private:
        vector <vector <int>>St_pt_list;
        vector <vector <int>>En_pt_list;
    
    private:
        //check if any textbox being highlighted yet
        bool Highlight_occ=0;
        //store id of Textboxed of Layer objects
        vector <vector <int> > Layer_Textbox_id;
        //store which textbox is chosen to be highlighted
        int Highlight_Choice_Textbox=0;
        //store which Layer's highlight will be triggered 
        string Highlight_Choice_Layer="Map";
    
    private:
        void Clear(){
            St_pt_list.clear();
            En_pt_list.clear();
        }
};

int Action_Processor::Add_Textbox(int Textbox_id,string Layer_id,vector <int>St_pt,vector <int>En_pt){
    En_pt[0]++;
    En_pt[1]++;
    En_pt[0]++;
    En_pt[1]++;
    St_pt_list.push_back(St_pt);
    En_pt_list.push_back(En_pt);
}

#endif