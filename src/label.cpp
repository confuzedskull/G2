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

#include "label.h"
#include "ui.h"
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

std::string ui::label::default_font_style = "helvetica";
int ui::label::default_allignment = CENTER;
int ui::label::default_font_size = 12;
int ui::label::default_spacing = 1;
color ui::label::default_fill_color = ui::default_fill_color;
color ui::label::default_border_color = ui::default_border_color;
color ui::label::default_font_color = BLACK;

int ui::label::get_allignment()
{
    return allignment;
}

std::string ui::label::get_type()
{
    return "label";
}

void ui::label::allign(int pos)
{
    if(pos==LEFT || pos==CENTER || pos==RIGHT)
        allignment=pos;
    else
        std::cerr<<"invalid allignment.\n";
}

void ui::label::allign(std::string pos)
{
    if(pos=="left")
        allign(LEFT);
    else if(pos=="right")
        allign(RIGHT);
    else if(pos=="center")
        allign(CENTER);
}

void ui::label::set_spacing(int val)
{
    spacing=val;
}

void ui::label::set_text(std::string txt)
{
    text=txt;
    if(isless((float)width,font_width*txt.length()))
        width=(int)(font_width*txt.length());
    if(isless((float)height,font_height))
        height=(int)font_height;
}

void ui::label::set_font(std::string style, int size)
{
    font_size=size;
    font_width=font_size*0.6;
    font_height=font_size;
    if(style=="helvetica")
    {
        if(size==10)
            font=GLUT_BITMAP_HELVETICA_10;
        else if(size==12)
            font=GLUT_BITMAP_HELVETICA_12;
        else if(size==18)
            font=GLUT_BITMAP_HELVETICA_18;
        else
            std::cerr<<"invalid font size\n";
    }
    else if(style=="times new roman")
    {
        if(size==10)
            font=GLUT_BITMAP_TIMES_ROMAN_10;
        if(size==24)
            font=GLUT_BITMAP_TIMES_ROMAN_24;
    }
    else
        std::cerr<<"invalid font style\n";
}

void ui::label::mouse_function()
{
    if(enabled)
    {
        if(double_clicked())
            filled=true;
        else
            filled=false;
        if(selected && dragged())
            width=cursor::left_up.x-cursor::left_down.x;
    }
}

void ui::label::update()
{
    mouse_function();
}

void ui::label::render()
{
    if(visible)
    {
        render_shape();
        render_border();
        int text_pos;
        switch(allignment)
        {
        case LEFT:
            text_pos=xmin;
            break;
        case CENTER:
            text_pos=position.x-((text.length()*font_width)/2);
            break;
        case RIGHT:
            text_pos=xmax;
            break;
        }
        glColor3f(font_color.r,font_color.g,font_color.b);
        glRasterPos2f(text_pos,position.y-(font_height/2));//update the character position
        for(unsigned c=0; c<text.length(); c++)//iterate through each character
            glutBitmapCharacter(font, text[c]);//print the character to the screen
        render_border();
    }
}

ui::label::label()
{
    filled=false;
    bordered=false;
    fill_color=default_fill_color;
    border_color=default_border_color;
    font_color=default_font_color;
    set_dimensions(12,12);
    allign(default_allignment);
    set_font(default_font_style,default_font_size);
    spacing=default_spacing;
    std::clog<<"object#"<<number<<"(label)"<<" created.\n";
}
