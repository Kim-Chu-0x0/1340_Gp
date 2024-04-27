#ifndef Sett
#define Sett

#include <iostream>
#include <string>
#include <vector>
#include "Object/Materials.h"
#include "Object/Display_Module_CLass/Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Setting
{
private:
    bool SET_Testmod = 0;

private:
    int SET_selectable;
    int SET_highlight_id = 0;
    vector <int> SET_Popup_highlight_id{0,0,0};
    void SET_reset_size(){
        SET_Popup_st_xy[0] = (Screen_Size[0] / 2) - (SET_Popup_Size[0] / 2);
        SET_Popup_st_xy[1] = (Screen_Size[1] / 2) - (SET_Popup_Size[1] / 2);
    }

protected:
    vector<int> SET_st_xy{0, 0};
    vector<int> SET_Popup_st_xy{0, 0};
    vector<int> SET_Size{5, 2};
    vector<int> SET_Popup_Size{30, 6};
    void SET_Output();
    string SET_Layer_name = "Map";
    string SET_Popup_Layer_name = "Setting";
    int SET_Phase;
};

void Setting::SET_Output()
{
    SET_selectable = Selectable_List[8];
    vector<Pixel> Output_Map;
    vector<int> en_xy{SET_st_xy[0] + SET_Size[0] - 1, SET_st_xy[1] + SET_Size[1] - 1};
    Pixel temp_pixel;
    string temp = string("000010000") + "0Setting0";
    for (int id = 0; id < temp.size(); id++)
    {
        if (temp[id] == '0')
        {
            temp_pixel.text = "/s";
        }
        else if (temp[id] == '1'){
            temp_pixel.text = "⚙";
        }
        else
        {
            temp_pixel.text = temp[id];
        }
        Output_Map.push_back(temp_pixel);
    }
    SET_highlight_id = R_Main.Add_Textbox("Setting", SET_selectable, SET_highlight_id, SET_Layer_name, Output_Map, SET_st_xy, en_xy, 0);
    if (SET_Phase==1){
        SET_reset_size();
        if (Setting_List[0]==0){
            temp_pixel.colour=White;
        }
        else{
            temp_pixel.colour=Green;
        }
        Output_Map.clear();
        temp = string("00000000000") + "ANSI0decode" + "0000Fix0000" + "00000000000";
        for (int id = 0; id < temp.size(); id++)
        {
            if (temp[id] == '0')
            {
                temp_pixel.text = "/s";
            }
            else
            {
                temp_pixel.text = temp[id];
            }
            Output_Map.push_back(temp_pixel);
        }
        vector <int> st_xy{SET_Popup_st_xy[0]+2,SET_Popup_st_xy[1]+1};
        en_xy[0]=st_xy[0]+5;
        en_xy[1]=st_xy[1]+3;
        SET_Popup_highlight_id[0] = R_Main.Add_Textbox("Setting_ANSI", SET_selectable, SET_Popup_highlight_id[0], SET_Popup_Layer_name, Output_Map, st_xy, en_xy, 0);
        temp_pixel.colour=White;
        Output_Map.clear();
        temp = string("00000000000") + "000Save0000" + "000Quit0000" + "00000000000";
        for (int id = 0; id < temp.size(); id++)
        {
            if (temp[id] == '0')
            {
                temp_pixel.text = "/s";
            }
            else
            {
                temp_pixel.text = temp[id];
            }
            Output_Map.push_back(temp_pixel);
        }
        st_xy[0]+=10;
        en_xy[0]=st_xy[0]+5;
        en_xy[1]=st_xy[1]+3;
        SET_Popup_highlight_id[1] = R_Main.Add_Textbox("Setting_Quit", SET_selectable, SET_Popup_highlight_id[1], SET_Popup_Layer_name, Output_Map, st_xy, en_xy, 0);
        Output_Map.clear();
        temp = string("00000000000") + "000Save0000" + "000Game0000" + "00000000000";
        for (int id = 0; id < temp.size(); id++)
        {
            if (temp[id] == '0')
            {
                temp_pixel.text = "/s";
            }
            else
            {
                temp_pixel.text = temp[id];
            }
            Output_Map.push_back(temp_pixel);
        }
        st_xy[0]+=10;
        en_xy[0]=st_xy[0]+5;
        en_xy[1]=st_xy[1]+3;
        SET_Popup_highlight_id[2] = R_Main.Add_Textbox("Setting_Save", SET_selectable, SET_Popup_highlight_id[2], SET_Popup_Layer_name, Output_Map, st_xy, en_xy, 0);
        Output_Map.clear();
        temp_pixel.text = "/s";
        for (int id = 0;id<(((SET_Popup_Size[0]*2)-1)*SET_Popup_Size[1]);id++){
            Output_Map.push_back(temp_pixel);
        }
        en_xy[0]=SET_Popup_st_xy[0]+SET_Popup_Size[0]-1;
        en_xy[1]=SET_Popup_st_xy[1]+SET_Popup_Size[1]-1;
        R_Main.Add_Textbox("", 0, 0, "PopUp_Map", Output_Map, SET_Popup_st_xy, en_xy, 0);
    }
}

#endif