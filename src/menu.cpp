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
#include <iostream>

int menu::item_selected()
{
    for(int i=0;i<items.size();i++)
    {
        if(items[i]->selected)
            return i;
    }
    return -1;
}

int menu::item_clicked()
{
    for(int i=0;i<items.size();i++)
    {
        if(items[i]->enabled && items[i]->left_clicked())
            return i;
    }
    return -1;
}

void menu::format()
{
    int total_width=0;//width of buttons and the spaces between
    int total_height=0;//height of buttons and spaces between
    int widest;//width of the widest item
    if(isgreater(title.get_width(),subtitle.get_width()))
        widest=title.get_width();
    else
        widest=subtitle.get_width();
    if(title_allignment=="middle")
        total_height=items.front()->get_height();
    //arrange the items
    for(unsigned i=0;i<items.size();i++)//use regular 'for' loop because 'i' is used as number
    {
        total_width+=items[i]->get_width();
        if(isgreater(items[i]->get_width(),widest))
            widest=items[i]->get_width();
        if(layout=="vertical")
            items[i]->set_position(position.x,position.y-total_height);//arrange item at bottom
        if(layout=="horizontal")
        {
            if(i%2==0)//divide the items among either side of the center of the menu
                items[i]->set_position(position.x-(total_width/2),position.y-(items[0]->get_height()));//even numbers go to the left side
            else
                items[i]->set_position(position.x+(total_width/2),position.y-(items[0]->get_height()));//odd numbers go to the right side
        }
        total_height+=(items[i]->get_height()+spacing);
    }
    //resize the menu
    if(layout=="vertical")
    {
        if(title.visible)
        {
            if(subtitle.visible)
                set_dimensions(widest+(margin*2),total_height+title.get_height()+subtitle.get_height()+spacing+(margin*2));
            else
                set_dimensions(widest+(margin*2),total_height+title.get_height()+spacing+(margin*2));
        }
        else
            set_dimensions(widest+(margin*2),total_height+(margin*2));

    }
    if(layout=="horizontal")
    {
        if(title.visible)
        {
            if(subtitle.visible)
                set_dimensions(widest+(margin*2),items[0]->get_height()+title.get_height()+subtitle.get_height()+spacing+(margin*2));
            else
                set_dimensions(widest+(margin*2),items[0]->get_height()+title.get_height()+spacing+(margin*2));
        }
        else
            set_dimensions(widest+(margin*2),items[0]->get_height()+(margin*2));
    }
    //set the position of the text
    if(title_allignment=="top")
    {
        title.set_position(position.x-(title.get_width()/2),ymax-margin-title.get_height());
        subtitle.set_position(position.x-(subtitle.get_width()/2),ymax-margin-title.get_height()-subtitle.get_height());
    }
    if(title_allignment=="middle")
    {
        title.set_position(position.x-(title.get_width()/2),position.y-(title.get_height()/2));
        subtitle.set_position(position.x-(subtitle.get_width()/2),position.y-(subtitle.get_height()/2));
    }
    if(title_allignment=="bottom")
    {
        title.set_position(position.x-(title.get_width()/2),ymin+margin+title.get_height()+subtitle.get_height());
        subtitle.set_position(position.x-(subtitle.get_width()/2),ymin+margin+subtitle.get_height());
    }
}

void menu::set_title(std::string t)
{
    title.clear();
    title.add_line(t);
}

void menu::set_subtitle(std::string s)
{
    subtitle.clear();
    subtitle.add_line(s);
    subtitle.show();
}

void menu::set_layout(std::string l)
{
    if(l=="vertical" || l=="horizontal")
        layout=l;
}

void menu::allign_title(std::string a)
{
    title_allignment=a;
}

void menu::add_item(button* b)
{
    items.push_back(b);
}

void menu::render()
{
    if(visible)
    {
        render_shape();
        title.render();
        subtitle.render();
        for(auto i:items)
            i->render();
        render_border();
    }
}

void menu::update()
{
    for(auto i:items)
    {
        if(i->selected)
            current_item=i;
        i->visible=visible;//if menu is visible, items are visible
        i->update();
    }
}

menu::menu()
{
    set_position(window::center.x,window::center.y);
    fill_color.set(0.75,0.75,0.75);//make the background dark gray
    set_title("menu");
    title.set_font("helvetica",18);
    allign_title("top");
    subtitle.set_font("helvetica",12);
    subtitle.hide();
    layout="vertical";
    spacing=10;
    margin=20;
    bordered=true;
    std::clog<<"object#"<<number<<"(menu)"<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
