#ifndef UPG
#define UPG

#include <iostream>
#include <string>
#include <vector>
#include "..\Display_Module_Class\Class_Pixel.h"
#include "Materials.h"

using namespace std;

//Type:
// 0 : Extra Card per draw (Min3 Max5)
// 1 : Extend Map Horizontaly
// 2 : Extend Map Vertically
// 3 : Extra Resource Output (All)
// 4 : Extra Resource Output (Specific Building)
// 5 : Reduce Resource Intakes (All)
// 6 : Reduce Resource Intakes (Specific Building)
// 7 : Increase Duration (All)
// 8 : Increase Duration (Specific Building)
// 9 : Extra Inventory Slot
// 10 : Increase Luck
// 11 : Increase Energy Regeneration
// 12 : Increase Maximum Energy
// 13 : Longer Preperation Time Before Disaster
// 14 : Increase Resource Output (Specific Type)
// 15 : Reduce Resource Intakes (Specific Type)
// 16 : Gain Extra Life
// 17 : Less Draw Consumption
// 18 : Receive T1 Resource Every Turn
class Upgrade
{
    // testing
private:
    bool TestMod = 0;

public:
    int type=0;
    int level=0;
};

#endif