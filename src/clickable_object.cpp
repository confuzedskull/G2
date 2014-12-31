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

#include "clickable_object.h"
#include "cursor.h"
#include "utilities.h"
#include "audio.h"
#include <math.h>
#include <iostream>

bool clickable_object::enable_dragging = false;

bool clickable_object::highlighted()
{
    //if object lies within selection box boundaries, return true
    return (enabled && cursor::highlighting &&
        position.x<cursor::xmax && position.x>cursor::xmin &&
        position.y>cursor::ymax && position.y<cursor::ymin);
}

bool clickable_object::dragged()
{
    return (enabled && draggable && cursor::left_dragging && !cursor::highlighting &&
       (cursor::left_drag.x<xmax) && (cursor::left_drag.x>xmin) &&
       (cursor::left_drag.y<ymax) && (cursor::left_drag.y>ymin));
}

bool clickable_object::hovered_over()
{
    return (enabled && !cursor::left_clicking &&
       (cursor::passive.x<xmax) && (cursor::passive.x>xmin) &&
       (cursor::passive.y<ymax) && (cursor::passive.y>ymin));
}

bool clickable_object::left_clicked()
{
    return (enabled && cursor::left_clicking &&
       (cursor::left_down.x<xmax) && (cursor::left_down.x>xmin) &&
       (cursor::left_down.y<ymax) && (cursor::left_down.y>ymin));
}

bool clickable_object::right_clicked()
{
    return (enabled && cursor::right_clicking &&
       (cursor::right_down.x<xmax) && (cursor::right_down.x>xmin) &&
       (cursor::right_down.y<ymax) && (cursor::right_down.y>ymin));
}

bool clickable_object::double_clicked()
{
    return (enabled && cursor::left_clicking && (click_time<1000) &&
        (cursor::left_down.x<xmax) && (cursor::left_down.x>xmin) &&
        (cursor::left_down.y<ymax) && (cursor::left_down.y>ymin));
}

void clickable_object::highlight_function()
{
    if(highlighted())//object lies within selection box
    {
        cursor::selected_objects[number]=this;
        selected=true;
    }
}

void clickable_object::drag_function()
{
    if(dragged())
        set_position(cursor::left_drag.x,cursor::left_drag.y);
}

void clickable_object::hover_function()
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

void clickable_object::left_click_function()
{
    if(left_clicked())//clicked this object
    {
        if(!selected)
        {
            if(!muted)
                audio::play(click_sound);
            std::clog<<"object#"<<number<<"(clickable object)"<<" selected"<<std::endl;
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

void clickable_object::right_click_function()
{
    if(right_clicked())//right clicked this object
        cursor::right_clicked_object=this;
}

void clickable_object::mouse_function()
{
    if(visible && enabled)
    {
        drag_function();
        highlight_function();
        left_click_function();
        right_click_function();
    }
}

void clickable_object::set_click_sound(std::string filename)
{
    if(audio::sounds.find(filename)!=audio::sounds.end())
        click_sound=filename;
    else
        std::cerr<<filename<<" not found.\n";
}

void clickable_object::set_hover_sound(std::string filename)
{
    if(audio::sounds.find(filename)!=audio::sounds.end())
        hover_sound=filename;
    else
        std::cerr<<filename<<" not found.\n";
}

void clickable_object::enable()
{
    enabled=true;
}

void clickable_object::disable()
{
    enabled=false;
}

void clickable_object::update()
{
    mouse_function();
}

void clickable_object::sync()
{
    if(left_clicked())
        click_time++;
    else
        click_time=0;
}

clickable_object::clickable_object(): basic_object()
{
    enable();
    draggable=enable_dragging;
    click_time=0;
}
