/*  This file is a part of G2 - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    G2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    G2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of G2.  If not, see <http://www.gnu.org/licenses/>.*/

#include "smart_object.h"
#include "utilities.h"
#include "game.h"
#include "audio.h"
#include <math.h>
#include <sstream>
#include <iostream>

std::string smart_object::default_collisionsound="";

std::string smart_object::get_type()
{
    return "smart object";
}

void smart_object::action_placeholder(){}

bool smart_object::within_range(complex_object target)
{
    return isless(utilities::distance(position,target.get_position()),(get_radius()+target.get_radius()));
}

bool smart_object::within_range(complex_object target, float range)
{
    return isless(utilities::distance(position,target.get_position()),(get_radius()+target.get_radius()+range));
}

bool smart_object::near_front(complex_object target)
{
    return isless(utilities::distance(front(),target.get_position()),target.get_height()/2);
}
bool smart_object::near_back(complex_object target)
{
    return isless(utilities::distance(back(),target.get_position()),target.get_height()/2);
}

bool smart_object::near_left(complex_object target)
{
    return isless(utilities::distance(left(),target.get_position()),target.get_width()/2);
}

bool smart_object::near_right(complex_object target)
{
    return isless(utilities::distance(right(),target.get_position()),target.get_width()/2);
}

void smart_object::watch(complex_object target)
{
    if(within_range(target))
        turnto_point((int)target.get_y(),(int)target.get_y());
}

void smart_object::follow(complex_object target)
{
    if(within_range(target))
        moveto_point((int)target.get_x(),(int)target.get_position().y);
}

void smart_object::repel(complex_object target)//object moves away from object B
{
    if(near_front(target))
        move_back();
    if(near_back(target))
        move_forward();
    if(near_left(target))
        move_right();
    if(near_right(target))
        move_left();
}

void smart_object::attract(complex_object target)//object moves toward object B
{
    if(near_front(target))
        move_forward();
    if(near_back(target))
        move_back();
    if(near_left(target))
        move_left();
    if(near_right(target))
        move_right();
}

void smart_object::simon_says(complex_object target)//object changes color according to side touched
{
    if(near_front(target))
        fill_color.set(RED);
    if(near_back(target))
        fill_color.set(GREEN);
    if(near_left(target))
        fill_color.set(BLUE);
    if(near_right(target))
        fill_color.set(YELLOW);
}

