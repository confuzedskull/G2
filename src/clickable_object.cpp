#include "clickable_object.h"
#include "cursor.h"
#include "compare.h"
#include <iostream>

bool clickable_object::left_clicked()
{
    if(cursor::left_click &&
            compare(cursor::left_down.x,xmax)==-1 &&
            compare(cursor::left_down.x,xmin)==1 &&
            compare(cursor::left_down.y,ymax)==-1 &&
            compare(cursor::left_down.y,ymin)==1)
        return true;
    else
        return false;
}

bool clickable_object::right_clicked()
{
    if(cursor::right_click &&
            compare(cursor::right_down.x,xmax)==-1 &&
            compare(cursor::right_down.x,xmin)==1 &&
            compare(cursor::right_down.y,ymax)==-1 &&
            compare(cursor::right_down.y,ymin)==1)
        return true;
    else
        return false;
}

bool clickable_object::highlighted()
{
    //if object lies within selection box boundaries, return true
    if(cursor::highlighting &&
            compare(current.x,cursor::xmax)==-1 &&
            compare(current.x,cursor::xmin)==1 &&
            compare(current.y,cursor::ymax)==1 &&
            compare(current.y,cursor::ymin)==-1)
        return true;
    else
        return false;
}

bool clickable_object::grabbed()
{
    if(cursor::left_dragging &&
            compare(cursor::left_drag.x,xmax)==-1 &&
            compare(cursor::left_drag.x,xmin)==1 &&
            compare(cursor::left_drag.y,ymax)==-1 &&
            compare(cursor::left_drag.y,ymin)==1)
        return true;
    else
        return false;
}

void clickable_object::mouse_function()
{
    if(left_clicked())//clicked this object
    {
        cursor::left_clicked_object=this;
        cursor::left_clicked_an_object = true;
        cursor::selected_object=number;
        selected = true;
    }

    if(cursor::left_click && cursor::selected_object !=number)//clicked another object
    {
        cursor::highlighted_objects[number]=false;
        selected = false;
    }

    if(cursor::left_click && !cursor::left_clicked_an_object)//clicked nothing
    {
        cursor::highlighted_objects[number]=false;
        selected = false;
    }

    if(highlighted())
    {
        cursor::highlighted_objects[number]=true;
        selected=true;
    }

    if(right_clicked())//right clicked this object
    {
        cursor::right_clicked_object=this;
        cursor::right_clicked_an_object=true;
    }

    if(grabbed() && !cursor::highlighting)
    {
        current.set(cursor::left_drag.x,cursor::left_drag.y);
        cursor::grabbed_an_object=true;
    }

    if(selected)
    {
        if(cursor::right_click && !right_clicked())
        {
            if(cursor::right_clicked_an_object)
            {
                //here I used a reference because current is always changing
                rally = &cursor::right_clicked_object->current;
            }
            else
            {
                rally = new point2f(cursor::right_down.x,cursor::right_down.y);
            }
            rally_set=true;
        }
        if(cursor::right_dragging && !right_clicked())
        {
            rally = new point2f(cursor::right_drag.x,cursor::right_drag.y);
            rally_set=true;
        }
    }
}

clickable_object::clickable_object()
{
    name="clickable object";
    selected=false;
    std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;
}
