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

void clickable_object::mouse_function()
{
    if(left_clicked())//clicked this object
    {
        cursor::left_clicked_object=this;
        cursor::left_clicked_an_object = true;
        cursor::selected_object=number;
        cursor::highlighted_objects[number]=true;
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
    }

    if(selected)
    {
        if(cursor::right_click && !right_clicked())
        {
            if(cursor::right_clicked_an_object)
            {
                rally = &cursor::right_clicked_object->current;//used a reference because current is always changing
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
        /*if(left_clicked() && cursor::left_dragging)//allows user to drag the object around
        {
            current.x = cursor::left_drag.x;
            current.y = cursor::left_drag.y;
        }*/
    }
}

clickable_object::clickable_object()
{
    name="clickable object";
    selected=false;
    std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;
}


