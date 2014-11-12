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

point2f physics_object::origin = point2f(window::width*0.9,window::height*0.6);

void physics_object::calc_delta_time()
{
    if(isgreaterequal(fabs(position.x-rest.x),0.01f))//at least difference of 0.01
    {
        start_time[0]=game::time;
        delta_time[0]=stop_time[0]-start_time[0];
    }
    else//difference of 0.01 or less is negligible
    {
        stop_time[0]=game::time;
        delta_time[0]=0.0f;
    }

    if(isgreaterequal(fabs(position.y-rest.y),0.01f))//at least difference of 0.01
    {
        start_time[1]=game::time;
        delta_time[1]=stop_time[1]-start_time[1];
    }
    else//difference of 0.01 or less is negligible
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
        velocity[0].x=(rest.x-position.x)/delta_time[0];
    velocity[1].x=velocity[0].x+momentum.x;//set final velocity

    if(isnormal(delta_time[1]))//makes sure it's not zero,infinity, or NaN
        velocity[0].y=(rest.y-position.y)/delta_time[1];
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
    if(isgreaterequal(fabs(momentum.x),0.01f))
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
    }

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
    calc_boundaries();
    set_resting();
    calc_points();
    calc_direction();
    physics();
    mouse_function();
}

void physics_object::load()
{
    std::ifstream object_file(file_name.c_str());//access file by name
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
    while(first_char!=';' && first_char!='\n')//no comment line or empty space detected
    {
        //load the cued actions
        first_char=object_file.peek();//check the first character of the line
        std::array<int,3> action;
        object_file>>action[0]>>action[1]>>action[2];//add action number, times to do, and  times performed
        action_cue.push(action);//add action to the cue
    }
    //load tangible object properties
    object_file>>touching[1];
    object_file>>touching[2];
    object_file>>touching[3];
    object_file>>touching[4];
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
    std::clog<<"object#"<<number<<'('<<type<<')'<<" loaded.\n";
}

void physics_object::save()
{
    std::ofstream object_file(file_name.c_str());
    object_file<<";basic object properties\n";
    object_file<<position.x<<','<<position.y<<";position\n";
    object_file<<rotation<<";rotation\n";
    object_file<<width<<'X'<<height<<";dimensions\n";
    object_file<<fill_color.str()<<";fill color RGB values\n";
    object_file<<marker_color.str()<<";marker color RGB values\n";
    object_file<<border_color.str()<<";border color RGB values\n";
    object_file<<filled<<";whether the shape is filled\n";
    object_file<<bordered<<";whether the shape has a border\n";
    object_file<<visible<<";whether you can see the object\n";
    object_file<<selected<<";whether the object is selected\n";
    object_file<<";complex object properties are generated after initialization\n";
    object_file<<";movable object properties\n";
    object_file<<speed<<";speed\n";
    object_file<<degrees_rotated<<";degrees rotated\n";
    object_file<<rest_rotation<<";resting rotation\n";
    object_file<<rally_set<<";whether or not the rally has been set\n";
    object_file<<moving_forward<<";whether the object is moving forward\n";
    object_file<<moving_backward<<";whether the object is moving backward\n";
    object_file<<moving_left<<";whether the object is moving left\n";
    object_file<<moving_right<<";whether the object is moving right\n";
    object_file<<turning_right<<";whether the object is turning right\n";
    object_file<<turning_left<<";whether the object is turning left\n";
    object_file<<";cued actions\n";
    for(int i=0;i<action_cue.size();i++)
        object_file<<action_cue.front().at(0)<<','<<action_cue.front().at(1)<<','<<action_cue.front().at(2)<<";action number, times done, times to do\n";
    object_file<<";tangible object properties\n";
    object_file<<touching[1]<<";number of the object touching the left side\n";
    object_file<<touching[2]<<";number of the object touching the right side\n";
    object_file<<touching[3]<<";number of the object touching the front side\n";
    object_file<<touching[4]<<";number of the object touching the back side\n";
    object_file<<collided<<";whether the object has collided\n";
    object_file<<";physics object properties\n";
    object_file<<mass<<";mass\n";
    object_file<<delta_time[0]<<";how long change in x took\n";
    object_file<<delta_time[1]<<";how long change in y took\n";
    object_file<<delta_time[2]<<";how long change in velocity x took\n";
    object_file<<delta_time[3]<<";how long change in velocity y took\n";
    object_file<<delta_time[4]<<";how long change in angle took\n";
    object_file<<delta_time[5]<<";how long change in angular velocity took\n";
    object_file<<velocity[0].x<<','<<velocity[0].y<<";initial velocity\n";
    object_file<<velocity[1].x<<','<<velocity[1].y<<";final velocity\n";
    object_file<<angular_velocity[0]<<";initial angular velocity\n";
    object_file<<angular_velocity[1]<<";final angular velocity\n";
    object_file<<acceleration.x<<','<<acceleration.y<<";acceleration\n";
    object_file<<angular_acceleration<<";angular acceleration\n";
    object_file<<momentum.x<<','<<momentum.y<<";momentum\n";
    object_file<<angular_momentum<<";angular momentum\n";
    object_file<<force.x<<','<<force.y<<";force\n";
    object_file.close();
    std::clog<<"object#"<<number<<'('<<type<<')'<<" saved.\n";
}

physics_object::physics_object()
{
    std::stringstream fn;
    fn<<"./data/objects/object#"<<number<<".pso";
    file_name=fn.str();
    type="physics object";
    mass=0.015f;//If this is too high, objects might just disappear off the screen
    fill_color=GRAY;
    position.set(origin);
    set_dimensions(32.0f,32.0f);
    velocity[0].x=0.00f;
    velocity[0].y=0.00f;
    angular_velocity[0]=0.00f;
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
