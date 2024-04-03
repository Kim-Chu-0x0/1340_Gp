#ifndef PIXEL
#define PIXEL

#include <string>
#include <iostream>

#define Black "\e[0;30m"
#define Red "\e[0;31m"
#define Green "\e[0;32m"
#define Yellow "\e[0;33m"
#define Blue "\e[0;34m"
#define Purple "\e[0;35m"
#define Cyan "\e[0;36m"
#define White "\e[0;37m"

using namespace std;

class Pixel
{
    public:
        string text;
        string colour=White;
        void set_colour(int id){
            switch (id)
            {
            case 1:
                colour=Black;
                break;
            case 2:
                colour=Red;
                break;
            case 3:
                colour=Green;
                break;
            case 4:
                colour=Yellow;
                break;
            case 5:
                colour=Blue;
                break;
            case 6:
                colour=Purple;
                break;
            case 7:
                colour=Cyan;
                break;
            case 8:
                colour=White;
                break;
            
            default:
                colour=White;
                break;
            }
        }
    void print(){
        cout<<colour+text;
    }
};

#endif