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
    int DUI_highlight_id = 0;

protected:
    vector<int> DUI_st_xy{0, 0};
    vector<int> DUI_Size{9, 4};
    void DUI_Output();

private:
    string DUI_Layer_name = "Map";
};

void Draw_UI::DUI_Output()
{
}

#endif