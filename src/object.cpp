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
#include <math.h>

//initialize static variable
int object::total_objects=0;

void object::set_dimensions(float w, float h)
{
    width=w;
    height=h;
    calc_boundaries();
}

void object::calc_boundaries()//calculates the limits of the object
{
    //these two variables store reused data in order to save calculations
    float half_width=width/2;
    float half_height=height/2;
    xmin=position.x-half_width;
    xmax=position.x+half_width;
    ymin=position.y-half_height;
    ymax=position.y+half_height;
    radius=distance(xmin,ymin,xmax,ymax)/2;
}

void object::render()//draws the object
{
    if(visible)
    {
        glPushMatrix();//need push and pop so that entire scene isn't rotated
        glTranslatef(position.x,position.y,0.0);//translate object according to coordinates
        glRotatef(rotation,0,0,1);//rotates object with object.rotation
        glTranslatef(-position.x,-position.y,0.0);//translate object according to coordinates
        glColor3f(primary_color.r,primary_color.g,primary_color.b);//color the square with object.primary_color

        glBegin(GL_POLYGON);//draws a filled in rectangle
        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner
        glEnd();//finish drawing
        glPopMatrix();//reset transformation matrix

        if(selected)//selected objects are marked by a green ellipse
        {
            glPushMatrix();//modify transformation matrix
            glTranslatef(position.x,position.y,0.0);//translate ellipse according to object coordinates
            glColor3f(0.0,1.0,0.0);//make the lines green
            glBegin(GL_LINE_LOOP);//draws a series of lines
            for (int i=0; i<360; i++)
            {
                float deg_rad=i*3.14159/180;//calculate degrees in radians
                glVertex2f(cos(deg_rad)*radius,sin(deg_rad)*radius);//ellipse function
            }
            glEnd();//finish drawing
            glPopMatrix();//reset transformation matrix
        }
        if(!rendered)
        {
            std::clog<<"object#"<<number<<": "<<name<<" rendered."<<std::endl;
            rendered=true;
        }
    }
}

void object::rotate(float angle)
{
    rotation+=angle;
}

object::object()
{
    name="unnamed";
    type="object";
    number=total_objects;
    total_objects++;
    position.set(window::width/2,window::height/2);
    set_dimensions(64,64);
    primary_color.set(BLACK);
    rotation=90.1;
    visible=true;
    rendered=false;
    selected=false;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}

object::object(float x, float y, float w, float h)
{
    name="unnamed";
    type="object";
    number=total_objects;
    total_objects++;
    position.set(x,y);
    set_dimensions(w,h);
    primary_color.set(BLACK);
    rotation=90.1;
    visible=true;
    rendered=false;
    selected=false;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}

object::object(float x, float y, float w, float h, color c)
{
    name="unnamed";
    type="object";
    number=total_objects;
    total_objects++;
    position.set(x,y);
    set_dimensions(w,h);
    primary_color.set(c);
    rotation=90.1;
    visible=true;
    rendered=false;
    selected=false;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
