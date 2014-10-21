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
#include "menu.h"
#include "text_object.h"
#include <vector>

//This namespace contains functions and variables related to the user interface
namespace ui
{
        //button pointers are used because the buttons are being created in init_buttons() and we just need to reference them
        extern std::vector<button*> buttons;
        extern std::vector<menu*> menus;
        extern std::vector<text_object*> text_objects;
        extern int margin;//space between window edge and text
        void check_clicked();//check every clickable object to see if the cursor clicked it
        void init_buttons();//initialize the buttons
        void init_menus();//initialize the menus
        void init_text();//initialize text
        void update_text();
}
#endif // UI_H
