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

#include "color.h"
#include <math.h>

void color::brighten()
{
    brighten(0.1);
}

void color::brighten(float brightness)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    if(isless(brightness,1.0f))
    {
        if(isless(r,1.0f) && isgreater(r,0.0f))
            r+=brightness;

        if(isless(g,1.0f) && isgreater(g,0.0f))
            g+=brightness;

        if(isless(b,1.0f) && isgreater(b,0.0f))
            b+=brightness;
    }
    changed=true;
}

void color::darken()
{
    darken(0.1f);
}

void color::darken(float brightness)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    if(isless(brightness,1.0f))
    {
        if(isgreater(r,0.0f))
        r-=brightness;

        if(isgreater(g,0.0f))
        g-=brightness;

        if(isgreater(b,0.0f))
        b-=brightness;
    }
    changed=true;
}

void color::set(float red, float green, float blue)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    r=red;
    g=green;
    b=blue;
    changed=true;
}

void color::set(float red, float green, float blue, float alpha)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    r=red;
    g=green;
    b=blue;
    a=alpha;
    changed=true;
}

void color::set(color c)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    r=c.r;
    g=c.g;
    b=c.b;
    changed=true;
}

void color::undo()
{
    if(changed)
    {
        r=prev_r;
        g=prev_g;
        b=prev_b;
        a=prev_a;
        changed=false;
    }
}

color::color()
{
    changed=false;
    r=0.0;
    g=0.0;
    b=0.0;
}

color::color(float red, float green, float blue)
{
    changed=false;
    r=red;
    g=green;
    b=blue;
}

color::color(float red, float green, float blue, float alpha)
{
    changed=false;
    r=red;
    g=green;
    b=blue;
    a=alpha;
}
