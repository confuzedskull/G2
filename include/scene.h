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
#include "text_object.h"
#include <map>
#include <vector>

class scene
{
    public:
    color background_color;
    //maps are used because we need to access the objects by referencing a common identifier (object.number)
    //object pointers are used because the objects are being created in game::init_objects() and we just need to reference them
    std::map<int,draggable_object*> draggable_objects;
    std::map<int,physics_object*> physics_objects;
    std::map<int,rts_object*> rts_objects;
    std::map<unsigned char, void (*)()> key_bindings;
    std::vector<text_object*> text_objects;
    //button pointers are used because the buttons are being created in init_buttons() and we just need to reference them
    std::vector<button*> buttons;
    std::vector<menu*> menus;
    void add_draggable_object(draggable_object*);//add a draggable object to the scene
    void add_physics_object(physics_object*);//add a physics object to the scene
    void add_rts_object(rts_object*);//add an rts object to the scene
    void bind_key(unsigned char, void (*)());
    void show_text();
    void hide_text();
    void show_buttons();
    void hide_buttons();
    void show_menus();
    void hide_menus();
    void render();
    void update();
    void clear();
    scene();
};

#endif // SCENE_H
