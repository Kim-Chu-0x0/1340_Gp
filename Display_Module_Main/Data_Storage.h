#ifndef DataS
#define DataS

#include <iostream>
#include <string>
#include <vector>
#include "Draw_Button.h"
#include "Map_Grid.h"
#include "Resources_Display.h"

using namespace std;

class Data_Storage{
    private:
        Map_Grid Grid;
        Resources_Display Res;
        Draw_Button Draw;
    public:
        void Initialize();
        void Refresh();
    private:
        void Relocate();
};

void Data_Storage::Refresh(){    
    Grid.Output();
    Res.Output();
    Draw.Output();
}

void Data_Storage::Relocate(){
    Res.st_xy[0]=0;
    Res.st_xy[1]=0;
    Grid.st_xy[0]=Res.Size[0]+Res.st_xy[0]+1;
    Grid.st_xy[1]=Res.st_xy[1];
    Draw.st_xy[0]=Res.st_xy[0];
    Draw.st_xy[1]=Grid.st_xy[1]+Grid.Size[1]-Draw.Size[1];
}

void Data_Storage::Initialize(){
    Grid.Set_Size(4,3);
    Grid.Reset();
    Relocate();
}

#endif