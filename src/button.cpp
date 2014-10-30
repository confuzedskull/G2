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

void button::format()
{
    width=label.get_width()+(margin*2);
    height=label.get_height()+(margin*2);
    calc_boundaries();
}

void button::set_label(std::string l)
{
    label.clear();
    label.add_line(l);
    format();
}

void button::allign_label(std::string allignment)
{
    label_allignment=allignment;
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
                std::clog<<"object#"<<number<<'('<<type<<')'<<"clicked.\n";
            }
        }
        else
            performed_action=false;
    }
}

void button::render()
{
    if(visible)
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

        mark_selected();
        //render button text
        label.render();
    }
}

void button::update()
{
    label.visible=visible;
    if(label_allignment=="left")
        label.set_position(xmin+margin,position.y-(label.get_height()/2));
    if(label_allignment=="center")
        label.set_position(position.x-(label.get_width()/2),position.y-(label.get_height()/2));
    if(label_allignment=="right")
        label.set_position(xmax-margin-label.get_width(),position.y-(label.get_height()/2));
    mouse_function();
}

void button::action_placeholder(){}

button::button()
{
    type="button";
    margin=5;
    position.set(0.0f,0.0f);
    primary_color.set(0.75f,0.75f,0.75f);
    primary_color.changed=false;
    set_label("click me");
    allign_label("center");
    action=button::action_placeholder;
    border=true;
    performed_action=false;
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}

button::button(float x, float y, char* l, void (*a)(void))
{
    type="button";
    margin=5;
    position.set(x,y);
    primary_color.set(0.75f,0.75f,0.75f);
    primary_color.changed=false;
    set_label("click me");
    allign_label("center");
    action=a;
    border=true;
    performed_action=false;
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
