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

#include "line2f.h"
#include "compare.h"

line2f::line2f()
{

}

point2f line2f::midpoint()
{
    point2f m;
    m.x = (A.x + B.x) / 2;
    m.y = (A.y + B.y) / 2;
    return m;
}

float line2f::slope()
{
    return (B.y - A.y) / (B.x - A.x);
}

bool line2f::hasPoint(point2f p)
{
    float s = (p.y - A.y) / (p.x - A.x);
    if(compare(s,slope())==0)
        return true;
    else
        return false;
}

void line2f::set(point2f a, point2f b)
{
    A.set(a.x,a.y);
    B.set(b.x,a.y);
}
