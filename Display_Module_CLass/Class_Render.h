#ifndef RENDER
#define RENDER

#include <iostream>
#include <string>
#include <vector>
#include "Class_Layer.h"
#include "Class_Pixel.h"
// ╋ ┫ ┣ ┻ ┳ ┓ ┏ ┗ ┛ ┃ ━ 

using namespace std;

class Render{
    public:
        Render(){
        }
    
    //Mutate Layer object
    public:
        void Add_Layer(){
            Layer temp(Screen_Size[0],Screen_Size[1]);
            Layer_list.push_back(temp);
            Layer_no++;
        }
        //Layer_list[0] will be the layer on top
        //Top [0]->[1]->...->[x]Bottom
        vector<Layer> Layer_list;
    private:
        void Clear(){
            Layer_list.clear();
            Layer_no=0;
        }
        int Layer_no;

    //Set screen size
    public:
        void Set_Size(int x_len,int y_len){
            if ((x_len<=0)||(y_len<=0)){
                cout<<endl<<"Size error, input must be positive numbers"<<endl;
                cout<<"Input: x="<<x_len<<" y="<<y_len<<endl;
                exit(0);
            }
            Screen_Size[0]=x_len;
            Screen_Size[1]=y_len;
        }
    private:
        vector <int> Screen_Size {0,0};

    //Trigger output
    public:
        void Render_Output();
        vector <Pixel> Output;
        void Render_Print();
    private:
        void Stack_Layer(vector <Pixel> Upper_Stack);
};

void Render::Render_Output(){
    Pixel temp;
    temp.text=" ";
    Output.clear();
    for (int id=0;id<((Screen_Size[0]*2+3)*(Screen_Size[1]+2));id++){
        Output.push_back(temp);
    }
    for (int id=Layer_no-1;id>=0;id--){
        Layer_list[id].Output();
        Stack_Layer(Layer_list[id].Output_Map);
    }
    Clear();
}

void Render::Stack_Layer(vector <Pixel> Upper_Stack){
    for (int id=0;id<Output.size();id++){
        if (!(Upper_Stack[id].text=="s/")){
            Output[id]=Upper_Stack[id];
        }
    }
}

void Render::Render_Print(){
    for (int id_y=0;id_y<(Screen_Size[1]+2);id_y++){
        for (int id_x=0;id_x<(Screen_Size[0]*2+3);id_x++){
            if (Output[id_y*(Screen_Size[0]*2+3)+id_x].text=="s/"){
                cout<<" ";
            }
            else{
                Output[id_y*(Screen_Size[0]*2+3)+id_x].print();
            }
        }
        cout<<'\n';
    }
    Output.clear();
}

#endif