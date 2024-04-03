#ifndef LAYER
#define LAYER

#include <iostream>
#include <string>
#include <vector>
#include "Class_Pixel.h"
// ╋ ┫ ┣ ┻ ┳ ┓ ┏ ┗ ┛ ┃ ━ 

#define Black "\e[0;30m"
#define Red "\e[0;31m"
#define Green "\e[0;32m"
#define Yellow "\e[0;33m"
#define Blue "\e[0;34m"
#define Purple "\e[0;35m"
#define Cyan "\e[0;36m"
#define White "\e[0;37m"

using namespace std;

class Layer
{
    //create object :
    //  Layer(length on x-axis,length on y-axis)

    //Layer_object.Add_Textbox(vector<string> Text,vector<int> startingpt coordinates(x,y),vector<int> endpt coordinates(x,y),bool whitespacing)

    //Layer_object.Output():
    //  generate processed map layer

    //Layer_object.Print():
    //  print out the layer object(for testing)

    //Layer_object.Output_Map :
    //  the processed map

    public:
        Layer(int x_len,int y_len){
            Map_xy.push_back(x_len+2);
            Map_xy.push_back(y_len+2);
            if (!(TestMod)){
                TestOutline=0;
                Check_Input=0;
            }
        }

    //Testing
    public:
        void Print();
    private:
        bool TestMod=0;
        bool TestOutline=1;
        bool Check_Input=1;

    //trigger the output
    public:
        void Output();
        vector<Pixel> Output_Map;
    private:
        //Map_xy:{x,y}
        vector<int> Map_xy;

    //Adding new textboxes
    public:
        void Add_Textbox(vector<Pixel> Text,vector<int> starting_xy,vector<int> endpt_xy,bool Whitespace);
    private:
        int Text_no=0;    
        vector<vector<Pixel>> Textbox;
        vector<vector<int>> Textbox_St;
        vector<vector<int>> Textbox_En;
        vector<bool> Textbox_Whitespace;
    
    //Outline;
    private:
        vector <Pixel> Outline();
        vector <vector <bool>> Outline_New();
        void Outline_Add(vector<int> starting_xy,vector<int> endpt_xy,vector <vector <bool>> &Map_bool);
        vector <Pixel> Outline_Bool_Exchange(vector <vector <bool>> Map_bool);
        void Outline_Format_Exchange(vector <Pixel>&Map_String);

    //fill in the text
    private:
        void Text_Implant(vector<int> starting_xy, vector<int> endpt_xy, vector <Pixel> Text, vector <Pixel>&Map_String, bool Whitespace);
};

void Layer::Print(){
    if (TestMod){
        cout<<"Printing started"<<endl;
        cout<<"Graphic size: "<<Output_Map.size()<<endl;
    }
    for (int id_y=0;id_y<Map_xy[1];id_y++){
        for (int id_x=0;id_x<Map_xy[0];id_x++){
            if (Output_Map[id_y*Map_xy[0]+id_x].text=="s/"){
                cout<<" ";
            }
            else{
                cout<<Output_Map[id_y*Map_xy[0]+id_x].text;
            }
        }
        cout<<'\n';
    }
}

void Layer::Output(){
    if (TestMod){
        cout<<"Map_xy:"<<Map_xy[0]<<"  "<<Map_xy[1]<<endl;
        cout<<"St:"<<Textbox_St.size()<<"  "<<"En:"<<Textbox_En.size()<<"  "<<"Textbox:"<<Textbox.size()<<"  "<<"Textbox_Whitespace:"<<Textbox_Whitespace.size()<<"  "<<endl;
    }
    vector<Pixel> Output=Outline();
    for (int id=0;id<Text_no;id++){
        Text_Implant(Textbox_St[id],Textbox_En[id],Textbox[id],Output,Textbox_Whitespace[id]);
    }
    if (TestMod){
        cout<<"Map processing done"<<endl;
    }
    for (int i=0; i<Output.size(); i++){
        Output_Map.push_back(Output[i]);
    }
}

void Layer::Text_Implant(vector<int> starting_xy, vector<int> endpt_xy, vector <Pixel> Text, vector <Pixel>&Map_String, bool Whitespace){
    int y_len=endpt_xy[1]-starting_xy[1]+1;
    int x_len=endpt_xy[0]-starting_xy[0]+1;
    int id_addition;
    Pixel whispc;
    whispc.text=" ";
    if (Whitespace){
        for (int id_y=y_len-1;id_y>=0;id_y--){
            for (int id_x=x_len-1;id_x>0;id_x--){
                id_addition=id_y*x_len+id_x;
                Text.insert(Text.begin()+id_addition,whispc);
            }
        }
    }
    x_len=x_len*2-1;
    endpt_xy[0]*=2;
    starting_xy[0]*=2;
    for (int id_y=starting_xy[1];id_y<=endpt_xy[1];id_y++){
        for (int id_x=starting_xy[0];id_x<=endpt_xy[0];id_x++){
            Map_String[id_y*Map_xy[0]+id_x]=Text[(id_y-starting_xy[1])*x_len+(id_x-starting_xy[0])];
        }
    }
    for (int id_y=starting_xy[1];id_y<=endpt_xy[1];id_y++){
        Map_String[id_y*Map_xy[0]+starting_xy[0]-1]=whispc;
        Map_String[id_y*Map_xy[0]+endpt_xy[0]+1]=whispc;
    }
    if(TestMod){
        cout<<"Text_Implant done"<<endl;
    }
}

