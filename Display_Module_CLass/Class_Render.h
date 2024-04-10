#ifndef RENDER
#define RENDER

#include <iostream>
#include <string>
#include <vector>
#include "Class_Layer.h"
#include "Class_Pixel.h"
// ╋ ┫ ┣ ┻ ┳ ┓ ┏ ┗ ┛ ┃ ━

using namespace std;

class Render
{
public:
    Render()
    {
    }
    // testing
protected:
    bool TestMod = 0;
    // Add textbox
public:
    // Add textbox to a specific Layer object
    int Add_Textbox(string Item_name, bool Selectable, int input_Textbox_id, string input_Layer_id, vector<Pixel> Text, vector<int> starting_xy, vector<int> endpt_xy, bool Whitespace);

    // Mutate Layer object
public:
    void Add_Layer_object(string id, int position);
    void Remove_Layer_object(string id);
    vector<Layer> Layer_list;

protected:
    // Layer_list[0] will be the layer on top
    // Top [0]->[1]->...->[x]Bottom
    void Add_Layer()
    {
        Layer temp(Screen_Size[0], Screen_Size[1]);
        Layer_list.push_back(temp);
    }

public:
    void Clear()
    {
        Layer_list.clear();
        for (int id = 0; id < Layer_no; id++)
        {
            Add_Layer();
        }
    }
    int Layer_no = 0;

    // ID cache
protected:
    // switch on/off highlight
    bool Enable_Highlight = 1;
    // store the id of Layer objects
    vector<string> Layer_id;
    // store the position of Layer objects
    vector<int> Layer_position;
    // store unique id of Textboxes of Layer objects
    vector<vector<int>> Layer_Textbox_id;
    // store type of Textboxes of Layer objects
    vector<vector<string>> Layer_Textbox_name;
    // store position of Textboxes located in Textbox list in Layer objects
    vector<vector<int>> Layer_Textbox_position;
    // store which textbox is chosen to be highlighted
    int Highlight_Choice_Textbox_id = 1;
    // store which Layer's highlight will be triggered
    string Highlight_Choice_Layer = "Map";
    int Layer_id_search(string input_Layer_id);
    int Textbox_id_search(int input_Textbox_id, int ifany_Layer_Location);

    // Set screen size
public:
    // can only be used once
    void Set_Size(int x_len, int y_len)
    {
        if ((x_len <= 0) || (y_len <= 0))
        {
            cout << '\n'
                 << "Size error, input must be positive numbers" << '\n';
            cout << "Input: x=" << x_len << " y=" << y_len << '\n';
            exit(0);
        }
        Screen_Size[0] = x_len;
        Screen_Size[1] = y_len;
        Clear();
    }

protected:
    // Size of the Screen
    vector<int> Screen_Size{0, 0};

    // Trigger output
public:
    // Trigger output
    void Render_Output();
    // store the output map
    vector<Pixel> Output;
    // Render_Output must be used before Print
    void Render_Print();

protected:
    void Stack_Layer(int id);
};

// Search for the id of Layer object in vector <string> Layer_id
int Render::Layer_id_search(string input_Layer_id)
{
    for (int id = 0; id < Layer_no; id++)
    {
        if (Layer_id[id] == input_Layer_id)
        {
            return id;
        }
    }
    cout << '\n'
         << "Error: Layer ID not found" << '\n';
    exit(0);
}

// Search for the id of Textbox in a Layer in vector <vector <int> > Layer_Textbox_id
int Render::Textbox_id_search(int input_Textbox_id, int Layer_Location)
{
    for (int id = 0; id < Layer_Textbox_id[Layer_Location].size(); id++)
    {
        if (Layer_Textbox_id[Layer_Location][id] == input_Textbox_id)
        {
            return id;
        }
    }
    return -1;
}

void Render::Add_Layer_object(string id, int position)
{
    for (int x = 0; x < Layer_no; x++)
    {
        if (Layer_position[x] == position)
        {
            cout << '\n'
                 << "Error: Layer position occupied" << '\n';
            exit(0);
        }
    }
    Layer_id.push_back(id);
    Layer_position.push_back(position);
    vector<int> temp;
    Layer_Textbox_id.push_back(temp);
    Layer_Textbox_position.push_back(temp);
    vector<string> st_temp;
    Layer_Textbox_name.push_back(st_temp);
    Layer_no++;
    Clear();
}

void Render::Remove_Layer_object(string id)
{
    int Layer_Location = Layer_id_search(id);
    Layer_id.erase(Layer_id.begin() + Layer_Location);
    Layer_position.erase(Layer_position.begin() + Layer_Location);
    Layer_Textbox_id.erase(Layer_Textbox_id.begin() + Layer_Location);
    Layer_Textbox_name.erase(Layer_Textbox_name.begin() + Layer_Location);
    Layer_Textbox_position.erase(Layer_Textbox_position.begin() + Layer_Location);
    Layer_no--;
    Clear();
}

