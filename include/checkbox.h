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

#ifndef CHECKBOX_H
#define CHECKBOX_H
#include "clickable_object.h"
#include "label.h"

class checkbox: public clickable_object
{
protected:
    int checked;
    label text;
public:
    int* option;
    int margin;
    color check_color;
    void set_label(std::string text);
    void set_label(std::string text,std::string pos);
    void put_label(std::string pos);
    void bind_option(int*);
    void mouse_function();
    void render();
    void update();
    checkbox();
};

#endif // CHECKBOX_H
