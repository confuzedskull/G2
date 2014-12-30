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

#include "checkbox.h"
#include "cursor.h"
#include "audio.h"
#include "ui.h"
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

std::string checkbox::default_texture = "";
std::string checkbox::default_mask = "";
std::string checkbox::default_click_sound = "";
std::string checkbox::default_hover_sound = "";
int checkbox::default_margin = 4;
int checkbox::default_width = 16;
int checkbox::default_height = 16;

void checkbox::bind_option(int* o)
{
    option=o;
}

std::string checkbox::get_type()
{
    return "checkbox";
}

void checkbox::set_label(std::string txt)
{
    text.set_text(txt);
    text.set_position(xmin-margin-(text.get_width()/2),position.y);
}

void checkbox::mouse_function()
{
    if(visible && enabled)
    {
        if(filled)
            hover_function();
        if(left_clicked())
        {
            if(!muted)
                audio::play(click_sound);
            if(*option==1)
                checked=0;
            else
                checked=1;
        }
        else
            *option=checked;
    }
}

void checkbox::format()
{
    calc_boundaries();
    text.set_position(xmin-margin-(text.get_width()/2),position.y);
}

void checkbox::render()
{
    if(visible)
    {
        render_shape();
        if(checked==1)
        {
            glColor3f(checkmark_color.r,checkmark_color.g,checkmark_color.b);//color the square with object.fill_color
            glBegin(GL_POLYGON);//draws a filled in polygon
            glVertex2f(xmin+checkmark_margin, ymin+checkmark_margin); // The bottom left corner
            glVertex2f(xmin+checkmark_margin, ymax-checkmark_margin); // The top left corner
            glVertex2f(xmax-checkmark_margin, ymax-checkmark_margin); // The top right corner
            glVertex2f(xmax-checkmark_margin, ymin+checkmark_margin); // The bottom right corner
            glEnd();//finish drawing
        }
        render_border();
        text.render();
    }
}

void checkbox::update()
{
    text.visible=visible;
    mouse_function();
}

checkbox::checkbox()
{
    bordered=true;
    set_dimensions(default_width,default_height);
    fill_color = color(0.75f,0.75f,0.75f);
    margin=default_margin;
    checked=1;
    checkmark_margin=2;
    checkmark_color=BLACK;
    set_texture(default_texture);
    set_mask(default_mask);
    set_click_sound(default_click_sound);
    set_hover_sound(default_hover_sound);
    std::clog<<"object#"<<number<<"(checkbox)"<<" created.\n";
}
