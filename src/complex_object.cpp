/*  This file is a part of G2 - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    G2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    G2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of G2.  If not, see <http://www.gnu.org/licenses/>.*/

#include "complex_object.h"
#include "utilities.h"
#include <math.h>
#include <sstream>
#include <fstream>
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
    return point2f(position.x+(forward.x*half_height),position.y+(forward.y*half_height));
}

point2f complex_object::back()
{
    float half_height = height/2;
    return point2f(position.x+(backward.x*half_height),position.y+(backward.y*half_height));
}

point2f complex_object::left()
{
    float half_width = width/2;
    return point2f(position.x+(leftward.x*half_width),position.y+(leftward.y*half_width));
}

point2f complex_object::right()
{
    float half_width = width/2;
    return point2f(position.x+(rightward.x*half_width),position.y+(rightward.y*half_width));
}

std::string complex_object::get_type()
{
    return "complex object";
}

void complex_object::orient()
{
    float deg_rad = 3.14159f/180.0f;
    leftward.set(-(sin(rotation*deg_rad)),cos(rotation*deg_rad));
    rightward.set(sin(rotation*deg_rad),-(cos(rotation*deg_rad)));
    forward.set(cos(rotation*deg_rad),sin(rotation*deg_rad));
    backward.set(-(cos(rotation*deg_rad)),-(sin(rotation*deg_rad)));
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
        glTranslatef(position.x,position.y,0.0f);//translate ellipse according to object coordinates
        glColor3f(marker_color.r,marker_color.g,marker_color.b);
        glBegin(GL_LINE_LOOP);//draws a series of lines
        for(int i=0; i<360; i++)
        {
            float deg_rad=i*3.14159f/180.0f;//calculate degrees in radians
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
        glPushMatrix();//need push and pop so that entire scene isn't rotated
        glTranslatef(position.x,position.y,0.0);//translate object according to coordinates
        glRotatef(rotation,0,0,1);//rotates object with object.rotation
        glTranslatef(-position.x,-position.y,0.0);//translate object according to coordinates
        render_shape();
        render_border();
        render_texture();
        mark_selected();
        glPopMatrix();//reset transformation matrix
    }
}

void complex_object::save()
{
    std::stringstream filename;
    filename<<"./data/objects/object#"<<number<<".cpo";
    std::ofstream object_file(filename.str());
    if(object_file.bad())
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //save basic object properties
    object_file<<position.x<<' '<<position.y<<std::endl;
    object_file<<rotation<<std::endl;
    object_file<<width<<' '<<height<<std::endl;
    object_file<<fill_color.str()<<std::endl;
    object_file<<marker_color.str()<<std::endl;
    object_file<<border_color.str()<<std::endl;
    object_file<<filled<<std::endl;
    object_file<<bordered<<std::endl;
    object_file<<textured<<std::endl;
    object_file<<masked<<std::endl;
    object_file<<visible<<std::endl;
    object_file<<selected<<std::endl;
    object_file<<muted<<std::endl;
    object_file<<texture<<std::endl;
    object_file<<mask<<std::endl;
    for(auto p:properties)
        object_file<<p.first<<' '<<p.second<<std::endl;
    object_file<<std::endl;
    object_file.close();
    std::clog<<"object#"<<number<<"(complex object)"<<" saved.\n";
}

void complex_object::load()
{
    std::ifstream object_file(file_name);//access file by name
    if(object_file.bad())//make sure the file is there
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //load basic object properties
    object_file>>position.x>>position.y;
    object_file>>rotation;
    object_file>>width>>height;
    object_file>>fill_color.r>>fill_color.g>>fill_color.b;
    object_file>>marker_color.r>>marker_color.g>>marker_color.b;
    object_file>>border_color.r>>border_color.g>>border_color.b;
    object_file>>filled;
    object_file>>bordered;
    object_file>>textured;
    object_file>>masked;
    object_file>>visible;
    object_file>>selected;
    object_file>>muted;
    object_file>>texture;
    object_file>>mask;
    char first_char=' ';
     //load custom properties
    while(first_char>0)//not newline or out of bounds
    {
        std::string name;
        int value;
        object_file.get();//eat the null character
        first_char=object_file.peek();//check the first character of the line
        if(first_char=='\n')
            break;
        object_file>>name>>value;
        add_property(name,value);
    }
    std::clog<<"object#"<<number<<"(complex object)"<<" loaded.\n";
}

complex_object::complex_object()
{
    marker_color=GREEN;
    rotation=90.0f;
}
