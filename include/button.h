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

#ifndef BUTTON_H
#define BUTTON_H
#include "clickable_object.h"
#include "text_object.h"
#include <string>

//A button displays text and executes a function when clicked
class button : public clickable_object
{
protected:
    text_object label;
public:
    bool border;//whether or not a border should be shown
    color border_color;//the color of the border
    int margin;//space between text and button border
    bool performed_action;//whether or not the button action executed
    void (*action)();//a function pointer which will be called when clicked
    void format();//adjusts the size of the button to fit the text
    void set_label(std::string l);
    void mouse_function();
    void render();
    void update();
    button();
    button(float x, float y, char* l, void (*a)(void));
};

#endif // BUTTON_H
