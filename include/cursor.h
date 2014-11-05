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

#ifndef CURSOR_H
#define CURSOR_H
#include "point.h"
#include "color.h"
#include "object.h"
#include "game.h"
#include <map>
//The cursor class stores data from the mouse that it's interfaced with. Since there can only be one mouse, all the data is static.
class cursor
{
public:
    static color box_color;//RGB values
    static point2f passive;
    static point2f left_down;
    static point2f left_up;
    static point2f left_drag;
    static point2f right_down;
    static point2f right_up;
    static point2f right_drag;
    static point2f rally;
    static clickable_object* left_clicked_object;
    static clickable_object* right_clicked_object;
    static bool set_rally;
    static bool left_click;
    static bool left_dragging;
    static bool right_click;
    static bool right_dragging;
    static bool left_clicked_an_object;
    static bool left_clicked_ui;
    static bool right_clicked_an_object;
    static bool grabbed_an_object;
    static bool highlighting;
    static bool highlighting_enabled;
    static std::map<int,clickable_object*> selected_objects;
    static float xmin,xmax,ymin,ymax;
    static int selected_object;
    static int objects_selected();
    static void calc_boundaries();
    static void selection_box();
    static void reset();
};
#endif // CURSOR_H
