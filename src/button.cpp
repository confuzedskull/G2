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
#include <string.h>

void button::format()
{
    width=label.get_width()+(margin*2);
    height=label.get_height()+(margin*2);
    calc_boundaries();
}

void button::set_label(char* l)
{
    label.set_text(l);
    format();
}

void button::mouse_function()
{
    if(visible)
    {
        if(hovered_over() && !primary_color.changed)
            primary_color.brighten();
        if(!hovered_over())
            primary_color.undo();
        if(left_clicked())
        {
            if(!performed_action)
            {
                action();
                performed_action=true;
            }
        }
        else
            performed_action=false;
    }
}

void button::render()
{
    //render button
    glColor3f(primary_color.r,primary_color.g,primary_color.b);
    glBegin(GL_POLYGON);//draws a filled in rectangle
    glVertex2f(xmin, ymin);//bottom left corner
    glVertex2f(xmin, ymax);//top left corner
    glVertex2f(xmax, ymax);//top right corner
    glVertex2f(xmax, ymin);//bottom right corner
    glEnd();//finish drawing
    //render border
    if(border)
    {
        glColor3f(border_color.r,border_color.g,border_color.b);
        glBegin(GL_LINES);//draws lines (in this case, a rectangle)
        glVertex2f(xmin, ymax);//top left corner
        glVertex2f(xmax, ymax);//top right corner
        glVertex2f(xmax, ymax);//top right corner
        glVertex2f(xmax, ymin);//bottom right corner
        glVertex2f(xmax, ymin);//bottom right corner
        glVertex2f(xmin, ymin);//bottom left corner
        glVertex2f(xmin, ymin);//bottom left corner
        glVertex2f(xmin, ymax);//top left corner
        glEnd();
    }
    //render button text
    label.set_position(position.x-(label.get_width()/2),position.y-(label.get_height()/2));
    label.render();
}

void button::update()
{
    mouse_function();
}

button::button()
{
    type="button";
    set_label("click me");
    margin=5;
    position.set(0.0f,0.0f);
    primary_color.set(0.75f,0.75f,0.75f);
    primary_color.changed=false;
    border=true;
    border_color=BLACK;
    performed_action=false;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}

button::button(float x, float y, char* l, void (*a)(void))
{
    type="button";
    set_label("click me");
    margin=5;
    position.set(x,y);
    primary_color.set(0.75f,0.75f,0.75f);
    primary_color.changed=false;
    action=a;
    border=true;
    border_color=BLACK;
    performed_action=false;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
