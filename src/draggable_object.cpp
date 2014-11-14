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

#include "draggable_object.h"
#include "complex_object.h"
#include "cursor.h"
#include "distance.h"
#include "window.h"
#include <math.h>
#include <iostream>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

point2i draggable_object::origin = point2i(window::width*0.9,window::height*0.7);

std::string draggable_object::get_filename()
{
    std::stringstream file_name;
    file_name<<"./data/objects/object#"<<number<<".dro";
    return file_name.str();
}

std::string draggable_object::get_type()
{
    return "draggable object";
}

bool draggable_object::grabbed()
{
    if(cursor::left_dragging && !cursor::highlighting &&
       (cursor::left_drag.x<xmax) && (cursor::left_drag.x>xmin) &&
       (cursor::left_drag.y<ymax) && (cursor::left_drag.y>ymin))
        return true;
    else
        return false;
}

void draggable_object::mouse_function()
{
    if(visible && enabled)
    {
        highlight_function();
        left_click_function();
        if(grabbed())//grabbed this object
        {
            position.set(cursor::left_drag);
            cursor::grabbed_an_object=true;
        }
    }
}

void draggable_object::update()
{
    calc_boundaries();
    calc_points();
    calc_direction();
    mouse_function();
}

void draggable_object::load()
{
    std::ifstream object_file(get_filename());//access file by name
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
    std::clog<<"object#"<<number<<"(draggable object)"<<" loaded.\n";
}

void draggable_object::save()
{
    std::ofstream object_file(get_filename());
    object_file<<";basic object properties\n";
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
    std::clog<<"object#"<<number<<"(draggable object)"<<" saved.\n";
}

draggable_object::draggable_object()
{
    fill_color=BLACK;
    position.set(origin);
    std::clog<<"object#"<<number<<"(draggable object)"<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
