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

#ifndef CLICKABLE_H
#define CLICKABLE_H
#include "physics_object.h"
//A clickable object interfaces with the cursor
class clickable_object: public physics_object
{
    public:
    bool selected;//marks this object as selected or not
    bool left_clicked();//checks if the cursor left clicked inside this object
    bool right_clicked();//checks if the cursor right clicked inside this object
    bool highlighted();//checks if this object lies within the highlighting box
    bool grabbed();//checks if this object was grabbed by the cursor
    void mouse_function();//performs a variety of actions dependent on cursor interaction
    void render();//makes the object visible
    clickable_object();
};
#endif // CLICKABLE_H
