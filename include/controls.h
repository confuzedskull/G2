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
#include <map>

//stores all variables and functions related to peripheral input
namespace controls
{
extern bool* toggles;
extern bool* toggle_states;//stores the toggle state before it is set
extern bool* key_states; //stores each on/off state of a keyboard key
void move_forward();//moves the currently selected object forward
void move_back();//moves the currently selected object back
void move_left();//moves the currently selected object left
void move_right();//moves the currently selected object right
void turn_left();//turns the currently selected object left
void turn_right();//turns the currently selected object right
void perform_action(unsigned char, void (*)());//performs the specified action
void toggle_action(unsigned char key, void (*)(), void (*)());
void check_clicked();//check if objects are clicked or not
void mouse_click(int button, int state, int x, int y);//handles mouse clicks
void mouse_move(int x, int y);//handles mouse movement
void mouse_drag(int x, int y);//handles mouse drag
void key_pressed(unsigned char key, int x, int y);//marks given key as pressed
void key_released(unsigned char key, int x, int y);//marks given key as released
void key_operations(void);//handles keyboard actions
};

#endif // CONTROLS_H
