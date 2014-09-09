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
#include "physics_object.h"

//A projectile collides with other physics objects
class projectile: public physics_object
{
    public:
    int range;//how far the projectile can go until it resets
    int power;//how much damage the projectile will make
    bool fired;//marks the object as being shot or not
    void reset();//puts the projectile back at its source
    void fire(object source);//an object fires a projectile
    void update();//updates the projectile's values
    projectile();
};
#endif // PROJECTILE_H
