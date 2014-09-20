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

#ifndef OBJECT_H
#define OBJECT_H
#include <stdlib.h>
#include <string>
#include "color.h"
#include "point2f.h"

//This is the base class for all other object types. It has basic properties such as name, color, and dimensions.
class object
{
    public:
    static int total_objects;
    std::string name;
    int number;
    point2f current;
    point2f rest;//resting point
    float rotation;
    float width, height;
    color primary_color;//RGB values
    bool visible;
    bool rendered;
    float xmax,xmin,ymax,ymin;//the boundaries of the object
    void set_boundaries();//calculates the max's and mins
    void render();//draws the object
    void rotate(float angle);//changes the object's rotation by the given angle
    int get_radius();//calculates a radius from the width and height
    object();
    object(float x, float y, float w, float h, color c);
};
#endif // OBJECT_H
