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
#include "ui.h"
#include <string>

class ui::dropdown_menu: public ui::menu, public ui::button
{
private:
    bool expanded;
    bool state_toggle;
public:
    static std::string default_texture;
    static std::string default_mask;
    static std::string default_click_sound;
    static std::string default_hover_sound;
    static std::string default_layout;
    static color default_fill_color;
    static color default_border_color;
    std::string get_type() override;
    void add_item(button* item) override;
    void mouse_function();
    void expand();
    void collapse();
    void render() override;
    void update() override;
    dropdown_menu();
};

#endif // DROPDOWN_MENU_H
