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

#include "object.h"
#include "window.h"
#include "distance.h"
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
#include <sstream>
#include <math.h>

//initialize static variable
int object::total_objects=0;
point2i object::origin = point2i(0,0);

int object::get_number()
{
    return number;
}

std::string object::get_type()
{
    return "basic object";
}

point2i object::get_position()
{
    return position;
}

point2i* object::get_positionptr()
{
    return &position;
}

float object::get_rotation()
{
    return rotation;
}

int object::get_width()
{
    return width;
}

int object::get_height()
{
    return height;
}

float object::get_radius()
{
    return distance(xmin,ymin,xmax,ymax)/2;;
}

void object::set_position(int x, int y)
{
    position.set(x,y);
    calc_boundaries();
}

void object::set_rotation(float angle)
{
    rotation=angle;
}

void object::set_dimensions(int w, int h)
{
    width=w;
    height=h;
    calc_boundaries();
}

void object::calc_boundaries()//calculates the limits of the object
{
    //these two variables store reused data in order to save calculations
    int half_width=width/2;
    int half_height=height/2;
    xmin=position.x-half_width;
    xmax=position.x+half_width;
    ymin=position.y-half_height;
    ymax=position.y+half_height;
}

void object::rotate(float angle)
{
    rotation+=angle;
}

void object::mark_selected()
{
    if(selected)
    {
        glColor3f(marker_color.r,marker_color.g,marker_color.b);
        glBegin(GL_LINES);//draws lines (in this case, a rectangle)
        glVertex2f(xmin-marker_width, ymax+marker_height);//top left corner
        glVertex2f(xmax+marker_width, ymax+marker_height);//top right corner
        glVertex2f(xmax+marker_width, ymax+marker_height);//top right corner
        glVertex2f(xmax+marker_width, ymin-marker_height);//bottom right corner
        glVertex2f(xmax+marker_width, ymin-marker_height);//bottom right corner
        glVertex2f(xmin-marker_width, ymin-marker_height);//bottom left corner
        glVertex2f(xmin-marker_width, ymin-marker_height);//bottom left corner
        glVertex2f(xmin-marker_width, ymax+marker_height);//top left corner
        glEnd();
    }
}

void object::hide()
{
    visible=false;
}

void object::show()
{
    visible=true;
}

void object::render_shape()
{
    if(filled)
    {
        glPushMatrix();//need push and pop so that entire scene isn't rotated
        glTranslatef(position.x,position.y,0.0);//translate object according to coordinates
        glRotatef(rotation,0,0,1);//rotates object with object.rotation
        glTranslatef(-position.x,-position.y,0.0);//translate object according to coordinates
        glColor3f(fill_color.r,fill_color.g,fill_color.b);//color the square with object.fill_color
        glBegin(GL_POLYGON);//draws a filled in rectangle
        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner
        glEnd();//finish drawing
        glPopMatrix();//reset transformation matrix
    }
}

void object::render_border()
{
    if(bordered)
    {
        glPushMatrix();//need push and pop so that entire scene isn't rotated
        glTranslatef(position.x,position.y,0.0);//translate object according to coordinates
        glRotatef(rotation,0,0,1);//rotates object with object.rotation
        glTranslatef(-position.x,-position.y,0.0);//translate object according to coordinates
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
        glPopMatrix();//reset transformation matrix
    }
}

void object::render()//draws the object
{
    if(visible)
    {
        render_shape();
        render_border();
        mark_selected();
    }
}

void object::update(){}

object::object()
{
    number=++total_objects;
    position.set(origin);
    rotation=0.0f;
    set_dimensions(64,64);
    marker_width=5;
    marker_height=5;
    fill_color.randomize();
    fill_color.changed=false;
    filled=true;
    marker_color=BLACK;
    border_color=BLACK;
    bordered=false;
    show();
    selected=false;
}

object::object(int x, int y, int w, int h)
{
    number=++total_objects;
    position.set(x,y);
    rotation=0.0f;
    set_dimensions(w,h);
    marker_width=5;
    marker_height=5;
    marker_color=BLACK;
    fill_color.randomize();
    fill_color.changed=false;
    filled=true;
    border_color=BLACK;
    bordered=false;
    show();
    selected=false;
}

object::object(int x, int y, int w, int h, color c)
{
    number=++total_objects;
    position.set(x,y);
    set_dimensions(w,h);
    marker_width=5;
    marker_height=5;
    marker_color=BLACK;
    fill_color.set(c);
    fill_color.changed=false;
    filled=true;
    border_color=BLACK;
    bordered=false;
    show();
    selected=false;
}

object::~object(){}
