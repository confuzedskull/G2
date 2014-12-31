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

#include "model.h"
#include "cursor.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string model::default_texture = "";
std::string model::default_mask = "";
std::string model::default_click_sound = "";
std::string model::default_hover_sound = "";
std::string model::default_collision_sound = "";
std::string model::default_movement_sound = "";
int model::default_width = 64;
int model::default_height = 64;
bool model::enable_fill = false;
bool model::enable_border = false;
bool model::enable_texture = true;
bool model::enable_mask = true;
bool model::enable_dragging = false;
bool model::enable_physics = false;
bool model::enable_rts_controls = false;
bool model::enable_keyboard_controls = false;
color model::default_fill_color = GRAY;
color model::default_border_color = BLACK;

std::string model::get_type()
{
    return "model";
}

void model::mouse_function()
{
    left_click_function();
    highlight_function();
    if(draggable)
        drag_function();
    if(rts_controls)
    {
        if(selected && cursor::right_clicking && !right_clicked())
        {
            //get rid of previous rally point
            if(rally_set)
                delete rally;
            //move to right click
            rally = new point2f(cursor::right_down.x,cursor::right_down.y);
            rally_set=true;
        }
        if(cursor::right_dragging && !right_clicked())
        {
            //get rid of previous rally point
            if(rally_set)
                delete rally;
            //move to right drag
            rally = new point2f(cursor::right_drag.x,cursor::right_drag.y);
            rally_set=true;
        }
    }
}

void model::load()
{
    std::clog<<file_name;
    std::ifstream object_file(file_name);//access file by name
    if(object_file.bad())//make sure the file is there
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //load basic object properties
    object_file>>position.x>>position.y;
    object_file>>rotation;
    object_file>>width>>height;
    object_file>>fill_color.r>>fill_color.g>>fill_color.b;
    object_file>>marker_color.r>>marker_color.g>>marker_color.b;
    object_file>>border_color.r>>border_color.g>>border_color.b;
    object_file>>filled;
    object_file>>bordered;
    object_file>>textured;
    object_file>>masked;
    object_file>>visible;
    object_file>>selected;
    object_file>>muted;
    object_file>>texture;
    object_file>>mask;
    //load clickable object properties
    object_file>>enabled;
    object_file>>draggable;
    object_file>>click_sound;
    object_file>>hover_sound;
    //load movable object properties
    object_file>>movement_sound;
    object_file>>speed;
    object_file>>degrees_rotated;
    object_file>>rally_set;
    object_file>>moving_forward;
    object_file>>moving_backward;
    object_file>>moving_left;
    object_file>>moving_right;
    object_file>>turning_right;
    object_file>>turning_left;
    char first_char=' ';
    while(first_char>0)//not newline or out of bounds
    {
        //load the cued actions
        object_file.get();//eat the null character
        first_char=object_file.peek();//check the first character of the line
        if(first_char=='\n')
            break;
        std::array<int,3> action;
        object_file>>action[0]>>action[1]>>action[2];//add action number, times to do, and  times performed
        action_cue.push(action);//add action to the cue
    }
    //load tangible object properties
    object_file>>touched_side[0];
    object_file>>touched_side[1];
    object_file>>touched_side[2];
    object_file>>touched_side[3];
    object_file>>collided;
    object_file>>collision_sound;
    //load physics objects properties
    object_file>>rest_position.x>>rest_position.y;
    object_file>>rest_rotation;
    object_file>>mass;
    object_file>>delta_time[0];
    object_file>>delta_time[1];
    object_file>>delta_time[2];
    object_file>>delta_time[3];
    object_file>>delta_time[4];
    object_file>>delta_time[5];
    object_file>>velocity[0].x>>velocity[0].y;
    object_file>>velocity[1].x>>velocity[1].y;
    object_file>>angular_velocity[0];
    object_file>>angular_velocity[1];
    object_file>>acceleration.x>>acceleration.y;
    object_file>>angular_acceleration;
    object_file>>momentum.x>>momentum.y;
    object_file>>angular_momentum;
    object_file>>force.x>>force.y;
    object_file>>friction;
    object_file>>energy[0];
    object_file>>energy[1];
    //save model properties
    object_file>>physics_enabled;
    object_file>>rts_controls;
    object_file>>keyboard_controls;
    object_file.close();
    std::clog<<"object#"<<number<<"(physics object)"<<" loaded.\n";
}

