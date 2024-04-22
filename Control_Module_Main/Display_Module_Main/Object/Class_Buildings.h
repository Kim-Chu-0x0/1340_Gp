#ifndef BUILDING
#define BUILDING

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "Display_Module_CLass/Class_Pixel.h"
#include "Materials.h"

using namespace std;

const int Processing_Building_type = 3;
const int Processing_Building_number = 9;
const vector<string> Processing_Building_type_list{
    "Processor",
    "Extractor",
    "Dismantler"};
const vector<string> Processing_Building_name_list{
    "Tier/s0/sprocessor",
    "Tier/s1/sprocessor",
    "Tier/s2/sprocessor",
    "Tier/s0/sExtractor",
    "Tier/s1/sExtractor",
    "Tier/s2/sExtractor",
    "Tier/s0/sDismantler",
    "Tier/s1/sDismantler",
    "Tier/s2/sDismantler"};
const int Production_Building_type = 4;
const int Production_Building_number = 12;
const vector<string> Production_Building_type_list{
    "Producer",
    "Processor",
    "Extractor",
    "Dismantler"};
const vector<string> Production_Building_name_list{
    "Tier/s0/sproducer",
    "Tier/s1/sproducer",
    "Tier/s2/sproducer",
    "Tier/s0/sprocessor",
    "Tier/s1/sprocessor",
    "Tier/s2/sprocessor",
    "Tier/s0/sExtractor",
    "Tier/s1/sExtractor",
    "Tier/s2/sExtractor",
    "Tier/s0/sDismantler",
    "Tier/s1/sDismantler",
    "Tier/s2/sDismantler"};
const int All_Building_type = 4;
const int All_Building_number = 12;
const vector<string> All_Building_type_list{
    "Producer",
    "Processor",
    "Extractor",
    "Dismantler"};
const vector<string> All_Building_name_list{
    "Tier/s0/sproducer",
    "Tier/s1/sproducer",
    "Tier/s2/sproducer",
    "Tier/s0/sprocessor",
    "Tier/s1/sprocessor",
    "Tier/s2/sprocessor",
    "Tier/s0/sExtractor",
    "Tier/s1/sExtractor",
    "Tier/s2/sExtractor",
    "Tier/s0/sDismantler",
    "Tier/s1/sDismantler",
    "Tier/s2/sDismantler"};
const int no_each_tier = 4;
const int no_of_t4 = 4;
const vector<string> Default_colour{Red, Yellow, Blue, Green};

class io_building
{
public:
  int item;
  int quantity = 0;
  int quantity_base = 0;
};

class Building
{
private:
  bool TestMod = 0;
  bool TestTEXT = 0;
  bool TestRNG = 0;
  bool TestBounus = 0;

public:
  string type;
  string name;
  vector<Pixel> graphic_S;
  vector<Pixel> description;
  vector<int> output_graphic_size_S{6, 6};
  vector<io_building> input_list;
  vector<io_building> output_list;
  int duration = -1;
  int countdown = -1;
  // 1:On 0:Off
  bool On_Off = 1;

private:
  int duration_base = -1;

private:
  int PC_Type = -1;
  int PC_Name = -1;
  int PD_Type = -1;
  int PD_Name = -1;
  int All_Type = -1;
  int All_Name = -1;

private:
  vector<int> graphic_size{11, 4};
  vector<string> unprocessed_graphic;
  vector<bool> req_tier{0,0,0,0};
  int req_constant;
  vector<bool> out_tier{0,0,0,0};
  int out_constant;
  int in_complexity;
  int out_complexity;
  bool costume = 0;

public:
  void Input_type(int id);
  void Refresh_stat();
  void Countdown_St();
  bool Pass_Turn();
  vector<vector<int>> Return_Req();
  vector<int> Get_Disaster_Req();
  void Restore_Lifespan(double value);

private:
  void Search_Location();
  void type_process();
  void normal_refresh();
  void basestat_bounus();
  void finalstat_bounus();
  void Costume_initialize();
  void Generate_Description();
};

void Building::Restore_Lifespan(double value){
  int T_value = (duration* value) /100 ;
  if ((T_value+countdown)>=duration){
    countdown=duration;
  }
  else{
    countdown+=T_value;
  }
}

// return 1 if lifespan <=0
bool Building::Pass_Turn()
{
  if (costume == 0)
  {
    countdown -= 1;
    if (countdown <= 0)
    {
      return 1;
    }
  }
  else if (name == "Disaster")
  {
    countdown += 1;
  }
  return 0;
}

