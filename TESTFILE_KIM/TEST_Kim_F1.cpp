//For testing display module
#include <iostream>
#include <string>
#include <vector>
#include "../Display_Module_Class/Class_Render.h"

using namespace std;

        //for (string input;input!="Q";input=take_input()){
            //cout<<input<<flush<<'\r'<<"\e[A"<<flush;
        //}

void test();

Render R_Main;
Pixel Pixel_test;

int main(){
    R_Main.Add_Layer_object("Map",0);
    for (int x=0;x<99;x++){
        test();
    }
    return 0;
}

void test(){
    vector<int> Size{15+rand()%20,15+rand()%20};
    cout<<"\x1B[2J\x1B[H";
    for (int x=0;x<20;x++){
        cout<<"\e[A";
    }
    R_Main.Set_Size(Size[0],Size[1]);
    vector<int> St(2,0);
    vector<int> En(2,0);
    for (int no1=0;no1<3+rand()%3;no1++){
        St[0]=rand()%(Size[0]-1);
        St[1]=rand()%(Size[1]-1);
        En[0]=St[0]+rand()%(Size[0]-St[0]-1);
        En[1]=St[1]+rand()%(Size[1]-St[1]-1);
        vector<Pixel> Temp;
        for (int x=0;x<(En[1]-St[1]+1)*(En[0]-St[0]+1);x++){
            Temp.push_back(Pixel_test);
        }
        for (int id=0;id<Temp.size();id++){
            Temp[id].text=to_string(rand()%7);
            Temp[id].set_colour(1+rand()%8);
        }
        R_Main.Add_Textbox("",0,0,"Map",Temp,St,En,1);
    }
    R_Main.Render_Output();
    R_Main.Render_Print();
    cin.get();
    cin.get();
    //for(int x=0;x<22;x++){
    //    cout<<"\e[A";
    //}
    //cout<<flush;
}