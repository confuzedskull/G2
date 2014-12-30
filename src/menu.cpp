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

int menu::default_spacing = 10;
int menu::default_margin = 20;
std::string menu::default_layout = "vertical";
std::string menu::default_texture = "";
std::string menu::default_mask = "";

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
    if(title.get_width()>subtitle.get_width())
        widest=title.get_width();
    else
        widest=subtitle.get_width();
    //arrange the items
    for(unsigned i=0;i<items.size();i++)//use regular 'for' loop because 'i' is used as number
    {
        if(items[i]->combined_width()>widest)
            widest=items[i]->combined_width();
        if(layout=="vertical")
        {
            if(items[i]->get_type()=="checkbox")
                items[i]->set_position(xmax-margin-items[i]->get_width(),ymax-margin-title.get_height()-total_height);
            else
                items[i]->set_position(position.x,ymax-margin-title.get_height()-items[i]->get_height()-total_height);
        }
        if(layout=="horizontal")
        {
            if(subtitle.visible)
                items[i]->set_position(xmin+margin+total_width,ymax-margin-title.get_height()-spacing-subtitle.get_height()-spacing-(items[0]->get_height()/2));
            else
                items[i]->set_position(xmin+margin+total_width,ymax-margin-title.get_height()-spacing-(items[0]->get_height()/2));
            total_width+=spacing;
        }
        items[i]->format();
        total_width+=items[i]->combined_width();
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
                set_dimensions(total_width+(margin*2),items[0]->get_height()+title.get_height()+spacing+subtitle.get_height()+spacing+(margin*2));
            else
                set_dimensions(total_width+(margin*2),items[0]->get_height()+title.get_height()+spacing+(margin*2));
        }
        else
            set_dimensions(total_width+(margin*2),items[0]->get_height()+(margin*2));
    }
    title.set_position(position.x,ymax-margin-(title.get_height()/2));
    subtitle.set_position(position.x,ymax-margin-title.get_height()-spacing-(subtitle.get_height()/2));
}

void menu::set_title(std::string txt)
{
    title.set_text(txt);
    format();
}

void menu::set_subtitle(std::string txt)
{
    subtitle.set_text(txt);
    subtitle.show();
    format();
}

void menu::set_layout(std::string l)
{
    if(l=="vertical" || l=="horizontal")
        layout=l;
    else
        std::cerr<<"invalid layout.\n";
}


void menu::add_item(button* item)
{
    items.push_back(item);
    format();
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
    set_texture(default_texture);
    set_mask(default_mask);
    title.set_text("menu");
    title.set_font("helvetica",18);
    subtitle.set_font("helvetica",12);
    subtitle.hide();
    layout=default_layout;
    spacing=default_spacing;
    margin=default_margin;
    bordered=true;
    std::clog<<"object#"<<number<<"(menu)"<<" created.\n";
}
