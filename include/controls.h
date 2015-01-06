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

#ifndef CONTROLS_H
#define CONTROLS_H
#include "ui.h"
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
    //navigation functions
    void move_forward();//moves the currently selected object forward
    void move_back();//moves the currently selected object back
    void move_left();//moves the currently selected object left
    void move_right();//moves the currently selected object right
    void turn_left();//turns the currently selected object left
    void turn_right();//turns the currently selected object right
    void next_item();//selects the next item in current menu
    void previous_item();//selects the previous item in current menu
    void choose_item();//clicks the current item in current menu
    void hide_menu(int index);//hides the menu at the given index
    void switch_menu(int index);//makes the menu at the specified index current and hides all other menus
    void switch_menu(ui::menu* new_menu);//makes the given menu current and hides all other menus
    void switch_scene(int index);//makes the scene at the given index current
    void switch_scene(scene* new_scene);//makes the given scene current
    //mouse functions
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