int Render::Add_Textbox(string Item_name, bool Selectable, int input_Textbox_id, string input_Layer_id, vector<Pixel> Text, vector<int> starting_xy, vector<int> endpt_xy, bool Whitespace)
{
    int Layer_Location = Layer_id_search(input_Layer_id);
    Layer_list[Layer_position[Layer_Location]].Add_Textbox(Text, starting_xy, endpt_xy, Whitespace);
    if (Selectable)
    {
        if (input_Textbox_id != 0)
        {
            int Textbox_Location = Textbox_id_search(input_Textbox_id, Layer_Location);
            Layer_Textbox_position[Layer_Location][Textbox_Location] = Layer_list[Layer_position[Layer_Location]].Text_no - 1;
            if (TestMod)
            {
                cout << "Textbox pos:" << Layer_Textbox_position[Layer_Location][Textbox_Location] << '\n';
            }
        }
        else
        {
            Layer_Textbox_id[Layer_Location].push_back(Layer_Textbox_id[Layer_Location].size() + 1);
            Layer_Textbox_name[Layer_Location].push_back(Item_name);
            Layer_Textbox_position[Layer_Location].push_back(Layer_list[Layer_position[Layer_Location]].Text_no - 1);
            if (TestMod)
            {
                cout << "Textbox id:" << Layer_Textbox_id[Layer_Location].size() << '\n';
                cout << "Textbox pos:" << Layer_Textbox_position[Layer_Location][Layer_Textbox_position[Layer_Location].size()] << '\n';
            }
            return Layer_Textbox_id[Layer_Location][Layer_Textbox_id[Layer_Location].size() - 1];
        }
    }
    return input_Textbox_id;
}

void Render::Render_Output()
{
    if (Enable_Highlight && (Highlight_Choice_Textbox_id != 0))
    {
        if (TestMod)
        {
            cout << '\n'
                 << "Highlight started" << '\n';
        }
        int Layer_Location = Layer_id_search(Highlight_Choice_Layer);
        int Textbox_Location = Textbox_id_search(Highlight_Choice_Textbox_id, Layer_Location);
        if (Textbox_Location != -1)
        {
            if (TestMod)
            {
                cout << '\n'
                     << "Highlight object " << Layer_id[Layer_Location] << " " << Layer_Textbox_id[Layer_Location][Textbox_Location] << '\n';
            }
            Layer_list[Layer_position[Layer_Location]].Enable_Highlight = 1;
            Layer_list[Layer_position[Layer_Location]].Highlight_no = Layer_Textbox_position[Layer_Location][Textbox_Location];
        }
    }
    Pixel temp;
    temp.text = " ";
    Output.clear();
    for (int id = 0; id < ((Screen_Size[0] * 2 + 3) * (Screen_Size[1] + 2)); id++)
    {
        Output.push_back(temp);
    }
    for (int id = Layer_no - 1; id >= 0; id--)
    {
        if (Layer_list[id].Text_no != 0)
        {
            Layer_list[id].Output();
            Stack_Layer(id);
        }
    }
    Clear();
}

void Render::Stack_Layer(int id)
{
    for (int y = Layer_list[id].Output_Map_NWT_ST_pt[1]; y < Layer_list[id].Output_Map_NWT_ST_pt[1] + Layer_list[id].Output_Map_NWT_Size[1]; y++)
    {
        for (int x = Layer_list[id].Output_Map_NWT_ST_pt[0]; x < Layer_list[id].Output_Map_NWT_ST_pt[0] + Layer_list[id].Output_Map_NWT_Size[0]; x++)
        {
            int ID = y * ((Screen_Size[0] + 2) * 2 - 1) + x;
            if (!(Layer_list[id].Output_Map[ID].text == " "))
            {
                Output[ID] = Layer_list[id].Output_Map[ID];
            }
        }
    }
}

void Render::Render_Print()
{
    for (int id_y = 0; id_y < (Screen_Size[1] + 2); id_y++)
    {
        for (int id_x = 0; id_x < (Screen_Size[0] * 2 + 3); id_x++)
        {
            if (Output[id_y * (Screen_Size[0] * 2 + 3) + id_x].text == "s/")
            {
                cout << " ";
            }
            else
            {
                Output[id_y * (Screen_Size[0] * 2 + 3) + id_x].print();
            }
        }
        cout << '\n';
    }
    Output.clear();
}

#endif