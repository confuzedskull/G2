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
#include "label.h"

//A button displays text and executes a function when clicked
class ui::button: public clickable_object
{
protected:
    int int_param1;
public:
    static std::string default_texture;
    static std::string default_mask;
    static std::string default_click_sound;
    static std::string default_hover_sound;
    static int default_margin;
    static int default_width;
    static int default_height;
    static color default_fill_color;
    static color default_border_color;
    label text;
    std::string get_type() override;
    int margin;//space between label and button border
    int combined_width();
    int combined_height();
    bool performed_action;//whether or not the button action executed
    void (*action)();//a function pointer which will be called when clicked
    void (*action1i)(int i);//a function pointer which will be called when clicked
    void set_action(void (*act)());
    void set_action(void (*act)(int),int i);
    void mouse_function();
    void render() override;
    void update();
    virtual void format();//adjusts the size of the button to fit the label
    virtual void set_label(std::string txt);
    static void action_placeholder();
    static void action_placeholder1i(int i);
    button();
    button(float x, float y, char* l, void (*a)(void));
};

#endif // BUTTON_H
