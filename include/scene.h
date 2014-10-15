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

#ifndef SCENE_H
#define SCENE_H
#include "draggable_object.h"
#include "physics_object.h"
#include "rts_object.h"
#include "button.h"
#include "menu.h"
#include <map>
#include <vector>

class scene
{
    public:
    color background_color;
    //maps are used for these objects because cursor::left_clicked_object points to clickable_object exclusively
    //object pointers are used because the objects are being created in init_objects() and we just need to reference them
    std::map<int,draggable_object*> draggable_objects;
    std::map<int,physics_object*> physics_objects;
    std::map<int,rts_object*> rts_objects;
    std::vector<button*> buttons;
    std::vector<menu*> menus;
    void render();
    void update();
    scene();
};

#endif // SCENE_H
