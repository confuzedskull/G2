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
#include "distance.h"
#include <math.h>
#include <iostream>

bool clickable_object::highlighted()
{
    //if object lies within selection box boundaries, return true
    if(cursor::highlighting && enabled &&
        position.x<cursor::xmax && position.x>cursor::xmin &&
        position.y>cursor::ymax && position.y<cursor::ymin)
        return true;
    else
        return false;
}

bool clickable_object::hovered_over()
{
    if(!cursor::left_click && enabled &&
       (cursor::passive.x<xmax) && (cursor::passive.x>xmin) &&
       (cursor::passive.y<ymax) && (cursor::passive.y>ymin))
        return true;
    else
        return false;
}

bool clickable_object::left_clicked()
{
    if(cursor::left_click && enabled &&
       (cursor::left_down.x<xmax) && (cursor::left_down.x>xmin) &&
       (cursor::left_down.y<ymax) && (cursor::left_down.y>ymin))
        return true;
    else
        return false;
}

bool clickable_object::right_clicked()
{
    if(cursor::right_click && enabled &&
       (cursor::right_down.x<xmax) && (cursor::right_down.x>xmin) &&
       (cursor::right_down.y<ymax) && (cursor::right_down.y>ymin))
        return true;
    else
        return false;
}

void clickable_object::highlight_function()
{
    if(highlighted())//object lies within selection box
    {
        cursor::selected_objects[number]=this;
        selected=true;
    }
}

void clickable_object::hover_function()
{
    if(hovered_over() && !fill_color.changed)
        fill_color.brighten();
    if(!hovered_over())
        fill_color.undo();
}

void clickable_object::left_click_function()
{
    if(left_clicked())//clicked this object
    {
        if(!selected)
            std::clog<<"object#"<<number<<"(clickable object)"<<" selected"<<std::endl;
        cursor::left_clicked_object=this;
        cursor::left_clicked_an_object = true;
        cursor::selected_object=number;
        cursor::selected_objects[number]=this;
        selected = true;
    }
    else if(selected)
    {
        if(cursor::left_click && !cursor::highlighting)
        {
            if(cursor::left_clicked_an_object && cursor::selected_object !=number)//clicked another object
            {
                selected = false;
                cursor::selected_objects.erase(number);
            }
            if(!cursor::left_clicked_ui)//clicked nothing
                selected = false;
        }
    }
}

void clickable_object::right_click_function()
{
    if(right_clicked())//right clicked this object
    {
        cursor::right_clicked_object=this;
        cursor::right_clicked_an_object=true;
    }
}

void clickable_object::mouse_function()
{
    if(visible && enabled)
    {
        highlight_function();
        left_click_function();
        right_click_function();
    }
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

clickable_object::clickable_object(): basic_object()
{
    enable();
}
