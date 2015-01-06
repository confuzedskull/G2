/*  This file is a part of G2 - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    G2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    G2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of G2.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef ADVANCED_H
#define ADVANCED_H
#include "interactive_object.h"
#include "physical_object.h"

class advanced_object: public interactive_object, public physical_object
{
public:
    static std::string default_texture;
    static std::string default_mask;
    static std::string default_clicksound;
    static std::string default_hoversound;
    static std::string default_collisionsound;
    static std::string default_movementsound;
    static int default_width;
    static int default_height;
    static bool enable_fill;
    static bool enable_border;
    static bool enable_texture;
    static bool enable_mask;
    static bool enable_physics;
    static bool enable_rtscontrols;
    static bool enable_keyboardcontrols;
    static color default_fillcolor;
    static color default_bordercolor;
    bool physics_enabled;
    bool rts_controls;
    bool keyboard_controls;
    std::vector<smart_object*> components;
    std::string get_type() override;
    void add_component(smart_object* component);
    void mouse_function() override;
    void load() override;
    void save() override;
    void sync() override;
    void update() override;
    advanced_object();
};

#endif // ADVANCED_H
