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

point2f draggable_object::origin = point2f(window::width*0.9,window::height*0.7);

bool draggable_object::grabbed()
{
    if(cursor::left_dragging && !cursor::highlighting &&
       isless(cursor::left_drag.x,xmax) && isgreater(cursor::left_drag.x,xmin) &&
       isless(cursor::left_drag.y,ymax) && isgreater(cursor::left_drag.y,ymin))
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
            position.set(cursor::left_drag.x,cursor::left_drag.y);
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

draggable_object::draggable_object()
{
    type="draggable object";
    fill_color=BLACK;
    position.set(origin);
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
