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
#include <math.h>

point2f physics_object::origin = point2f(window::width*0.9,window::height*0.7);

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

physics_object::physics_object()
{
    type="physics object";
    mass=0.015f;//If this is too high, objects might just disappear off the screen
    primary_color=GRAY;
    position.set(origin);
    set_dimensions(32.0f,32.0f);
    velocity[0].x=0.00f;
    velocity[0].y=0.00f;
    angular_velocity[0]=0.00f;
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
