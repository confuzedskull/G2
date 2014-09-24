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
#include <cstring>
#include <stdio.h>
#include <math.h>
//initialize variables
bool* ui::key_states=new bool[256];
bool ui::temp_toggle=false;
bool ui::toggle_text=false;
char ui::text0[30] = "";
char ui::text1[30] = "";
char ui::text2[20] = "";
char ui::text3[30] = "";
char ui::text4[30] = "";
char ui::text5[20] = "";
char ui::text6[10] = "";
char ui::text7[10] = "";
char ui::text8[10] = "";
char ui::text9[10] = "";
char ui::text10[20] = "";
char ui::text11[20] = "";
char ui::text12[20] = "";

//This prints text of rgba color at x,y on the screen
void ui::glutPrint(float x, float y, void* font, char* text, color c)
{
    if(!text || !strlen(text)) return;
    bool blending = false;
    if(glIsEnabled(GL_BLEND)) blending = true;
    glEnable(GL_BLEND);
    glColor4f(c.r,c.g,c.b,c.a);
    glRasterPos2f(x,y);
    while (*text)
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
    if(!blending) glDisable(GL_BLEND);
}

void ui::print_text()
{
    sprintf(text0,"object no.%i", game::clickable_objects[cursor::selected_object].number);
    glutPrint (window::width/40,window::height-20, GLUT_BITMAP_HELVETICA_12, text0, BLACK);

    sprintf(text1,"current:%.2f,%.2f", game::clickable_objects[cursor::selected_object].current.x,game::clickable_objects[cursor::selected_object].current.y);
    glutPrint (window::width/40,window::height-40, GLUT_BITMAP_HELVETICA_12, text1, BLACK);

    sprintf(text2,"resting: %.2f, %.2f",game::clickable_objects[cursor::selected_object].rest.x,game::clickable_objects[cursor::selected_object].rest.y);
    glutPrint (window::width/40,window::height-60, GLUT_BITMAP_HELVETICA_12, text2, BLACK);

    sprintf(text3,"initial velocity: %.2f,%.2f",game::clickable_objects[cursor::selected_object].velocity[0].x,game::clickable_objects[cursor::selected_object].velocity[0].y);
    glutPrint (window::width/40,window::height-80, GLUT_BITMAP_HELVETICA_12, text3, BLACK);

    sprintf(text4,"final velocity: %.2f,%.2f",game::clickable_objects[cursor::selected_object].velocity[1].x,game::clickable_objects[cursor::selected_object].velocity[1].y);
    glutPrint (window::width/40,window::height-100, GLUT_BITMAP_HELVETICA_12, text4, BLACK);

    sprintf(text5,"delta_time x: %.2f y:%.2f",game::clickable_objects[cursor::selected_object].delta_time[0],game::clickable_objects[cursor::selected_object].delta_time[1]);
    glutPrint (window::width/40,window::height-120, GLUT_BITMAP_HELVETICA_12, text5, BLACK);

    sprintf(text6,"momentum: %.2f %.2f",game::clickable_objects[cursor::selected_object].momentum.x,game::clickable_objects[cursor::selected_object].momentum.y);
    glutPrint (window::width/40,window::height-140, GLUT_BITMAP_HELVETICA_12, text6, BLACK);

    sprintf(text7,"force: %.2f %.2f",game::clickable_objects[cursor::selected_object].force.x,game::clickable_objects[cursor::selected_object].force.y);
    glutPrint (window::width/40,window::height-160, GLUT_BITMAP_HELVETICA_12, text7, BLACK);

    sprintf(text8,"acceleration: %.2f %.2f",game::clickable_objects[cursor::selected_object].acceleration.x,game::clickable_objects[cursor::selected_object].acceleration.y);
    glutPrint (window::width/40,window::height-180, GLUT_BITMAP_HELVETICA_12, text8, BLACK);

    sprintf(text9,"delta_time velocity: %.2f %.2f",game::clickable_objects[cursor::selected_object].delta_time[2],game::clickable_objects[cursor::selected_object].delta_time[3]);
    glutPrint (window::width/40,window::height-200, GLUT_BITMAP_HELVETICA_12, text9, BLACK);

    sprintf(text10,"touching object no. L:%d R:%d T:%d B:%d",game::clickable_objects[cursor::selected_object].touching[0], game::clickable_objects[cursor::selected_object].touching[1], game::clickable_objects[cursor::selected_object].touching[2],game::clickable_objects[cursor::selected_object].touching[3]);
    glutPrint (window::width/40,window::height-220, GLUT_BITMAP_HELVETICA_12, text10, BLACK);

    sprintf(text11,"game time: %.2f",game::time);
    glutPrint (window::width/40,window::height-240, GLUT_BITMAP_HELVETICA_12, text11, BLACK);

    sprintf(text12,"click:%.2f,%.2f",cursor::left_down.x,cursor::left_down.y);
    glutPrint (window::width/40,window::height-260, GLUT_BITMAP_HELVETICA_12, text12, BLACK);
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
    for(int a=0; a<game::clickable_objects.size(); a++)
    {
        if(left_clicked && game::clickable_objects[a].left_clicked())
        {
            left_clicked=true;
        }
        else
        {
            left_clicked=false;
        }
    }
    cursor::left_clicked_an_object = left_clicked;
    bool right_clicked=true;
    for(int a=0; a<game::clickable_objects.size(); a++)
    {
        if(right_clicked && game::clickable_objects[a].right_clicked())
            right_clicked=true;
        else
            right_clicked=false;
    }
    cursor::right_clicked_an_object = right_clicked;
    bool grabbed=true;
    for(int a=0; a<game::clickable_objects.size(); a++)
    {
        if(grabbed && game::clickable_objects[a].grabbed())
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
    key_states[key] = true; // Set the state of the current key to pressed
}

void ui::key_up(unsigned char key, int x, int y)
{
    key_states[key] = false; // Set the state of the current key to not pressed
}

void ui::key_operations(void)
{
    if(key_states['w'] || key_states['W'])
    game::clickable_objects[cursor::selected_object].move_forward();

    if(key_states['s'] || key_states['S'])
    game::clickable_objects[cursor::selected_object].move_back();

    if(key_states['a'] || key_states['A'])
    game::clickable_objects[cursor::selected_object].move_left();

    if(key_states['d'] || key_states['D'])
    game::clickable_objects[cursor::selected_object].move_right();

    if(key_states['q'] || key_states['Q'])
    game::clickable_objects[cursor::selected_object].turn_left();

    if(key_states['e'] || key_states['E'])
    game::clickable_objects[cursor::selected_object].turn_right();

    if(key_states['i'] || key_states['I'])
    {
        if(toggle_text)
            temp_toggle=false;
        else
            temp_toggle=true;
    }
    else
        toggle_text=temp_toggle;
// spacebar
    if(key_states[32])
    {
        if(!game::projectiles[cursor::selected_object].fired)
            game::projectiles[cursor::selected_object].fire(game::clickable_objects[cursor::selected_object]);
    }
//escape
    if (key_states[27])
        exit(0);
}
