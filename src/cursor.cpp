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
//initialize static variables
point2f cursor::passive = point2f(0.0,0.0);
bool cursor::left_click = false;
point2f cursor::left_down =  point2f(0.0,0.0);
bool cursor::right_click = false;
point2f cursor::right_down = point2f(0.0,0.0);
bool cursor::highlighting = false;
float cursor::xmax = 0.0;
float cursor::xmin = 0.0;
float cursor::ymax = 0.0;
float cursor::ymin = 0.0;
clickable_object* cursor::left_clicked_object = new clickable_object();
int cursor::selected_object = 1;
bool cursor::left_clicked_an_object = false;
std::vector<bool> cursor::highlighted_objects(game::rts_objects.size(),false);
bool cursor::right_dragging = false;
clickable_object* cursor::right_clicked_object = new clickable_object();
bool cursor::right_clicked_an_object = false;
bool cursor::left_dragging = false;
bool cursor::grabbed_an_object=false;
point2f cursor::left_drag = point2f(0.0,0.0);
color cursor::box_color = GREEN;
point2f cursor::left_up = point2f(0.0,0.0);
point2f cursor::right_up = point2f(0.0,0.0);
point2f cursor::right_drag = point2f(0.0,0.0);

int cursor::objects_selected()
{
    int selected = 0;
    for(unsigned i=0; i<game::rts_objects.size(); i++)
    {
        if(highlighted_objects[i])
            selected++;
    }
    return selected;
}

void cursor::calc_boundaries()//boundaries of the selection box
{
    xmin= left_down.x;
    xmax= left_drag.x;
    ymin= left_down.y;
    ymax= left_drag.y;
}

void cursor::selection_box()//this is the box that is created when user clicks and drags
{
    if(highlighting)
    {
        bool blending = false;
        if(glIsEnabled(GL_BLEND))
            blending = true;
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(box_color.r,box_color.g,box_color.b,0.5);
        glBegin(GL_QUADS);
        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner
        glEnd();
        if(!blending)
        glDisable(GL_BLEND);
    }
}

void cursor::reset()
{
    passive.set(0.0,0.0);
    left_down.set(0.0,0.0);
    right_down.set(0.0,0.0);
    left_up.set(0.0,0.0);
    right_up.set(0.0,0.0);
    left_drag.set(0.0,0.0);
    right_drag.set(0.0,0.0);
    left_click = false;
    right_click = false;
    left_dragging = false;
    right_dragging = false;
    highlighting = false;
    highlighted_objects.assign(game::rts_objects.size(),false);
    selected_object = 0;
    left_clicked_object = new clickable_object();
    right_clicked_object = new clickable_object();
    left_clicked_an_object = false;
    right_clicked_an_object = false;
    grabbed_an_object=false;
    box_color = GREEN;
    xmax = 0.0;
    xmin = 0.0;
    ymax = 0.0;
    ymin = 0.0;
}
