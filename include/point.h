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

#ifndef POINT_H
#define POINT_H

//A point2f is a 2D point that consists of two floating point values
class point2f
{
    public:
    float x;
    float y;
    void set(float a, float b);
    void set(point2f p);
    point2f();
    point2f(float a, float b);
};

//A point2i is a 2D point that consists of two integer values
class point2i
{
    public:
    int x;
    int y;
    void set(int a, int b);
    void set(point2i p);
    point2i();
    point2i(int a, int b);
};
#endif // POINT_H
