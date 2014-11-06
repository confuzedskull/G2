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

#ifndef GAME_H
#define GAME_H
#include "scene.h"
#include <time.h>
#include <vector>
#include <map>

//stores important functions and variables related to the game
namespace game
{
    extern float time;//stores the current game time in seconds
    extern clock_t time_started;//start time
    extern double time_elapsed;//time since start
    extern bool paused;//whether the game is active or not
    extern scene* current_scene;
    extern std::vector<scene*> scenes;
    extern std::vector<int*> options;
    void initialize();//initialize the objects
    void collision_detection();//handles object collision
    void add_option(int* option);
    void add_draggable_object();//add a draggable object to the current scene
    void add_physics_object();//add a physics object to the current scene
    void add_rts_object();//add an rts object to the current scene
    void create_object();//creates an object of the previously created type
    void delete_selected();//remove the selected object from the game
    void play();//open game screen
    void pause();//open pause screen
    void resume();//unpause the game
    void warn_quit();//warn user before quitting
    void warn_return();//warn user before returning to main menu
    void return_menu();//open main menu
    void quit();//close the program
    void update();//update variables
    void sync();//update clock-based events
};
#endif // GAME_H
