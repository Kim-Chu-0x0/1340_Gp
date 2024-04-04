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
    
    //Add textbox
    public:
        //Add textbox to a specific Layer object
        int Add_Textbox(int input_Textbox_id,string input_Layer_id,vector<Pixel> Text,vector<int> starting_xy,vector<int> endpt_xy,bool Whitespace);

    //Mutate Layer object
    public:
        void Add_Layer_object(string id,int position);
        void Remove_Layer_object(string id);
        vector<Layer> Layer_list;
    private:
        //Layer_list[0] will be the layer on top
        //Top [0]->[1]->...->[x]Bottom
        void Add_Layer(){
            Layer temp(Screen_Size[0],Screen_Size[1]);
            Layer_list.push_back(temp);
        }
        void Clear(){
            Highlight_occ=0;
            Layer_list.clear();
            for (int id=0;id<Layer_no;id++){
                Add_Layer();
            }
        }
        int Layer_no=0;

    //ID cache
    private:
        //check if any textbox being highlighted
        bool Highlight_occ=0;
        //store the id of Layer objects
        vector <string> Layer_id;
        //store the position of Layer objects
        vector <int> Layer_position;
        //store id of Textboxed of Layer objects
        vector <vector <int> > Layer_Textbox_id;
        //store which textbox is chosen to be highlighted
        int Highlight_Choice_Textbox=0;
        //store which Layer's highlight will be triggered 
        string Highlight_Choice_Layer="Map";

    //Set screen size
    public:
        //can only be used once
        void Set_Size(int x_len,int y_len){
            if ((x_len<=0)||(y_len<=0)){
                cout<<endl<<"Size error, input must be positive numbers"<<endl;
                cout<<"Input: x="<<x_len<<" y="<<y_len<<endl;
                exit(0);
            }
            Screen_Size[0]=x_len;
            Screen_Size[1]=y_len;
            Clear();
        }
    private:
        //Size of the Screen
        vector <int> Screen_Size {0,0};

    //Trigger output
    public:
        //Trigger output
        void Render_Output();
        //store the output map
        vector <Pixel> Output;
        //Render_Output must be used before Print
        void Render_Print();
    private:
        void Stack_Layer(vector <Pixel> Upper_Stack);
};

void Render::Add_Layer_object(string id,int position){
    for (int x=0;x<Layer_no;x++){
        if (Layer_position[x]==position){
            cout<<endl<<"Error: Layer position occupied"<<endl;
            exit(0);
        }
    }
    Layer_id.push_back(id);
    Layer_position.push_back(position);
    vector <int> temp;
    Layer_Textbox_id.push_back(temp);
    Layer_no++;
    Clear();
}

void Render::Remove_Layer_object(string id){
    bool suc=0;
    for (int x=0;x<Layer_no;x++){
        if (Layer_id[x]==id){
            Layer_id.erase(Layer_id.begin()+x);
            Layer_position.erase(Layer_position.begin()+x);
            Layer_Textbox_id.erase(Layer_Textbox_id.begin()+x);
            suc=1;
            break;
        }
    }
    if(!suc){
        cout<<endl<<"Error: Layer ID not found"<<endl;
        exit(0);
    }
    Layer_no--;
    Clear();
}

int Render::Add_Textbox(int input_Textbox_id,string input_Layer_id,vector<Pixel> Text,vector<int> starting_xy,vector<int> endpt_xy,bool Whitespace){
    bool suc=0;
    for (int id=0;id<Layer_no;id++){
        if (Layer_id[id]==input_Layer_id){
            Layer_list[Layer_position[id]].Add_Textbox(Text,starting_xy,endpt_xy,Whitespace);
            if(input_Textbox_id!=0){
                if ((input_Layer_id == Highlight_Choice_Layer) && ( Highlight_Choice_Textbox == input_Textbox_id )){
                Layer_list[Layer_position[id]].Enable_Highlight=1;
                Layer_list[Layer_position[id]].Highlight_no=Layer_list[Layer_position[id]].Text_no;
                Highlight_occ=1;
                }
            }
            else{
                Layer_Textbox_id[id].push_back(Layer_Textbox_id[id].size()+1);
            }
            suc=1;
            break;
        }
    }
    if(!suc){
        cout<<endl<<"Error: Layer ID not found"<<endl;
        exit(0);
    }
    return 0;
}
        

void Render::Render_Output(){
    if (!Highlight_occ){
        for (int id=0;id<Layer_no;id++){
            if (Layer_id[id]==Highlight_Choice_Layer){
                Layer_list[id].Enable_Highlight=1;
                Layer_list[id].Highlight_no=0;
            }
        }
    }
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