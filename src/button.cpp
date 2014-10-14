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

#include "button.h"
#include "ui.h"
#include "window.h"
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
#include <math.h>

bool button::hovered_over()
{
    if(!cursor::left_click &&
       isless(cursor::passive.x,xmax) && isgreater(cursor::passive.x,xmin) &&
       isless(cursor::passive.y,ymax) && isgreater(cursor::passive.y,ymin))
        return true;
    else
        return false;
}

bool button::left_clicked()
{
    if(cursor::left_click &&
       isless(cursor::left_down.x,xmax) && isgreater(cursor::left_down.x,xmin) &&
       isless(cursor::left_down.y,ymax) && isgreater(cursor::left_down.y,ymin))
        return true;
    else
        return false;
}

void button::fit_label()
{
    width=(((float)strlen(label)-2)*(font_size*0.6f))+(label_margin*2.0f);
    height=font_size+(label_margin*2.0f);
    calc_boundaries();
}

void button::set_label(char* l)
{
    label=l;
    fit_label();
}

void button::mouse_function()
{
    if(hovered_over() && !primary_color.changed)
        primary_color.brighten();
    if(!hovered_over())
        primary_color.undo();
    if(left_clicked() && !performed_action)
    {
        action();
        performed_action=true;
    }
    if(!left_clicked())
        performed_action=false;

}

void button::render()
{
    //render button
    glColor3f(primary_color.r,primary_color.g,primary_color.b);//color the square with object.primary_color
    glBegin(GL_POLYGON);//draws a filled in rectangle
    glVertex2f(xmin, ymin); // The bottom left corner
    glVertex2f(xmin, ymax); // The top left corner
    glVertex2f(xmax, ymax); // The top right corner
    glVertex2f(xmax, ymin); // The bottom right corner
    glEnd();//finish drawing
    //render button text
    ui::glutPrint(xmin+label_margin,ymin+label_margin+spacing,label);
}

void button::update()
{
    mouse_function();
}

button::button()
{
    label="click me";
    type="button";
    label_margin=4.0f;
    font_size=12.0f;
    spacing=1.0f;
    position.set(0.0f,0.0f);
    fit_label();
    primary_color.set(0.75f,0.75f,0.75f);
    primary_color.changed=false;
    performed_action=false;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
