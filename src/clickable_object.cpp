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

bool clickable_object::hovered_over()
{
    if(!cursor::left_click &&
       isless(cursor::passive.x,xmax) && isgreater(cursor::passive.x,xmin) &&
       isless(cursor::passive.y,ymax) && isgreater(cursor::passive.y,ymin))
        return true;
    else
        return false;
}

bool clickable_object::left_clicked()
{
    if(cursor::left_click &&
       isless(cursor::left_down.x,xmax) && isgreater(cursor::left_down.x,xmin) &&
       isless(cursor::left_down.y,ymax) && isgreater(cursor::left_down.y,ymin))
        return true;
    else
        return false;
}

bool clickable_object::right_clicked()
{
    if(cursor::right_click &&
       isless(cursor::right_down.x,xmax) && isgreater(cursor::right_down.x,xmin) &&
       isless(cursor::right_down.y,ymax) && isgreater(cursor::right_down.y,ymin))
        return true;
    else
        return false;
}

void clickable_object::mouse_function()
{
    if(left_clicked())//clicked this object
    {
        if(!selected)
        std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" selected"<<std::endl;
        cursor::left_clicked_object=this;
        cursor::left_clicked_an_object = true;
        cursor::selected_object=number;
        selected = true;
    }

    if(cursor::left_click && cursor::left_clicked_an_object && cursor::selected_object!=number)//clicked another object
    {
        cursor::highlighted_objects[number]=false;
        selected = false;
    }

    if(cursor::left_click && !cursor::left_clicked_an_object)//clicked nothing
    {
        cursor::highlighted_objects[number]=false;
        selected = false;
    }

    if(right_clicked())//right clicked this object
    {
        cursor::right_clicked_object=this;
        cursor::right_clicked_an_object=true;
    }
}

void clickable_object::update()
{
    mouse_function();
}

clickable_object::clickable_object(): object()
{
    type="clickable object";
    selected=false;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
