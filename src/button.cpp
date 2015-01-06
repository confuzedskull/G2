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

#include "button.h"
#include "ui.h"
#include "window.h"
#include "cursor.h"
#include "audio.h"
#include <iostream>
#include <sstream>
#include <math.h>

std::string ui::button::default_texture="";
std::string ui::button::default_mask="";
std::string ui::button::default_clicksound="";
std::string ui::button::default_hoversound="";
color ui::button::default_fillcolor = ui::default_fillcolor;
color ui::button::default_bordercolor = ui::default_bordercolor;
int ui::button::default_margin = 5;
int ui::button::default_width = 48;
int ui::button::default_height = 12;

int ui::button::combined_width()
{
    if(text.get_allignment()==LEFT || text.get_allignment()==RIGHT)
        return text.get_width()+margin+width;
    else
    {
        if(text.get_width()>width)
            return text.get_width();
        else
            return width;
    }
}

int ui::button::combined_height()
{
    if(text.get_allignment()==TOP || text.get_allignment()==BOTTOM)
        return text.get_height()+margin+height;
    else
    {
        if(text.get_height()>height)
            return text.get_height();
        else
            return height;
    }
}

std::string ui::button::get_type()
{
    return "button";
}

void ui::button::set_label(std::string txt)
{
    text.set_text(txt);
    text.set_position(position.x,position.y);
    if(width<text.get_width()+(margin*2))
        width=text.get_width()+(margin*2);
    if(height<text.get_height()+(margin*2))
        height=text.get_height()+(margin*2);
    calc_boundaries();
}

void ui::button::set_action(void (*act)())
{
    action=act;
}

void ui::button::set_action(void (*act)(int), int i)
{
    action1i=act;
    int_param1=i;
}

void ui::button::set_action(void (*act)(int, int), int i1, int i2)
{
    action2i=act;
    int_param1=i1;
    int_param2=i2;
}

void ui::button::set_action(void (*act)(int*) ,int* ip)
{
    action1ip=act;
    intptr_param1=ip;
}

void ui::button::set_action(void (*act)(float), float f)
{
    action1f=act;
    f_param1=f;
}

void ui::button::set_action(void (*act)(float, float), float f1, float f2)
{
    action2f=act;
    f_param1=f1;
    f_param2=f2;
}

void ui::button::set_action(void (*act)(std::string), std::string s)
{
    action1s=act;
    str_param1=s;
}

void ui::button::set_action(void (*act)(std::string, int), std::string s, int i)
{
    action1s1i=act;
    str_param1=s;
    int_param2=i;
}

void ui::button::mouse_function()
{
    if(visible)
    {
        hover_function();
        if(left_clicked())
        {
            if(!performed_action)
            {
                if(!muted)
                    audio::play(click_sound);
                action();
                action1i(int_param1);
                action1s1i(str_param1,int_param2);
                action1ip(intptr_param1);
                performed_action=true;
                std::clog<<"object#"<<number<<"(button)"<<" clicked.\n";
            }
        }
        else
            performed_action=false;
    }
}

void ui::button::render()
{
    if(visible)
    {
        render_shape();
        render_border();
        text.render();
        mark_selected();
    }
}

void ui::button::update()
{
    text.visible=visible;
    mouse_function();
}

void ui::button::load()
{
    std::clog<<file_name;
    std::ifstream object_file(file_name);//access file by name
    if(object_file.bad())//make sure the file is there
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //load basic object properties
    object_file>>position.x>>position.y;
    object_file>>rotation;
    object_file>>width>>height;
    object_file>>fill_color.r>>fill_color.g>>fill_color.b;
    object_file>>marker_color.r>>marker_color.g>>marker_color.b;
    object_file>>border_color.r>>border_color.g>>border_color.b;
    object_file>>filled;
    object_file>>bordered;
    object_file>>textured;
    object_file>>masked;
    object_file>>visible;
    object_file>>selected;
    object_file>>muted;
    object_file>>texture;
    object_file>>mask;
    //load interactive object properties
    object_file>>click_detection;
    object_file>>drag_detection;
    object_file>>click_sound;
    object_file>>hover_sound;
    object_file.close();
    //load label
    object_file>>text.text;
    object_file>>text.allignment;
    object_file>>text.spacing;
    object_file>>text.font_size;
    object_file>>text.font_width>>text.font_height;
    object_file>>text.font_color.r>>text.font_color.g>>text.font_color.b;
    std::clog<<"object#"<<number<<"(button)"<<" loaded.\n";
}

void ui::button::save()
{
    std::stringstream filename;
    filename<<"./data/buttons/object#"<<number<<".btn";
    std::ofstream object_file(filename.str());
    if(object_file.bad())
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //save basic object properties
    object_file<<position.x<<' '<<position.y<<std::endl;
    object_file<<rotation<<std::endl;
    object_file<<width<<' '<<height<<std::endl;
    object_file<<fill_color.str()<<std::endl;
    object_file<<marker_color.str()<<std::endl;
    object_file<<border_color.str()<<std::endl;
    object_file<<filled<<std::endl;
    object_file<<bordered<<std::endl;
    object_file<<textured<<std::endl;
    object_file<<masked<<std::endl;
    object_file<<visible<<std::endl;
    object_file<<selected<<std::endl;
    object_file<<muted<<std::endl;
    object_file<<texture<<std::endl;
    object_file<<mask<<std::endl;
    //save interactive object properties
    object_file<<click_detection<<std::endl;
    object_file<<drag_detection<<std::endl;
    object_file<<hover_detection<<std::endl;
    object_file<<highlight_detection<<std::endl;
    object_file<<click_sound<<std::endl;
    object_file<<hover_sound<<std::endl;
    //save label
    object_file<<text.text<<std::endl;
    object_file<<text.allignment<<std::endl;
    object_file<<text.spacing<<std::endl;
    object_file<<text.font_size<<std::endl;
    object_file<<text.font_width<<' '<<text.font_height<<std::endl;
    object_file<<text.font_color.str()<<std::endl;
    object_file.close();
    std::clog<<"object#"<<number<<"(button)"<<" saved.\n";
}

void ui::button::action_placeholder(){}

void ui::button::action_placeholder1i(int i){}

void ui::button::action_placeholder2i(int i1, int i2){}

void ui::button::action_placeholder1ip(int* ip){}

void ui::button::action_placeholder1f(float f){}

void ui::button::action_placeholder2f(float f1, float f2){}

void ui::button::action_placeholder1s(std::string s){}

void ui::button::action_placeholder1s1i(std::string s,int i){}

ui::button::button()
{
    set_dimensions(default_width,default_height);
    fill_color=default_fillcolor;
    border_color=default_bordercolor;
    margin=default_margin;
    set_label("click me");
    action=ui::button::action_placeholder;
    action1i=ui::button::action_placeholder1i;
    action2i=ui::button::action_placeholder2i;
    action1ip=ui::button::action_placeholder1ip;
    action1f=ui::button::action_placeholder1f;
    action2f=ui::button::action_placeholder2f;
    action1s=ui::button::action_placeholder1s;
    action1s1i=ui::button::action_placeholder1s1i;
    bordered=true;
    performed_action=false;
    set_texture(default_texture);
    set_mask(default_mask);
    set_clicksound(default_clicksound);
    set_hoversound(default_hoversound);
    std::clog<<"object#"<<number<<"(button)"<<" created.\n";
}