//For Disaster only
vector<int> Building::Get_Disaster_Req(){
  vector<int> Tp_1(17, 0);
  for (int id = 0; id < input_list.size(); id++)
  {
    Tp_1[input_list[id].item] += input_list[id].quantity;
  }
  return Tp_1;
}

vector<vector<int>> Building::Return_Req()
{
  vector<int> Tp_1(17, 0);
  vector<int> Tp_2(17, 0);
  if (On_Off == 1)
  {
    if (name!="Disaster"){
      for (int id = 0; id < input_list.size(); id++)
      {
        Tp_1[input_list[id].item] += input_list[id].quantity;
      }
    }
    if (!(name=="Disaster"&&Other_Buffs[1]>0)){
      for (int id = 0; id < output_list.size(); id++)
      {
        Tp_2[output_list[id].item] += output_list[id].quantity;
      }
    }
  }
  vector<vector<int>> Output{Tp_1, Tp_2};
  return Output;
}

void Building::Countdown_St()
{
  if (costume == 0)
  {
    countdown = duration;
  }
}

void Building::Refresh_stat()
{
  if (costume == 0)
  {
    normal_refresh();
  }
  else if (name == "Disaster")
  {
    output_list[0].quantity = (1+(countdown/2)) * output_list[0].quantity_base;
    Generate_Description();
  }
}

void Building::basestat_bounus()
{
  double Temp_d;
  Temp_d = out_constant;
  Temp_d *= (1.0 + (((Upgrade_List[10][1] / 100) - 1) / 2));
  out_constant = Temp_d;
  Temp_d = req_constant;
  Temp_d /= (1.0 + (((Upgrade_List[10][1] / 100) - 1) / 2));
  req_constant = Temp_d;
  if (TestBounus)
  {
    cout << '\n'
         << "basestat_bounus" << '\n';
    cout << "req_constant: " << req_constant << '\n';
    cout << "out_constant: " << out_constant << '\n';
  }
}

