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
#include <string.h>

//initialize variables
bool* controls::toggles = new bool[256];
bool* controls::key_states = new bool[256];
bool* controls::toggle_states = new bool[256];

void controls::move_forward()
{
    if(cursor::left_clicked_object->get_type()== "physics object" && !game::paused)
    game::scenes[window::current_scene]->physics_objects[cursor::selected_object]->move_forward();
}

void controls::move_back()
{
    if(cursor::left_clicked_object->get_type()== "physics object" && !game::paused)
    game::scenes[window::current_scene]->physics_objects[cursor::selected_object]->move_back();
}

void controls::move_left()
{
    if(cursor::left_clicked_object->get_type()== "physics object" && !game::paused)
    game::scenes[window::current_scene]->physics_objects[cursor::selected_object]->move_left();
}

void controls::move_right()
{
    if(cursor::left_clicked_object->get_type()== "physics object" && !game::paused)
    game::scenes[window::current_scene]->physics_objects[cursor::selected_object]->move_right();
}

void controls::turn_left()
{
    if(cursor::left_clicked_object->get_type()== "physics object" && !game::paused)
    game::scenes[window::current_scene]->physics_objects[cursor::selected_object]->turn_left();
}

void controls::turn_right()
{
    if(cursor::left_clicked_object->get_type()== "physics object" && !game::paused)
    game::scenes[window::current_scene]->physics_objects[cursor::selected_object]->turn_right();
}

void controls::perform_action(unsigned char key, void (*action)())
{
    if(key_states[key])//given key is pressed
        action();//perform the given action
}

void controls::toggle_action(unsigned char key, void (*actionA)(), void (*actionB)())
{
    if(key_states[key])
    {
        if(toggles[key])
        {
            if(toggle_states[key])
                actionA();
            toggle_states[key]=false;
        }
        else
        {
            if(!toggle_states[key])
                actionB();
            toggle_states[key]=true;
        }
    }
    else
        toggles[key]=toggle_states[key];
}

//NOTE: This function uses C++11 "for" loops
void controls::check_clicked()
{
    //The only way to check if no objects are being clicked is by checking every object
    bool left_clicked=false;
    while(!left_clicked)
    {
        for(auto r:game::scenes[window::current_scene]->rts_objects)
            left_clicked=r.second->left_clicked();
        for(auto d:game::scenes[window::current_scene]->draggable_objects)
            left_clicked=d.second->left_clicked();
        for(auto p:game::scenes[window::current_scene]->physics_objects)
            left_clicked=p.second->left_clicked();
        for(auto b:game::scenes[window::current_scene]->buttons)
            left_clicked=b->left_clicked();
        if(!left_clicked)//at this point, no objects have been left clicked so leave the loop
            break;
    }
    cursor::left_clicked_an_object = left_clicked;

    bool right_clicked=false;
    while(!right_clicked)
    {
        for(auto r:game::scenes[window::current_scene]->rts_objects)
            right_clicked=r.second->right_clicked();
        for(auto d:game::scenes[window::current_scene]->draggable_objects)
            right_clicked=d.second->right_clicked();
        for(auto p:game::scenes[window::current_scene]->physics_objects)
            right_clicked=p.second->right_clicked();
        if(!right_clicked)//at this point, no objects have been right clicked so leave the loop
            break;
    }
    cursor::right_clicked_an_object = right_clicked;

    bool grabbed=true;
    for(auto d:game::scenes[window::current_scene]->draggable_objects)
    {
        if(d.second->grabbed())
        {
            grabbed=true;
            break;
        }
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
    for(auto k:game::scenes[window::current_scene]->key_bindings)//iterate through the current scene's keybindings
        perform_action(k.first,k.second);
    toggle_action('i',ui::show_text,ui::hide_text);
    toggle_action('I',ui::show_text,ui::hide_text);
    toggle_action(27,game::pause,game::resume);
}
