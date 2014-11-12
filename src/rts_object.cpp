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

point2f rts_object::origin = point2f(window::width*0.9,window::height*0.5);

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
                    rally = new point2f(cursor::right_down.x,cursor::right_down.y);
                rally_set=true;
            }
            if(cursor::right_dragging && !right_clicked())
            {
                //move to right drag
                rally = new point2f(cursor::right_drag.x,cursor::right_drag.y);
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
    std::ifstream object_file(file_name.c_str());//access file by name
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
    std::clog<<"object#"<<get_number()<<'('<<type<<')'<<" loaded.\n";
}

void rts_object::save()
{
    std::ofstream object_file(file_name.c_str());
    object_file<<"//basic object properties\n";
    object_file<<position.x<<','<<position.y<<";position\n";
    object_file<<rotation<<";rotation\n";
    object_file<<width<<'X'<<height<<";dimensions\n";
    object_file<<fill_color.str()<<";fill color RGB values\n";
    object_file<<marker_color.str()<<";marker color RGB values\n";
    object_file<<border_color.str()<<";border color RGB values\n";
    object_file<<filled<<";whether the shape is filled\n";
    object_file<<bordered<<";whether the shape has a border\n";
    object_file<<visible<<";whether you can see the object\n";
    object_file<<selected<<";whether the object is selected\n";
    object_file<<";complex object properties are generated after initialization\n";
    object_file<<";movable object properties\n";
    object_file<<speed<<";speed\n";
    object_file<<degrees_rotated<<";degrees rotated\n";
    object_file<<rest_rotation<<";resting rotation\n";
    object_file<<rally_set<<";whether or not the rally has been set\n";
    object_file<<moving_forward<<";whether the object is moving forward\n";
    object_file<<moving_backward<<";whether the object is moving backward\n";
    object_file<<moving_left<<";whether the object is moving left\n";
    object_file<<moving_right<<";whether the object is moving right\n";
    object_file<<turning_right<<";whether the object is turning right\n";
    object_file<<turning_left<<";whether the object is turning left\n";
    object_file<<";cued actions\n";
    for(int i=0;i<action_cue.size();i++)
        object_file<<action_cue.front().at(0)<<','<<action_cue.front().at(1)<<','<<action_cue.front().at(2)<<";action number, times done, times to do\n";
    object_file<<";tangible object properties\n";
    object_file<<touching[1]<<";number of the object touching the left side\n";
    object_file<<touching[2]<<";number of the object touching the right side\n";
    object_file<<touching[3]<<";number of the object touching the front side\n";
    object_file<<touching[4]<<";number of the object touching the back side\n";
    object_file<<collided<<";whether the object has collided\n";
    object_file.close();
    std::clog<<"object#"<<number<<'('<<type<<')'<<" saved.\n";
}

rts_object::rts_object(): clickable_object(), tangible_object(), complex_object()
{
    std::stringstream fn;
    fn<<"./data/objects/object#"<<number<<".rso";
    file_name=fn.str();
    type="rts object";
    position.set(origin);
    speed=2.0f;
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
