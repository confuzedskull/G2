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

#include "checkbox.h"
#include "cursor.h"
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
#include <iostream>

void checkbox::set_label(std::string l)
{
    text.clear();
    text.add_line(l);
    allign_label("left");
}

void checkbox::allign_label(std::string allignment)
{
    if(allignment=="left")
        text.set_position(xmin-margin-text.get_width(),position.y-(text.get_height()/2));
    if(allignment=="right")
        text.set_position(xmax+margin,position.y);
    if(allignment=="top")
        text.set_position(position.x-(text.get_width()/2),ymax+margin);
    if(allignment=="bottom")
        text.set_position(position.x-(text.get_width()/2),ymin-margin-text.get_height());
}

void checkbox::bind_option(int* o)
{
    option=o;
}

void checkbox::mouse_function()
{
    if(visible && enabled)
    {
        if(filled)
        {
            if(hovered_over() && !fill_color.changed)
                fill_color.brighten();
            if(!hovered_over())
                fill_color.undo();
        }
        if(left_clicked())
        {
            if(*option==1)
                checked=0;
            else
                checked=1;
        }
        else
            *option=checked;
    }
}

void checkbox::render()
{
    if(visible)
    {
        render_shape();
        if(checked==1)
        {
            glColor3f(checkmark_color.r,checkmark_color.g,checkmark_color.b);//color the square with object.fill_color
            glBegin(GL_POLYGON);//draws a filled in polygon
            glVertex2f(xmin+checkmark_margin, ymin+checkmark_margin); // The bottom left corner
            glVertex2f(xmin+checkmark_margin, ymax-checkmark_margin); // The top left corner
            glVertex2f(xmax-checkmark_margin, ymax-checkmark_margin); // The top right corner
            glVertex2f(xmax-checkmark_margin, ymin+checkmark_margin); // The bottom right corner
            glEnd();//finish drawing
        }
        render_border();
        text.render();
    }
}

void checkbox::update()
{
    mouse_function();
}

checkbox::checkbox()
{
    bordered=true;
    set_dimensions(16,16);
    fill_color = color(0.75f,0.75f,0.75f);
    margin=4;
    checked=1;
    checkmark_margin=2;
    checkmark_color=BLACK;
    std::clog<<"object#"<<number<<"(checkbox)"<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
