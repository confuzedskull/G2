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

#include "text_object.h"
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
#include <string>
#include <iostream>

float text_object::get_width()
{
    width=font_width*longest_line;
    return width;
}

float text_object::get_height()
{
    height=(font_height*lines)+((lines-1)*spacing);
    return height;
}

void text_object::set_text(char* t)
{
    text=t;
    calc_lines();
}

void text_object::set_font(char* style, int size)
{
    font_size=size;
    font_width=font_size*0.6;
    font_height=font_size;
    if(strcmp(style,"helvetica")==0)
    {
        if(size==10)
            font=GLUT_BITMAP_HELVETICA_10;
        if(size==12)
            font=GLUT_BITMAP_HELVETICA_12;
        if(size==18)
            font=GLUT_BITMAP_HELVETICA_18;
    }
    if(strcmp(style,"times new roman")==0)
    {
        if(size==10)
            font=GLUT_BITMAP_TIMES_ROMAN_10;
        if(size==24)
            font=GLUT_BITMAP_TIMES_ROMAN_24;
    }
}

void text_object::calc_lines()
{
    int current_line;
    int previous_line=0;
    lines=1;
    longest_line=0;
    if(strchr(text,'\n')!=NULL)//newline is detected
    {
        for(unsigned i=0; i<strlen(text);i++)
        {
            if(text[i]=='\n')
            {
                current_line=i-previous_line;
                previous_line=i;
                lines++;
                if(current_line>longest_line)
                    longest_line=current_line;
            }
        }
    }
    else
        longest_line=strlen(text);
}

void text_object::render()
{
    if(strchr(text,'\n')!=NULL)//newline is detected
    {
        char* current_line="";
        int new_y=position.y;
        for(unsigned i=0; i<strlen(text);i++)
        {
            if(text[i]=='\n')
            {
                ui::glutPrint(position.x,new_y,font,current_line);
                current_line="";
                new_y-=spacing+font_height;
            }
            else
                current_line+=text[i];
        }
    }
    else
        ui::glutPrint(position.x,position.y,font,text);
}

text_object::text_object()
{
    type="text object";
    text="";
    set_font("helvetica",12);
    spacing=1;
    std::clog<<"object#"<<number<<": "<<name<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
