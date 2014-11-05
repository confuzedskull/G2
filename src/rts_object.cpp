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

rts_object::rts_object(): clickable_object(), tangible_object(), complex_object()
{
    type="rts object";
    position.set(origin);
    speed=2.0f;
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
