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
#include "controls.h"
#include "cursor.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

//initialize variables
int ui::overlay_margin = 10;

void ui::show_text()
{
    if(game::state==PLAYING)
    game::play_scene->show_text();
}

void ui::hide_text()
{
    if(game::state==PLAYING)
    game::play_scene->hide_text();
}

void ui::update_text()
{
    using namespace std;
    label* object_info = game::play_scene->labels[0];
    if(object_info->visible && !cursor::selected_objects.empty())
    {
        unsigned index = cursor::selected_object;
        object_info->clear();
        object_info->add_line("object #:"+to_string(cursor::left_clicked_object->get_number()));
        object_info->add_line("type: "+cursor::left_clicked_object->get_type());
        object_info->add_line("dimensions: "+to_string(cursor::left_clicked_object->get_width())+'X'+to_string(cursor::left_clicked_object->get_height()));
        object_info->add_line("rotation: "+to_string(cursor::left_clicked_object->get_rotation()));
        object_info->add_line("current position: "+to_string(cursor::left_clicked_object->get_position().x)+", "+to_string(cursor::left_clicked_object->get_position().y));
        if(cursor::left_clicked_object->get_type()=="physics object")//display the following if a physics object is selected
        {
            physics_object* po = game::current_scene->physics_objects[index];
            object_info->add_line("resting position: "+to_string(po->get_resting().x)+", "+to_string(po->get_resting().y));
            object_info->add_line("mass: "+to_string(po->mass));
            object_info->add_line("speed: "+to_string(po->speed));
            object_info->add_line("time moving: "+to_string(po->delta_time[0])+", "+to_string(po->delta_time[1]));
            object_info->add_line("initial velocity: "+to_string(po->velocity[0].x)+", "+to_string(po->velocity[0].y));
            object_info->add_line("final velocity: "+to_string(po->velocity[1].x)+", "+to_string(po->velocity[1].y));
            object_info->add_line("time accelerating: "+to_string(po->delta_time[2])+", "+to_string(po->delta_time[3]));
            object_info->add_line("acceleration: "+to_string(po->acceleration.x)+", "+to_string(po->acceleration.y));
            object_info->add_line("momentum: "+to_string(po->momentum.x)+", "+to_string(po->momentum.y));
            object_info->add_line("force: "+to_string(po->force.x)+", "+to_string(po->force.y));
            object_info->add_line("object touching side L:"+to_string(po->touched_side[0])+"R:"+to_string(po->touched_side[1])
                                                        +"T:"+to_string(po->touched_side[2])+"B:"+to_string(po->touched_side[3]));
        }
        if(cursor::left_clicked_object->get_type()=="draggable object")//display the following if a draggable object is selected
        {
            draggable_object* draggable=game::current_scene->draggable_objects[index];
            object_info->add_line("object touching side"+to_string(draggable->touched_side[0])+to_string(draggable->touched_side[1])+to_string(draggable->touched_side[2])+to_string(draggable->touched_side[3]));
        }
        if(cursor::left_clicked_object->get_type()=="rts object")//display the following if a RTS object is selected
        {
            rts_object* rtso=game::current_scene->rts_objects[index];
            object_info->add_line("rally point: "+to_string(rtso->get_rally()->x)+", "+to_string(rtso->get_rally()->y));
            object_info->add_line("speed: "+to_string(rtso->speed));
            object_info->add_line("object touching side L:"+to_string(rtso->touched_side[0])+"R:"+to_string(rtso->touched_side[1])+"T:"+to_string(rtso->touched_side[2])+"B:"+to_string(rtso->touched_side[3]));
        }
    }
    label* game_info = game::play_scene->labels[1];
    if(game_info->visible)
    {
        game_info->clear();
        game_info->add_line("game time: "+to_string(game::time));
        game_info->add_line("mouse move: "+to_string(cursor::passive.x)+", "+to_string(cursor::passive.y));
        game_info->add_line("mouse click: "+to_string(cursor::left_down.x)+", "+to_string(cursor::left_down.y));
        game_info->add_line("mouse drag: "+to_string(cursor::left_drag.x)+", "+to_string(cursor::left_drag.y));
    }
}
