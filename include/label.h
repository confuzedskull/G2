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

#ifndef LABEL_H
#define LABEL_H
#include "basic_object.h"
#include <vector>
#include <string>
#include <sstream>

//A label stores a string which can be formatted and displayed on screen
class label: virtual public basic_object
{
protected:
    std::string text;
    int allignment;
    void* font;//points to a GLUT font
    int spacing;//the space between each line
    int font_size;
    float font_width;
    float font_height;
public:
    static std::string default_style;
    static int default_allignment;
    static int default_size;
    static int default_spacing;
    int get_allignment();
    color font_color;
    void allign(int pos);
    void allign(std::string pos);
    void set_spacing(int val);
    void set_text(std::string txt);
    void set_font(std::string style, int size);
    void render() override;//prints the text to the screen
    label();
};
#endif // LABEL_H
