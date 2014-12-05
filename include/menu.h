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
    label title;
    label subtitle;
    std::string layout;
    std::string title_allignment;
public:
    std::vector<button*> items;
    int spacing;//space between buttons
    int margin;
    button* current_item;
    int item_selected();//returns index of selected item
    int item_clicked();//returns index of clicked item
    void set_title(std::string t);
    void set_subtitle(std::string s);
    void set_layout(std::string l);
    void allign_title(std::string a);
    virtual void add_item(button* b);
    void format();
    void render() override;
    void update() override;
    menu();
};

#endif // MENU_H
