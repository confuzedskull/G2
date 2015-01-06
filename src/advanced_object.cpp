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

#include "advanced_object.h"
#include "cursor.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string advanced_object::default_texture = "";
std::string advanced_object::default_mask = "";
std::string advanced_object::default_clicksound = "";
std::string advanced_object::default_hoversound = "";
std::string advanced_object::default_collisionsound = "";
std::string advanced_object::default_movementsound = "";
int advanced_object::default_width = 64;
int advanced_object::default_height = 64;
bool advanced_object::enable_fill = false;
bool advanced_object::enable_border = false;
bool advanced_object::enable_texture = true;
bool advanced_object::enable_mask = true;
bool advanced_object::enable_physics = false;
bool advanced_object::enable_rtscontrols = false;
bool advanced_object::enable_keyboardcontrols = false;
color advanced_object::default_fillcolor = GRAY;
color advanced_object::default_bordercolor = BLACK;

std::string advanced_object::get_type()
{
    return "advanced object";
}

void advanced_object::add_component(smart_object* component)
{
    components.push_back(component);
}

void advanced_object::mouse_function()
{
    leftclick_function();
    highlight_function();
    if(drag_detection)
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

void advanced_object::load()
{
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
    char first_char=' ';
     //load custom properties
    while(first_char>0)//not newline or out of bounds
    {
        std::string name;
        int value;
        object_file.get();//eat the null character
        first_char=object_file.peek();//check the first character of the line
        if(first_char=='\n')
            break;
        object_file>>name>>value;
        add_property(name,value);
    }
    //load interactive object properties
    object_file>>click_detection;
    object_file>>drag_detection;
    object_file>>hover_detection;
    object_file>>highlight_detection;
    object_file>>click_sound;
    object_file>>hover_sound;
    //load mobile object properties
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
    first_char=' ';
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
    //load smart object properties
    object_file>>touched_side[0];
    object_file>>touched_side[1];
    object_file>>touched_side[2];
    object_file>>touched_side[3];
    object_file>>collided;
    object_file>>collision_sound;
    //load physical object properties
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
    //save advanced_object properties
    object_file>>physics_enabled;
    object_file>>rts_controls;
    object_file>>keyboard_controls;
    object_file.close();
    std::clog<<"object#"<<number<<"(advanced object)"<<" loaded.\n";
}

void advanced_object::save()
{
    std::stringstream filename;
    filename<<"./data/objects/object#"<<number<<".avo";
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
    for(auto p:properties)
        object_file<<p.first<<' '<<p.second<<std::endl;
    object_file<<std::endl;
    //save interactive object properties
    object_file<<click_detection<<std::endl;
    object_file<<drag_detection<<std::endl;
    object_file<<hover_detection<<std::endl;
    object_file<<highlight_detection<<std::endl;
    object_file<<click_sound<<std::endl;
    object_file<<hover_sound<<std::endl;
    //save mobile object properties
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
    //save smart object properties
    object_file<<touched_side[0]<<std::endl;
    object_file<<touched_side[1]<<std::endl;
    object_file<<touched_side[2]<<std::endl;
    object_file<<touched_side[3]<<std::endl;
    object_file<<collided<<std::endl;
    object_file<<collision_sound<<std::endl;
    //save physical object properties
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
    //save advanced object properties
    object_file<<physics_enabled<<std::endl;
    object_file<<rts_controls<<std::endl;
    object_file<<keyboard_controls;
    object_file.close();
    std::clog<<"object#"<<number<<"(advanced object)"<<" saved.\n";
}

void advanced_object::sync()
{
    if(physics_enabled)
    {
        apply_friction();
        apply_inertia();
    }
    interactive_object::sync();
    perform_actions()||moveto_rally();
    for(auto c:components)
        c->sync();
}

void advanced_object::update()
{
    if(physics_enabled)
        calc_physics();
    mobile_object::update();
    smart_object::update();
    interactive_object::update();
    for(auto c:components)
        c->update();
}
advanced_object::advanced_object()
{
    filled=false;
    textured=true;
    masked=true;
    click_detection=enable_clicking;
    drag_detection=enable_dragging;
    hover_detection=enable_hovering;
    highlight_detection=enable_highlighting;
    physics_enabled=enable_physics;
    rts_controls=enable_rtscontrols;
    keyboard_controls=enable_keyboardcontrols;
    fill_color=default_fillcolor;
    border_color=default_bordercolor;
    set_dimensions(default_width,default_height);
    set_texture(default_texture);
    set_mask(default_mask);
    set_clicksound(default_clicksound);
    set_hoversound(default_hoversound);
    set_collisionsound(default_collisionsound);
    set_movementsound(default_movementsound);
}
