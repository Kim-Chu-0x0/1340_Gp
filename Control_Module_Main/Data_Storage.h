#ifndef DataS
#define DataS

#include <iostream>
#include <string>
#include <vector>
#include "..\Display_Module_Main\Draw_Button.h"
#include "..\Display_Module_Main\Map_Grid.h"
#include "..\Display_Module_Main\Resources_Display.h"

using namespace std;

class Data_Storage : public Map_Grid, public Resources_Display, public Draw_Button{
    private:
        bool Testmod=0;
    public:
        void Initialize();
        void Refresh();
    private:
        void Relocate();
};

void Data_Storage::Refresh(){    
    Grid_Output();
    Res_Output();
    Draw_Output();
    if (Testmod){
        cout<<'\n'<<"D_Main refreshed"<<'\n';
    }
}

void Data_Storage::Relocate(){
    Res_st_xy[0]=0;
    Res_st_xy[1]=0;
    Grid_st_xy[0]=Res_Size[0]+Res_st_xy[0]+1;
    Grid_st_xy[1]=Res_st_xy[1];
    Draw_st_xy[0]=Res_st_xy[0];
    Draw_st_xy[1]=Grid_st_xy[1]+Grid_Size[1]-Draw_Size[1];
}

void Data_Storage::Initialize(){
    Grid_Set_Size(4,3);
    Grid_Reset();
    Relocate();
}

#endif