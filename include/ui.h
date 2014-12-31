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

#ifndef UI_H
#define UI_H
#include "color.h"
#include <string>

//This namespace contains classes and variables related to the user interface
namespace ui
{
    extern std::string default_texture;
    extern std::string default_mask;
    extern color default_fill_color;
    extern color default_border_color;
    class label;
    class button;
    class checkbox;
    class menu;
    class dropdown_menu;
}
const int CENTER=0;
const int LEFT=1;
const int RIGHT=2;
const int TOP=3;
const int BOTTOM=4;
const int MIDDLE=5;
#endif // UI_H
