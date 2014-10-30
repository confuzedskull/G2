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

#ifndef DROPDOWN_MENU_H
#define DROPDOWN_MENU_H
#include "menu.h"
#include "button.h"
#include "clickable_object.h"
#include <string>

class dropdown_menu: public menu, public clickable_object
{
private:
    bool expanded;
    bool state_toggle;
public:
    void add_item(button*);
    void mouse_function();
    void expand();
    void collapse();
    void update();
    dropdown_menu();
};

#endif // DROPDOWN_MENU_H
