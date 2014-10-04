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

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "tangible_object.h"
#include "point2f.h"

//A projectile collides with other physics objects
class projectile: public tangible_object
{
    public:
    float range;//how far the projectile can go until it resets
    float traveled;//how far the projectile has gone
    int power;//how much damage the projectile will make
    bool fired;
    void fire(movable_object source);//an object fires a projectile
    void update();//updates the projectile's values
    void reset();
    projectile();
};
#endif // PROJECTILE_H
