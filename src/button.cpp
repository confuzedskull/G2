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

void button::format()
{
    width=(((float)strlen(label))*(font_size*0.6f))+(label_margin*2.0f);
    height=font_size+(label_margin*2.0f);
    calc_boundaries();
}

void button::set_label(char* l)
{
    label=l;
    format();
}

void button::set_font(void* f)
{
    font=f;
    if(f==GLUT_BITMAP_HELVETICA_12)
        font_size=12;
    if(f==GLUT_BITMAP_HELVETICA_18)
        font_size=18;
}

void button::mouse_function()
{
    if(visible)
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
    ui::glutPrint(xmin+label_margin,ymin+label_margin+spacing,font,label);
}

void button::update()
{
    mouse_function();
}

button::button()
{
    label="click me";
    type="button";
    label_margin=6.0f;
    font=GLUT_BITMAP_HELVETICA_12;
    font_size=12.0f;
    spacing=1.0f;
    position.set(0.0f,0.0f);
    format();
    primary_color.set(0.75f,0.75f,0.75f);
    primary_color.changed=false;
    border=true;
    border_color=BLACK;
    performed_action=false;
    std::clog<<"object#"<<number<<": "<<label<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}

button::button(float x, float y, char* l, void (*a)(void))
{
    label="click me";
    type="button";
    label_margin=6.0f;
    set_font(GLUT_BITMAP_HELVETICA_12);
    spacing=1.0f;
    position.set(x,y);
    set_label(l);
    action=a;
    std::clog<<"object#"<<number<<": "<<label<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
