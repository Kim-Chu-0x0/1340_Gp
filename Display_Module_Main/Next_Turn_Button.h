#ifndef NTB
#define NTB

#include <iostream>
#include <string>
#include <vector>
#include "..\Display_Module_Class\Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class NT_Button
{
private:
    bool NTB_Testmod = 0;

private:
    int NTB_highlight_id;
    int NTB_selectable;

protected:
    vector<int> DUI_st_xy{0, 0};
    vector<int> DUI_Size{0, 0};
    void NTB_Output();

private:
    void NTB_Refresh_Pos();

protected:
    string NTB_Layer_name = "Map";
};

#endif