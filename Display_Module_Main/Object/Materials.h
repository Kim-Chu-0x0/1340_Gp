#ifndef MATERIAL
#define MATERIAL

#include <string>
#include "Display_Module_CLass/Class_Pixel.h"

;using namespace std;

Pixel Materials_Graphic(int id)
{
    Pixel output;
    output.colour = White;
    if (Setting_List[0]==0){
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
            output.text = "☊";
            break;
        case 13:
            output.text = "♬";
            break;
        case 14:
            output.text = "☁";
            break;
        case 15:
            output.text = "⇕";
            break;
        case 16:
            output.colour = H_Yellow;
            output.text = "⧰";
            break;
        }
    }
    else{
        switch (id)
        {
        case 0:
            output.colour = Red;
            output.text = "*";
            break;
        case 1:
            output.colour = Yellow;
            output.text = "*";
            break;
        case 2:
            output.colour = Blue;
            output.text = "*";
            break;
        case 3:
            output.colour = Green;
            output.text = "*";
            break;
        case 4:
            output.colour = Red;
            output.text = "+";
            break;
        case 5:
            output.colour = Yellow;
            output.text = "+";
            break;
        case 6:
            output.colour = Blue;
            output.text = "+";
            break;
        case 7:
            output.colour = Green;
            output.text = "+";
            break;
        case 8:
            output.colour = Red;
            output.text = "@";
            break;
        case 9:
            output.colour = Yellow;
            output.text = "@";
            break;
        case 10:
            output.colour = Blue;
            output.text = "@";
            break;
        case 11:
            output.colour = Green;
            output.text = "@";
            break;
        case 12:
            output.text = "#";
            break;
        case 13:
            output.text = "$";
            break;
        case 14:
            output.text = "%";
            break;
        case 15:
            output.text = "&";
            break;
        case 16:
            output.colour = H_Yellow;
            output.text = "~";
            break;
        }
    }
    return output;
}

// Special escapes:
//  "/"+(00-16)
//  "/s"
vector<Pixel> To_Pixel(string Input)
{
    vector<Pixel> Output;
    Pixel temp;
    for (int id = 0; id < Input.size(); id++)
    {
        if (Input[id] == '/')
        {
            if (Input[id + 1] == 's')
            {
                temp.text = "/s";
                Output.push_back(temp);
                id++;
            }
            else
            {
                id++;
                id++;
                Output.push_back(Materials_Graphic((int(Input[id - 1] - '0') * 10) + int(Input[id] - '0')));
            }
        }
        else
        {
            temp.text = Input[id];
            Output.push_back(temp);
        }
    }
    return Output;
}
#endif