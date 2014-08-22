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
        cursor::selected_object=number;
        cursor::highlighted_objects[number]=true;
        selected = true;
    }

    if(!left_clicked() && cursor::left_clicked_an_object)//clicked another object
    {
        cursor::highlighted_objects[number]=false;
        selected = false;
    }

    if(!cursor::left_clicked_an_object)//clicked nothing
    {
        cursor::highlighted_objects[number]=false;
    }

    if(highlighted())
    {
        cursor::highlighted_objects[number]=true;
        selected=true;
    }

    if(right_clicked())
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
                delete &rally;
                rally = new point2f(cursor::right_down.x,cursor::right_down.y);
                //rally = &cursor1.right_down;
            }
            rally_set=true;
        }
        if(cursor::right_dragging && !right_clicked())
        {
            //rally = &cursor::right_drag;
            rally_set=true;
        }
        if(cursor::objects_selected()==1 && cursor::left_dragging)
        {
            current.x = cursor::left_drag.x;
            current.y = cursor::left_drag.y;
        }

        //current_color.set(GREEN);
    }
    else
    {
        //undo_color();
    }
}

clickable_object::clickable_object()
{
    name="clickable object";
    selected=false;
    std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;
}


