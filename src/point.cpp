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

#include "point.h"

point2f::point2f()
{

}
point2f::point2f(float a, float b)
{
    x = a;
    y = b;
}

void point2f::set(float a, float b)
{
    x = a;
    y = b;
}

void point2f::set(point2f p)
{
    x = p.x;
    y = p.y;
}

point2i::point2i()
{
    x=0;
    y=0;
}

point2i::point2i(int a, int b)
{
    x = a;
    y = b;
}

void point2i::set(int a, int b)
{
    x = a;
    y = b;
}

void point2i::set(point2i p)
{
    x=p.x;
    y=p.y;
}
