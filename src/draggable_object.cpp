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
            position.set((float)cursor::left_drag.x,(float)cursor::left_drag.y);
            cursor::grabbed_an_object=true;
        }
    }
}

void draggable_object::update()
{
    movable_object::update();
    mouse_function();
}

void draggable_object::load()
{
    std::ifstream object_file(file_name);//access file by name
    if(object_file.bad())//make sure the file is there
        return;
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
    object_file>>visible;
    object_file>>selected;
    //load movable object properties
    object_file>>speed;
    object_file>>degrees_rotated;
    object_file>>rally_set;
    object_file>>moving_forward;
    object_file>>moving_backward;
    object_file>>moving_left;
    object_file>>moving_right;
    object_file>>turning_right;
    object_file>>turning_left;
    char first_char;
    while(first_char!='\n')//no empty space detected
    {
        //load the cued actions
        first_char=object_file.peek();//check the first character of the line
        std::array<int,3> action;
        object_file>>action[0]>>action[1]>>action[2];//add action number, times to do, and  times performed
        action_cue.push(action);//add action to the cue
    }
    //load tangible object properties
    object_file>>touched_side[0];
    object_file>>touched_side[1];
    object_file>>touched_side[2];
    object_file>>touched_side[3];
    object_file>>collided;
    object_file.close();
    std::clog<<"object#"<<number<<"(draggable object)"<<" loaded.\n";
}

void draggable_object::save()
{
    std::stringstream filename;
    filename<<"./data/objects/object#"<<number<<".dro";
    std::ofstream object_file(filename.str());
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
    object_file<<visible<<std::endl;
    object_file<<selected<<std::endl;
    //save movable object properties
    object_file<<speed<<std::endl;
    object_file<<degrees_rotated<<std::endl;
    object_file<<rally_set<<std::endl;
    object_file<<moving_forward<<std::endl;
    object_file<<moving_backward<<std::endl;
    object_file<<moving_left<<std::endl;
    object_file<<moving_right<<std::endl;
    object_file<<turning_right<<std::endl;
    object_file<<turning_left<<std::endl;
    for(int i=0;i<action_cue.size();i++)
        object_file<<action_cue.front().at(0)<<' '<<action_cue.front().at(1)<<' '<<action_cue.front().at(2)<<std::endl;
    object_file<<std::endl;//add an empty line to signal end of action cue
    //save tangible object properties
    object_file<<touched_side[0]<<std::endl;
    object_file<<touched_side[1]<<std::endl;
    object_file<<touched_side[2]<<std::endl;
    object_file<<touched_side[3]<<std::endl;
    object_file<<collided<<std::endl;
    object_file.close();
    std::clog<<"object#"<<number<<"(draggable object)"<<" saved.\n";
}

draggable_object::draggable_object()
{
    fill_color=BLACK;
    position.set((float)origin.x,(float)origin.y);
    std::clog<<"object#"<<number<<"(draggable object)"<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
