#ifndef BUILDING
#define BUILDING

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "..\Display_Module_Class\Class_Pixel.h"
#include "Materials.h"

using namespace std;

const int Processing_Building_type = 1;
const int Processing_Building_number = 3;
const vector<string> Processing_Building_type_list{
  "Processor"
  };
const vector<string> Processing_Building_name_list{
  "Tier/s0/sprocessor",
  "Tier/s1/sprocessor",
  "Tier/s2/sprocessor"
};
const int Production_Building_type = 2;
const int Production_Building_number = 6;
const vector<string> Production_Building_type_list{
  "Producer",
  "Processor"
  };
const vector<string> Production_Building_name_list{
  "Tier/s0/sproducer",
  "Tier/s1/sproducer",
  "Tier/s2/sproducer",
  "Tier/s0/sprocessor",
  "Tier/s1/sprocessor",
  "Tier/s2/sprocessor"
};
const int All_Building_type = 2;
const int All_Building_number = 6;
const vector<string> All_Building_type_list{
  "Producer",
  "Processor"
  };
const vector<string> All_Building_name_list{
  "Tier/s0/sproducer",
  "Tier/s1/sproducer",
  "Tier/s2/sproducer",
  "Tier/s0/sprocessor",
  "Tier/s1/sprocessor",
  "Tier/s2/sprocessor"
};
const int no_each_tier = 4;
const int no_of_t4 = 4;
const vector<string> Default_colour{Red, Yellow, Blue, Green};

class io_building
{
public:
  int item;
  int quantity = 0;
};

class Building
{
private:
  bool TestMod = 0;
  bool TestTEXT = 0;
  bool TestRNG = 0;

public:
  string name;
  vector<Pixel> graphic_S;
  vector<Pixel> description;
  vector<int> output_graphic_size_S{6, 6};
  vector<io_building> input_list;
  vector<io_building> output_list;
  int duration = -1;

private:
  vector<int> graphic_size{11, 4};
  vector<string> unprocessed_graphic;
  int req_tier;
  int req_constant;
  int out_tier;
  int out_constant;
  int in_complexity;
  int out_complexity;
  bool costume = 0;

public:
  void Input_type(int id);

private:
  void type_process();
  void normal_refresh();
  void basestat_bounus();
  void finalstat_bounus();
  void Costume_initialize();
  void Generate_Description();
};

void Building::basestat_bounus()
{
  1;
}

void Building::finalstat_bounus()
{
  1;
}

