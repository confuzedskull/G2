/*  This file is a part of G2 - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    G2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    G2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of G2.  If not, see <http://www.gnu.org/licenses/>.*/

#include "pvector.h"
#include <math.h>

float pvector::magnitude()
{
    return sqrt((x*x)+(y*y));
}

void pvector::set(float x_direction, float y_direction)
{
    x=x_direction;
    y=y_direction;
}

pvector::pvector()
{
    x=0.0f;
    y=0.0f;
}

pvector::pvector(float x_direction, float y_direction)
{
    x=x_direction;
    y=y_direction;
}