void Layer::Add_Textbox(vector<Pixel> Text,vector<int> starting_xy,vector<int> endpt_xy,bool Whitespace){
    //starting_xy:(x1,y1)is the top-left coordinate of the outline box, endpt_xy:(x2,y2)is the bottom-right one
    //Whitespace =1: hv whitespace between words,Whitespace =0: no whitespace
    if ((starting_xy[0]>endpt_xy[0])||(starting_xy[1]>endpt_xy[1])){
        cout<<"Location error, Starting_pt should be smaller than End_pt"<<endl;
        cout<<"St: "<<starting_xy[0]<<"  "<<starting_xy[1]<<endl;
        cout<<"En: "<<endpt_xy[0]<<"  "<<endpt_xy[1]<<endl;
        exit(0);
    }
    if (((starting_xy[0]<0)||(starting_xy[1]<0))||((endpt_xy[0]<0)||(endpt_xy[1]<0))){
        cout<<"Location error, Starting_pt and End_pt should be positive"<<endl;
        cout<<"St: "<<starting_xy[0]<<"  "<<starting_xy[1]<<endl;
        cout<<"En: "<<endpt_xy[0]<<"  "<<endpt_xy[1]<<endl;
        exit(0);
    }
    if (((starting_xy[0]+3>Map_xy[0])||(starting_xy[1]+3>Map_xy[1]))||((endpt_xy[0]+3>Map_xy[0])||(endpt_xy[1]+3>Map_xy[1]))){
        cout<<"Location error, Starting_pt and End_pt should locate within the map"<<endl;
        cout<<"St: "<<starting_xy[0]<<"  "<<starting_xy[1]<<endl;
        cout<<"En: "<<endpt_xy[0]<<"  "<<endpt_xy[1]<<endl;
        cout<<"Map Size: "<<Map_xy[0]-2<<" "<<Map_xy[1]-2;
        exit(0);
    }
    if (((Whitespace)&&((endpt_xy[0]-starting_xy[0]+1)*(endpt_xy[1]-starting_xy[1]+1)!=Text.size()))||((!Whitespace)&&(((endpt_xy[0]-starting_xy[0])*2+1)*(endpt_xy[1]-starting_xy[1]+1)!=Text.size()))){
        cout<<"Input error, length of text didn't match the size of the box"<<endl;
        cout<<"St: "<<starting_xy[0]<<"  "<<starting_xy[1]<<endl;
        cout<<"En: "<<endpt_xy[0]<<"  "<<endpt_xy[1]<<endl;
        cout<<"Input Text Length: "<<Text.size()<<endl;
        cout<<"Proper length: ";
        if (Whitespace){
            cout<<(endpt_xy[0]-starting_xy[0]+1)*(endpt_xy[1]-starting_xy[1]+1)<<endl;
        }
        else{
            cout<<((endpt_xy[0]-starting_xy[0])*2+1)*(endpt_xy[1]-starting_xy[1]+1)<<endl;
        }
        exit(0);
    }
    Textbox.insert(Textbox.begin()+Text_no,Text);
    Textbox_St.insert(Textbox_St.begin()+Text_no,starting_xy);
    Textbox_En.insert(Textbox_En.begin()+Text_no,endpt_xy);
    Textbox_Whitespace.insert(Textbox_Whitespace.begin()+Text_no,Whitespace);
    Textbox_St[Text_no][0]++;
    Textbox_St[Text_no][1]++;
    Textbox_En[Text_no][0]++;
    Textbox_En[Text_no][1]++;
    if (TestMod){
        cout<<"Text size: "<<Textbox[Text_no].size()<<endl;
        cout<<"St: "<<Textbox_St[Text_no][0]<<"  "<<Textbox_St[Text_no][1]<<endl;
        cout<<"En: "<<Textbox_En[Text_no][0]<<"  "<<Textbox_En[Text_no][1]<<endl;
        cout<<"Whitespace: "<<Textbox_Whitespace[Text_no]<<endl;
        cout<<"Textbox addition done"<<endl;
    }
    Text_no++;
}

vector <Pixel> Layer::Outline(){
    vector< vector <bool> >Outline_temp=Outline_New();
    for (int id=0;id<Text_no;id++){
        Outline_Add(Textbox_St[id],Textbox_En[id],Outline_temp);
    }
    vector <Pixel> Output=Outline_Bool_Exchange(Outline_temp);
    Outline_Format_Exchange(Output);
    if (TestOutline){
        cout<<"Outline done"<<endl;
    }
    return Output;
}

