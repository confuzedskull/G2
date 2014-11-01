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
#include "label.h"
#include <vector>

//This namespace contains functions and variables related to the user interface
namespace ui
{
        extern int margin;//space between window edge and text
        void check_clicked();//check every clickable object to see if the cursor clicked it
        void show_text();//makes the text of the current scene visible
        void hide_text();//makes the text of the current scene invisible
        void update_text();//updates the text
}
#endif // UI_H
