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
    front_left.set(position.x+((forward.x+leftward.x)*half_height),position.y+((forward.y+leftward.y)*half_height));
    front_right.set(position.x+((forward.x+rightward.x)*half_height),position.y+((forward.y+rightward.y)*half_height));
    back_left.set(position.x+((backward.x+leftward.x)*half_width),position.y+((backward.y+leftward.y)*half_width));
    back_right.set(position.x+((backward.x+rightward.x)*half_width),position.y+((backward.y+rightward.y)*half_width));
}

void complex_object::set_dimensions(float w, float h)
{
    width=w;
    height=h;
    calc_boundaries();
    calc_points();
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
        glColor3f(primary_color.r,primary_color.g,primary_color.b);//color the square with object.primary_color
        glBegin(GL_POLYGON);//draws a filled in polygon
        glVertex2f(back_left.x, back_left.y); // The bottom left corner
        glVertex2f(front_left.x, front_left.y); // The top left corner
        glVertex2f(front_right.x, front_right.y); // The top right corner
        glVertex2f(back_right.x, back_right.y); // The bottom right corner
        glEnd();//finish drawing
        mark_selected();

        if(!rendered)
        {
            std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" rendered."<<std::endl;
            rendered=true;
        }
    }
}

complex_object::complex_object()
{
    type="complex object";
    marker_color=GREEN;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
