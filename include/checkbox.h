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

#ifndef CHECKBOX_H
#define CHECKBOX_H
#include "button.h"

//A checkbox is a button which toggles a value on and off
class ui::checkbox: public ui::button
{
private:
    int checked;
public:
    static std::string default_texture;
    static std::string default_mask;
    static std::string default_clicksound;
    static std::string default_hoversound;
    static int default_margin;
    static int default_width;
    static int default_height;
    static color default_fillcolor;
    static color default_bordercolor;
    int* option;
    int checkmark_margin;
    color checkmark_color;
    std::string get_type() override;
    void bind_option(int*);
    void set_label(std::string txt) override;
    void mouse_function() override;
    void update() override;
    void render() final override;
    void load() override;
    void save() override;
    checkbox();
};

#endif // CHECKBOX_H
