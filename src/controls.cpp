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
#include <string.h>
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
    if(cursor::left_clicked_object->get_type()=="physics object" && game::state!=PAUSED)
    game::play_scene->physics_objects[cursor::selected_object]->move_forward();
}

void controls::move_back()
{
    if(cursor::left_clicked_object->get_type()=="physics object" && game::state!=PAUSED)
    game::play_scene->physics_objects[cursor::selected_object]->move_back();
}

void controls::move_left()
{
    if(cursor::left_clicked_object->get_type()=="physics object" && game::state!=PAUSED)
    game::play_scene->physics_objects[cursor::selected_object]->move_left();
}

void controls::move_right()
{
    if(cursor::left_clicked_object->get_type()=="physics object" && game::state!=PAUSED)
    game::play_scene->physics_objects[cursor::selected_object]->move_right();
}

void controls::turn_left()
{
    if(cursor::left_clicked_object->get_type()=="physics object" && game::state!=PAUSED)
    game::play_scene->physics_objects[cursor::selected_object]->turn_left();
}

void controls::turn_right()
{
    if(cursor::left_clicked_object->get_type()=="physics object" && game::state!=PAUSED)
    game::play_scene->physics_objects[cursor::selected_object]->turn_right();
}

void controls::next_item()
{
    menu* current_menu = game::current_scene->current_menu;
    int i = current_menu->item_selected();
    if(i==-1)
        current_menu->items.front()->selected=true;
    else
    {
        current_menu->items[i]->selected=false;
        if((i+1)<current_menu->items.size())//close to end
            current_menu->items[i+1]->selected=true;
        else
            current_menu->items.front()->selected=true;
    }
}

void controls::previous_item()
{
    menu* current_menu = game::current_scene->current_menu;
    int i = current_menu->item_selected();
    if(i==-1)
        current_menu->items.front()->selected=true;
    else
    {
        current_menu->items[i]->selected=false;
        if((i-1)>=0)
            current_menu->items[i-1]->selected=true;
        else
            current_menu->items.back()->selected=true;
    }
}

void controls::choose_item()
{
    if(game::current_scene->current_menu->item_selected()!=-1)
    {
        cursor::left_click=true;
        cursor::left_down.x=(int)game::current_scene->current_menu->current_item->get_x();
        cursor::left_down.y=(int)game::current_scene->current_menu->current_item->get_y();
    }
}

void controls::switch_menu(int index)
{
    game::current_scene->switch_menu(index);
}

void controls::switch_menu(menu* new_menu)
{
    game::current_scene->switch_menu(new_menu);
}

void controls::switch_scene(int index)
{
    if(index>=0 && index<game::scenes.size())
    {
        cursor::reset();
        game::scenes[index]->switch_menu(0);
        game::current_scene=game::scenes[index];
    }
    else
        std::cerr<<"scene index out of bounds.\n";
}

void controls::switch_scene(scene* new_scene)
{
    cursor::reset();
    new_scene->switch_menu(0);
    game::current_scene=new_scene;
}


void controls::show_foreground()
{
    game::play_scene->foreground.show();
}
void controls::hide_foreground()
{
    game::play_scene->foreground.hide();
}

void controls::show_middleground()
{
    game::play_scene->middleground.show();
}

void controls::hide_middleground()
{
    game::play_scene->middleground.hide();
}

void controls::show_background()
{
    game::play_scene->background.show();
}

void controls::hide_background()
{
    game::play_scene->background.hide();
}

void controls::show_draggable_objects()
{
    game::play_scene->show_draggable_objects();
}

void controls::hide_draggable_objects()
{
    game::play_scene->hide_draggable_objects();
}

void controls::show_physics_objects()
{
    game::play_scene->show_physics_objects();
}

void controls::hide_physics_objects()
{
    game::play_scene->hide_physics_objects();
}

void controls::show_rts_objects()
{
    game::play_scene->show_rts_objects();
}

void controls::hide_rts_objects()
{
    game::play_scene->hide_rts_objects();
}

