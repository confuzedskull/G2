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

#ifndef LABEL_H
#define LABEL_H
#include "interactive_object.h"
#include "ui.h"
#include <string>

//A label stores a string which can be formatted and displayed on screen
class ui::label: public interactive_object
{
    friend button;
    friend checkbox;
    friend menu;
    friend dropdown_menu;
protected:
    std::string text;
    int allignment;
    void* font;//points to a GLUT font
    int spacing;//the space between each line
    int font_size;
    float font_width;
    float font_height;
public:
    static std::string default_font_style;
    static int default_allignment;
    static int default_font_size;
    static int default_spacing;
    static color default_fillcolor;
    static color default_bordercolor;
    static color default_font_color;
    int get_allignment();
    std::string get_type() override;
    std::string get_text();
    color font_color;
    void allign(int pos);
    void allign(std::string pos);
    void set_spacing(int val);
    void set_text(std::string txt);
    void set_font(std::string style, int size);
    void update() override;
    void render() override;//prints the text to the screen
    void load() override;
    void save() override;
    label();
};
#endif // LABEL_H
