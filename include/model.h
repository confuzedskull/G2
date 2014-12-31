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

#ifndef MODEL_H
#define MODEL_H
#include "clickable_object.h"
#include "physics_object.h"

class model: public clickable_object, public physics_object
{
public:
    static std::string default_texture;
    static std::string default_mask;
    static std::string default_click_sound;
    static std::string default_hover_sound;
    static std::string default_collision_sound;
    static std::string default_movement_sound;
    static int default_width;
    static int default_height;
    static bool enable_fill;
    static bool enable_border;
    static bool enable_texture;
    static bool enable_mask;
    static bool enable_dragging;
    static bool enable_physics;
    static bool enable_rts_controls;
    static bool enable_keyboard_controls;
    static color default_fill_color;
    static color default_border_color;
    bool physics_enabled;
    bool rts_controls;
    bool keyboard_controls;
    std::string get_type() override;
    void mouse_function() override;
    void load();
    void save();
    void sync() override;
    void update() override;
    model();
};

#endif // MODEL_H
