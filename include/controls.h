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

#ifndef CONTROLS_H
#define CONTROLS_H
#include "menu.h"
#include "scene.h"
#include <map>
#include <string>

//stores all variables and functions related to peripheral input
namespace controls
{
    //variables
    extern bool toggles[256];//stores the toggle states of regular keys
    extern bool toggle_states[256];//stores the toggle state before it is set
    extern bool key_states[256];//stores each on/off state of regular key
    extern std::map<std::string,bool> special_toggles;//stores the toggle states of special keys
    extern std::map<std::string,bool> special_toggle_states;//stores the toggle state before it is set
    extern std::map<std::string,bool> special_states;//stores each on/off state of a special key
    //gameplay functions
    void move_forward();//moves the currently selected object forward
    void move_back();//moves the currently selected object back
    void move_left();//moves the currently selected object left
    void move_right();//moves the currently selected object right
    void turn_left();//turns the currently selected object left
    void turn_right();//turns the currently selected object right
    void next_item();//selects the next item
    void previous_item();//selects the previous item
    void choose_item();//selects the current item
    void switch_menu(int index);
    void switch_menu(menu* new_menu);
    void switch_scene(int index);
    void switch_scene(scene* new_scene);
    void show_foreground();
    void hide_foreground();
    void show_middleground();
    void hide_middleground();
    void show_background();
    void hide_background();
    void show_draggable_objects();//show all draggable objects in play scene
    void hide_draggable_objects();//hide all draggable objects in play scene
    void show_physics_objects();//show all physics objects in play scene
    void hide_physics_objects();//hide all physics objects in play scene
    void show_rts_objects();//show all rts objects in play scene
    void hide_rts_objects();//hide all rts objects in play scene
    void show_textures();//show all textures
    void hide_textures();//hide all textures
    void mute_all();//mute all sounds
    void unmute_all();//unmute all sounds
    void add_draggable_object();//add a draggable object to the play scene
    void add_physics_object();//add a physics object to the play scene
    void add_rts_object();//add an rts object to the play scene
    void create_object();//creates an object of the previously created type
    void delete_selected();//remove the selected object from the game
    //mouse functions
    void check_clicked();//check if objects are clicked or not
    void mouse_click(int button, int state, int x, int y);//handles mouse clicks
    void mouse_move(int x, int y);//handles mouse movement
    void mouse_drag(int x, int y);//handles mouse drag
    //keyboard functions
    void key_pressed(unsigned char key, int x, int y);//marks given key as pressed
    void key_released(unsigned char key, int x, int y);//marks given key as released
    void key_operations(void);//handles keyboard actions
    void special_keys(int,int,int);//handles special keys
};

#endif // CONTROLS_H
