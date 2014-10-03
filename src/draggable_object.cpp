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

bool draggable_object::grabbed()
{
    if(cursor::left_dragging &&
            isless(cursor::left_drag.x,xmax) &&
            isgreater(cursor::left_drag.x,xmin) &&
            isless(cursor::left_drag.y,ymax) &&
            isgreater(cursor::left_drag.y,ymin))
        return true;
    else
        return false;
}

void draggable_object::mouse_function()
{
    if(left_clicked())//clicked this object
    {
        cursor::left_clicked_object=this;
        cursor::left_clicked_an_object = true;
        cursor::selected_object=number;
        selected = true;
    }

    if(cursor::left_click && cursor::selected_object !=number)//clicked another object
    {
        cursor::highlighted_objects[number]=false;
        selected = false;
    }

    if(cursor::left_click && !cursor::left_clicked_an_object)//clicked nothing
    {
        cursor::highlighted_objects[number]=false;
        selected = false;
    }

    if(right_clicked())//right clicked this object
    {
        cursor::right_clicked_object=this;
        cursor::right_clicked_an_object=true;
    }

    if(grabbed())//grabbed this object
    {
        current.set(cursor::left_drag.x,cursor::left_drag.y);
        cursor::grabbed_an_object=true;
    }
}

//draggable objects need their own render method because they do not have a selection indicator
void draggable_object::render()
{
    glColor3f(primary_color.r,primary_color.g,primary_color.b);//color the square with object.primary_color
    if(!rendered)
    {
        std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" rendered."<<std::endl;
        rendered=true;
    }
    if(visible)
    {
        glBegin(GL_POLYGON);//draws a solid shape
        glVertex2f(back_left.x, back_left.y); // The bottom left corner
        glVertex2f(front_left.x, front_left.y); // The top left corner
        glVertex2f(front_right.x, front_right.y); // The top right corner
        glVertex2f(back_right.x, back_right.y); // The bottom right corner
        glEnd();//finish drawing
    }
}

void draggable_object::update()
{
    set_boundaries();
    calc_points();
    calc_direction();
    mouse_function();
}

draggable_object::draggable_object()
{
    type="draggable object";
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created."<<std::endl;
}
