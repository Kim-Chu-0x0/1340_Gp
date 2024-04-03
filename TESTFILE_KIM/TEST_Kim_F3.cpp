#include <string>
#include <iostream>
#include "..\Display_Module_Class\Class_Render.h"

using namespace std;


#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

//High intensty background 
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB 
#define WHTHB "\e[0;107m"

int main(){
    cout<<string(CYNB)+"HIIIII"<<endl;
    cout<<string(CYNHB)+"HIIIII"<<endl;
    return 0;
}