void Building::normal_refresh()
{
  finalstat_bounus();
  graphic_S.clear();
  Pixel temp_pixel;

  temp_pixel.colour = White;
  temp_pixel.text = "⬇";
  graphic_S.push_back(temp_pixel);

  for (int x = 0; x < input_list.size(); x++)
  {
    temp_pixel.text = "/s";
    graphic_S.push_back(temp_pixel);
    graphic_S.push_back(Materials_Graphic(input_list[x].item));
  }
  temp_pixel.colour = White;
  temp_pixel.text = "/s";
  for (int x = 1 + (input_list.size() * 2); x < graphic_size[0]; x++)
  {
    graphic_S.push_back(temp_pixel);
  }

  vector<string> colour_tape(graphic_size[0], Black);
  int counter = 0;
  vector<int> size_of_colour(no_each_tier, -1);
  switch (output_list.size())
  {
  case 1:
    size_of_colour[0] = 11;
    break;
  case 2:
    size_of_colour[0] = 5;
    size_of_colour[1] = 6;
    break;
  case 3:
    size_of_colour[0] = 4;
    size_of_colour[1] = 3;
    size_of_colour[2] = 4;
    break;
  case 4:
    size_of_colour[0] = 2;
    size_of_colour[1] = 3;
    size_of_colour[2] = 3;
    size_of_colour[3] = 3;
    break;
  default:
    cout << '\n'
         << "Error: Unknown number of output item" << '\n';
  }

  for (int id = 0; id < output_list.size(); id++)
  {
    string temp_colour;
    if (output_list[id].item < (no_each_tier * 3))
    {
      temp_colour = Default_colour[output_list[id].item % no_each_tier];
    }
    else
    {
      temp_colour = White;
    }
    for (int x = 0; x < size_of_colour[id]; x++)
    {
      colour_tape[counter] = temp_colour;
      counter++;
    }
  }

  if ((counter != graphic_size[0]))
  {
    cout << '\n'
         << "Building Colourtapes Error: Wrong Size" << '\n';
    cout << "counter: " << counter << '\n';
    exit(0);
  }
  for (int y = 0; y < graphic_size[1]; y++)
  {
    for (int x = 0; x < graphic_size[0]; x++)
    {
      temp_pixel.text = unprocessed_graphic[y * graphic_size[0] + x];
      if (temp_pixel.text == "0")
      {
        temp_pixel.text = "/s";
      }
      temp_pixel.colour = colour_tape[x];
      graphic_S.push_back(temp_pixel);
    }
  }

  temp_pixel.colour = White;
  temp_pixel.text = "⬇";
  graphic_S.push_back(temp_pixel);

  for (int x = 0; x < output_list.size(); x++)
  {
    temp_pixel.text = "/s";
    graphic_S.push_back(temp_pixel);
    graphic_S.push_back(Materials_Graphic(output_list[x].item));
  }
  temp_pixel.colour = White;
  temp_pixel.text = "/s";
  for (int x = 1 + (output_list.size() * 2); x < graphic_size[0]; x++)
  {
    graphic_S.push_back(temp_pixel);
  }
  if (TestMod)
  {
    cout << '\n'
         << "graphic_S size: " << graphic_S.size() << '\n';
  }
  Generate_Description();
}

void Building::Costume_initialize()
{
  graphic_S.clear();
  if (name == "Empty/sSpace")
  {
    Pixel temp;
    temp.text = "/s";
    for (int id = 0; id < graphic_size[0] * (graphic_size[1] + 2); id++)
    {
      graphic_S.push_back(temp);
    }
  }
  if (TestMod)
  {
    cout << '\n'
         << "Blank object created" << '\n'
         << "graphic_S size: " << graphic_S.size() << '\n';
  }
}

void Building::Generate_Description()
{
  description.clear();
  vector<string> text_raw_1;
  if (!costume)
  {
    vector<string> text_temp{
        "Name:",
        "Input:",
        "Output:",
        "Duration:"};
    text_temp[0] += name;
    text_temp[3] += to_string(duration);
    if (input_list.size()==0){
      text_temp[1] += "/s";
      text_temp[1] += "None";
    }
    for (int x = 0; x < input_list.size(); x++)
    {
      text_temp[1] += "/s";
      text_temp[1] += to_string(input_list[x].quantity);
      text_temp[1] += "/";
      if (input_list[x].item<10){
        text_temp[1]+="0";
      }
      text_temp[1] += to_string(input_list[x].item);
    }
    for (int x = 0; x < output_list.size(); x++)
    {
      text_temp[2] += "/s";
      text_temp[2] += to_string(output_list[x].quantity);
      text_temp[2] += "/";
      if (output_list[x].item<10){
        text_temp[2]+="0";
      }
      text_temp[2] += to_string(output_list[x].item);
    }
    if (TestTEXT){
      cout<<'\n';
      for (int id = 0;id<text_temp.size();id++){
        cout<<"line "<<id<<' '<<text_temp[id]<<'\n';
      }
    }
    text_raw_1=text_temp;
  }
  else
  {
    ;
  }
  string text_raw_2;
  for (int id = 0; id < text_raw_1.size(); id++)
  {
    int count = 0;
    for (int length = 0; length < text_raw_1[id].size(); length++)
    {
      if (text_raw_1[id][length] == '/')
      {
        if (text_raw_1[id][length+1] == 's'){
          count++;
        }
        else{
          count++;
          count++;
        }
      }
    }
    text_raw_2 += text_raw_1[id];
    for (int length = text_raw_1[id].size() - count; length < 33; length++)
    {
      text_raw_2 += "/s";
    }
  }
  if (TestTEXT){
    cout<<'\n'<<text_raw_2<<'\n';
  }
  description = To_Pixel(text_raw_2);
}

