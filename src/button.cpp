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

void button::format()
{
    width=text.get_width()+(margin*2);
    height=text.get_height()+(margin*2);
    calc_boundaries();
}

void button::set_label(std::string l)
{
    text.clear();
    text.add_line(l);
    format();
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
            cursor::left_clicked_ui = true;
            if(!performed_action)
            {
                action();
                performed_action=true;
                std::clog<<"object#"<<number<<'('<<type<<')'<<"clicked.\n";
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
        text.set_position(xmin+margin,position.y-(text.get_height()/2));
    if(text_allignment=="center")
        text.set_position(position.x-(text.get_width()/2),position.y-(text.get_height()/2));
    if(text_allignment=="right")
        text.set_position(xmax-margin-text.get_width(),position.y-(text.get_height()/2));
    mouse_function();
}

void button::action_placeholder(){}

button::button()
{
    type="button";
    margin=5;
    position.set(0.0f,0.0f);
    fill_color.set(0.75f,0.75f,0.75f);
    fill_color.changed=false;
    set_label("click me");
    allign_label("center");
    action=button::action_placeholder;
    bordered=true;
    performed_action=false;
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}

button::button(float x, float y, char* l, void (*a)(void))
{
    type="button";
    margin=5;
    position.set(x,y);
    fill_color.set(0.75f,0.75f,0.75f);
    fill_color.changed=false;
    set_label("click me");
    allign_label("center");
    action=a;
    bordered=true;
    performed_action=false;
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
