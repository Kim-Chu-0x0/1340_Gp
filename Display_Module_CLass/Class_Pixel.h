#ifndef PIXEL
#define PIXEL

#include <string>
#include <iostream>
#include <vector>

#define Black "\e[0;30m"
#define Red "\e[0;31m"
#define Green "\e[0;32m"
#define Yellow "\e[0;33m"
#define Blue "\e[0;34m"
#define Purple "\e[0;35m"
#define Cyan "\e[0;36m"
#define White "\e[0;37m"

#define B_Black "\e[1;30m"
#define B_Red "\e[1;31m"
#define B_Green "\e[1;32m"
#define B_Yellow "\e[1;33m"
#define B_Blue "\e[1;34m"
#define B_Purple "\e[1;35m"
#define B_Cyan "\e[1;36m"
#define B_White "\e[1;37m"

#define H_Black "\e[0;90m"
#define H_Red "\e[0;91m"
#define H_Green "\e[0;92m"
#define H_Yellow "\e[0;93m"
#define H_Blue "\e[0;94m"
#define H_Purple "\e[0;95m"
#define H_Cyan "\e[0;96m"
#define H_White "\e[0;97m"

#define Highlightcolour "\e[1;95m"

using namespace std;

// contains 2 string object
// text and colour
class Pixel
{
public:
    string text;
    string colour = White;
    void set_colour(int id)
    {
        switch (id)
        {
        case 1:
            colour = Black;
            break;
        case 2:
            colour = Red;
            break;
        case 3:
            colour = Green;
            break;
        case 4:
            colour = Yellow;
            break;
        case 5:
            colour = Blue;
            break;
        case 6:
            colour = Purple;
            break;
        case 7:
            colour = Cyan;
            break;
        case 8:
            colour = White;
            break;
        case 9:
            colour = Highlightcolour;
            break;
        case 10:
            colour = B_Black;
            break;
        case 11:
            colour = B_Red;
            break;
        case 12:
            colour = B_Green;
            break;
        case 13:
            colour = B_Yellow;
            break;
        case 14:
            colour = B_Blue;
            break;
        case 15:
            colour = B_Purple;
            break;
        case 16:
            colour = B_Cyan;
            break;
        case 17:
            colour = B_White;
            break;
        case 18:
            colour = H_Black;
            break;
        case 19:
            colour = H_Red;
            break;
        case 20:
            colour = H_Green;
            break;
        case 21:
            colour = H_Yellow;
            break;
        case 22:
            colour = H_Blue;
            break;
        case 23:
            colour = H_Purple;
            break;
        case 24:
            colour = H_Cyan;
            break;
        case 25:
            colour = H_White;
            break;
        default:
            colour = White;
            break;
        }
    }
    void print()
    {
        cout << colour + text;
    }
};

#endif