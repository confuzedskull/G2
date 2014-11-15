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

#include "rts_object.h"
#include "cursor.h"
#include "game.h"
#include "window.h"
#include <math.h>
#include <iostream>

point2i rts_object::origin = point2i(window::width*0.9,window::height*0.5);

std::string rts_object::get_type()
{
    return "rts object";
}

void rts_object::mouse_function()
{
    if(visible && enabled)
    {
        highlight_function();
        left_click_function();
        right_click_function();
        if(selected)//you can only move an object when it is selected
        {
            if(cursor::right_click && !right_clicked())
            {
                if(cursor::right_clicked_an_object)
                    rally = cursor::right_clicked_object->get_positionptr();//set rally to reference point because position is always changing
                else//move to right clicked empty space
                    rally = new point2i(cursor::right_down.x,cursor::right_down.y);
                rally_set=true;
            }
            if(cursor::right_dragging && !right_clicked())
            {
                //move to right drag
                rally = new point2i(cursor::right_drag.x,cursor::right_drag.y);
                rally_set=true;
            }
        }
    }
}

void rts_object::update()
{
    calc_boundaries();
    calc_points();
    calc_direction();
    mouse_function();
}

void rts_object::load()
{
    std::ifstream object_file(file_name);//access file by name
    if(object_file.bad())//make sure the file is there
        return;
    //load basic object properties
    object_file>>position.x>>position.y;
    object_file>>rotation;
    object_file>>width>>height;
    object_file>>fill_color.r>>fill_color.g>>fill_color.b;
    object_file>>marker_color.r>>marker_color.g>>marker_color.b;
    object_file>>border_color.r>>border_color.g>>border_color.b;
    object_file>>filled;
    object_file>>bordered;
    object_file>>visible;
    object_file>>selected;
    //load movable object properties
    object_file>>speed;
    object_file>>degrees_rotated;
    object_file>>rest_rotation;
    object_file>>rally_set;
    object_file>>moving_forward;
    object_file>>moving_backward;
    object_file>>moving_left;
    object_file>>moving_right;
    object_file>>turning_right;
    object_file>>turning_left;
    char first_char;
    while(first_char!=';' && first_char!='\n')//no comment line or empty space detected
    {
        //load the cued actions
        first_char=object_file.peek();//check the first character of the line
        std::array<int,3> action;
        object_file>>action[0]>>action[1]>>action[2];//add action number, times to do, and  times performed
        action_cue.push(action);//add action to the cue
    }
    //load tangible object properties
    object_file>>touching[1];
    object_file>>touching[2];
    object_file>>touching[3];
    object_file>>touching[4];
    object_file>>collided;
    object_file.close();
    std::clog<<"object#"<<get_number()<<"(rts object)"<<" loaded.\n";
}

void rts_object::save()
{
    std::stringstream filename;
    filename<<"./data/objects/object#"<<number<<".rso";
    std::ofstream object_file(filename.str());
    object_file<<position.x<<' '<<position.y<<std::endl;
    object_file<<rotation<<std::endl;
    object_file<<width<<' '<<height<<std::endl;
    object_file<<fill_color.str()<<std::endl;
    object_file<<marker_color.str()<<std::endl;
    object_file<<border_color.str()<<std::endl;
    object_file<<filled<<std::endl;
    object_file<<bordered<<std::endl;
    object_file<<visible<<std::endl;
    object_file<<selected<<std::endl;
    object_file<<speed<<std::endl;
    object_file<<degrees_rotated<<std::endl;
    object_file<<rest_rotation<<std::endl;
    object_file<<rally_set<<std::endl;
    object_file<<moving_forward<<std::endl;
    object_file<<moving_backward<<std::endl;
    object_file<<moving_left<<std::endl;
    object_file<<moving_right<<std::endl;
    object_file<<turning_right<<std::endl;
    object_file<<turning_left<<std::endl;
    for(int i=0;i<action_cue.size();i++)
        object_file<<action_cue.front().at(0)<<' '<<action_cue.front().at(1)<<' '<<action_cue.front().at(2)<<std::endl;
    object_file<<touching[1]<<std::endl;
    object_file<<touching[2]<<std::endl;
    object_file<<touching[3]<<std::endl;
    object_file<<touching[4]<<std::endl;
    object_file<<collided<<std::endl;
    object_file.close();
    std::clog<<"object#"<<number<<"(rts object)"<<" saved.\n";
}

rts_object::rts_object(): clickable_object(), tangible_object(), complex_object()
{
    position.set((float)origin.x, (float)origin.y);
    speed=2.0f;
    std::clog<<"object#"<<number<<"(rts object)"<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
