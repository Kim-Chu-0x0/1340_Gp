//for testing output module
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include "..\Object\Class_Buildings.h"
#include "..\Display_Module\Class_Render.h"

using namespace std;

void test();

Render Main;
Pixel Pixel_test;

int main(){
    for (int x=0;x<99;x++){
        srand(x);
        test();
    }
    return 0;
}

void test(){
    cout<<"\x1B[2J\x1B[H";
    Building TEMP;
    vector<int> St{1,1};
    vector<int> En{6,6};
    TEMP.type(0);
    Main.Set_Size(20,20);
    Main.Add_Layer();
    Main.Layer_list[0].Add_Textbox(TEMP.graphic,St,En,0);
    Main.Render_Output();
    Main.Render_Print();
    cin.get();
    cin.get();
    //for(int x=0;x<22;x++){
    //    cout<<"\e[A";
    //}
    //cout<<flush;
}