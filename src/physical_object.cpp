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

#include "physical_object.h"
#include "game.h"
#include "window.h"
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>

point2i physical_object::default_position = point2i(64,window::height*0.6);
int physical_object::default_width = 32;
int physical_object::default_height = 32;
std::string physical_object::default_texture = "";
std::string physical_object::default_mask = "";
std::string physical_object::default_clicksound = "";
std::string physical_object::default_hoversound = "";
std::string physical_object::default_collisionsound = "";
std::string physical_object::default_movementsound = "";

std::string physical_object::get_type()
{
    return "physics object";
}

point2f physical_object::get_resting()
{
    return rest_position;
}

void physical_object::rest()
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

void physical_object::calc_delta_time()
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
void physical_object::calc_velocity()
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

void physical_object::calc_acceleration()
{
    if(isnormal(delta_time[2]))//makes sure it's not zero,infinity, or NaN
        acceleration.x=(velocity[0].x-velocity[1].x)/delta_time[2];

    if(isnormal(delta_time[3]))//makes sure it's not zero,infinity, or NaN
        acceleration.y=(velocity[0].y-velocity[1].y)/delta_time[3];

    if(isnormal(delta_time[5]))//makes sure it's not zero,infinity, or NaN
        angular_acceleration=(angular_velocity[0]-angular_velocity[1])/delta_time[5];
}

void physical_object::calc_force()
{
    force.x=mass*acceleration.x;
    force.y=mass*acceleration.y;
}
//calculate initial momentum
void physical_object::calc_momentum()
{
    momentum.x=mass*velocity[0].x;
    momentum.y=mass*velocity[0].y;
    angular_momentum=mass*angular_velocity[0];
}
//calculate momentum after elastic collision with object p
void physical_object::calc_momentum(physical_object p)
{
    momentum.x=momentum.x+p.momentum.x-(p.mass*p.velocity[1].x);
    momentum.y=momentum.y+p.momentum.y-(p.mass*p.velocity[1].y);
}

void physical_object::calc_energy()
{
    if(moving())
        energy[1]=(mass/2)*(velocity[0].magnitude()*velocity[0].magnitude());//calculate energy
    else
        energy[0]=speed;//the object has the potential energy of one step
}

void physical_object::calc_physics()
{
    calc_delta_time();
    calc_velocity();
    calc_acceleration();
    calc_force();
    calc_momentum();
    calc_energy();
}

void physical_object::apply_inertia()
{
    if(moving_horizontal() && isgreaterequal(fabs(momentum.x),0.01f))
        position.x+=momentum.x*energy[0];
    if(moving_vertical() && isgreaterequal(fabs(momentum.y),0.01f))
        position.y+=momentum.y*energy[0];
    if(isgreaterequal(fabs(angular_momentum),0.01f))
        rotation+=angular_momentum*energy[0];
}

void physical_object::apply_friction()
{
    if(moving() && isgreater(energy[0],0.01f))
        energy[0]-=friction;
}

void physical_object::update()
{
    mobile_object::update();
    smart_object::update();
    calc_physics();
    rest();
}

void physical_object::sync()
{
    perform_actions();
    apply_inertia();
    apply_friction();
}

void physical_object::save()
{
    std::stringstream filename;
    filename<<"./data/objects/object#"<<number<<".pso";
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
    object_file.close();
    std::clog<<"object#"<<number<<"(physical object)"<<" saved.\n";
}

void physical_object::load()
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
    std::clog<<"object#"<<number<<"(physical object)"<<" loaded.\n";
}

physical_object::physical_object()
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
    set_collisionsound(default_collisionsound);
    set_movementsound(default_movementsound);
    std::clog<<"object#"<<number<<"(physical object)"<<" created.\n";
}
