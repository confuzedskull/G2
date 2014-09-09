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

#ifndef LINE2F_H
#define LINE2F_H
#include "point2f.h"

//A line2f is a 2D line that consists of three point2f's
class line2f
{
    public:
    point2f A;
    point2f B;
    point2f midpoint();
    void set(point2f a,point2f b);
    bool hasPoint(point2f p);
    float slope();
    line2f();
    line2f(point2f a, point2f b);
};
#endif // LINE2F_H