void Building::type_process()
{
  // id of item(int element) start at 0
  // input generation
  input_list.clear();
  output_list.clear();
  int input_variance = req_tier * no_each_tier;
  vector<int> element_used;
  for (int x = 0; x < input_variance; x++)
  {
    element_used.push_back(x);
  }
  int input_temp;
  io_building temp_io;
  for (double x = 1 + ((in_complexity - pow(in_complexity, 0.7)) * ((rand() % 81) + 70) / 100); x > 0; x--)
  {
    if (TestMod && TestRNG)
    {
      cout << "inputRNG: " << x << '\n';
    }
    if ((element_used.size()) > 0)
    {
      input_temp = rand() % element_used.size();
      temp_io.item = element_used[input_temp];
      element_used.erase(element_used.begin() + input_temp);
      input_list.push_back(temp_io);
    }
  }
  while (req_constant > 0)
  {
    input_temp = rand() % input_list.size();
    int cost = input_list[input_temp].item / graphic_size[1];
    cost = pow(cost, (((rand() % graphic_size[1]) + 9) / 10));
    input_list[input_temp].quantity++;
    req_constant -= cost;
  }
  // output generation
  int output_variance, output_st;
  if (out_tier < out_complexity + 1)
  {
    output_st = 0;
    if (out_tier > 3)
    {
      output_variance = 3 * no_each_tier;
      output_variance += no_of_t4;
    }
    else
    {
      output_variance = out_tier * no_each_tier;
    }
  }
  else
  {
    if (out_complexity > 2)
    {
      output_variance = 3 * no_each_tier;
      output_variance += no_of_t4;
    }
    else
    {
      output_variance = (out_complexity + 1) * no_each_tier;
    }
    output_st = (out_tier - out_complexity - 1) * no_each_tier;
  }
  element_used.clear();
  for (int x = output_st; x < output_st + output_variance; x++)
  {
    element_used.push_back(x);
  }
  int output_temp;
  for (double x = 1 + ((out_complexity - pow(out_complexity, 0.7)) * ((rand() % 81) + 70) / 100); x > 0; x--)
  {
    if (TestMod && TestRNG)
    {
      cout << "outputRNG: " << x << '\n';
    }
    if ((element_used.size()) > 0)
    {
      output_temp = rand() % element_used.size();
      temp_io.item = element_used[output_temp];
      element_used.erase(element_used.begin() + output_temp);
      output_list.push_back(temp_io);
    }
  }
  while (out_constant > 0)
  {
    output_temp = rand() % output_list.size();
    int cost = output_list[output_temp].item / graphic_size[1];
    cost = pow(cost, (((rand() % graphic_size[1]) + 9) / 10));
    output_list[output_temp].quantity++;
    out_constant -= cost;
  }
  if (TestMod)
  {
    cout << '\n'
         << "Input size: " << input_list.size() << '\n';
    cout << "Output size: " << output_list.size() << '\n';
  }
  normal_refresh();
}

