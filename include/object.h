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
#include "color.h"
#include "point.h"
#include <string>

//This is the base class for all other object types. It has basic properties such as name, color, and dimensions.
class object
{
protected:
    int number;
    std::string type;
    point2f position;
    float rotation;
    float width;
    float height;
    float radius;
    bool rendered;//whether the render method has been called or not
    float xmax,xmin,ymax,ymin;//the boundaries of the object
public:
    static int total_objects;
    static point2f origin;
    std::string name;
    int get_number();
    std::string get_type();
    point2f get_position();
    point2f* get_positionptr();
    float get_rotation();
    float get_width();
    float get_height();
    float get_radius();
    color primary_color;//RGB values
    bool visible;//whether the object should be shown or not
    bool selected;//whether the object has been selected or not
    void rotate(float angle);//changes the object's rotation by the given angle
    void set_position(float x, float y);
    void set_rotation(float angle);
    void set_dimensions(float w, float h);
    void calc_boundaries();//calculates the max's and mins
    void mark_selected();//visually indicates whether object is selected
    void render();//draws the object
    void update();
    object();
    object(float x, float y, float w, float h);
    object(float x, float y, float w, float h, color c);
};
#endif // OBJECT_H
