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

#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H
#include "object.h"

//A text object stores a string which can be formatted and displayed on screen
class text_object: public object
{
protected:
    char* text;
    void* font;
    int font_size;
    int font_width;
    int font_height;
    int lines;
    int longest_line;//the length of the longest line (excluding newline character)
public:
    int spacing;//the space between each line
    float get_width();//overrides object::get_width()
    float get_height();//overrides object::get_height()
    void set_text(char* t);
    void set_font(char* style, int size);
    void calc_lines();//finds the number of lines and the length of the longest line
    void render();//prints the text to the screen
    text_object();
};

#endif // TEXT_OBJECT_H
