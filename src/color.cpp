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
#include <stdlib.h>
#include <time.h>
#include <sstream>

std::string color::str()
{
    std::stringstream name;
    name<<r<<','<<g<<','<<b;
    return name.str();
}

bool color::matches(color c)
{
    return (!isless(r,c.r) && !isgreater(r,c.r)
       && !isless(g,c.g) && !isgreater(g,c.g)
       && !isless(b,c.b) && !isgreater(b,c.b));
}

void color::randomize()
{
    srand(time(NULL));//initialize a new random seed
    r=(rand()%10+1)/10.0f;//generate a number between 1 and 10, then divide by 10(so that it is in range 0.1 - 1.0)
    //srand(time(NULL));//initialize a new random seed
    g=(rand()%10+1)/10.0f;//generate a number between 1 and 10, then divide by 10(so that it is in range 0.1 - 1.0)
    //srand(time(NULL));//initialize a new random seed
    b=(rand()%10+1)/10.0f;//generate a number between 1 and 10, then divide by 10(so that it is in range 0.1 - 1.0)
}

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
    if(values_set)
    {
        prev_r=r;
        prev_g=g;
        prev_b=b;
        prev_a=a;
        changed=true;
    }
    r=red;
    g=green;
    b=blue;
    values_set=true;
}

void color::set(float red, float green, float blue, float alpha)
{
    if(values_set)
    {
        prev_r=r;
        prev_g=g;
        prev_b=b;
        prev_a=a;
        changed=true;
    }
    r=red;
    g=green;
    b=blue;
    a=alpha;
    values_set=true;
}

void color::set(std::string c)
{
    if(values_set)
    {
        prev_r=r;
        prev_g=g;
        prev_b=b;
        prev_a=a;
        changed=true;
    }
    if(c=="red")
        set(RED);
    if(c=="orange")
        set(ORANGE);
    if(c=="yellow")
        set(YELLOW);
    if(c=="green")
        set(GREEN);
    if(c=="blue")
        set(BLUE);
    if(c=="purple")
        set(PURPLE);
    if(c=="white")
        set(WHITE);
    if(c=="gray")
        set(GRAY);
    if(c=="black")
        set(BLACK);
    values_set=true;
}

void color::set(color c)
{
    if(values_set)
    {
        prev_r=r;
        prev_g=g;
        prev_b=b;
        prev_a=a;
        changed=true;
    }
    r=c.r;
    g=c.g;
    b=c.b;
    values_set=true;
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
    r=0.0;
    g=0.0;
    b=0.0;
    values_set=false;
    changed=false;
}

color::color(float red, float green, float blue)
{
    r=red;
    g=green;
    b=blue;
    values_set=false;
    changed=false;
}

color::color(float red, float green, float blue, float alpha)
{
    r=red;
    g=green;
    b=blue;
    a=alpha;
    values_set=false;
    changed=false;
}
