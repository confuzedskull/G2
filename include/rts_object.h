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

#ifndef RTS_OBJECT_H
#define RTS_OBJECT_H
#include "clickable_object.h"
#include "tangible_object.h"

class rts_object: public clickable_object, public tangible_object
{
    public:
        static point2f origin;
        std::string get_type() override;
        std::string get_filename() override;
        void mouse_function() override;//performs a variety of actions dependent on cursor interaction
        void update() override;
        void load();
        void save();
        rts_object();
};

#endif // RTS_OBJECT_H