void smart_object::identify_touched(complex_object target)//variable touched_side[] is updated with number of the touched object
{
    if(near_left(target))
        touched_side[0]=target.get_number();
    else
        touched_side[0]=-1;

    if(near_right(target))
        touched_side[1]=target.get_number();
    else
        touched_side[1]=-1;

    if(near_front(target))
        touched_side[2]=target.get_number();
    else
        touched_side[2]=-1;

    if(near_back(target))
        touched_side[3]=target.get_number();
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

void smart_object::set_collisionsound(std::string filename)
{
    if(audio::sounds.find(filename)!=audio::sounds.end())
        collision_sound=filename;
    else
        std::cerr<<filename<<" not found.\n";
}

void smart_object::update()
{
    if(collided)
    {
        if(!muted)
            audio::play(collision_sound);
        action();
    }
    mobile_object::update();
}

void smart_object::save()
{
    std::stringstream filename;
    filename<<"./data/objects/object#"<<number<<".smo";
    std::ofstream object_file(filename.str());
    if(object_file.bad())
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //save basic object properties
    object_file<<position.x<<' '<<position.y<<std::endl;
    object_file<<rotation<<std::endl;
    object_file<<width<<' '<<height<<std::endl;
    object_file<<fill_color.str()<<std::endl;
    object_file<<marker_color.str()<<std::endl;
    object_file<<border_color.str()<<std::endl;
    object_file<<filled<<std::endl;
    object_file<<bordered<<std::endl;
    object_file<<textured<<std::endl;
    object_file<<masked<<std::endl;
    object_file<<visible<<std::endl;
    object_file<<selected<<std::endl;
    object_file<<muted<<std::endl;
    object_file<<texture<<std::endl;
    object_file<<mask<<std::endl;
    for(auto p:properties)
        object_file<<p.first<<' '<<p.second<<std::endl;
    object_file<<std::endl;
    //save mobile object properties
    object_file<<movement_sound<<std::endl;
    object_file<<speed<<std::endl;
    object_file<<degrees_rotated<<std::endl;
    object_file<<rally_set<<std::endl;
    object_file<<moving_forward<<std::endl;
    object_file<<moving_backward<<std::endl;
    object_file<<moving_left<<std::endl;
    object_file<<moving_right<<std::endl;
    object_file<<turning_right<<std::endl;
    object_file<<turning_left<<std::endl;
    while(!action_cue.empty())
    {
        object_file<<action_cue.front().at(0)<<' '<<action_cue.front().at(1)<<' '<<action_cue.front().at(2)<<std::endl;
        action_cue.pop();
    }
    object_file<<std::endl;//add an empty line to signal end of action cue
    //save smart object properties
    object_file<<touched_side[0]<<std::endl;
    object_file<<touched_side[1]<<std::endl;
    object_file<<touched_side[2]<<std::endl;
    object_file<<touched_side[3]<<std::endl;
    object_file<<collided<<std::endl;
    object_file<<collision_sound<<std::endl;
    object_file.close();
    std::clog<<"object#"<<number<<"(smart object)"<<" saved.\n";
}

void smart_object::load()
{
    std::ifstream object_file(file_name);//access file by name
    if(object_file.bad())//make sure the file is there
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //load basic object properties
    object_file>>position.x>>position.y;
    object_file>>rotation;
    object_file>>width>>height;
    object_file>>fill_color.r>>fill_color.g>>fill_color.b;
    object_file>>marker_color.r>>marker_color.g>>marker_color.b;
    object_file>>border_color.r>>border_color.g>>border_color.b;
    object_file>>filled;
    object_file>>bordered;
    object_file>>textured;
    object_file>>masked;
    object_file>>visible;
    object_file>>selected;
    object_file>>muted;
    object_file>>texture;
    object_file>>mask;
    char first_char=' ';
     //load custom properties
    while(first_char>0)//not newline or out of bounds
    {
        std::string name;
        int value;
        object_file.get();//eat the null character
        first_char=object_file.peek();//check the first character of the line
        if(first_char=='\n')
            break;
        object_file>>name>>value;
        add_property(name,value);
    }
    //load mobile object properties
    object_file>>movement_sound;
    object_file>>speed;
    object_file>>degrees_rotated;
    object_file>>rally_set;
    object_file>>moving_forward;
    object_file>>moving_backward;
    object_file>>moving_left;
    object_file>>moving_right;
    object_file>>turning_right;
    object_file>>turning_left;
    first_char=' ';
    while(first_char>0)//not newline or out of bounds
    {
        //load the cued actions
        object_file.get();//eat the null character
        first_char=object_file.peek();//check the first character of the line
        if(first_char=='\n')
            break;
        std::array<int,3> action;
        object_file>>action[0]>>action[1]>>action[2];//add action number, times to do, and  times performed
        action_cue.push(action);//add action to the cue
    }
    //load smart object properties
    object_file>>touched_side[0];
    object_file>>touched_side[1];
    object_file>>touched_side[2];
    object_file>>touched_side[3];
    object_file>>collided;
    object_file>>collision_sound;
    std::clog<<"object#"<<number<<"(smart object)"<<" loaded.\n";
}

smart_object::smart_object(): mobile_object()
{
    collided=false;
    touched_side[0]=-1;
    touched_side[1]=-1;
    touched_side[2]=-1;
    touched_side[3]=-1;
    set_collisionsound(default_collisionsound);
    action=smart_object::action_placeholder;
}
