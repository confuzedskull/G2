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

#ifndef MENU_H
#define MENU_H
#include "button.h"
#include <vector>

class menu: public object
{
protected:
    char* title;
    void* font;
    int font_width;
    int font_height;
public:
    std::vector<button*> items;
    int layout;
    int spacing;
    int margin;
    void open();
    void close();
    void format();
    void set_title(char* t);
    void set_font(void* f);
    void render();
    void update();
    menu();
};
const int VERTICAL = 0;
const int HORIZONTAL = 1;

#endif // MENU_H
