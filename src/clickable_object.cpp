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
#include "compare.h"
#include "distance.h"
#include <math.h>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
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

    if(highlighted())//object lies within selection box
    {
        cursor::highlighted_objects[number]=true;
        selected=true;
    }

    if(right_clicked())//right clicked this object
    {
        cursor::right_clicked_object=this;
        cursor::right_clicked_an_object=true;
    }

    if(grabbed() && !cursor::highlighting)//object is left clicked and dragged
    {
        current.set(cursor::left_drag.x,cursor::left_drag.y);
        cursor::grabbed_an_object=true;
    }

    if(selected)//you can only move an object when it is selected
    {
        if(cursor::right_click && !right_clicked())
        {
            if(cursor::right_clicked_an_object)
            {
                //move to right clicked object
                rally = &cursor::right_clicked_object->current;//set rally to reference point because current is always changing
            }
            else//move to right clicked empty space
            {
                rally = new point2f(cursor::right_down.x,cursor::right_down.y);
            }
            rally_set=true;
        }
        if(cursor::right_dragging && !right_clicked())
        {
            //move to right drag
            rally = new point2f(cursor::right_drag.x,cursor::right_drag.y);
            rally_set=true;
        }
    }
}
//clickable objects need their own render method because they have a selection indicator
void clickable_object::render()
{
    glColor3f(primary_color.r,primary_color.g,primary_color.b);//color the square with object.primary_color
    if(!rendered)
    {
        std::clog<<"object#"<<number<<": "<<name<<" rendered."<<std::endl;
        rendered=true;
    }
    if(visible)
    {
        glBegin(GL_POLYGON);//draws a solid shape
        glVertex2f(back_left.x, back_left.y); // The bottom left corner
        glVertex2f(front_left.x, front_left.y); // The top left corner
        glVertex2f(front_right.x, front_right.y); // The top right corner
        glVertex2f(back_right.x, back_right.y); // The bottom right corner
        glEnd();//finish drawing

        if(selected)//selected objects are marked by a green ellipse
        {
            //we need an x and y radius so that the ellipse matches the object's dimensions
            float x_radius = distance(front_left,back_right)/2;//measure half the diagonal
            float y_radius = distance(back_left,front_right)/2;//measure the other diagonal
            glPushMatrix();//modify transformation matrix
            glTranslatef(current.x,current.y,0.0);//translate ellipse according to object coordinates
            glColor3f(0.0,1.0,0.0);//make the lines green
            glBegin(GL_LINE_LOOP);//draws a series of lines
            for (int i=0; i<360; i++)
            {
                float deg_rad = i*3.14159/180;//calculate degrees in radians
                glVertex2f(cos(deg_rad)*x_radius,sin(deg_rad)*y_radius);//ellipse function
            }
            glEnd();//finish drawing
            glPopMatrix();//reset transformation matrix
        }
    }
}

clickable_object::clickable_object()
{
    name="clickable object";
    selected=false;
    std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;
}
