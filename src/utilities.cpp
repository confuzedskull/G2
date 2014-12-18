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

#include "utilities.h"
#include <cmath>

//this function checks endianness
bool utilities::is_big_endian()
{
    int i=1;
    return !((char*)&i)[0];
}

//this function retrieves the appropriate value according to endianness
int16_t utilities::to_int16(char* buffer, int length)
{
    int16_t i=0;
    if(!is_big_endian())
        for(int j=0;j<length;j++)
            ((char*)&i)[j]=buffer[j];
    else
        for(int j=0;j<length;j++)
            ((char*)&i)[3-j]=buffer[j];
    return i;
}

//this function retrieves the appropriate value according to endianness
int32_t utilities::to_int32(char* buffer, int length)
{
    int32_t i=0;
    if(!is_big_endian())
        for(int j=0;j<length;j++)
            ((char*)&i)[j]=buffer[j];
    else
        for(int j=0;j<length;j++)
            ((char*)&i)[sizeof(int)-1-j]=buffer[j];
    return i;
}

float utilities::distance(float x1, float y1, float x2, float y2)//calculates distance given x,y values
{
    return (sqrt(pow((x2 - x1),2) + pow((y2 - y1),2)));
}

int utilities::distance(int x1, int y1, int x2, int y2)//calculates distance given x,y values
{
    return (sqrt(pow((x2 - x1),2) + pow((y2 - y1),2)));
}

int utilities::distance(point2i A, point2i B)//calculates distance from A to B
{
    return (int)(sqrt(pow((B.x - A.x),2) + pow((B.y - A.y),2)));
}

float utilities::distance(point2f A, point2f B)//calculates distance from A to B
{
    return (sqrt(pow((B.x - A.x),2) + pow((B.y - A.y),2)));
}

float utilities::distance(point2i A, point2f B)
{
    return (sqrt(pow((B.x - A.x),2) + pow((B.y - A.y),2)));
}

float utilities::distance(point2f A, point2i B)
{
    return (sqrt(pow((B.x - A.x),2) + pow((B.y - A.y),2)));
}
