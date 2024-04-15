#ifndef INV
#define INV

#include <iostream>
#include <string>
#include <vector>
#include "..\Object\Class_Card.h"
#include "..\Display_Module_Class\Class_Render.h"

using namespace std;

// a Render object(or Sub class of Render) R_Main must be created before this headfile is called
// Render R_Main;
class Inventory
{
    // testing
private:
    bool INV_TestMod = 0;

    // item access
protected:
    void INV_Fill_Item(vector<int> xy, Building item);
    void INV_Reset();

protected:
    vector<Card> INV_item_list;
    vector<int> INV_Highlight_Data;

};
#endif