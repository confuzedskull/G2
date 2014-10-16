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
#include "cursor.h"
#include "ui.h"
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
#include <string>
#include <math.h>

void menu::open()
{
    visible=true;
}

void menu::close()
{
    visible=false;
}

void menu::format()
{
    //in this function we assume the buttons have the same height but different widths
    int widest=strlen(title)*font_width;//start with the width of title
    int total_width;//width of buttons and the spaces between
    //arrange the items
    for(unsigned i=0;i<items.size();i++)
    {
        total_width+=items[i]->get_width()+spacing;
        if(isgreater(items[i]->get_width(),widest))
            widest=items[i]->get_width();
        if(layout==VERTICAL)
            items[i]->set_position(position.x,position.y-((items[i]->get_height())+spacing)*i);
        if(layout==HORIZONTAL)
            items[i]->set_position(position.x-(((items[i]->get_width())+spacing)*i),position.y);
    }
    //resize the menu
    if(layout==VERTICAL)
        set_dimensions(widest+(margin*2),((items[0]->get_height()+spacing)*items.size())+font_height+(margin*2));
    if(layout==HORIZONTAL)
        set_dimensions(total_width+(margin*2),items[0]->get_height()+font_height+spacing+(margin*2));
}

void menu::set_title(char* t)
{
    title=t;
}

void menu::set_font(void* f)
{
    font=f;
    if(f==GLUT_BITMAP_HELVETICA_12)
    {
        font_height=12;
        font_width=font_height*0.6;
    }

    if(f==GLUT_BITMAP_HELVETICA_18)
    {
        font_height=18;
        font_width=font_height*0.6;
    }
}

void menu::render()
{
    if(visible)
    {
        glColor3f(primary_color.r,primary_color.g,primary_color.b);//color the square with object.primary_color
        glBegin(GL_POLYGON);//draws a filled in rectangle
        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner
        glEnd();//finish drawing
        ui::glutPrint(position.x-((strlen(title)/2)*font_width),position.y+font_height+spacing,font,title);
        for(unsigned i=0; i<items.size(); i++)
        {
            items[i]->render();
        }
    }
}

void menu::update()
{
    for(unsigned i=0; i<items.size(); i++)
    {
        items[i]->visible=visible;
        items[i]->update();
    }
}

menu::menu()
{
    type="menu";
    set_title("Options");
    set_font(GLUT_BITMAP_HELVETICA_18);
    layout=VERTICAL;
    spacing=10;
    margin=20;
    primary_color.set(0.75,0.75,0.75);
    set_position(window::center.x,window::center.y);
    set_dimensions(window::width,window::height);
}
