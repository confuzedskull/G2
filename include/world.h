#ifndef WORLD_H
#define WORLD_H
#include "limits.h"

class world
{
    public:
    char* name;
    int type;
    int state;
    float timer;
    float gravity;
    float wind;
    int no_of_objects;
    bool settings[10];
};
#endif // WORLD_H

