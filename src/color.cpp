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
void color::brighten()
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    a+=0.1;
}

void color::brighten(float alpha)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    a+=alpha;
}

void color::darken()
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    a-=0.1;
}

void color::darken(float alpha)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    a-=alpha;
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
}

void color::undo()
{
    r=prev_r;
    g=prev_g;
    b=prev_b;
    a=prev_a;
}

color::color()
{
    r=0.0;
    g=0.0;
    b=0.0;
}

color::color(float red, float green, float blue)
{
    r=red;
    g=green;
    b=blue;
}

color::color(float red, float green, float blue, float alpha)
{
    r=red;
    g=green;
    b=blue;
    a=alpha;
}
