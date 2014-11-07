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

void rts_object::save()
{
    std::stringstream file_name;
    file_name<<"./data/objects/object#"<<number<<".rso";
    std::ofstream save_data(file_name.str());
    save_data<<"//basic object properties\n";
    save_data<<number<<"//number\n";
    save_data<<position.x<<','<<position.y<<"//position\n";
    save_data<<rotation<<"//rotation\n";
    save_data<<width<<'X'<<height<<"//dimensions\n";
    save_data<<marker_width<<'X'<<marker_height<<"//selection marker dimensions\n";
    save_data<<fill_color.str()<<"//fill color RGB values\n";
    save_data<<marker_color.str()<<"//marker color RGB values\n";
    save_data<<border_color.str()<<"//border color RGB values\n";
    save_data<<filled<<"//whether the shape is filled\n";
    save_data<<bordered<<"//whether the shape has a border\n";
    save_data<<visible<<"//whether you can see the object\n";
    save_data<<selected<<"//whether the object is selected\n";
    save_data<<"//complex object properties are generated after initialization\n";
    save_data<<"//movable object properties\n";
    save_data<<speed<<"//speed\n";
    save_data<<degrees_rotated<<"//degrees rotated\n";
    save_data<<rest_rotation<<"//resting rotation\n";
    save_data<<rally_set<<"//whether or not the rally has been set\n";
    save_data<<moving_forward<<"//whether the object is moving forward\n";
    save_data<<moving_backward<<"//whether the object is moving backward\n";
    save_data<<moving_left<<"//whether the object is moving left\n";
    save_data<<moving_right<<"//whether the object is moving right\n";
    save_data<<turning_right<<"//whether the object is turning right\n";
    save_data<<turning_left<<"//whether the object is turning left\n";
    save_data<<"//cued actions\n";
    for(int i=0;i<action_cue.size();i++)
        save_data<<action_cue.front().at(0)<<','<<action_cue.front().at(1)<<','<<action_cue.front().at(2)<<"//action number, times done, times to do\n";
    save_data<<"//tangible object properties\n";
    save_data<<touching[1]<<"//number of the object touching the left side\n";
    save_data<<touching[2]<<"//number of the object touching the right side\n";
    save_data<<touching[3]<<"//number of the object touching the front side\n";
    save_data<<touching[4]<<"//number of the object touching the back side\n";
    save_data<<collided<<"//whether the object has collided\n";
    save_data.close();
    std::clog<<"object#"<<number<<'('<<type<<')'<<" saved.\n";
}

rts_object::rts_object(): clickable_object(), tangible_object(), complex_object()
{
    type="rts object";
    position.set(origin);
    speed=2.0f;
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
