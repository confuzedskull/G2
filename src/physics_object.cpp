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

void physics_object::save()
{
    std::stringstream file_name;
    file_name<<"./data/objects/object#"<<number<<".pso";
    std::ofstream save_data(file_name.str());
    save_data<<"//basic object properties\n";
    save_data<<number<<"//number\n";
    save_data<<position.x<<','<<position.y<<"//position\n";
    save_data<<rotation<<"//rotation\n";
    save_data<<width<<'X'<<height<<"//dimensions\n";
    save_data<<marker_width<<'X'<<marker_height<<"//selection marker dimensions\n";
    save_data<<fill_color.str()<<"//fill color RGB values\n";
    save_data<<marker_color.str()<<"//marker color RGB values\n";
    save_data<<border_color.str()<<"//border color RGB values\n";
    save_data<<filled<<"//whether the shape is filled\n";
    save_data<<bordered<<"//whether the shape has a border\n";
    save_data<<visible<<"//whether you can see the object\n";
    save_data<<selected<<"//whether the object is selected\n";
    save_data<<"//complex object properties are generated after initialization\n";
    save_data<<"//movable object properties\n";
    save_data<<speed<<"//speed\n";
    save_data<<degrees_rotated<<"//degrees rotated\n";
    save_data<<rest_rotation<<"//resting rotation\n";
    save_data<<rally_set<<"//whether or not the rally has been set\n";
    save_data<<moving_forward<<"//whether the object is moving forward\n";
    save_data<<moving_backward<<"//whether the object is moving backward\n";
    save_data<<moving_left<<"//whether the object is moving left\n";
    save_data<<moving_right<<"//whether the object is moving right\n";
    save_data<<turning_right<<"//whether the object is turning right\n";
    save_data<<turning_left<<"//whether the object is turning left\n";
    save_data<<"//cued actions\n";
    for(int i=0;i<action_cue.size();i++)
        save_data<<action_cue.front().at(0)<<','<<action_cue.front().at(1)<<','<<action_cue.front().at(2)<<"//action number, times done, times to do\n";
    save_data<<"//tangible object properties\n";
    save_data<<touching[1]<<"//number of the object touching the left side\n";
    save_data<<touching[2]<<"//number of the object touching the right side\n";
    save_data<<touching[3]<<"//number of the object touching the front side\n";
    save_data<<touching[4]<<"//number of the object touching the back side\n";
    save_data<<collided<<"//whether the object has collided\n";
    save_data<<"//physics object properties\n";
    save_data<<mass<<"//mass\n";
    save_data<<delta_time[0]<<"//how long change in x took\n";
    save_data<<delta_time[1]<<"//how long change in y took\n";
    save_data<<delta_time[2]<<"//how long change in velocity x took\n";
    save_data<<delta_time[3]<<"//how long change in velocity y took\n";
    save_data<<delta_time[4]<<"//how long change in angle took\n";
    save_data<<delta_time[5]<<"//how long change in angular velocity took\n";
    save_data<<velocity[0].x<<','<<velocity[0].y<<"//initial velocity\n";
    save_data<<velocity[1].x<<','<<velocity[1].y<<"//final velocity\n";
    save_data<<angular_velocity[0]<<"//initial angular velocity\n";
    save_data<<angular_velocity[1]<<"//final angular velocity\n";
    save_data<<acceleration.x<<','<<acceleration.y<<"//acceleration\n";
    save_data<<angular_acceleration<<"//angular acceleration\n";
    save_data<<momentum.x<<','<<momentum.y<<"//momentum\n";
    save_data<<angular_momentum<<"//angular momentum\n";
    save_data<<force.x<<','<<force.y<<"/force\n";
    save_data.close();
    std::clog<<"object#"<<number<<'('<<type<<')'<<" saved.\n";
}

physics_object::physics_object()
{
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