vector <vector <bool>> Layer::Outline_New(){
    // Create a new vector with sieze of [x*y][4]
    // for auto outline only
    vector <bool> Map_bool_l1(4,false);
    vector <vector <bool>> Map_bool(Map_xy[0]*Map_xy[1],Map_bool_l1);
    if (TestOutline){
        cout<<"New Outline done"<<endl;
    }
    return Map_bool;
}

void Layer::Outline_Add(vector<int> starting_xy,vector<int> endpt_xy,vector <vector <bool>> &Map_bool){
    //starting_xy:(x1,y1)is the top-left coordinate of the outline box, endpt_xy:(x2,y2)is the bottom-right one
    //the inner vector of Map_bool:{0,0,0,0}-->{up,down,left,right}
    starting_xy[0]--;
    starting_xy[1]--;
    endpt_xy[0]++;
    endpt_xy[1]++;
    if (TestOutline){
        cout<<starting_xy[0]<<"  "<<starting_xy[1]<<"  "<<endpt_xy[0]<<"  "<<endpt_xy[1]<<endl;
    }
    for (int x=starting_xy[0];x<endpt_xy[0];x++){
        Map_bool [starting_xy[1]*Map_xy[0]+x] [3]=1;
        Map_bool [starting_xy[1]*Map_xy[0]+x+1] [2]=1;
        Map_bool [endpt_xy[1]*Map_xy[0]+x] [3]=1;
        Map_bool [endpt_xy[1]*Map_xy[0]+x+1] [2]=1;
    }
    for (int y=starting_xy[1];y<endpt_xy[1];y++){
        Map_bool [y*Map_xy[0]+starting_xy[0]] [1]=1;
        Map_bool [(y+1)*Map_xy[0]+starting_xy[0]] [0]=1;
        Map_bool [y*Map_xy[0]+endpt_xy[0]] [1]=1;
        Map_bool [(y+1)*Map_xy[0]+endpt_xy[0]] [0]=1;
    }
}

vector <Pixel> Layer::Outline_Bool_Exchange(vector <vector <bool>> Map_bool){
    int Sum=0;
    vector <Pixel> Map_String;
    Pixel temp;
    temp.text="s/";
    for (int x=0;x<Map_xy[0]*Map_xy[1];x++){
        Map_String.push_back(temp);
    }
    for (int id=0;id<Map_xy[0]*Map_xy[1];id++){
        Sum=0;
        if (Map_bool[id][0]){
            Sum+=1;
        }
        if (Map_bool[id][1]){
            Sum+=2;
        }
        if (Map_bool[id][2]){
            Sum+=4;
        } 
        if (Map_bool[id][3]){
            Sum+=8;
        }
        switch (Sum)
        {
        case 0:
            break;
        case 3:
            Map_String[id].text="┃";
            break;
        case 5:
            Map_String[id].text="┛";
            break;
        case 9:
            Map_String[id].text="┗";
            break;
        case 6:
            Map_String[id].text="┓";
            break;
        case 10:
            Map_String[id].text="┏";
            break;
        case 12:
            Map_String[id].text="━";
            break;
        case 7:
            Map_String[id].text="┫";
            break;
        case 11:
            Map_String[id].text="┣";
            break;
        case 13:
            Map_String[id].text="┻";
            break;
        case 14:
            Map_String[id].text="┳";
            break;
        case 15:
            Map_String[id].text="╋";
            break;
        }
    }
    if (TestOutline){
        cout<<"Bool Trans done"<<endl;
    }
    return Map_String;
}

void Layer::Outline_Format_Exchange(vector <Pixel>&Map_String){
    int id;
    Pixel temp;
    for (int id_y=Map_xy[1]-1;id_y>=0;id_y--){
        for (int id_x=Map_xy[0]-1;id_x>0;id_x--){
            id=id_y*Map_xy[0]+id_x;
            //cout<<"x:"<<id_x<<"  "<<"y:"<<id_y<<"  "<<"id:"<<id<<"  "<<"-1:"<<Map_String[id-1]<<"  "<<"0:"<<Map_String[id];
            if ((Map_String[id-1].text=="┗")||(Map_String[id-1].text=="┏")||(Map_String[id-1].text=="┣")||(Map_String[id-1].text=="┻")||(Map_String[id-1].text=="┳")||(Map_String[id-1].text=="╋")||(Map_String[id-1].text=="━")){
                //cout<<"  Line"<<endl;
                temp.text="━";
            }
            else if((Map_String[id-1].text=="s/")||((id_x!=Map_xy[0]-1)&&(Map_String[id+1].text=="s/"))){
                //cout<<"  Skip"<<endl;
                temp.text="s/";
            }
            else{
                //cout<<"  Space"<<endl;
                temp.text=" ";
                
            }
            Map_String.insert(Map_String.begin()+id,temp);
        }
    }
    Map_xy[0]*=2;
    Map_xy[0]-=1;
    if (TestOutline){
        cout<<"Map extend done"<<endl;
    }
}

#endif