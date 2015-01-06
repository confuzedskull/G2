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

#ifndef MENU_H
#define MENU_H
#include "button.h"
#include "label.h"
#include <vector>
#include <string>

class ui::menu: virtual public basic_object
{
protected:
    std::string layout;
public:
    static int default_spacing;
    static int default_margin;
    static std::string default_layout;
    static std::string default_texture;
    static std::string default_mask;
    static color default_fillcolor;
    static color default_bordercolor;
    std::vector<button*> items;
    std::string get_type() override;
    ui::button* current_item;
    ui::button* next_item;
    ui::button* previous_item;
    ui::label title;
    ui::label subtitle;
    int spacing;//space between items
    int margin;//space between edges and content
    bool item_chosen;//whether an item has been clicked
    virtual void add_item(button* item);
    virtual void add_item(std::string text, void (*action)());
    void set_title(std::string txt);
    void set_subtitle(std::string txt);
    void set_layout(std::string l);
    void format();
    void render() override;
    void update() override;
    void load() override;
    void save() override;
    menu();
};

#endif // MENU_H
