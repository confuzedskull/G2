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

#ifndef DRAGGABLE_OBJECT_H
#define DRAGGABLE_OBJECT_H
#include "clickable_object.h"
#include "tangible_object.h"

class draggable_object: public clickable_object, public tangible_object
{
    public:
        static void add_to_game();
        bool grabbed();//checks if this object was grabbed by the cursor
        void mouse_function();//performs a variety of actions dependent on cursor interaction
        void update();
        draggable_object();
};

#endif // DRAGGABLE_OBJECT_H
