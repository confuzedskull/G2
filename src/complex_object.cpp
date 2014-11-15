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
#include "complex_object.h"
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

point2f complex_object::get_position()
{
    return position;
}

void complex_object::calc_direction()
{
    float var = 3.14159/180;
    leftward.set(-(sin(rotation*var)),cos(rotation*var));
    rightward.set(sin(rotation*var),-(cos(rotation*var)));
    forward.set(cos(rotation*var),sin(rotation*var));
    backward.set(-(cos(rotation*var)),-(sin(rotation*var)));
}

void complex_object::rotate(float angle)
{
    rotation+=angle;
    calc_direction();//direction is relative to rotation so it must be updated
    calc_points();//points must move with rotation
}

void complex_object::set_position(float x, float y)
{
    position.set(x,y);
    calc_points();
}

void complex_object::set_rotation(float angle)
{
    rotation=angle;
    calc_direction();
    calc_points();
}

void complex_object::calc_points()
{
    float half_width=width/2;
    float half_height=height/2;
    front.set(position.x+(forward.x*half_height),position.y+(forward.y*half_height));
    back.set(position.x+(backward.x*half_height),position.y+(backward.y*half_height));
    left.set(position.x+(leftward.x*half_width),position.y+(leftward.y*half_width));
    right.set(position.x+(rightward.x*half_width),position.y+(rightward.y*half_width));
}

void complex_object::set_dimensions(int w, int h)
{
    width=w;
    height=h;
    calc_boundaries();
    calc_points();
}

void complex_object::render_shape()
{
    if(filled)
    {
        glPushMatrix();//need push and pop so that entire scene isn't rotated
        glTranslatef(position.x,position.y,0.0);//translate object according to coordinates
        glRotatef(rotation,0,0,1);//rotates object with object.rotation
        //glTranslatef(-position.x,-position.y,0.0);//translate object according to coordinates
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

void complex_object::mark_selected()
{
    if(selected)//selected objects are marked by a green ellipse
    {
        glPushMatrix();//modify transformation matrix
        glTranslatef(position.x,position.y,0.0);//translate ellipse according to object coordinates
        glColor3f(marker_color.r,marker_color.g,marker_color.b);
        glBegin(GL_LINE_LOOP);//draws a series of lines
        for(int i=0; i<360; i++)
        {
            float deg_rad=i*3.14159/180;//calculate degrees in radians
            glVertex2f(cos(deg_rad)*radius,sin(deg_rad)*radius);//ellipse function
        }
        glEnd();//finish drawing
        glPopMatrix();//reset transformation matrix
    }
}

//complex objects have their own render method because each vertex is an object whose properties are constantly changing
void complex_object::render()
{
    if(visible)
    {
        render_shape();
        render_border();
        mark_selected();
    }
}

complex_object::complex_object()
{
    marker_color=GREEN;
    rotation=90.1;
}
