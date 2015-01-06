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

#ifndef BUTTON_H
#define BUTTON_H
#include "interactive_object.h"
#include "label.h"

//A button displays text and executes a function when clicked
class ui::button: public interactive_object
{
protected:
    int int_param1,int_param2;
    int* intptr_param1;
    float f_param1,f_param2;
    std::string str_param1;
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
    ui::label text;
    std::string get_type() override;
    int margin;//space between label and button border
    int combined_width();
    int combined_height();
    bool performed_action;//whether or not the button action executed
    void (*action)();//a function pointer which will be called when clicked
    void (*action1i)(int i);//a function pointer which will be called when clicked
    void (*action2i)(int i1, int i2);//a function pointer which will be called when clicked
    void (*action1ip)(int* i);//a function pointer which will be called when clicked
    void (*action1f)(float f);//a function pointer which will be called when clicked
    void (*action2f)(float f1, float f2);//a function pointer which will be called when clicked
    void (*action1s)(std::string s);//a function pointer which will be called when clicked
    void (*action1s1i)(std::string s, int i);//a function pointer which will be called when clicked
    void set_action(void (*act)());
    void set_action(void (*act)(int), int i);
    void set_action(void (*act)(int*), int* ip);
    void set_action(void (*act)(int,int), int i1, int i2);
    void set_action(void (*act)(float), float f);
    void set_action(void (*act)(float,float), float f1, float f2);
    void set_action(void (*act)(std::string), std::string s);
    void set_action(void (*act)(std::string,int), std::string s, int i);
    void mouse_function();
    void render() override;
    void update();
    void load() override;
    void save() override;
    virtual void set_label(std::string txt);
    static void action_placeholder();
    static void action_placeholder1i(int i);
    static void action_placeholder1ip(int* ip);
    static void action_placeholder2i(int i1,int i2);
    static void action_placeholder1f(float f);
    static void action_placeholder2f(float f1, float f2);
    static void action_placeholder1s(std::string s);
    static void action_placeholder1s1i(std::string s, int i);
    button();
};

#endif // BUTTON_H
