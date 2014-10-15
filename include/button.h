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

class button : public clickable_object
{
    protected:
        char* label;
    public:
        bool border;
        color border_color;
        float label_margin;//space between text and button border
        float font_size;//the height of the font in pt (not pixels)
        float spacing;//space between each line
        bool hovered_over();
        bool left_clicked();
        bool performed_action;
        void* font;
        void (*action)();//a function pointer which will be called when clicked
        void fit_label();//adjusts the size of the button to fit the text
        void set_label(char* l);
        void mouse_function();
        void render();
        void update();
        button();
        button(float x, float y, char* l, void (*a)(void));
};

#endif // BUTTON_H