void model::save()
{
    std::stringstream filename;
    filename<<"./data/models/object#"<<number<<".mdl";
    std::ofstream object_file(filename.str());
    if(object_file.bad())
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //save basic object properties
    object_file<<position.x<<' '<<position.y<<std::endl;
    object_file<<rotation<<std::endl;
    object_file<<width<<' '<<height<<std::endl;
    object_file<<fill_color.str()<<std::endl;
    object_file<<marker_color.str()<<std::endl;
    object_file<<border_color.str()<<std::endl;
    object_file<<filled<<std::endl;
    object_file<<bordered<<std::endl;
    object_file<<textured<<std::endl;
    object_file<<masked<<std::endl;
    object_file<<visible<<std::endl;
    object_file<<selected<<std::endl;
    object_file<<muted<<std::endl;
    object_file<<texture<<std::endl;
    object_file<<mask<<std::endl;
    //save clickable object properties
    object_file<<enabled<<std::endl;
    object_file<<draggable<<std::endl;
    object_file<<click_sound<<std::endl;
    object_file<<hover_sound<<std::endl;
    //save movable object properties
    object_file<<movement_sound<<std::endl;
    object_file<<speed<<std::endl;
    object_file<<degrees_rotated<<std::endl;
    object_file<<rally_set<<std::endl;
    object_file<<moving_forward<<std::endl;
    object_file<<moving_backward<<std::endl;
    object_file<<moving_left<<std::endl;
    object_file<<moving_right<<std::endl;
    object_file<<turning_right<<std::endl;
    object_file<<turning_left<<std::endl;
    while(!action_cue.empty())
    {
        object_file<<action_cue.front().at(0)<<' '<<action_cue.front().at(1)<<' '<<action_cue.front().at(2)<<std::endl;
        action_cue.pop();
    }
    object_file<<std::endl;//add an empty line to signal end of action cue
    //save tangible object properties
    object_file<<touched_side[0]<<std::endl;
    object_file<<touched_side[1]<<std::endl;
    object_file<<touched_side[2]<<std::endl;
    object_file<<touched_side[3]<<std::endl;
    object_file<<collided<<std::endl;
    object_file<<collision_sound<<std::endl;
    //save physics object properties
    object_file<<rest_position.x<<' '<<rest_position.y<<std::endl;
    object_file<<rest_rotation<<std::endl;
    object_file<<mass<<std::endl;
    object_file<<delta_time[0]<<std::endl;
    object_file<<delta_time[1]<<std::endl;
    object_file<<delta_time[2]<<std::endl;
    object_file<<delta_time[3]<<std::endl;
    object_file<<delta_time[4]<<std::endl;
    object_file<<delta_time[5]<<std::endl;
    object_file<<velocity[0].x<<' '<<velocity[0].y<<std::endl;
    object_file<<velocity[1].x<<' '<<velocity[1].y<<std::endl;
    object_file<<angular_velocity[0]<<std::endl;
    object_file<<angular_velocity[1]<<std::endl;
    object_file<<acceleration.x<<' '<<acceleration.y<<std::endl;
    object_file<<angular_acceleration<<std::endl;
    object_file<<momentum.x<<' '<<momentum.y<<std::endl;
    object_file<<angular_momentum<<std::endl;
    object_file<<force.x<<' '<<force.y<<std::endl;
    object_file<<friction<<std::endl;
    object_file<<energy[0]<<std::endl;
    object_file<<energy[1]<<std::endl;
    //save model properties
    object_file<<physics_enabled<<std::endl;
    object_file<<rts_controls<<std::endl;
    object_file<<keyboard_controls;
    object_file.close();
    std::clog<<"object#"<<number<<"(model)"<<" saved.\n";
}

void model::sync()
{
    if(physics_enabled)
    {
        apply_friction();
        apply_inertia();
    }
    clickable_object::sync();
    perform_actions()||move_to_rally();
}

void model::update()
{
    if(physics_enabled)
        calc_physics();
    movable_object::update();
    tangible_object::update();
    clickable_object::update();
}
model::model()
{
    filled=false;
    textured=true;
    masked=true;
    draggable=enable_dragging;
    physics_enabled=enable_physics;
    rts_controls=enable_rts_controls;
    keyboard_controls=enable_keyboard_controls;
    fill_color=default_fill_color;
    border_color=default_border_color;
    set_dimensions(default_width,default_height);
    set_texture(default_texture);
    set_mask(default_mask);
    set_click_sound(default_click_sound);
    set_hover_sound(default_hover_sound);
    set_collision_sound(default_collision_sound);
    set_movement_sound(default_movement_sound);
}
