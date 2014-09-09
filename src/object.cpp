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

//initialize static variable
int object::total_objects=0;

void object::set_boundaries()//calculates the max's and mins
{
    xmin= current.x-(width/2);
    xmax= current.x+(width/2);
    ymin= current.y-(height/2);
    ymax= current.y+(height/2);

}

void object::render()//draws the object
{
    glPushMatrix();//need push and pop so that entire scene isn't rotated
    glTranslatef(current.x,current.y,0.0);//translate object according to coordinates
    glRotatef(rotation,0,0,1);//rotates object with object.rotation
    glTranslatef(-current.x,-current.y,0.0);//translate object according to coordinates
    glColor3f(primary_color.r,primary_color.g,primary_color.b);//color the square with object.primary_color

    if(!visible)
    {
        std::clog<<"object#"<<number<<": "<<name<<" rendered."<<std::endl;
        visible=true;
    }
    glBegin(GL_POLYGON);//draws a filled in rectangle
    glVertex2f(xmin, ymin); // The bottom left corner
    glVertex2f(xmin, ymax); // The top left corner
    glVertex2f(xmax, ymax); // The top right corner
    glVertex2f(xmax, ymin); // The bottom right corner

    glEnd();//finish drawing

    glPopMatrix();//reset transformation matrix

}

void object::rotate(float angle)
{
    rotation+=angle;
}

int object::get_radius()//calculates a radius from the width and height
{
    return ((width/2)+(height/2))/2;
}


object::object()//constructs an object
{
    name="generic object";
    number=total_objects;
    total_objects++;
    current.x=320.0;
    current.y=160.0;
    rest.x=320.0;
    rest.y=160.0;
    width=64;
    height=64;
    primary_color.set(0.0,0.0,0.0);
    rotation=90;
    visible=false;
    std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;
}

object::object(float x, float y, float w, float h, color c)
{
    name="generic object";
    number=total_objects;
    total_objects++;
    current.x=x;
    current.y=y;
    rest.x=x;
    rest.y=y;
    width=w;
    height=h;
    primary_color.set(c);
    rotation=90.1;
    visible=false;
}