// Generate a building item in random
void Building::Input_type(int id)
{
  // output/input tier:
  // 0:no in/output
  // 1:can in/output tier1 materials
  // 2:can in/output tier2 materials
  // 3:can in/output tier3 materials
  // 4:can in/output tier4 materials
  if (id == 0)
  {
    name = "Tier/s0/sproducer";
    vector<string> temp_vector{
        "0", "0", "╔", "═", "═", "═", "═", "═", "═", "═", "╗",
        "0", "╔", "╣", "0", "0", "0", "■", "0", "0", "0", "║",
        "╔", "╩", "╩", "═", "═", "═", "═", "═", "═", "═", "╣",
        "╚", "═", "═", "═", "═", "═", "═", "═", "═", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier = 0;
    req_constant = 0;
    out_tier = 1;
    out_constant = 10;
    in_complexity = 1;
    out_complexity = 1;
    duration = 10;
  }
  else if (id == 1)
  {
    name = "Tier/s1/sproducer";
    vector<string> temp_vector{
        "0", "0", "╔", "═", "═", "═", "═", "═", "═", "═", "╗",
        "0", "╔", "╣", "0", "■", "0", "■", "0", "0", "0", "║",
        "╔", "╩", "╩", "╦", "═", "═", "═", "╦", "═", "═", "╣",
        "╚", "═", "═", "╩", "═", "═", "═", "╩", "═", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier = 0;
    req_constant = 0;
    out_tier = 1;
    out_constant = 13;
    in_complexity = 2;
    out_complexity = 2;
    duration = 12;
  }
  else if (id == 2)
  {
    name = "Tier/s2/sproducer";
    vector<string> temp_vector{
        "0", "0", "╔", "╩", "═", "╬", "═", "╦", "═", "═", "╗",
        "0", "╔", "╣", "0", "■", "║", "■", "║", "■", "0", "║",
        "╔", "╩", "╩", "╦", "═", "╩", "═", "╬", "═", "═", "╣",
        "╚", "═", "═", "╩", "═", "═", "═", "╩", "═", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier = 0;
    req_constant = 0;
    out_tier = 2;
    out_constant = 18;
    in_complexity = 3;
    out_complexity = 3;
    duration = 14;
  }
  else if (id == 3)
  {
    name = "Tier/s0/sprocessor";
    vector<string> temp_vector{
        "0", "╔", "═", "═", "═", "═", "═", "═", "═", "╗", "0",
        "╔", "╝", "0", "0", "0", "▲", "0", "0", "0", "╚", "╗",
        "╠", "═", "═", "╦", "═", "═", "═", "╦", "═", "═", "╣",
        "╚", "═", "═", "╝", "0", "0", "0", "╚", "═", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier = 1;
    req_constant = 10;
    out_tier = 2;
    out_constant = 10;
    in_complexity = 1;
    out_complexity = 1;
    duration = 10;
  }
  else if (id == 4)
  {
    name = "Tier/s1/sprocessor";
    vector<string> temp_vector{
        "0", "╔", "═", "═", "═", "═", "═", "═", "═", "╗", "0",
        "╔", "╣", "0", "▲", "0", "▲", "0", "0", "0", "╠", "╗",
        "╠", "╩", "═", "╦", "═", "═", "═", "╦", "═", "╩", "╣",
        "╚", "═", "═", "╝", "0", "0", "0", "╚", "═", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier = 1;
    req_constant = 10;
    out_tier = 2;
    out_constant = 14;
    in_complexity = 2;
    out_complexity = 2;
    duration = 12;
  }
  else if (id == 5)
  {
    name = "Tier/s2/sprocessor";
    vector<string> temp_vector{
        "0", "╔", "═", "═", "═", "═", "═", "═", "═", "╗", "0",
        "╔", "╣", "0", "▲", "0", "▲", "0", "▲", "0", "╠", "╗",
        "╠", "╩", "╦", "╦", "═", "╦", "═", "╦", "╦", "╩", "╣",
        "╚", "═", "╩", "╝", "0", "╩", "0", "╚", "╩", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier = 2;
    req_constant = 12;
    out_tier = 3;
    out_constant = 20;
    in_complexity = 3;
    out_complexity = 3;
    duration = 14;
  }
  else if (id == 6)
  {
    name = "Empty/sSpace";
    costume = 1;
  }
  else
  {
    cout << "Input Error: Unknown Building id" << '\n';
    exit(0);
  }
  if (TestMod)
  {
    cout << '\n'
         << "name: " << name << '\n';
    cout << "req_tier: " << req_tier << '\n';
    cout << "req_constant: " << req_constant << '\n';
    cout << "out_tier: " << out_tier << '\n';
    cout << "out_constant: " << out_constant << '\n';
    cout << "in_complexity: " << in_complexity << '\n';
    cout << "out_complexity: " << out_complexity << '\n';
    cout << "duration: " << duration << '\n';
  }
  if (!costume)
  {
    basestat_bounus();
    type_process();
  }
  else
  {
    Costume_initialize();
  }
}

#endif