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
#include <sstream>
#include <fstream>
#include <math.h>

std::string ui::label::default_font_style = "helvetica";
int ui::label::default_allignment = CENTER;
int ui::label::default_font_size = 12;
int ui::label::default_spacing = 1;
color ui::label::default_fillcolor = ui::default_fillcolor;
color ui::label::default_bordercolor = ui::default_bordercolor;
color ui::label::default_font_color = BLACK;

int ui::label::get_allignment()
{
    return allignment;
}

std::string ui::label::get_type()
{
    return "label";
}

std::string ui::label::get_text()
{
    return text;
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

void ui::label::update()
{
    interactive_object::mouse_function();
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

void ui::label::load()
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
    object_file>>hover_detection;
    object_file>>highlight_detection;
    object_file>>click_sound;
    object_file>>hover_sound;
    //load label properties
    object_file>>text;
    object_file>>allignment;
    object_file>>spacing;
    object_file>>font_size;
    object_file>>font_width>>font_height;
    object_file>>font_color.r>>font_color.g>>font_color.b;
    object_file.close();
    std::clog<<"object#"<<number<<"(label)"<<" loaded.\n";
}

void ui::label::save()
{
    std::stringstream filename;
    filename<<"./data/labels/object#"<<number<<".lbl";
    std::ofstream object_file(filename.str());
    if(object_file.bad())
    {
        std::cerr<<"bad file name.\n";
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
    //save label properties
    object_file<<text<<std::endl;
    object_file<<allignment<<std::endl;
    object_file<<spacing<<std::endl;
    object_file<<font_size<<std::endl;
    object_file<<font_width<<' '<<font_height<<std::endl;
    object_file<<font_color.str()<<std::endl;
    object_file.close();
    std::clog<<"object#"<<number<<"(label)"<<" saved.\n";
}

ui::label::label()
{
    filled=false;
    bordered=false;
    fill_color=default_fillcolor;
    border_color=default_bordercolor;
    font_color=default_font_color;
    set_dimensions(48,12);
    allign(default_allignment);
    set_font(default_font_style,default_font_size);
    spacing=default_spacing;
    set_text("label");
    std::clog<<"object#"<<number<<"(label)"<<" created.\n";
}
