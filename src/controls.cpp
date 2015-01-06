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
#include <cmath>
#include <cstring>
#include <iostream>

//initialize variables
bool controls::toggles[256] = {false};
bool controls::key_states[256] = {false};
bool controls::toggle_states[256] = {false};
std::map<std::string,bool> controls::special_toggles;
std::map<std::string,bool> controls::special_toggle_states;
std::map<std::string,bool> controls::special_states;

void controls::move_forward()
{
    if(game::play_scene->player->keyboard_controls && game::state!=PAUSED)
        game::play_scene->player->move_forward();
}

void controls::move_back()
{
    if(game::play_scene->player->keyboard_controls && game::state!=PAUSED)
        game::play_scene->player->move_back();
}

void controls::move_left()
{
    if(game::play_scene->player->keyboard_controls && game::state!=PAUSED)
        game::play_scene->player->move_left();
}

void controls::move_right()
{
    if(game::play_scene->player->keyboard_controls && game::state!=PAUSED)
        game::play_scene->player->move_right();
}

void controls::turn_left()
{
    if(game::play_scene->player->keyboard_controls && game::state!=PAUSED)
        game::play_scene->player->turn_left();
}

void controls::turn_right()
{
    if(game::play_scene->player->keyboard_controls && game::state!=PAUSED)
        game::play_scene->player->turn_right();
}

void controls::next_item()
{
    cursor::passive.x=(int)game::current_scene->current_menu->next_item->get_x();
    cursor::passive.y=(int)game::current_scene->current_menu->next_item->get_y();
}

void controls::previous_item()
{
    cursor::passive.x=(int)game::current_scene->current_menu->previous_item->get_x();
    cursor::passive.y=(int)game::current_scene->current_menu->previous_item->get_y();
}

void controls::choose_item()
{
    cursor::left_clicking=true;
    cursor::left_down.x=(int)game::current_scene->current_menu->current_item->get_x();
    cursor::left_down.y=(int)game::current_scene->current_menu->current_item->get_y();
}

void controls::hide_menu(int index)
{
    game::current_scene->menus[index]->hide();
}

void controls::switch_menu(int index)
{
    game::current_scene->switch_menu(index);
}

void controls::switch_menu(ui::menu* new_menu)
{
    game::current_scene->switch_menu(new_menu);
}

void controls::switch_scene(int index)
{
    if(index>=0 && index<game::scenes.size())
    {
        cursor::reset();
        game::current_scene=game::scenes[index];
    }
    else
        std::cerr<<"scene index out of bounds.\n";
}

void controls::switch_scene(scene* new_scene)
{
    cursor::reset();
    game::current_scene=new_scene;
}

void controls::mouse_click(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        cursor::left_down.set(x,window::height-y);
        cursor::left_clicking=true;
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        cursor::left_up.set(x,window::height-y);
        cursor::highlighting=false;
        cursor::left_clicking=false;
    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        cursor::highlighting=false;
        cursor::right_clicking=true;
        cursor::right_down.set(x,window::height-y);
    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP)
    {
        cursor::highlighting=false;
        cursor::right_clicking=false;
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
    if(cursor::left_clicking)//mouse left button is down
    {
        if(cursor::highlighting_enabled)
        {
            //this condition makes it so that the user has to make a rectangle larger than 10x10. That way, highlighting is less sensitive
            if((x>cursor::left_down.x+10) && ((window::height - y)<cursor::left_down.y+10))
                cursor::highlighting=true;
            else
                cursor::highlighting=false;
        }
        else
            cursor::highlighting=false;
        cursor::left_drag.set(x,(window::height-y));
        //see if drag point is different from start point
        if(((x<cursor::left_down.x)||(x>cursor::left_down.x))
           &&(((window::height - y)<cursor::left_down.y)||((window::height - y)>cursor::left_down.y)))
            cursor::left_dragging=true;
        else
            cursor::left_dragging=false;
    }
    else
        cursor::left_dragging=false;

    if(cursor::right_clicking)
    {
        cursor::highlighting=false;
        cursor::right_drag.set(x,(window::height-y));
        //see if drag point is different from start point
        if(((x<cursor::right_down.x)||(x>cursor::right_down.x))
           &&(((window::height - y)<cursor::right_down.y)||((window::height - y)>cursor::right_down.y)))
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
    for(auto key:game::current_scene->key_bindings)//C+11 "for" loop
    {
        if(key_states[key.first])//binded key is pressed
            key.second();//just perform the associated action
    }
    for(auto key:game::current_scene->key_toggles)
    {
        if(key_states[key.first])
        {
            if(toggles[key.first])
            {
                if(toggle_states[key.first])
                    *key.second=0;
                toggle_states[key.first]=false;
            }
            else
            {
                if(!toggle_states[key.first])
                    *key.second=1;
                toggle_states[key.first]=true;
            }
        }
        else
            toggles[key.first]=toggle_states[key.first];
    }
}

void controls::special_keys(int key,int x,int y)
{
    //first we need to reset all the key values
    for(auto s:special_states)
        s.second=false;
    //then we will check them again
    switch(key)
    {
    case GLUT_KEY_F1:
        special_states["F1"]=true;
        break;
    case GLUT_KEY_F2:
        special_states["F2"]=true;
        break;
    case GLUT_KEY_F3:
        special_states["F3"]=true;
        break;
    case GLUT_KEY_F4:
        special_states["F4"]=true;
        break;
    case GLUT_KEY_F5:
        special_states["F5"]=true;
        break;
    case GLUT_KEY_F6:
        special_states["F6"]=true;
        break;
    case GLUT_KEY_F7:
        special_states["F7"]=true;
        break;
    case GLUT_KEY_F8:
        special_states["F8"]=true;
        break;
    case GLUT_KEY_F9:
        special_states["F9"]=true;
        break;
    case GLUT_KEY_F10:
        special_states["F10"]=true;
        break;
    case GLUT_KEY_F11:
        special_states["F11"]=true;
        break;
    case GLUT_KEY_F12:
        special_states["F12"]=true;
        break;
    case GLUT_KEY_UP:
        special_states["up"]=true;
        break;
    case GLUT_KEY_DOWN:
        special_states["down"]=true;
        break;
    case GLUT_KEY_LEFT:
        special_states["left"]=true;
        break;
    case GLUT_KEY_RIGHT:
        special_states["right"]=true;
        break;
    case GLUT_KEY_PAGE_UP:
        special_states["page up"]=true;
        break;
    case GLUT_KEY_PAGE_DOWN:
        special_states["page down"]=true;
        break;
    case GLUT_KEY_HOME:
        special_states["home"]=true;
        break;
    case GLUT_KEY_END:
        special_states["end"]=true;
        break;
    case GLUT_KEY_INSERT:
        special_states["insert"]=true;
        break;
    }

    for(auto key:game::current_scene->special_bindings)//C+11 "for" loop
    {
        if(special_states[key.first])//binded key is pressed
            key.second();//just perform the associated action
    }
    for(auto key:game::current_scene->special_toggles)
    {
            if(special_states[key.first])
            {
                if(special_toggles[key.first])
                {
                    if(special_toggle_states[key.first])
                        *key.second=0;
                    special_toggle_states[key.first]=false;
                }
                else
                {
                    if(!special_toggle_states[key.first])
                        *key.second=1;
                    special_toggle_states[key.first]=true;
                }
            }
            else
                special_toggles[key.first]=special_toggle_states[key.first];
    }
}
