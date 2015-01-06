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
#include <sstream>

std::string ui::checkbox::default_texture = "";
std::string ui::checkbox::default_mask = "";
std::string ui::checkbox::default_clicksound = "";
std::string ui::checkbox::default_hoversound = "";
int ui::checkbox::default_margin = 4;
int ui::checkbox::default_width = 16;
int ui::checkbox::default_height = 16;
color ui::checkbox::default_fillcolor = ui::default_fillcolor;
color ui::checkbox::default_bordercolor = ui::default_bordercolor;

void ui::checkbox::bind_option(int* o)
{
    option=o;
}

std::string ui::checkbox::get_type()
{
    return "checkbox";
}

void ui::checkbox::set_label(std::string txt)
{
    text.set_text(txt);
    text.set_position(xmin-margin-(text.get_width()/2),position.y);
}

void ui::checkbox::mouse_function()
{
    if(visible)
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

void ui::checkbox::render()
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

void ui::checkbox::update()
{
    text.visible=visible;
    mouse_function();
}

void ui::checkbox::load()
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
    //load label
    object_file>>text.text;
    object_file>>text.allignment;
    object_file>>text.spacing;
    object_file>>text.font_size;
    object_file>>text.font_width>>text.font_height;
    object_file>>text.font_color.r>>text.font_color.g>>text.font_color.b;
    //load checkbox properties
    object_file>>checked;
    object_file>>checkmark_margin;
    object_file>>checkmark_color.r>>checkmark_color.g>>checkmark_color.b;
    object_file.close();
    std::clog<<"object#"<<number<<"(checkbox)"<<" loaded.\n";
}

void ui::checkbox::save()
{
    std::stringstream filename;
    filename<<"./data/buttons/object#"<<number<<".cbx";
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
    //save checkbox properties
    object_file<<checked<<std::endl;
    object_file<<checkmark_margin<<std::endl;
    object_file<<checkmark_color.str()<<std::endl;
    object_file.close();
    std::clog<<"object#"<<number<<"(checkbox)"<<" saved.\n";
}

ui::checkbox::checkbox()
{
    bordered=true;
    set_dimensions(default_width,default_height);
    fill_color=default_fillcolor;
    border_color=default_bordercolor;
    margin=default_margin;
    checked=1;
    checkmark_margin=2;
    checkmark_color=BLACK;
    set_texture(default_texture);
    set_mask(default_mask);
    set_clicksound(default_clicksound);
    set_hoversound(default_hoversound);
    std::clog<<"object#"<<number<<"(checkbox)"<<" created.\n";
}