void controls::show_textures()
{
    game::play_scene->show_textures();
}

void controls::hide_textures()
{
    game::play_scene->hide_textures();
}

void controls::mute_all()
{
    game::play_scene->mute_all();
}

void controls::unmute_all()
{
    game::play_scene->unmute_all();
}

void controls::add_draggable_object()
{
    draggable_object* new_do = new draggable_object();
    game::play_scene->add_object(new_do);
}

void controls::add_physics_object()
{
    physics_object* new_po = new physics_object();
    game::play_scene->add_object(new_po);
}

void controls::add_rts_object()
{
    rts_object* new_rtso = new rts_object();
    game::play_scene->add_object(new_rtso);
}

void controls::create_object()
{
    if(game::play_scene->last_object->get_type()=="draggable object")
        game::play_scene->add_object(new draggable_object());
    if(game::play_scene->last_object->get_type()=="physics object")
        game::play_scene->add_object(new physics_object());
    if(game::play_scene->last_object->get_type()=="rts object")
        game::play_scene->add_object(new rts_object());
}

void controls::delete_selected()
{
    for(auto so:cursor::selected_objects)
    {
        if(game::play_scene->draggable_objects.find(so.first)!=game::play_scene->draggable_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<"(draggable object)"<<" deleted."<<std::endl;
            delete game::play_scene->draggable_objects[so.first];
            game::play_scene->draggable_objects.erase(so.first);
        }
        if(game::play_scene->physics_objects.find(so.first)!=game::play_scene->physics_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<"(physics object)"<<" deleted."<<std::endl;
            delete game::play_scene->physics_objects[so.first];
            game::play_scene->physics_objects.erase(so.first);
        }
        if(game::play_scene->rts_objects.find(so.first)!=game::play_scene->rts_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<"(rts object)"<<" deleted."<<std::endl;
            delete game::play_scene->rts_objects[so.first];
            game::play_scene->rts_objects.erase(so.first);
        }
    }
    cursor::selected_objects.clear();
}

//NOTE: This function uses C++11 "for" loops
void controls::check_clicked()
{
    //The only way to check if no objects are being clicked is by checking every object
    bool left_clicked=false;
    while(!left_clicked)
    {
        for(auto r:game::current_scene->rts_objects)
            left_clicked=r.second->left_clicked();
        for(auto d:game::current_scene->draggable_objects)
            left_clicked=d.second->left_clicked();
        for(auto p:game::current_scene->physics_objects)
            left_clicked=p.second->left_clicked();
        if(!left_clicked)//at this point, no objects have been left clicked so leave the loop
            break;
    }
    cursor::left_clicked_an_object = left_clicked;

    left_clicked=false;
    while(!left_clicked)
    {
        for(auto b:game::current_scene->buttons)
            left_clicked=b->left_clicked();
        for(auto cb:game::current_scene->checkboxes)
            left_clicked=cb->left_clicked();
        for(auto dm:game::current_scene->dropdown_menus)
        {
            left_clicked=dm->left_clicked();
            left_clicked=dm->item_clicked()!=-1;
        }
        if(!left_clicked)//at this point, no objects have been left clicked so leave the loop
            break;
    }
    cursor::left_clicked_ui = left_clicked;

    bool right_clicked=false;
    while(!right_clicked)
    {
        for(auto r:game::current_scene->rts_objects)
            right_clicked=r.second->right_clicked();
        for(auto d:game::current_scene->draggable_objects)
            right_clicked=d.second->right_clicked();
        for(auto p:game::current_scene->physics_objects)
            right_clicked=p.second->right_clicked();
        if(!right_clicked)//at this point, no objects have been right clicked so leave the loop
            break;
    }
    cursor::right_clicked_an_object = right_clicked;

    bool grabbed=false;
    for(auto d:game::current_scene->draggable_objects)
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
    if(cursor::left_click)//mouse left button is down
    {
        if(cursor::highlighting_enabled && !cursor::left_clicked_an_object && !cursor::grabbed_an_object)
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

    if(cursor::right_click)
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
