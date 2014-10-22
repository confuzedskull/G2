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
#ifndef WINDOW_H
#define WINDOW_H
#include "point.h"

namespace window
{
extern int width;
extern int height;
extern point2i center;
extern int position_x;
extern int position_y;
extern double refresh_rate;
void change_size(int w, int h);
void initialize();
void render();
void update();
};
#endif // WINDOW_H
