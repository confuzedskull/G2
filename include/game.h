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
#include <time.h>
#include "clickable_object.h"
#include "projectile.h"
#include <vector>

//stores important settings and global variables for the program
class game
{
    public:
    static float time;
    static clock_t time_started;
    static double time_elapsed;
    static std::vector<clickable_object> clickable_objects;
    static std::vector<projectile> projectiles;
    static int current_projectile;
    static void init_objects();
    static void collision_detection();
};
#endif // GAME_H
