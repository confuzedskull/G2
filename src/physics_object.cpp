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
#include <stdlib.h>

point2i physics_object::default_position = point2i(64,window::height*0.6);
int physics_object::default_width = 32;
int physics_object::default_height = 32;
std::string physics_object::default_texture = "";
std::string physics_object::default_mask = "";
std::string physics_object::default_click_sound = "";
std::string physics_object::default_hover_sound = "";
std::string physics_object::default_collision_sound = "";
std::string physics_object::default_movement_sound = "";

std::string physics_object::get_type()
{
    return "physics object";
}

point2f physics_object::get_resting()
{
    return rest_position;
}

void physics_object::rest()
{
    if(!moving_horizontal())
        rest_position.x=position.x;
    if(!moving_vertical())
        rest_position.y=position.y;
    if(!turning())
        rest_rotation=rotation;
    if(islessequal(momentum.magnitude(),1.0f))
        reset_motion();
}

void physics_object::calc_delta_time()
{
    if(isgreater(fabs(position.x-rest_position.x),0.01f))//check for a change in position
    {
        start_time[0]=game::time;
        delta_time[0]=stop_time[0]-start_time[0];
    }
    else
    {
        stop_time[0]=game::time;
        delta_time[0]=0.0f;
    }
    if(isgreater(fabs(position.y-rest_position.y),0.01f))//check for a change in position
    {
        start_time[1]=game::time;
        delta_time[1]=stop_time[1]-start_time[1];
    }
    else
    {
        stop_time[1]=game::time;
        delta_time[1]=0.0f;
    }
    if(moving_horizontal() && isgreaterequal(fabs(velocity[1].x-velocity[0].x),0.01f))//at least difference of 0.01
    {
        start_time[2]=game::time;
        delta_time[2]=stop_time[2]-start_time[2];
    }
    else//difference of 0.01 or less is negligible
    {
        stop_time[2]=game::time;
        delta_time[2]=0.0f;
    }
    if(moving_vertical() && isgreaterequal(fabs(velocity[1].y-velocity[0].y),0.01f))//at least difference of 0.01
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

void physics_object::calc_energy()
{
    if(moving())
        energy[1]=(mass/2)*(velocity[0].magnitude()*velocity[0].magnitude());//calculate energy
    else
        energy[0]=speed;//the object has the potential energy of one step
}

void physics_object::calc_physics()
{
    calc_delta_time();
    calc_velocity();
    calc_acceleration();
    calc_force();
    calc_momentum();
    calc_energy();
}

void physics_object::apply_inertia()
{
    if(moving_horizontal() && isgreaterequal(fabs(momentum.x),0.01f))
        position.x+=momentum.x*energy[0];
    if(moving_vertical() && isgreaterequal(fabs(momentum.y),0.01f))
        position.y+=momentum.y*energy[0];
    if(isgreaterequal(fabs(angular_momentum),0.01f))
        rotation+=angular_momentum*energy[0];
}

void physics_object::apply_friction()
{
    if(moving() && isgreater(energy[0],0.01f))
        energy[0]-=friction;
}

void physics_object::update()
{
    movable_object::update();
    tangible_object::update();
    calc_physics();
    rest();
}

void physics_object::sync()
{
    perform_actions();
    apply_inertia();
    apply_friction();
}

physics_object::physics_object()
{
    position.set((float)default_position.x, (float)default_position.y);
    set_dimensions(default_width,default_height);
    fill_color=GRAY;
    set_texture(default_texture);
    set_mask(default_mask);
    rest();
    mass=0.015f;//warning: if you set this too high with inertia enabled, the object may fly off the screen
    velocity[0].x=0.00f;
    velocity[0].y=0.00f;
    angular_velocity[0]=0.00f;
    friction=0.01f;
    energy[0]=speed;
    set_collision_sound(default_collision_sound);
    set_movement_sound(default_movement_sound);
    std::clog<<"object#"<<number<<"(physics object)"<<" created.\n";
}
