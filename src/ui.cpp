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

#include "ui.h"
#include "window.h"
#include "game.h"
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
#include <string.h>
#include <stdio.h>

//initialize variables
std::vector<char*> ui::info_overlay(20,new char[30]);//create 20 lines of 30 character length
float ui::margin = 10.0f;
float ui::spacing = 20.0f;

void ui::glutPrint(float x, float y, void* font, char* text, color c)
{
    if(!text || !strlen(text))
        return;
    bool blending = false;
    if(glIsEnabled(GL_BLEND))
        blending = true;
    glEnable(GL_BLEND);
    glColor4f(c.r,c.g,c.b,c.a);
    glRasterPos2f(x,y);
    while(*text)
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
    if(!blending)
        glDisable(GL_BLEND);
}

void ui::glutPrint(float x, float y, void* font, char* text)
{
    glutPrint(x, y, font, text, BLACK);
}

void ui::glutPrint(float x, float y, char* text)
{
    glutPrint(x, y, GLUT_BITMAP_HELVETICA_12, text);
}

void ui::print_overlay()
{
    unsigned index = cursor::selected_object;//this value is relative to the object's corresponding container
    unsigned line = 0;//used for spacing each line

    sprintf(info_overlay[line],"selected object: #%d - %s", cursor::left_clicked_object->number, cursor::left_clicked_object->name);
    glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

    sprintf(info_overlay[line],"type: %s", cursor::left_clicked_object->type);
    glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

    sprintf(info_overlay[line],"dimensions: %.2fX%.2f", cursor::left_clicked_object->width,cursor::left_clicked_object->height);
    glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

    sprintf(info_overlay[line],"rotation: %.2f", cursor::left_clicked_object->rotation);
    glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

    sprintf(info_overlay[line],"current position: %.2f,%.2f", cursor::left_clicked_object->position.x,cursor::left_clicked_object->position.y);
    glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

    if(strcmp(cursor::left_clicked_object->type,"physics object")==0)//display the following if a physics object is selected
    {
        sprintf(info_overlay[line],"resting position: %.2f, %.2f",game::physics_objects[index]->rest.x,game::physics_objects[index]->rest.y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"mass: %.2f",game::physics_objects[index]->mass);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"speed: %.2f",game::physics_objects[index]->speed);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"time moving: %.2f,%.2f",game::physics_objects[index]->delta_time[0],game::physics_objects[index]->delta_time[1]);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"initial velocity: %.2f,%.2f",game::physics_objects[index]->velocity[0].x,game::physics_objects[index]->velocity[0].y);
        glutPrint (margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"final velocity: %.2f,%.2f",game::physics_objects[index]->velocity[1].x,game::physics_objects[index]->velocity[1].y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"time accelerating: %.2f %.2f",game::physics_objects[index]->delta_time[2],game::physics_objects[index]->delta_time[3]);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"acceleration: %.2f %.2f",game::physics_objects[index]->acceleration.x,game::physics_objects[index]->acceleration.y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"momentum: %.2f %.2f",game::physics_objects[index]->momentum.x,game::physics_objects[index]->momentum.y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"force: %.2f %.2f",game::physics_objects[index]->force.x,game::physics_objects[index]->force.y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"object touching side L:%d R:%d T:%d B:%d",game::physics_objects[index]->touching[0], game::physics_objects[index]->touching[1], game::physics_objects[index]->touching[2],game::physics_objects[index]->touching[3]);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);
    }
    if(strcmp(cursor::left_clicked_object->type,"draggable object")==0)//display the following if a draggable object is selected
    {
        index = cursor::selected_object-game::physics_objects.size();
        sprintf(info_overlay[line],"object touching side L:%d R:%d T:%d B:%d",game::draggable_objects[index]->touching[0], game::draggable_objects[index]->touching[1],game::draggable_objects[index]->touching[2],game::draggable_objects[index]->touching[3]);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);
    }
    if(strcmp(cursor::left_clicked_object->type,"rts object")==0)//display the following if a RTS object is selected
    {
        index = cursor::selected_object-(game::physics_objects.size()+game::draggable_objects.size());
        sprintf(info_overlay[line],"speed: %.2f",game::rts_objects[index]->speed);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"rally point: %.2f, %.2f",game::rts_objects[index]->rally->x,game::rts_objects[index]->rally->y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"object touching side L:%d R:%d T:%d B:%d",game::rts_objects[index]->touching[0], game::rts_objects[index]->touching[1], game::rts_objects[index]->touching[2],game::rts_objects[index]->touching[3]);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);
    }
    sprintf(info_overlay[line],"game time: %.2fs",game::time);
    glutPrint(window::width-(margin+150),window::height-(spacing*1), info_overlay[line++]);

    sprintf(info_overlay[line],"mouse move: %.2f,%.2f",cursor::passive.x,cursor::passive.y);
    glutPrint(window::width-(margin+150),window::height-(spacing*2), info_overlay[line++]);

    sprintf(info_overlay[line],"mouse click: %.2f,%.2f",cursor::left_down.x,cursor::left_down.y);
    glutPrint(window::width-(margin+150),window::height-(spacing*3), info_overlay[line++]);

    sprintf(info_overlay[line],"mouse drag: %.2f,%.2f",cursor::left_drag.x,cursor::left_drag.y);
    glutPrint(window::width-(margin+150),window::height-(spacing*4), info_overlay[line++]);
}
