/*  This file is a part of 2DWorld - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    2DWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    2DWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of 2DWorld.  If not, see <http://www.gnu.org/licenses/>.*/

#include "tangible_object.h"
#include "distance.h"
#include "game.h"
#include <iostream>
#include <math.h>

bool tangible_object::is_close(complex_object B)
{
    if(islessequal(distance(position,B.get_position()),(radius+B.get_radius())))
        return true;
    else
        return false;
}

bool tangible_object::near_front(complex_object B)
{
    if(isless(distance(front,B.get_position()),B.get_height()/2))
        return true;
    else
        return false;
}
bool tangible_object::near_back(complex_object B)
{
    if(isless(distance(back,B.get_position()),B.get_height()/2))
        return true;
    else
        return false;
}

bool tangible_object::near_left(complex_object B)
{
    if(isless(distance(left,B.get_position()),B.get_width()/2))
        return true;
    else
        return false;
}

bool tangible_object::near_right(complex_object B)
{
    if(isless(distance(right,B.get_position()),B.get_width()/2))
        return true;
    else
        return false;
}

void tangible_object::repel(complex_object B)//object moves away from object B
{
    if(near_front(B))
        move_back();
    if(near_back(B))
        move_forward();
    if(near_left(B))
        move_right();
    if(near_right(B))
        move_left();
}

void tangible_object::attract(complex_object B)//object moves toward object B
{
    if(near_front(B))
        move_forward();
    if(near_back(B))
        move_back();
    if(near_left(B))
        move_left();
    if(near_right(B))
        move_right();
}

void tangible_object::simon_says(complex_object B)//object changes color according to side touched
{
    if(near_front(B))
        primary_color.set(RED);
    if(near_back(B))
        primary_color.set(GREEN);
    if(near_left(B))
        primary_color.set(BLUE);
    if(near_right(B))
        primary_color.set(YELLOW);
}

void tangible_object::identify_touched(complex_object B)//variable touching[] is updated with number of the touched object
{
    if(near_left(B))
        touching[0]=B.get_number();
    else
        touching[0]=-1;

    if(near_right(B))
        touching[1]=B.get_number();
    else
        touching[1]=-1;

    if(near_front(B))
        touching[2]=B.get_number();
    else
        touching[2]=-1;

    if(near_back(B))
        touching[3]=B.get_number();
    else
        touching[3]=-1;

    bool touched=false;
    for(int i=0;i<4;i++)
    {
        if(touched||touching[i]!=-1)
            touched=true;
        else
            touched=false;
    }
    collided=touched;
}

tangible_object::tangible_object(): movable_object()
{
    type="tangible object";
    collided=false;
    touching[0]=-1;
    touching[1]=-1;
    touching[2]=-1;
    touching[3]=-1;
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
