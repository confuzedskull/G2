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

#include "controls.h"
#include "cursor.h"
#include "window.h"
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
#include <math.h>
#include <iostream>

//initialize variables
bool* controls::key_states = new bool[256];
bool controls::temp_toggle = false;
bool controls::toggle_overlay = false;

void controls::check_clicked()
{
    //The only way to check if no objects are being clicked is by checking every object
    bool left_clicked=true;
    bool right_clicked=true;
    for(std::map<int,rts_object*>::iterator a=game::rts_objects.begin(); a!=game::rts_objects.end(); ++a)
    {
        if(left_clicked && a->second->left_clicked())
            left_clicked=true;
        else
            left_clicked=false;

        if(right_clicked && a->second->right_clicked())
            right_clicked=true;
        else
            right_clicked=false;
    }
    cursor::left_clicked_an_object = left_clicked;
    cursor::right_clicked_an_object = right_clicked;

    bool grabbed=true;
    for(std::map<int,draggable_object*>::iterator a=game::draggable_objects.begin(); a!=game::draggable_objects.end(); ++a)
    {
        if(grabbed && a->second->grabbed())
            grabbed=true;
        else
            grabbed=false;
    }
    cursor::grabbed_an_object = grabbed;
}

void controls::mouse_click(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        cursor::left_down.set(x,window::height-y);
        cursor::left_click=true;
    }

    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        cursor::left_up.set(x,window::height-y);
        cursor::highlighting=false;
        cursor::left_click=false;
    }

    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        cursor::highlighting=false;
        cursor::right_click=true;
        cursor::right_down.set(x,window::height-y);
    }

    if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP)
    {
        cursor::highlighting=false;
        cursor::right_click=false;
        cursor::right_up.set(x,window::height-y);
        cursor::right_dragging=false;
    }
}

void controls::mouse_move(int x, int y)
{
    cursor::passive.set(x,window::height-y);
}

void controls::mouse_drag(int x, int y)
{
    if(cursor::left_click)
    {
        if(!cursor::left_clicked_an_object && !cursor::grabbed_an_object)
        {
            //this condition makes it so that the user has to make a rectangle larger than 10x10. That way, highlighting is less sensitive
            if(isgreater(x,cursor::left_down.x+10) && isless((window::height - y),cursor::left_down.y+10))
                cursor::highlighting=true;
            else
                cursor::highlighting=false;
        }
        else
            cursor::highlighting=false;
        cursor::left_drag.set(x,(window::height-y));
        //see if drag point is different from start point
        if((isless(x,cursor::left_down.x)||isgreater(x,cursor::left_down.x))
           &&(isless((window::height - y),cursor::left_down.y)||isgreater((window::height - y),cursor::left_down.y)))
            cursor::left_dragging=true;
        else
            cursor::left_dragging=false;
    }
    else
        cursor::left_dragging=false;

    if(cursor::right_click)
    {
        cursor::highlighting=false;
        cursor::right_drag.set(x,(window::height-y));
        //see if drag point is different from start point
        if((isless(x,cursor::right_down.x)||isgreater(x,cursor::right_down.x))
           &&(isless((window::height - y),cursor::right_down.y)||isgreater((window::height - y),cursor::right_down.y)))
            cursor::right_dragging=true;
        else
            cursor::right_dragging=false;
    }
    else
        cursor::right_dragging=false;
}

void controls::key_pressed(unsigned char key, int x, int y)
{
    key_states[key] = true;
}

void controls::key_released(unsigned char key, int x, int y)
{
    key_states[key] = false;
}

void controls::key_operations(void)
{
    unsigned index = cursor::selected_object;//number of the currently selected object
    if(strcmp(cursor::left_clicked_object->get_type(), "physics object")==0)
    {
        if(key_states['w'] || key_states['W'])
            game::physics_objects[index]->move_forward();

        if(key_states['s'] || key_states['S'])
            game::physics_objects[index]->move_back();

        if(key_states['a'] || key_states['A'])
            game::physics_objects[index]->move_left();

        if(key_states['d'] || key_states['D'])
            game::physics_objects[index]->move_right();

        if(key_states['q'] || key_states['Q'])
            game::physics_objects[index]->turn_left();

        if(key_states['e'] || key_states['E'])
            game::physics_objects[index]->turn_right();

        /*if(key_states[32])//spacebar
        {
            if(!game::projectiles[index].fired)
                game::projectiles[index].fire(*game::physics_objects[index]);
        }*/
    }
    if(key_states['i'] || key_states['I'])
    {
        if(toggle_overlay)
        {
            if(temp_toggle)
            std::clog<<"toggled information overlay off\n";
            temp_toggle=false;
        }
        else
        {
            if(!temp_toggle)
            std::clog<<"toggled information overlay on\n";
            temp_toggle=true;
        }
    }
    else
        toggle_overlay=temp_toggle;

    if(key_states[27])//escape
    {
        std::clog<<"exiting...\n";
        exit(0);
    }
}
