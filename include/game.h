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
#include <time.h>
#include <vector>
#include <map>

//This class stores important settings and global variables for the program
class game
{
    public:
    static float time;//stores the current game time in seconds
    static clock_t time_started;
    static double time_elapsed;
    //maps are used for these objects because cursor::left_clicked_object points to clickable_object exclusively
    //object pointers are used because the objects are being created in init_objects() and we just need to reference them
    static std::map<int,draggable_object*> draggable_objects;
    static std::map<int,physics_object*> physics_objects;
    static std::map<int,rts_object*> rts_objects;
    //projectiles don't need to be individually initialized so pointers aren't used
    //static std::vector<projectile> projectiles;//projectiles don't need to be initialized so they aren't pointers
    //buttons are just like the other objects but they don't need to be found with a key
    static std::vector<button*> buttons;
    static void init_objects();//initialize the objects
    static void collision_detection();
};
#endif // GAME_H
