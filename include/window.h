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
class window
{
    public:
        static int width;
        static int height;
        static int position_x;
        static int position_y;
        static double refresh_rate;
        static void change_size(int w, int h);
        static void initialize();
        static void render_scene();
        static void update_scene();
};
#endif // WINDOW_H
