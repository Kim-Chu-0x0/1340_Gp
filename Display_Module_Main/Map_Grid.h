#ifndef GRID
#define GRID

#include <iostream>
#include <string>
#include <vector>
#include "..\Object\Class_Buildings.h"
#include "..\Display_Module_Class\Class_Render.h"

using namespace std;

//a render object Main must be created before this headfile is called
//Render Main;

class Map_Grid{
    //item access
    public:
        void Set_Building(vector <int> xy, Building item);
        void CoverAll_Biulding(vector <Building> item_list);
    private:
        vector <Building> Building_list;

    //size control
    public:
        void Set_Size(int x,int y){
            if ( ! ((Size[0]==0)&&(Size[1]==0)) ){
                cout<<endl<<"Error: Size can not be changed"<<endl;
                exit(0);
            }
            Size[0]=x;
            Size[1]=y;
            Building temp;
            for (int x=0;x<Size[0]*Size[1];x++){
                Building_list.push_back(temp);
            }
        }
        void Expand(int x,int y){
            if ( ! ((x>=0)&&(y>=0)) ){
                cout<<endl<<"Error: Size can not be negative number"<<endl;
                cout<<endl<<"Your input: x="<<x<<" y="<<y<<endl;
                exit(0);
            }
            if ((Size[0]==0)&&(Size[1]==0)){
                cout<<endl<<"Error: Set the size first"<<endl;
                exit(0);
            }
            //rightward
            Building temp;
            for (int id_y=Size[1]-1;id_y>=0;id_y--){
                for (int id_x=0;id_x<x;id_x++){
                    Building_list.insert(Building_list.begin()+id_y*Size[0],temp);
                }
            }
            Size[0]+=x;
            //downward
            for (int id_y=0;id_y<y;id_y++){
                for (int id_x=0;id_x<Size[0];id_x++){
                    Building_list.push_back(temp);
                }
            }
            Size[1]+=y;
        }
    private:
        vector <int> Size{0,0};
    
    //output control
    public:
        //-1 means the bottom most layer
        //-2 means the second layer from the bottom
        int Layer_no=-1;
};

void Map_Grid::Set_Building(vector <int> xy, Building item){
    if (xy.size()==2){
        int x=xy[0];
        int y=xy[1];
        if ((x>=Size[0])||(y>=Size[1])){
            cout<<endl<<"Coordinates Error: x and y should locate within the grid system"<<endl;
            cout<<"input x: "<<x<<" y: "<<y<<endl;
            cout<<"Grid size x: "<<Size[0]<<" y: "<<Size[1]<<endl;
        }
        Building_list[Size[0]*y+x]=item;
    }
    else{
        Building_list[xy[0]]=item;
    }
}

void Map_Grid::CoverAll_Biulding(vector <Building> item_list){
    if (item_list.size()!=Size[0]*Size[1]){
        cout<<endl<<"Input Error: Size of input vector should equal to the size of the grid"<<endl;
        cout<<"input size: "<<item_list.size()<<endl;
        cout<<"Grid size : "<<Size[0]*Size[1]<<endl;
    }
    for (int id=0;id<item_list.size();id++){
        vector <int> temp{id};
        Set_Building (temp,item_list[id]);
    }
}

#endif