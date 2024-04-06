#ifndef MATERIAL
#define MATERIAL

#include <string>
#include "..\Display_Module_Class\Class_Pixel.h"

using namespace std;

Pixel Materials_Graphic(int id)
{
    Pixel output;
    output.colour = White;
    switch (id)
    {
    case 0:
        output.colour = Red;
        output.text = "☀";
        break;
    case 1:
        output.colour = Yellow;
        output.text = "☀";
        break;
    case 2:
        output.colour = Blue;
        output.text = "☀";
        break;
    case 3:
        output.colour = Green;
        output.text = "☀";
        break;
    case 4:
        output.colour = Red;
        output.text = "✦";
        break;
    case 5:
        output.colour = Yellow;
        output.text = "✦";
        break;
    case 6:
        output.colour = Blue;
        output.text = "✦";
        break;
    case 7:
        output.colour = Green;
        output.text = "✦";
        break;
    case 8:
        output.colour = Red;
        output.text = "✇";
        break;
    case 9:
        output.colour = Yellow;
        output.text = "✇";
        break;
    case 10:
        output.colour = Blue;
        output.text = "✇";
        break;
    case 11:
        output.colour = Green;
        output.text = "✇";
        break;
    case 12:
        output.text = "𖦹";
        break;
    case 13:
        output.text = "♬";
        break;
    case 14:
        output.text = "☁";
        break;
    case 15:
        output.text = "𖤘";
        break;
    }
    return output;
}

#endif