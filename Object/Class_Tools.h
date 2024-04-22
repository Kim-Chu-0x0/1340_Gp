#ifndef TOOL
#define TOOL

#include <iostream>
#include <string>
#include <vector>
#include "../Display_Module_Class/Class_Pixel.h"
#include "Materials.h"

using namespace std;

class Tool
{
    // testing
private:
    bool TestMod = 0;
    bool TestText = 0;

public:
    int type = 0;
    double value = 0;
    vector<Pixel> description;
    void Input_Type(int id);
};

void Tool::Input_Type(int id)
{
    type = id;
    int temp;
    switch (id)
    {
    case 2:
        temp = 20 * Upgrade_List[10][1] / 100;
        value = 20 + rand() % (temp);
        break;
    case 4:
        temp = 1 * Upgrade_List[10][1] / 100;
        value = int(1 + rand() % (temp));
        break;
    case 5:
        temp = 30 * Upgrade_List[10][1] / 100;
        value = 20 + rand() % (temp);
        break;
    case 6:
        temp = 22 * Upgrade_List[10][1] / 100;
        value = 12 + rand() % (temp);
        break;
    case 7:
        temp = 14 * Upgrade_List[10][1] / 100;
        value = 5 + rand() % (temp);
        break;
    default:
        value = 1;
        break;
    }
    vector<string> insert_list;
    string value_string = to_string(value).substr(0, 4);
    string raw_text = ",";
    switch (id)
    {
    case 0:
        raw_text += "Move-position-of-a-Building";
        break;
    case 1:
        raw_text += "Demolish-a-Building";
        break;
    case 2:
        insert_list.push_back(value_string);
        raw_text += "Restore-lifespan-of a-Building,by-//%(Of-maximum-value)";
        break;
    case 3:
        raw_text += "Prevent-energy-lost-due-to,corruption-this-turn";
        break;
    case 4:
        insert_list.push_back(value_string);
        raw_text += "Gain-//-Free-Draw";
        break;
    case 5:
        insert_list.push_back(value_string);
        raw_text += "Gain-//-T1-resource,(All-type)";
        break;
    case 6:
        insert_list.push_back(value_string);
        raw_text += "Gain-//-T2-resource,(All-type)";
        break;
    case 7:
        insert_list.push_back(value_string);
        raw_text += "Gain-//-T3-resource,(All-type)";
        break;
    }
    int text_pos = 0;
    string pros_text1, pros_text2;
    for (int id = 0; id < insert_list.size(); id++)
    {
        for (; !(raw_text[text_pos] == '/' && raw_text[text_pos + 1] == '/'); text_pos++)
        {
            pros_text1 += raw_text[text_pos];
        }
        pros_text1 += insert_list[id];
        text_pos++;
        text_pos++;
    }
    for (; text_pos < raw_text.size(); text_pos++)
    {
        pros_text1 += raw_text[text_pos];
    }
    if (insert_list.size() == 0)
    {
        pros_text1 = raw_text;
    }
    if (TestText)
    {
        cout << '\n'
             << "pros_text1: " << pros_text1 << '\n';
    }
    for (int id = 0; id < pros_text1.size(); id++)
    {
        if (pros_text1[id] == '-')
        {
            pros_text2 += "/s";
        }
        else
        {
            pros_text2 += pros_text1[id];
        }
    }
    if (TestText)
    {
        cout << '\n'
             << "pros_text2: " << pros_text2 << '\n';
    }
    pros_text1 = "";
    vector<Pixel> Output = To_Pixel(pros_text2);
    Pixel space;
    space.text = "/s";
    int counter = 0;
    for (int id = Output.size() - 1; id >= 0; id--)
    {
        counter++;
        if (Output[id].text == ",")
        {
            Output[id] = space;
            for (int time = counter; time < 33; time++)
            {
                Output.insert(Output.begin() + id + counter, space);
            }
            counter = 0;
        }
    }
    Output.erase(Output.begin());
    Output.push_back(space);
    description = Output;
    if (TestMod)
    {
        cout << '\n'
             << "Tools description generation completed" << '\n';
    }
    if (TestText)
    {
        cout << '\n'
             << "Size: " << Output.size() << '\n';
    }
}

#endif