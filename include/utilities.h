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

#ifndef UTILITIES_H
#define UTILITIES_H
#include "point.h"
#include <cstdint>

namespace utilities
{
bool is_big_endian();
int16_t to_int16(char* buffer, int length);
int32_t to_int32(char* buffer, int length);
float distance(float x1, float y1, float x2, float y2);//calculates distance given x,y values
int distance(int x1, int y1, int x2, int y2);//calculates distance given x,y values
int distance(point2i A, point2i B);//calculates distance from A to B
float distance(point2f A, point2f B);//calculates distance from A to B
float distance(point2i A, point2f B);//calculates distance from A to B
float distance(point2f A, point2i B);//calculates distance from A to B
void increment(int* value);
void increment(float* value);
void decrement(int* value);
void decrement(float* value);
};

#endif // UTILITIES_H
