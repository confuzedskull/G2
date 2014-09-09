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

void projectile::reset()
{
    current.x=rest.x;
    current.y=rest.y;
    fired=false;
}

void projectile::fire(object source)//an object fires a projectile
{
    if(!fired)
    {
        current.x=source.current.x;
        rest.x=source.current.x;
        current.y=source.current.y;
        rest.y=source.current.y;
        rotation=source.rotation;
        calc_step();//orient it to the direction aiming
        fired=true;
    }
}

void projectile::update()
{
//        set_boundaries();

    if(fired)
        move_forward(range);
    else
    {
        //set projectile position to somewhere outside of scene
        current.x=0;
        current.y=0;
    }
}

projectile::projectile()
{
    name="projectile";
    width=10;
    height=10;
    range=1000;
    fired=false;
    step_size=0.5;
//        set_boundaries();
    primary_color=RED;

}
