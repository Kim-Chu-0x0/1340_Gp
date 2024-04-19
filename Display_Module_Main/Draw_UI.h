#ifndef DrawUI
#define DrawUI

#include <iostream>
#include <string>
#include <vector>
#include "..\Object\Materials.h"
#include "..\Display_Module_Class\Class_Render.h"
#include "..\Object\Class_Card.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Draw_UI
{
private:
    bool DUI_Testmod = 0;

private:
    vector <int> DUI_highlight_id;

protected:
    vector<int> DUI_st_xy{0, 0};
    vector<int> DUI_Size{0, 0};
    vector<Card> DUI_item_list;
    int selection=0;
    void DUI_Output();
    void DUI_Draw_Card();
private:
    void DUI_Refresh_Pos();

protected:
    string DUI_Layer_name = "PopUp_1";
};

void Draw_UI::DUI_Draw_Card()
{
    DUI_item_list.clear();
    for (int no = 0;no<Upgrade_List[0][1];no++){
        Card temp;
        temp.Random();
        DUI_item_list.push_back(temp);
        DUI_highlight_id.push_back(0);
    }
}

void Draw_UI::DUI_Refresh_Pos(){
    DUI_Size[0]=(DUI_item_list.size()*(Size_of_icon[0]+1))-1;
    DUI_Size[1]=5+DUI_item_list[selection].Size_of_Description[1];
    DUI_st_xy[0]=(Screen_Size[0]/2)-(DUI_Size[0]/2);
    DUI_st_xy[1]=(Screen_Size[1]/2)-(DUI_Size[1]/2);
}

void Draw_UI::DUI_Output()
{
    selection=0;
    if (DUI_highlight_id[0]!=0){
        for (int id = 0;id<DUI_highlight_id.size();id++){
            if (R_Main.Highlight_Choice_Textbox_id==DUI_highlight_id[id]){
                selection=id;
            }
        }
    }
    DUI_Refresh_Pos();
    for(int id =0;id<DUI_item_list.size();id++){
        vector <int>temp_St{DUI_st_xy[0]+(id*(Size_of_icon[0]+1)),DUI_st_xy[1]};
        vector <int>temp_En{temp_St[0]+(Size_of_icon[0]-1),temp_St[1]+(Size_of_icon[1]-1)};
        DUI_highlight_id[id] = R_Main.Add_Textbox("Card_Draw", 1, DUI_highlight_id[id], DUI_Layer_name, DUI_item_list[id].Graphic, temp_St, temp_En, 0);
        if(DUI_Testmod){
            cout<<'\n'<<"Item "<<id<<" id: "<<DUI_highlight_id[id]<<'\n';
        }
    }
    if(DUI_Testmod){
        cout<<'\n'<<"DUI first part Outputed"<<'\n';
    }
    vector <int>temp_St{DUI_st_xy[0]+((selection-1)*(Size_of_icon[0]+1)),DUI_st_xy[1]+(Size_of_icon[1]+1)};
    if (selection==0){
        temp_St[0]+=(Size_of_icon[0]+1);
    }
    else if(selection==DUI_item_list.size()-1){
        temp_St[0]-=(Size_of_icon[0]+1);
    }
    vector <int>temp_En{temp_St[0]+DUI_item_list[selection].Size_of_Description[0]-1,temp_St[1]+DUI_item_list[selection].Size_of_Description[1]-1};
    R_Main.Add_Textbox("", 0, 0, DUI_Layer_name, DUI_item_list[selection].Description, temp_St, temp_En, 0);
    if(DUI_Testmod){
        cout<<'\n'<<"DUI Output completed"<<'\n';
    }
}

#endif