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

#include "projectile.h"
#include "distance.h"
#include "compare.h"

void projectile::fire(complex_object source)//an object fires a projectile
{
    current.set(source.current.x,source.current.y);//put the projectile where the source is
    rotation=source.rotation;//match the rotation of the source
    primary_color.set(source.primary_color);//match the color of the source
    fired=true;
    visible=true;
}

void projectile::update()
{
    if(fired)
    {
        if(compare(traveled,range)==-1)//projectile is within range
        {
            move_forward(speed);
            traveled+=speed;
        }
        else
        {
            fired=false;
            current.set(0.0f,0.0f);//set projectile position to somewhere outside of scene
            traveled=0.0f;
            visible=false;
        }
    }
    else
    {
        current.set(0.0f,0.0f);//set projectile position to somewhere outside of scene
        traveled=0.0f;
        visible=false;
    }
}

projectile::projectile()
{
    name="projectile";
    width=10;
    height=10;
    range=1000.0f;
    traveled=0.0f;
    speed=50.0f;
    fired=false;
    primary_color=RED;
}
