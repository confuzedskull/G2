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
#include <math.h>
#include <iostream>

void projectile::fire(movable_object source)//fires the projectile from the source
{
    current.set(source.current.x,source.current.y);//put the projectile where the source is
    rotation=source.rotation;//match the rotation of the source
    calc_points();
    calc_direction();
    set_boundaries();
    fired=true;
    visible=true;
}

void projectile::update()
{
    if(fired)
    {
        if(isless(traveled,range) && !collided)//projectile is within range and hasn't collided
        {
            calc_points();
            move_forward();
            traveled+=speed;
        }
        else
        {
            fired=false;
            reset();
        }
    }
    else
        reset();
}

void projectile::reset()
{
    traveled=0.0f;
    visible=false;
}

projectile::projectile()
{
    type="projectile";
    width=10.0f;
    height=10.0f;
    range=1000.0f;
    traveled=0.0f;
    speed=50.0f;
    fired=false;
    visible=false;
    primary_color=RED;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created."<<std::endl;
}