void Building::finalstat_bounus()
{
  if (TestBounus)
  {
    cout << '\n'
         << "finalstat_bounus(before)" << '\n';
    if (input_list.size() != 0)
    {
      cout << "input_list[0]: " << input_list[0].quantity << '\n';
    }
    if (output_list.size() != 0)
    {
      cout << "output_list[0]: " << output_list[0].quantity << '\n';
    }
    cout << "duration: " << duration << '\n';
  }
  double Temp_d;
  double counter = 0;
  if (countdown == -1)
  {
    counter += Upgrade_List[7][1];
    if (All_Type != -1)
    {
      counter += Upgrade_List[20][(All_Type * 2) + 1];
    }
    if (All_Name != -1)
    {
      counter += Upgrade_List[8][(All_Name * 2) + 1];
    }
    Temp_d = duration_base;
    Temp_d *= 1.0 + (counter / 100);
    duration = Temp_d;
    counter = 0;
  }
  counter += Upgrade_List[3][1];
  if (All_Type != -1)
  {
    counter += Upgrade_List[14][(All_Type * 2) + 1];
  }
  if (All_Name != -1)
  {
    counter += Upgrade_List[4][(All_Name * 2) + 1];
  }
  for (int id = 0; id < output_list.size(); id++)
  {
    Temp_d = output_list[id].quantity_base;
    Temp_d *= 1.0 + (counter / 100);
    output_list[id].quantity = Temp_d;
  }
  counter = 0;
  counter += Upgrade_List[5][1];
  if (All_Type != -1)
  {
    counter += Upgrade_List[15][(All_Type * 2) + 1];
  }
  if (All_Name != -1)
  {
    counter += Upgrade_List[6][(All_Name * 2) + 1];
  }
  for (int id = 0; id < input_list.size(); id++)
  {
    Temp_d = input_list[id].quantity_base;
    Temp_d *= 1.0 + (counter / 100);
    input_list[id].quantity = Temp_d;
  }
  if (TestBounus)
  {
    cout << "after" << '\n';
    if (input_list.size() != 0)
    {
      cout << "input_list[0]: " << input_list[0].quantity << '\n';
    }
    if (output_list.size() != 0)
    {
      cout << "output_list[0]: " << output_list[0].quantity << '\n';
    }
    cout << "duration: " << duration << '\n';
  }
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
         << "(normal_refresh)Error: Building Colourtapes: Wrong Size" << '\n';
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
  if ((!On_Off) && (countdown != -1))
  {
    for (int id = 0; id < graphic_S.size(); id++)
    {
      graphic_S[id].colour = White;
    }
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
    if (TestMod)
    {
      cout << '\n'
           << "Blank object created" << '\n'
           << "graphic_S size: " << graphic_S.size() << '\n';
    }
  }
  if (name == "Disaster")
  {
    Pixel temp;
    for (int id = 0; id < graphic_size[0] * (graphic_size[1] + 2); id++)
    {
      temp.set_colour(1 + (rand() % 8));
      switch (rand() % 10)
      {
      case 0:
        temp.text = "@";
        break;
      case 1:
        temp.text = "%";
        break;
      case 2:
        temp.text = "#";
        break;
      case 3:
        temp.text = "$";
        break;
      case 4:
        temp.text = "*";
        break;
      case 5:
        temp.text = "&";
        break;
      case 6:
        temp.text = "?";
        break;
      case 7:
        temp.text = "+";
        break;
      case 8:
        temp.text = "/s";
        break;
      case 9:
        temp.text = "/s";
        break;
      }
      graphic_S.push_back(temp);
    }
    countdown = 1;
    input_list.clear();
    output_list.clear();
    io_building temp_io;

    temp_io.item = 16;
    temp_io.quantity_base = -1 * (5 + rand() % 2) / (1.0 + (((Upgrade_List[10][1] / 100) - 1) / 4));
    output_list.push_back(temp_io);

    vector<int> element_used;
    for (int x = 0; x < 4 * no_each_tier; x++)
    {
      element_used.push_back(x);
    }
    int input_temp;
    for (double x = 3 + (rand() % 4); x > 0; x--)
    {
      if ((element_used.size()) > 0)
      {
        input_temp = rand() % element_used.size();
        temp_io.item = element_used[input_temp];
        element_used.erase(element_used.begin() + input_temp);
        input_list.push_back(temp_io);
      }
    }
    req_constant = 30 + (rand() % 6) + (Turn_No * (3 + (rand() % 2)));
    while (req_constant > 0)
    {
      input_temp = rand() % input_list.size();
      int cost = input_list[input_temp].item / graphic_size[1];
      cost = pow(cost, (((rand() % graphic_size[1]) + 9) / 10));
      input_list[input_temp].quantity++;
      req_constant -= cost;
    }
    Generate_Description();
    if (TestMod)
    {
      cout << '\n'
           << "Disaster created" << '\n'
           << "graphic_S size: " << graphic_S.size() << '\n';
    }
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
    if (countdown != -1)
    {
      text_temp[3] = "Lifespan:";
      text_temp[3] += to_string(countdown);
    }
    else
    {
      text_temp[3] += to_string(duration);
    }
    if (input_list.size() == 0)
    {
      text_temp[1] += "/s";
      text_temp[1] += "None";
    }
    for (int x = 0; x < input_list.size(); x++)
    {
      text_temp[1] += "/s";
      text_temp[1] += to_string(input_list[x].quantity);
      text_temp[1] += "/";
      if (input_list[x].item < 10)
      {
        text_temp[1] += "0";
      }
      text_temp[1] += to_string(input_list[x].item);
    }
    for (int x = 0; x < output_list.size(); x++)
    {
      text_temp[2] += "/s";
      text_temp[2] += to_string(output_list[x].quantity);
      text_temp[2] += "/";
      if (output_list[x].item < 10)
      {
        text_temp[2] += "0";
      }
      text_temp[2] += to_string(output_list[x].item);
    }
    if (countdown != -1)
    {
      if (On_Off)
      {
        text_temp.push_back("State:/sOn");
      }
      else
      {
        text_temp.push_back("State:/sOff");
      }
    }
    if (TestTEXT)
    {
      cout << '\n';
      for (int id = 0; id < text_temp.size(); id++)
      {
        cout << "line " << id << ' ' << text_temp[id] << '\n';
      }
    }
    text_raw_1 = text_temp;
  }
  else
  {
    if (name == "Disaster")
    {
      vector<string> text_temp{"Requirements:"};
      for (int id = 0; id < 1 + ((input_list.size() - 1) / 3); id++)
      {
        text_temp.push_back("");
        for (int no = 0; (no < 3) && (((id * 3) + no) < input_list.size()); no++){
          text_temp[id+1] += "/s";
          text_temp[id+1] += to_string(input_list[((id * 3) + no)].quantity);
          text_temp[id+1] += "/";
          if (input_list[((id * 3) + no)].item < 10)
          {
            text_temp[id+1] += "0";
          }
          text_temp[id+1] += to_string(input_list[((id * 3) + no)].item);
        }
      }
      text_raw_1 = text_temp;
    }
  }
  string text_raw_2;
  for (int id = 0; id < text_raw_1.size(); id++)
  {
    int count = 0;
    for (int length = 0; length < text_raw_1[id].size(); length++)
    {
      if (text_raw_1[id][length] == '/')
      {
        if (text_raw_1[id][length + 1] == 's')
        {
          count++;
        }
        else
        {
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
  if (TestTEXT)
  {
    cout << '\n'
         << text_raw_2 << '\n';
  }
  description = To_Pixel(text_raw_2);
}

void Building::type_process()
{
  // id of item(int element) start at 0
  // input generation
  input_list.clear();
  output_list.clear();
  vector<int> element_used;
  for (int y = 0; y < 4; y++)
  {
    if (req_tier[y]){
      for (int x = 0; x < no_each_tier; x++){
        element_used.push_back(x+(y*no_each_tier));
      }
    }
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
    input_list[input_temp].quantity_base++;
    req_constant -= cost;
  }
  // output generation
  element_used.clear();
  for (int y = 0; y < 4; y++)
  {
    if (out_tier[y]){
      for (int x = 0; x < no_each_tier; x++){
        element_used.push_back(x+(y*no_each_tier));
      }
    }
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
    output_list[output_temp].quantity_base++;
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

void Building::Search_Location()
{
  for (int id = 0; id < Processing_Building_type_list.size(); id++)
  {
    if (Processing_Building_type_list[id] == type)
    {
      PC_Type = id;
    }
  }
  for (int id = 0; id < Processing_Building_name_list.size(); id++)
  {
    if (Processing_Building_name_list[id] == name)
    {
      PC_Name = id;
    }
  }
  for (int id = 0; id < Production_Building_type_list.size(); id++)
  {
    if (Production_Building_type_list[id] == type)
    {
      PD_Type = id;
    }
  }
  for (int id = 0; id < Production_Building_name_list.size(); id++)
  {
    if (Production_Building_name_list[id] == name)
    {
      PD_Name = id;
    }
  }
  for (int id = 0; id < All_Building_type_list.size(); id++)
  {
    if (All_Building_type_list[id] == type)
    {
      All_Type = id;
    }
  }
  for (int id = 0; id < All_Building_name_list.size(); id++)
  {
    if (All_Building_name_list[id] == name)
    {
      All_Name = id;
    }
  }
  if (TestMod)
  {
    cout << '\n'
         << "All_Type= " << All_Type << '\n';
    cout << '\n'
         << "All_Name= " << All_Name << '\n';
    cout << '\n'
         << "PD_Type= " << PD_Type << '\n';
    cout << '\n'
         << "PD_Name= " << PD_Name << '\n';
    cout << '\n'
         << "PC_Type= " << PC_Type << '\n';
    cout << '\n'
         << "PC_Name= " << PC_Name << '\n';
  }
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
    type = "Producer";
    name = "Tier/s0/sproducer";
    vector<string> temp_vector{
        "0", "0", "╔", "═", "═", "═", "═", "═", "═", "═", "╗",
        "0", "╔", "╣", "0", "0", "0", "■", "0", "0", "0", "║",
        "╔", "╩", "╩", "═", "═", "═", "═", "═", "═", "═", "╣",
        "╚", "═", "═", "═", "═", "═", "═", "═", "═", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_constant = 0;
    out_tier[0] = 1;
    out_constant = 10;
    in_complexity = 1;
    out_complexity = 1;
    duration_base = 10;
  }
  else if (id == 1)
  {
    type = "Producer";
    name = "Tier/s1/sproducer";
    vector<string> temp_vector{
        "0", "0", "╔", "═", "═", "═", "═", "═", "═", "═", "╗",
        "0", "╔", "╣", "0", "■", "0", "■", "0", "0", "0", "║",
        "╔", "╩", "╩", "╦", "═", "═", "═", "╦", "═", "═", "╣",
        "╚", "═", "═", "╩", "═", "═", "═", "╩", "═", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_constant = 0;
    out_tier[0] = 1;
    out_constant = 13;
    in_complexity = 2;
    out_complexity = 2;
    duration_base = 12;
  }
  else if (id == 2)
  {
    type = "Producer";
    name = "Tier/s2/sproducer";
    vector<string> temp_vector{
        "0", "0", "╔", "╩", "═", "╬", "═", "╦", "═", "═", "╗",
        "0", "╔", "╣", "0", "■", "║", "■", "║", "■", "0", "║",
        "╔", "╩", "╩", "╦", "═", "╩", "═", "╬", "═", "═", "╣",
        "╚", "═", "═", "╩", "═", "═", "═", "╩", "═", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_constant = 0;
    out_tier[0] = 1;
    out_tier[1] = 1;
    out_constant = 18;
    in_complexity = 3;
    out_complexity = 3;
    duration_base = 14;
  }
  else if (id == 3)
  {
    type = "Processor";
    name = "Tier/s0/sprocessor";
    vector<string> temp_vector{
        "0", "╔", "═", "═", "═", "═", "═", "═", "═", "╗", "0",
        "╔", "╝", "0", "0", "0", "▲", "0", "0", "0", "╚", "╗",
        "╠", "═", "═", "╦", "═", "═", "═", "╦", "═", "═", "╣",
        "╚", "═", "═", "╝", "0", "0", "0", "╚", "═", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier[0] = 1;
    req_constant = 4;
    out_tier[0] = 1;
    out_tier[1] = 1;
    out_constant = 10;
    in_complexity = 1;
    out_complexity = 1;
    duration_base = 10;
  }
  else if (id == 4)
  {
    type = "Processor";
    name = "Tier/s1/sprocessor";
    vector<string> temp_vector{
        "0", "╔", "═", "═", "═", "═", "═", "═", "═", "╗", "0",
        "╔", "╣", "0", "▲", "0", "▲", "0", "0", "0", "╠", "╗",
        "╠", "╩", "═", "╦", "═", "═", "═", "╦", "═", "╩", "╣",
        "╚", "═", "═", "╝", "0", "0", "0", "╚", "═", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier[0] = 1;
    req_constant = 5;
    out_tier[0] = 1;
    out_tier[1] = 1;
    out_constant = 14;
    in_complexity = 2;
    out_complexity = 2;
    duration_base = 12;
  }
  else if (id == 5)
  {
    type = "Processor";
    name = "Tier/s2/sprocessor";
    vector<string> temp_vector{
        "0", "╔", "═", "═", "═", "═", "═", "═", "═", "╗", "0",
        "╔", "╣", "0", "▲", "0", "▲", "0", "▲", "0", "╠", "╗",
        "╠", "╩", "╦", "╦", "═", "╦", "═", "╦", "╦", "╩", "╣",
        "╚", "═", "╩", "╝", "0", "╩", "0", "╚", "╩", "═", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier[0] = 1;
    req_tier[1] = 1;
    req_constant = 6;
    out_tier[1] = 1;
    out_tier[2] = 1;
    out_constant = 20;
    in_complexity = 3;
    out_complexity = 3;
    duration_base = 14;
  }
  else if (id == 6)
  {
    name = "Empty/sSpace";
    costume = 1;
  }
  else if (id == 7)
  {
    name = "Disaster";
    costume = 1;
  }
  else if (id == 8)
  {
    type = "Extractor";
    name = "Tier/s0/sExtractor";
    vector<string> temp_vector{
        "╔", "╗", "0", "╔", "═", "═", "═", "╗", "0", "╔", "╗",
        "║", "║", "0", "║", "0", "●", "0", "║", "0", "║", "║",
        "║", "║", "0", "╚", "═", "═", "═", "╝", "0", "║", "║",
        "╚", "╩", "═", "═", "═", "═", "═", "═", "═", "╩", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier[0] = 1;
    req_tier[1] = 1;
    req_constant = 5;
    out_tier[1] = 1;
    out_tier[2] = 1;
    out_tier[3] = 1;
    out_constant = 12;
    in_complexity = 2;
    out_complexity = 3;
    duration_base = 8;
  }
  else if (id == 9)
  {
    type = "Extractor";
    name = "Tier/s1/sExtractor";
    vector<string> temp_vector{
        "╔", "●", "0", "╔", "═", "═", "═", "╗", "0", "●", "╗",
        "╠", "╗", "0", "║", "0", "0", "0", "║", "0", "╔", "╣",
        "║", "║", "0", "╚", "═", "╦", "═", "╝", "0", "║", "║",
        "╚", "╩", "═", "═", "═", "╩", "═", "═", "═", "╩", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier[0] = 1;
    req_tier[1] = 1;
    req_constant = 6;
    out_tier[1] = 1;
    out_tier[2] = 1;
    out_tier[3] = 1;
    out_constant = 16;
    in_complexity = 2;
    out_complexity = 4;
    duration_base = 9;
  }
  else if (id == 10)
  {
    type = "Extractor";
    name = "Tier/s2/sExtractor";
    vector<string> temp_vector{
        "╔", "●", "0", "╔", "═", "═", "═", "╗", "0", "●", "╗",
        "╠", "╦", "═", "╣", "0", "●", "0", "╠", "═", "╦", "╣",
        "║", "║", "0", "╚", "═", "╦", "═", "╝", "0", "║", "║",
        "╚", "╩", "═", "═", "═", "╩", "═", "═", "═", "╩", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier[0] = 1;
    req_tier[1] = 1;
    req_tier[2] = 1;
    req_constant = 7;
    out_tier[2] = 1;
    out_tier[3] = 1;
    out_constant = 22;
    in_complexity = 2;
    out_complexity = 4;
    duration_base = 12;
  }
  else if (id == 11)
  {
    type = "Dismantler";
    name = "Tier/s0/sDismantler";
    vector<string> temp_vector{
        "╔", "╦", "═", "╦", "═", "╦", "═", "╦", "═", "╦", "╗",
        "0", "║", "0", "0", "0", "𐓏", "0", "0", "0", "║", "0",
        "0", "║", "0", "0", "0", "0", "0", "0", "0", "║", "0",
        "╚", "╩", "═", "╩", "═", "╩", "═", "╩", "═", "╩", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier[1] = 1;
    req_tier[2] = 1;
    req_tier[3] = 1;
    req_constant = 5;
    out_tier[0] = 1;
    out_constant = 22;
    in_complexity = 2;
    out_complexity = 2;
    duration_base = 6;
  }
  else if (id == 12)
  {
    type = "Dismantler";
    name = "Tier/s1/sDismantler";
    vector<string> temp_vector{
        "╔", "╦", "╦", "╦", "═", "╦", "═", "╦", "╦", "╦", "╗",
        "0", "║", "0", "0", "0", "𐓏", "0", "0", "0", "║", "0",
        "0", "║", "0", "╦", "═", "𐓏", "═", "╦", "0", "║", "0",
        "╚", "╩", "═", "╩", "═", "╩", "═", "╩", "═", "╩", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier[1] = 1;
    req_tier[2] = 1;
    req_tier[3] = 1;
    req_constant = 7;
    out_tier[0] = 1;
    out_constant = 24;
    in_complexity = 2;
    out_complexity = 2;
    duration_base = 7;
  }
  else if (id == 13)
  {
    type = "Dismantler";
    name = "Tier/s2/sDismantler";
    vector<string> temp_vector{
        "╔", "╦", "╦", "╦", "═", "╦", "═", "╦", "╦", "╦", "╗",
        "0", "╬", "0", "0", "𐓏", "𐓏", "𐓏", "0", "0", "╬", "0",
        "0", "║", "0", "╦", "╩", "╬", "╩", "╦", "0", "║", "0",
        "╚", "╩", "╩", "╩", "═", "╩", "═", "╩", "╩", "╩", "╝"};
    unprocessed_graphic = temp_vector;
    req_tier[2] = 1;
    req_tier[3] = 1;
    req_constant = 8;
    out_tier[0] = 1;
    out_tier[1] = 1;
    out_constant = 28;
    in_complexity = 2;
    out_complexity = 3;
    duration_base = 8;
  }
  else
  {
    cout << "(Input_type)Error: Unknown Building id" << '\n';
    exit(0);
  }
  if (!costume)
  {
    if (TestMod)
    {
      cout << '\n'
           << "name: " << name << '\n';
      cout << "req_constant: " << req_constant << '\n';
      cout << "out_constant: " << out_constant << '\n';
      cout << "in_complexity: " << in_complexity << '\n';
      cout << "out_complexity: " << out_complexity << '\n';
      cout << "duration_base: " << duration << '\n';
    }
    Search_Location();
    basestat_bounus();
    type_process();
  }
  else
  {
    Costume_initialize();
  }
}

#endif