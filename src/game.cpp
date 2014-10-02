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

#include "game.h"
#include "window.h"
#include "cursor.h"
#include "object.h"
#include <iostream>
#include <time.h>

clock_t game::time_started;
float game::time = 0.0f;
double game::time_elapsed = 0.0f;
std::vector<draggable_object> draggable_objects;
std::vector<physics_object> game::physics_objects;
std::vector<rts_object> game::rts_objects;
std::vector<projectile> game::projectiles;

void game::collision_detection()
{
    for(unsigned a=0; a<game::rts_objects.size(); a++)
    {
        for(unsigned b=0; b<game::rts_objects.size(); b++)
        {
            if(a!=b && rts_objects[a].is_close(rts_objects[b]))//check objects colliding with other objects
            {
                rts_objects[a].identify_touched(rts_objects[b]);
                rts_objects[a].repel(rts_objects[b]);
            }
        }
    }
    for(unsigned a=0; a<game::physics_objects.size(); a++)
    {
        for(unsigned b=0; b<game::physics_objects.size(); b++)
        {
            if(a!=b && physics_objects[a].is_close(physics_objects[b]))//check objects colliding with other objects
            {
                physics_objects[a].identify_touched(physics_objects[b]);
                physics_objects[a].repel(physics_objects[b]);
            }
            if(a!=b && physics_objects[a].is_close(projectiles[b]))//check objects colliding with projectiles
            {
                rts_objects[a].identify_touched(projectiles[b]);
            }
            if(a!=b && projectiles[a].is_close(physics_objects[b]))//check projectiles colliding with objects
            projectiles[a].reset();
        }
    }
    /*for(unsigned a=0; a<game::draggable_objects.size(); a++)
    {
        for(unsigned b=0; b<game::draggable_objects.size(); b++)
        {
            if(a!=b && draggable_objects[a].is_close(draggable_objects[b]))//check objects colliding with other objects
            {
                draggable_objects[a].identify_touched(draggable_objects[b]);
                draggable_objects[a].repel(draggable_objects[b]);
            }
        }
    }*/
}

void game::init_objects()
{
    object::total_objects=0;//reset the object count

//initialize the physics objects
    //first object (yes first, because the index starts at 0) from physics objects container
    physics_objects.push_back(physics_object());
    physics_objects[0].name="small square";
    physics_objects[0].primary_color.set(0.5,0.5,0.5);
    physics_objects[0].current.set(window::width/2-48,window::height/2+48);
    physics_objects[0].width=32;
    physics_objects[0].height=32;
    physics_objects[0].add_action(2,76);//move right 96 units
    physics_objects[0].add_action(4,76);//move down 96 units
    physics_objects[0].add_action(1,76);//move left 96 units
    physics_objects[0].add_action(3,76);//move up 96 units
    physics_objects[0].add_action(5,90);//turn left 90 degrees
    physics_objects[0].add_action(6,90);//turn right 90 degrees
    std::clog<<"object#"<<physics_objects[0].number<<": "<<physics_objects[0].name<<" initialized."<<std::endl;
//initialize the draggable objects
    //first object from draggable objects container
/*    draggable_objects.push_back(draggable_object());
    draggable_objects[0].name="black square";
    draggable_objects[0].primary_color.set(BLACK);
    std::clog<<"object#"<<draggable_objects[0].number<<": "<<draggable_objects[0].name<<" initialized."<<std::endl;*/
//initialize the rts objects
    //first object from rts_objects container
    rts_objects.push_back(rts_object());
    rts_objects[0].name="yellow square";
    rts_objects[0].primary_color.set(YELLOW);
    rts_objects[0].current.set(window::width/2+96,window::height/2);
    std::clog<<"object#"<<rts_objects[0].number<<": "<<rts_objects[0].name<<" initialized."<<std::endl;

    //second object from rts_objects container
    rts_objects.push_back(rts_object());
    rts_objects[1].name="green square";
    rts_objects[1].primary_color.set(GREEN);
    rts_objects[1].current.set(window::width/2,window::height/2-96);
    std::clog<<"object#"<<rts_objects[1].number<<": "<<rts_objects[1].name<<" initialized."<<std::endl;

    //third object from rts_objects container
    rts_objects.push_back(rts_object());
    rts_objects[2].name="red square";
    rts_objects[2].primary_color.set(RED);
    rts_objects[2].current.set(window::width/2,window::height/2+96);
    std::clog<<"object#"<<rts_objects[2].number<<": "<<rts_objects[2].name<<" initialized."<<std::endl;

    //fourth object from rts_objects container
    rts_objects.push_back(rts_object());
    rts_objects[3].name="blue square";
    rts_objects[3].primary_color.set(BLUE);
    rts_objects[3].current.set(window::width/2-96,window::height/2);
    std::clog<<"object#"<<rts_objects[3].number<<": "<<rts_objects[3].name<<" initialized."<<std::endl;

    //create a projectile for each physics object
    projectiles.assign(physics_objects.size(),projectile());

    //unhighlight everything
    cursor::highlighted_objects.assign(rts_objects.size(),false);
}
