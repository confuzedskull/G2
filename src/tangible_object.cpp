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
#include "utilities.h"
#include "game.h"
#include "audio.h"
#include <iostream>
#include <math.h>

std::string tangible_object::default_collision_sound="clack.wav";

bool tangible_object::is_close(complex_object B)
{
    if(islessequal(utilities::distance(position,B.get_position()),(get_radius()+B.get_radius())))
        return true;
    else
        return false;
}

bool tangible_object::near_front(complex_object B)
{
    if(isless(utilities::distance(front(),B.get_position()),B.get_height()/2))
        return true;
    else
        return false;
}
bool tangible_object::near_back(complex_object B)
{
    if(isless(utilities::distance(back(),B.get_position()),B.get_height()/2))
        return true;
    else
        return false;
}

bool tangible_object::near_left(complex_object B)
{
    if(isless(utilities::distance(left(),B.get_position()),B.get_width()/2))
        return true;
    else
        return false;
}

bool tangible_object::near_right(complex_object B)
{
    if(isless(utilities::distance(right(),B.get_position()),B.get_width()/2))
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
        fill_color.set(RED);
    if(near_back(B))
        fill_color.set(GREEN);
    if(near_left(B))
        fill_color.set(BLUE);
    if(near_right(B))
        fill_color.set(YELLOW);
}

void tangible_object::identify_touched(complex_object B)//variable touched_side[] is updated with number of the touched object
{
    if(near_left(B))
        touched_side[0]=B.get_number();
    else
        touched_side[0]=-1;

    if(near_right(B))
        touched_side[1]=B.get_number();
    else
        touched_side[1]=-1;

    if(near_front(B))
        touched_side[2]=B.get_number();
    else
        touched_side[2]=-1;

    if(near_back(B))
        touched_side[3]=B.get_number();
    else
        touched_side[3]=-1;

    bool touched=false;
    for(int i=0;i<4;i++)
    {
        if(touched||touched_side[i]!=-1)
            touched=true;
        else
            touched=false;
    }
    collided=touched;
}

void tangible_object::set_collision_sound(std::string filename)
{
    if(audio::sounds.find(filename)!=audio::sounds.end())
        collision_sound=filename;
    else
        std::cerr<<filename<<" not found.\n";
}

void tangible_object::update()
{
    if(collided && !muted)
        audio::play(collision_sound);
}

tangible_object::tangible_object(): movable_object()
{
    collided=false;
    touched_side[0]=-1;
    touched_side[1]=-1;
    touched_side[2]=-1;
    touched_side[3]=-1;
    set_collision_sound(default_collision_sound);
}
