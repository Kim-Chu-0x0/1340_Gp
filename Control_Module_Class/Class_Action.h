#ifndef ACTION
#define ACTION

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// store the action to be performed when player input (e.g.WASD)
class Action
{
    // Action list:
    // 0:NULL
    // 1:Move upward
    // 2:Move downward
    // 3:Move leftward
    // 4:Move rightward
private:
    int Up = 1;
    int Down = 2;
    int Left = 3;
    int Right = 4;
    int Enter = 0;
};

#endif