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
#ifndef UI_H
#define UI_H
#include "color.h"
namespace ui
{
        extern bool* key_states; //stores each on/off state of a keyboard key
        extern bool temp_toggle;
        extern bool toggle_text;
        //text for information overlay
        extern char text0[30];
        extern char text1[30];
        extern char text2[20];
        extern char text3[20];
        extern char text4[20];
        extern char text5[20];
        extern char text6[10];
        extern char text7[10];
        extern char text8[10];
        extern char text9[10];
        extern char text10[20];
        extern char text11[20];
        extern char text12[20];
        void glutPrint(float x, float y, void* font, char* text, color c);
        void print_text();
        void mouse_click(int button, int state, int x, int y);
        void check_clicked();
        void mouse_drag(int x, int y);
        void key_pressed(unsigned char key, int x, int y);
        void key_up(unsigned char key, int x, int y);
        void key_operations(void);
}
#endif // UI_H
