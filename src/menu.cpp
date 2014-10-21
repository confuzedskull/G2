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

void menu::format()
{
    int widest;//width of the widest item
    if(isgreater(title.get_width(),subtitle.get_width()))
        widest=title.get_width();
    else
        widest=subtitle.get_width();
    int total_width=0;//width of buttons and the spaces between
    int total_height=0;//height of buttons and spaces between
    //arrange the items
    for(unsigned i=0;i<items.size();i++)//use regular 'for' loop because 'i' is used as number
    {
        total_width+=items[i]->get_width();
        if(isgreater(items[i]->get_width(),widest))
            widest=items[i]->get_width();
        if(layout==VERTICAL)
            items[i]->set_position(position.x,position.y-total_height);
        if(layout==HORIZONTAL)
        {
            if(i%2==0)//here the iterator is being used as a number
                items[i]->set_position(position.x-(total_width/2),position.y-(items[0]->get_height()));
            else
                items[i]->set_position(position.x+(total_width/2),position.y-(items[0]->get_height()));
        }
        total_height+=(items[i]->get_height()+spacing);
    }
    //resize the menu
    if(layout==VERTICAL)
    {
        if(subtitle.visible)
            set_dimensions(widest+(margin*2),total_height+title.get_height()+subtitle.get_height()+spacing+(margin*2));
        else
            set_dimensions(widest+(margin*2),total_height+title.get_height()+spacing+(margin*2));
    }
    if(layout==HORIZONTAL)
    {
        if(subtitle.visible)
            set_dimensions(widest+(margin*2),items[0]->get_height()+title.get_height()+subtitle.get_height()+spacing+(margin*2));
        else
            set_dimensions(widest+(margin*2),items[0]->get_height()+title.get_height()+spacing+(margin*2));
    }
    //set the position of the text
    title.set_position(position.x-(title.get_width()/2),ymax-margin-title.get_height());
    subtitle.set_position(position.x-(subtitle.get_width()/2),ymax-margin-title.get_height()-subtitle.get_height());
}

void menu::set_title(std::string t)
{
    title.add_line(t);
    format();
}

void menu::set_subtitle(std::string s)
{
    subtitle.visible=true;
    subtitle.add_line(s);
    format();
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
        title.render();
        subtitle.render();
        for(auto i:items)
        {
            i->render();
        }
    }
}

void menu::update()
{
    for(auto i:items)
    {
        i->visible=visible;
        i->update();
    }
}

menu::menu()
{
    type="menu";
    set_position(window::center.x,window::center.y);
    primary_color.set(0.75,0.75,0.75);
    title.set_font("helvetica",18);
    subtitle.set_font("helvetica",12);
    subtitle.visible=false;
    layout=VERTICAL;
    spacing=10;
    margin=20;
}
