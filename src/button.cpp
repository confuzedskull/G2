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

#include "button.h"
#include "ui.h"
#include "window.h"
#include "cursor.h"
#include "audio.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <math.h>

std::string button::default_texture="";
std::string button::default_mask="";
std::string button::default_click_sound="";
std::string button::default_hover_sound="";
std::string button::default_allignment="center";
int button::default_margin = 5;
int button::default_width = 48;
int button::default_height = 16;

void button::format()
{
    if(width<text.get_width()+(margin*2))
        width=text.get_width()+(margin*2);
    if(height<text.get_height()+(margin*2))
        height=text.get_height()+(margin*2);
    calc_boundaries();
}

void button::set_label(std::string txt)
{
    text.clear();
    text.add_line(txt);
    format();
}

void button::set_action(void (*act)())
{
    action=act;
}

void button::set_action(void (*act)(int),int i)
{
    action1i=act;
    int_param1=i;
}

void button::allign_label(std::string allignment)
{
    text_allignment=allignment;
}

void button::mouse_function()
{
    if(visible && enabled)
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
                performed_action=true;
                std::clog<<"object#"<<number<<"(button)"<<" clicked.\n";
            }
        }
        else
            performed_action=false;
    }
}

void button::render()
{
    if(visible)
    {
        render_shape();
        render_border();
        text.render();
        mark_selected();
    }
}

void button::update()
{
    text.visible=visible;
    if(text_allignment=="left")
        text.set_position(xmin+margin,get_position().y-(text.get_height()/2));
    if(text_allignment=="center")
        text.set_position(get_position().x-(text.get_width()/2),get_position().y-(text.get_height()/2));
    if(text_allignment=="right")
        text.set_position(xmax-margin-text.get_width(),get_position().y-(text.get_height()/2));
    mouse_function();
}

void button::action_placeholder(){}

void button::action_placeholder1i(int i){}

button::button()
{
    position.set(0.0f,0.0f);
    set_dimensions(default_width,default_height);
    fill_color.set(0.75f,0.75f,0.75f);
    fill_color.changed=false;
    margin=default_margin;
    set_label("click me");
    allign_label(default_allignment);
    action=button::action_placeholder;
    action1i=button::action_placeholder1i;
    bordered=true;
    performed_action=false;
    set_texture(default_texture);
    set_mask(default_mask);
    set_click_sound(default_click_sound);
    set_hover_sound(default_hover_sound);
    std::clog<<"object#"<<number<<"(button)"<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}

button::button(float x, float y, char* txt, void (*act)(void))
{
    position.set(x,y);
    set_dimensions(default_width,default_height);
    fill_color.set(0.75f,0.75f,0.75f);
    fill_color.changed=false;
    margin=default_margin;
    set_label(txt);
    allign_label(default_allignment);
    action=act;
    bordered=true;
    performed_action=false;
    set_texture(default_texture);
    set_mask(default_mask);
    set_click_sound(default_click_sound);
    set_hover_sound(default_hover_sound);
    std::clog<<"object#"<<number<<"(button)"<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
