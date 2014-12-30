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

#ifndef MENU_H
#define MENU_H
#include "button.h"
#include "label.h"
#include <vector>
#include <string>

class menu: virtual public basic_object
{
protected:
    std::string layout;
public:
    static int default_spacing;
    static int default_margin;
    static std::string default_layout;
    static std::string default_texture;
    static std::string default_mask;
    std::vector<button*> items;
    button* current_item;
    label title;
    label subtitle;
    int spacing;//space between items
    int margin;//space between edges and content
    int item_selected();//returns index of selected item
    int item_clicked();//returns index of clicked item
    virtual void add_item(button* item);
    void set_title(std::string txt);
    void set_subtitle(std::string txt);
    void set_layout(std::string l);
    void format();
    void render() override;
    void update() override;
    menu();
};

#endif // MENU_H
