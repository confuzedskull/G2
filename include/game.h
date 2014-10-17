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
#include "physics_object.h"
#include "draggable_object.h"
#include "rts_object.h"
#include "projectile.h"
#include "button.h"
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
    extern bool paused;
    extern std::vector<scene*> scenes;
    //maps are used for these objects because cursor::left_clicked_object points to clickable_object exclusively
    //object pointers are used because the objects are being created in init_objects() and we just need to reference them
    extern std::map<int,draggable_object*> draggable_objects;
    extern std::map<int,physics_object*> physics_objects;
    extern std::map<int,rts_object*> rts_objects;
    void init_objects();//initialize the objects
    void init_scenes();//initialize the objects
    void collision_detection();//handles object collision
    void add_draggable_object();//add a draggable object to the scene
    void add_physics_object();//add a physics object to the scene
    void add_rts_object();//add an rts object to the scene
    void delete_selected();//delete the currently selected object
    void play();//open game screen
    void pause();//open pause screen
    void resume();//open game screen
    void return_warning();//warn user before returning to main menu
    void return_menu();//open main menu
    void quit();//close the program
};
#endif // GAME_H
