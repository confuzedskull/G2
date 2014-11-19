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

#include "physics_object.h"
#include "game.h"
#include "window.h"
#include <iostream>
#include <fstream>
#include <math.h>

point2i physics_object::origin = point2i(window::width*0.9,window::height*0.6);

std::string physics_object::get_type()
{
    return "physics object";
}

void physics_object::calc_delta_time()
{
    if(abs(position.x-rest_position.x)>0)
    {
        start_time[0]=game::time;
        delta_time[0]=stop_time[0]-start_time[0];
    }
    else
    {
        stop_time[0]=game::time;
        delta_time[0]=0.0f;
    }

    if(abs(position.y-rest_position.y)>0)
    {
        start_time[1]=game::time;
        delta_time[1]=stop_time[1]-start_time[1];
    }
    else
    {
        stop_time[1]=game::time;
        delta_time[1]=0.0f;
    }

    if(isgreaterequal(fabs(velocity[1].x-velocity[0].x),0.01f))//at least difference of 0.01
    {
        start_time[2]=game::time;
        delta_time[2]=stop_time[2]-start_time[2];
    }
    else//difference of 0.01 or less is negligible
    {
        stop_time[2]=game::time;
        delta_time[2]=0.0f;
    }

    if(isgreaterequal(fabs(velocity[1].y-velocity[0].y),0.01f))//at least difference of 0.01
    {
        start_time[3]=game::time;
        delta_time[3]=stop_time[3]-start_time[3];
    }
    else//difference of 0.01 or less is negligible
    {
        stop_time[3]=game::time;
        delta_time[3]=0.0f;
    }

    if(isgreaterequal(fabs(rotation-rest_rotation),0.01f))//at least difference of 0.01
    {
        start_time[4]=game::time;
        delta_time[4]=stop_time[4]-start_time[4];
    }
    else//difference of 0.01 or less is negligible
    {
        stop_time[4]=game::time;
        delta_time[4]=0.0f;
    }

    if(isgreaterequal(fabs(angular_velocity[1]-angular_velocity[0]),0.01f))//at least difference of 0.01
    {
        start_time[5]=game::time;
        delta_time[5]=stop_time[5]-start_time[5];
    }
    else//difference of 0.01 or less is negligible
    {
        stop_time[5]=game::time;
        delta_time[5]=0.0f;
    }
}
void physics_object::calc_velocity()
{
    if(isnormal(delta_time[0]))//makes sure it's not zero,infinity, or NaN
        velocity[0].x=(rest_position.x-position.x)/delta_time[0];
    velocity[1].x=velocity[0].x+momentum.x;//set final velocity

    if(isnormal(delta_time[1]))//makes sure it's not zero,infinity, or NaN
        velocity[0].y=(rest_position.y-position.y)/delta_time[1];
    velocity[1].y=velocity[0].y+momentum.y;//set final velocity

    if(isnormal(delta_time[4]))//makes sure it's not zero,infinity, or NaN
        angular_velocity[0]=(rest_rotation-rotation)/delta_time[4];
    angular_velocity[1]=angular_velocity[0]+angular_momentum;//set final velocity
}

void physics_object::calc_acceleration()
{
    if(isnormal(delta_time[2]))//makes sure it's not zero,infinity, or NaN
        acceleration.x=(velocity[0].x-velocity[1].x)/delta_time[2];

    if(isnormal(delta_time[3]))//makes sure it's not zero,infinity, or NaN
        acceleration.y=(velocity[0].y-velocity[1].y)/delta_time[3];

    if(isnormal(delta_time[5]))//makes sure it's not zero,infinity, or NaN
        angular_acceleration=(angular_velocity[0]-angular_velocity[1])/delta_time[5];
}

void physics_object::calc_force()
{
    force.x=mass*acceleration.x;
    force.y=mass*acceleration.y;
}
//calculate initial momentum
void physics_object::calc_momentum()
{
    momentum.x=mass*velocity[0].x;
    momentum.y=mass*velocity[0].y;
    angular_momentum=mass*angular_velocity[0];
}
//calculate momentum after elastic collision with object p
void physics_object::calc_momentum(physics_object p)
{
    momentum.x=momentum.x+p.momentum.x-(p.mass*p.velocity[1].x);
    momentum.y=momentum.y+p.momentum.y-(p.mass*p.velocity[1].y);
}

