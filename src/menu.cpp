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

#include "menu.h"
#include "window.h"
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
#include "cursor.h"

void menu::open()
{
    visible=true;
}

void menu::close()
{
    visible=false;
}

void menu::render()
{
    if(visible)
    {
        glPushMatrix();//need push and pop so that entire scene isn't rotated
        glColor3f(primary_color.r,primary_color.g,primary_color.b);//color the square with object.primary_color
        glBegin(GL_POLYGON);//draws a filled in rectangle
        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner
        glEnd();//finish drawing
        glPopMatrix();//reset transformation matrix
    }
    for(unsigned i=0; i<items.size(); i++)
    {
        items[i]->render();
    }
}

void menu::update()
{
    for(unsigned i=0; i<items.size(); i++)
    {
        items[i]->update();
    }
}

menu::menu()
{
    type="menu";
    primary_color.set(0.75,0.75,0.75);
    set_position(window::center.x,window::center.y);
    set_dimensions(window::width,window::height);
}
