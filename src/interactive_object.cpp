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

#include "interactive_object.h"
#include "cursor.h"
#include "utilities.h"
#include "audio.h"
#include <math.h>
#include <sstream>
#include <iostream>

bool interactive_object::enable_clicking = true;
bool interactive_object::enable_dragging = false;
bool interactive_object::enable_hovering = true;
bool interactive_object::enable_highlighting = false;

bool interactive_object::highlighted()
{
    //if object lies within selection box boundaries, return true
    return (cursor::highlighting &&
        position.x<cursor::xmax && position.x>cursor::xmin &&
        position.y>cursor::ymax && position.y<cursor::ymin);
}

bool interactive_object::dragged()
{
    return (drag_detection && cursor::left_dragging && !cursor::highlighting &&
       (cursor::left_drag.x<xmax) && (cursor::left_drag.x>xmin) &&
       (cursor::left_drag.y<ymax) && (cursor::left_drag.y>ymin));
}

bool interactive_object::hovered_over()
{
    return (hover_detection && !cursor::left_clicking &&
       (cursor::passive.x<xmax) && (cursor::passive.x>xmin) &&
       (cursor::passive.y<ymax) && (cursor::passive.y>ymin));
}

bool interactive_object::left_clicked()
{
    return (click_detection && cursor::left_clicking &&
       (cursor::left_down.x<xmax) && (cursor::left_down.x>xmin) &&
       (cursor::left_down.y<ymax) && (cursor::left_down.y>ymin));
}

bool interactive_object::right_clicked()
{
    return (click_detection && cursor::right_clicking &&
       (cursor::right_down.x<xmax) && (cursor::right_down.x>xmin) &&
       (cursor::right_down.y<ymax) && (cursor::right_down.y>ymin));
}

void interactive_object::highlight_function()
{
    if(highlighted())//object lies within selection box
    {
        cursor::selected_objects[number]=this;
        selected=true;
    }
}

void interactive_object::drag_function()
{
    if(dragged())
        set_position(cursor::left_drag.x,cursor::left_drag.y);
}

void interactive_object::hover_function()
{
    if(hovered_over() && !fill_color.changed)
    {
        if(!muted)
            audio::play(hover_sound);
        fill_color.brighten();
    }
    if(!hovered_over())
        fill_color.undo();
}

void interactive_object::leftclick_function()
{
    if(left_clicked())//clicked this object
    {
        if(!selected)
        {
            if(!muted)
                audio::play(click_sound);
            std::clog<<"object#"<<number<<"(interactive object)"<<" selected"<<std::endl;
        }
        cursor::left_clicked_object=this;
        cursor::selected_object=number;
        cursor::selected_objects[number]=this;
        selected = true;
    }
    else if(selected)
    {
        if(cursor::left_clicking && !cursor::highlighting)
        {
            if(cursor::selected_object!=number)//clicked another object
            {
                selected = false;
                cursor::selected_objects.erase(cursor::selected_object);
            }
        }
    }
}

void interactive_object::rightclick_function()
{
    if(right_clicked())//right clicked this object
        cursor::right_clicked_object=this;
}

void interactive_object::mouse_function()
{
    if(visible)
    {
        drag_function();
        highlight_function();
        leftclick_function();
        rightclick_function();
    }
}

void interactive_object::set_clicksound(std::string filename)
{
    if(audio::sounds.find(filename)!=audio::sounds.end())
        click_sound=filename;
    else
        std::cerr<<filename<<" not found.\n";
}

void interactive_object::set_hoversound(std::string filename)
{
    if(audio::sounds.find(filename)!=audio::sounds.end())
        hover_sound=filename;
    else
        std::cerr<<filename<<" not found.\n";
}

void interactive_object::update()
{
    mouse_function();
}

void interactive_object::load()
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
    //load interactive object properties
    object_file>>click_detection;
    object_file>>drag_detection;
    object_file>>hover_detection;
    object_file>>highlight_detection;
    object_file>>click_sound;
    object_file>>hover_sound;
    object_file.close();
    std::clog<<"object#"<<number<<"(interactive object)"<<" loaded.\n";
}

void interactive_object::save()
{
    std::stringstream filename;
    filename<<"./data/objects/object#"<<number<<".iao";
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
    //save interactive object properties
    object_file<<click_detection<<std::endl;
    object_file<<drag_detection<<std::endl;
    object_file<<hover_detection<<std::endl;
    object_file<<highlight_detection<<std::endl;
    object_file<<click_sound<<std::endl;
    object_file<<hover_sound<<std::endl;
    object_file.close();
    std::clog<<"object#"<<number<<"(interactive object)"<<" saved.\n";
}

interactive_object::interactive_object(): basic_object()
{
    click_detection=enable_clicking;
    drag_detection=enable_dragging;
    hover_detection=enable_hovering;
    highlight_detection=enable_highlighting;
}