void physics_object::inertia()
{
    /*if(isgreaterequal(fabs(momentum.x),0.01f))
    {
        position.x+=momentum.x;
        moving_left=true;
        moving_right=true;
    }

    if(isgreaterequal(fabs(momentum.y),0.01f))
    {
        position.y+=momentum.y;
        moving_forward=true;
        moving_backward=true;
    }*/

    if(isgreaterequal(fabs(angular_momentum),0.01f))
    {
        rotation+=angular_momentum;
        turning_left=true;
        turning_right=true;
    }
}

void physics_object::physics()
{
    calc_delta_time();
    calc_velocity();
    calc_acceleration();
    calc_force();
    calc_momentum();
    reset_motion();
}

void physics_object::update()
{
    movable_object::update();
    physics();
    mouse_function();
}

void physics_object::load()
{
    std::clog<<file_name;
    std::ifstream object_file(file_name);//access file by name
    if(object_file.bad())//make sure the file is there
        return;
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
    object_file>>visible;
    object_file>>selected;
    //load movable object properties
    object_file>>speed;
    object_file>>degrees_rotated;
    object_file>>rest_rotation;
    object_file>>rally_set;
    object_file>>moving_forward;
    object_file>>moving_backward;
    object_file>>moving_left;
    object_file>>moving_right;
    object_file>>turning_right;
    object_file>>turning_left;
    char first_char;
    while(first_char!='\n')//empty space detected
    {
        //load the cued actions
        first_char=object_file.peek();//check the first character of the line
        std::array<int,3> action;
        object_file>>action[0]>>action[1]>>action[2];//add action number, times to do, and  times performed
        action_cue.push(action);//add action to the cue
    }
    //load tangible object properties
    object_file>>touching[0];
    object_file>>touching[1];
    object_file>>touching[2];
    object_file>>touching[3];
    object_file>>collided;
    //load physics objects properties
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
    object_file.close();
    std::clog<<"object#"<<number<<"(physics object)"<<" loaded.\n";
}

void physics_object::save()
{
    std::stringstream filename;
    filename<<"./data/objects/object#"<<number<<".pso";
    std::ofstream object_file(filename.str());
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
    object_file<<visible<<std::endl;
    object_file<<selected<<std::endl;
    //save movable object properties
    object_file<<speed<<std::endl;
    object_file<<degrees_rotated<<std::endl;
    object_file<<rest_rotation<<std::endl;
    object_file<<rally_set<<std::endl;
    object_file<<moving_forward<<std::endl;
    object_file<<moving_backward<<std::endl;
    object_file<<moving_left<<std::endl;
    object_file<<moving_right<<std::endl;
    object_file<<turning_right<<std::endl;
    object_file<<turning_left<<std::endl;
    for(int i=0;i<action_cue.size();i++)
        object_file<<action_cue.front().at(0)<<' '<<action_cue.front().at(1)<<' '<<action_cue.front().at(2)<<std::endl;
    object_file<<std::endl;//add an empty line to signal end of action cue
    //save tangible object properties
    object_file<<touching[0]<<std::endl;
    object_file<<touching[1]<<std::endl;
    object_file<<touching[2]<<std::endl;
    object_file<<touching[3]<<std::endl;
    object_file<<collided<<std::endl;
    //save physics object properties
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
    object_file.close();
    std::clog<<"object#"<<number<<"(physics object)"<<" saved.\n";
}

physics_object::physics_object()
{
    mass=0.015f;//If this is too high, objects might just disappear off the screen
    fill_color=GRAY;
    position.set((float)origin.x, (float)origin.y);
    set_dimensions(32.0f,32.0f);
    velocity[0].x=0.00f;
    velocity[0].y=0.00f;
    angular_velocity[0]=0.00f;
    std::clog<<"object#"<<number<<"(physics object)"<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
