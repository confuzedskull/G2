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

//This class stores important settings and global variables for the program
class game
{
    public:
    static float time;//stores the current game time in seconds
    static clock_t time_started;
    static double time_elapsed;
    //below I used pointers because the objects will be created in init_objects()
    static std::vector<draggable_object*> draggable_objects;
    static std::vector<physics_object*> physics_objects;
    static std::vector<rts_object*> rts_objects;
    static std::vector<button*> buttons;
    static std::vector<projectile> projectiles;//projectiles don't need to be initialized so they aren't pointers
    static void init_objects();//initialize the objects
    static void collision_detection();
};
#endif // GAME_H
