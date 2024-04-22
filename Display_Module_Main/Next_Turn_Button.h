#ifndef NTB
#define NTB

#include <iostream>
#include <string>
#include <vector>
#include "..\Display_Module_Class\Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Next_Turn_Button
{
private:
    bool NTB_Testmod = 0;

private:
    int NTB_highlight_id;
    int NTB_selectable;

protected:
    vector<int> NTB_st_xy{0, 0};
    vector<int> NTB_Size{9, 0};
    void NTB_Output();

protected:
    string NTB_Layer_name = "Map";
};

void Next_Turn_Button::NTB_Output(){
    NTB_selectable=Selectable_List[6];
    int counter =(NTB_Size[1]-(NTB_Size[1]%2))/2;
    string text="";
    for (int no = 0;no<counter;no++){
        text+="00000000000000000";
    }
    text+="0000Next0Turn0000";
    counter =((NTB_Size[1]+(NTB_Size[1]%2))/2)-1;
    for (int no = 0;no<counter;no++){
        text+="00000000000000000";
    }
    vector <Pixel> Output;
    Pixel temp;
    if (End_turn_able){
        temp.colour = B_Yellow;
    }
    else{
        temp.colour = B_Red;
    }
    for (int id = 0; id < text.size(); id++)
    {
        if (text[id] == '0')
        {
            temp.text = "/s";
        }
        else
        {
            temp.text = text[id];
        }
        Output.push_back(temp);
    }
    vector <int> en_xy{NTB_st_xy[0]+NTB_Size[0]-1,NTB_st_xy[1]+NTB_Size[1]-1};
    if (End_turn_able){
        NTB_highlight_id = R_Main.Add_Textbox("NTB_T", NTB_selectable, NTB_highlight_id, NTB_Layer_name, Output, NTB_st_xy, en_xy, 0);
    }
    else{
        NTB_highlight_id = R_Main.Add_Textbox("NTB_F", NTB_selectable, NTB_highlight_id, NTB_Layer_name, Output, NTB_st_xy, en_xy, 0);
    }
}

#endif