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
#include "distance.h"
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

point2f complex_object::front()
{
    float half_height = height/2;
    return point2f(position.x+((forward.x/step_size)*half_height),position.y+((forward.y/step_size)*half_height));
}

point2f complex_object::back()
{
    float half_height = height/2;
    return point2f(position.x+((backward.x/step_size)*half_height),position.y+((backward.y/step_size)*half_height));
}

point2f complex_object::left()
{
    float half_width = width/2;
    return point2f(position.x+((leftward.x/step_size)*half_width),position.y+((leftward.y/step_size)*half_width));
}

point2f complex_object::right()
{
    float half_width = width/2;
    return point2f(position.x+((rightward.x/step_size)*half_width),position.y+((rightward.y/step_size)*half_width));
}

void complex_object::orient()
{
    float deg_rad = 3.14159/180;
    leftward.set(-(sin(rotation*deg_rad))*step_size,cos(rotation*deg_rad)*step_size);
    rightward.set(sin(rotation*deg_rad)*step_size,-(cos(rotation*deg_rad))*step_size);
    forward.set(cos(rotation*deg_rad)*step_size,sin(rotation*deg_rad)*step_size);
    backward.set(-(cos(rotation*deg_rad))*step_size,-(sin(rotation*deg_rad))*step_size);
}

void complex_object::rotate(float angle)
{
    rotation+=angle;
    orient();//direction is relative to rotation so it must be updated
}

void complex_object::set_rotation(float angle)
{
    rotation=angle;
    orient();
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
            glVertex2f(cos(deg_rad)*get_radius(),sin(deg_rad)*get_radius());//ellipse function
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
    rotation=90.1f;
    step_size=1.0f;
}
