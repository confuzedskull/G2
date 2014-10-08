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
#include <iostream>
#include <math.h>

//initialize variables
bool* ui::key_states = new bool[256];
bool ui::temp_toggle = false;
bool ui::toggle_overlay = false;
std::vector<char*> ui::info_overlay(20,new char[30]);//create 15 lines of 30 character length
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
    unsigned index = cursor::selected_object;
    unsigned line = 0;

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

    if(strcmp(cursor::left_clicked_object->type,"physics object")==0)
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
    if(strcmp(cursor::left_clicked_object->type,"draggable object")==0)
    {
        index = cursor::selected_object-game::physics_objects.size();
        sprintf(info_overlay[line],"object touching side L:%d R:%d T:%d B:%d",game::draggable_objects[index]->touching[0], game::draggable_objects[index]->touching[1],game::draggable_objects[index]->touching[2],game::draggable_objects[index]->touching[3]);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);
    }
    if(strcmp(cursor::left_clicked_object->type,"rts object")==0)
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
    glutPrint(window::width-(margin+120),window::height-(spacing*1), info_overlay[line++]);

    sprintf(info_overlay[line],"click: %.2f,%.2f",cursor::left_down.x,cursor::left_down.y);
    glutPrint(window::width-(margin+120),window::height-(spacing*2), info_overlay[line++]);

    sprintf(info_overlay[line],"drag: %.2f,%.2f",cursor::left_drag.x,cursor::left_drag.y);
    glutPrint(window::width-(margin+120),window::height-(spacing*3), info_overlay[line++]);
}

void ui::mouse_click(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        cursor::left_down.set(x,window::height-y);
        cursor::left_click=true;
    }

    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        cursor::left_up.set(x,window::height-y);
        cursor::highlighting=false;
        cursor::left_click=false;
    }

    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        cursor::highlighting=false;
        cursor::right_click=true;
        cursor::right_down.set(x,window::height-y);
    }

    if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP)
    {
        cursor::highlighting=false;
        cursor::right_click=false;
        cursor::right_up.set(x,window::height-y);
        cursor::right_dragging=false;
    }
}

//The only way to check if no objects are being clicked is by checking every object
void ui::check_clicked()
{
    bool left_clicked = true;
    for(unsigned a=0; a<game::rts_objects.size(); a++)
    {
        if(left_clicked && game::rts_objects[a]->left_clicked())
            left_clicked=true;
        else
            left_clicked=false;
    }
    cursor::left_clicked_an_object = left_clicked;
    bool right_clicked=true;
    for(unsigned a=0; a<game::rts_objects.size(); a++)
    {
        if(right_clicked && game::rts_objects[a]->right_clicked())
            right_clicked=true;
        else
            right_clicked=false;
    }
    cursor::right_clicked_an_object = right_clicked;
    bool grabbed=true;
    for(unsigned a=0; a<game::draggable_objects.size(); a++)
    {
        if(grabbed && game::draggable_objects[a]->grabbed())
            grabbed=true;
        else
            grabbed=false;
    }
    cursor::grabbed_an_object = grabbed;
}

//This is called when user clicks and drags
void ui::mouse_drag(int x, int y)
{
    if(cursor::left_click)
    {
        if(!cursor::left_clicked_an_object && !cursor::grabbed_an_object)
        {
            //this condition makes it so that the user has to make a rectangle larger than 10x10. That way, highlighting is less sensitive
            if(isgreater(x,cursor::left_down.x+10) && isless((window::height - y),cursor::left_down.y+10))
                cursor::highlighting=true;
            else
                cursor::highlighting=false;
        }
        else
            cursor::highlighting=false;
        cursor::left_drag.set(x,(window::height-y));
        //see if drag point is different from start point
        if((isless(x,cursor::left_down.x)||isgreater(x,cursor::left_down.x))
           &&(isless((window::height - y),cursor::left_down.y)||isgreater((window::height - y),cursor::left_down.y)))
            cursor::left_dragging=true;
        else
            cursor::left_dragging=false;
    }
    else
        cursor::left_dragging=false;

    if(cursor::right_click)
    {
        cursor::highlighting=false;
        cursor::right_drag.set(x,(window::height-y));
        //see if drag point is different from start point
        if((isless(x,cursor::right_down.x)||isgreater(x,cursor::right_down.x))
           &&(isless((window::height - y),cursor::right_down.y)||isgreater((window::height - y),cursor::right_down.y)))
            cursor::right_dragging=true;
        else
            cursor::right_dragging=false;
    }
    else
        cursor::right_dragging=false;
}

void ui::key_pressed(unsigned char key, int x, int y)
{
    key_states[key] = true;
}

void ui::key_released(unsigned char key, int x, int y)
{
    key_states[key] = false;
}

void ui::key_operations(void)
{
    if(strcmp(cursor::left_clicked_object->type, "physics object")==0)
    {
        if(key_states['w'] || key_states['W'])
            game::physics_objects[cursor::selected_object]->move_forward();

        if(key_states['s'] || key_states['S'])
            game::physics_objects[cursor::selected_object]->move_back();

        if(key_states['a'] || key_states['A'])
            game::physics_objects[cursor::selected_object]->move_left();

        if(key_states['d'] || key_states['D'])
            game::physics_objects[cursor::selected_object]->move_right();

        if(key_states['q'] || key_states['Q'])
            game::physics_objects[cursor::selected_object]->turn_left();

        if(key_states['e'] || key_states['E'])
            game::physics_objects[cursor::selected_object]->turn_right();

        if(key_states[32])//spacebar
        {
            if(!game::projectiles[cursor::selected_object].fired)
                game::projectiles[cursor::selected_object].fire(*game::physics_objects[cursor::selected_object]);
        }
    }
    if(key_states['i'] || key_states['I'])
    {
        if(toggle_overlay)
        {
            if(temp_toggle)
            std::clog<<"toggled information overlay off\n";
            temp_toggle=false;
        }
        else
        {
            if(!temp_toggle)
            std::clog<<"toggled information overlay on\n";
            temp_toggle=true;
        }
    }
    else
        toggle_overlay=temp_toggle;

    if(key_states[27])//escape
    {
        std::clog<<"exiting...\n";
        exit(0);
    }
}
