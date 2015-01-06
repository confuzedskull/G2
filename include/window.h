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
#ifndef WINDOW_H
#define WINDOW_H
#include "point.h"
#include <string>

//This namespace contains variables and functions related to function
namespace window
{
    extern int width;
    extern int height;
    extern int refresh_rate;//frequency of screen updates (in hertz)
    extern point2i center;
    extern point2i position;//this refers to the upper left corner of the window
    extern std::string title;
    void change_size(int w, int h);
    void initialize();
    void render();
    void update();
};
#endif // WINDOW_H
