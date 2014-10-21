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
#include "text_object.h"
#include <vector>
#include <string>

class menu: public object
{
protected:
    text_object title;
    text_object subtitle;
public:
    std::vector<button*> items;
    int layout;
    int spacing;//space between buttons
    int margin;
    void set_title(std::string t);
    void set_subtitle(std::string s);
    void format();
    void render();
    void update();
    menu();
};
const int VERTICAL = 0;
const int HORIZONTAL = 1;

#endif // MENU_H
