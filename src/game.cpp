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
#include <iostream>
#include <time.h>

//initialize variables
clock_t game::time_started;
float game::time = 0.0f;
double game::time_elapsed = 0.0d;
clickable_object* game::clickable_objects = new clickable_object[max_objects];
projectile* game::projectiles = new projectile[max_projectiles];

void game::collision_detection()
{
    for(int a=0; a<game::max_objects; a++)
    {
        for(int b=0; b<game::max_objects; b++)
        {
            if(a!=b && clickable_objects[a].is_close(clickable_objects[b]))//check objects colliding with other objects
            {
                clickable_objects[a].identify(clickable_objects[b]);
                clickable_objects[a].repel(clickable_objects[b]);
            }
            if(a!=b && clickable_objects[a].is_close(projectiles[b]))//check objects colliding with projectiles
            {
                clickable_objects[a].identify(projectiles[b]);
            }
            if(a!=b && projectiles[a].is_close(clickable_objects[b]))//check projectiles colliding with objects
            {
                projectiles[a].collided=true;
                projectiles[a].reset();
            }
            else
                projectiles[a].collided=false;
        }
    }
}

void game::init_objects()
{
    //initialize the clickable_objects

    //first object (yes first, because the index starts at 0) from clickable_objects array
    clickable_objects[0].name="small square";
    clickable_objects[0].primary_color.set(0.5,0.5,0.5);
    clickable_objects[0].current.set(window::width/2-48,window::height/2+48);
    clickable_objects[0].width=32;
    clickable_objects[0].height=32;
    clickable_objects[0].set_boundaries();
    clickable_objects[0].add_action(2,96);
    clickable_objects[0].add_action(4,96);
    clickable_objects[0].add_action(1,96);
    clickable_objects[0].add_action(3,96);
    clickable_objects[0].add_action(5,90);
    clickable_objects[0].add_action(6,90);
    std::clog<<"object#"<<clickable_objects[0].number<<": "<<clickable_objects[0].name<<" initialized."<<std::endl;

    //second object from clickable objects array
    clickable_objects[1].name="black square";
    clickable_objects[1].primary_color.set(BLACK);
    clickable_objects[1].set_boundaries();
    std::clog<<"object#"<<clickable_objects[1].number<<": "<<clickable_objects[1].name<<" initialized."<<std::endl;

    //third object from clickable_objects array
    clickable_objects[2].name="yellow square";
    clickable_objects[2].primary_color.set(YELLOW);
    clickable_objects[2].current.set(window::width/2+96,window::height/2);
    clickable_objects[2].set_boundaries();
    std::clog<<"object#"<<clickable_objects[2].number<<": "<<clickable_objects[2].name<<" initialized."<<std::endl;

    //fourth object from clickable_objects array
    clickable_objects[3].name="green square";
    clickable_objects[3].primary_color.set(GREEN);
    clickable_objects[3].current.set(window::width/2,window::height/2-96);
    clickable_objects[3].set_boundaries();
    std::clog<<"object#"<<clickable_objects[3].number<<": "<<clickable_objects[3].name<<" initialized."<<std::endl;

    //fifth object from clickable_objects array
    clickable_objects[4].name="red square";
    clickable_objects[4].primary_color.set(RED);
    clickable_objects[4].current.set(window::width/2,window::height/2+96);
    clickable_objects[4].set_boundaries();
    std::clog<<"object#"<<clickable_objects[4].number<<": "<<clickable_objects[4].name<<" initialized."<<std::endl;

    //sixth object from clickable_objects array
    clickable_objects[5].name="blue square";
    clickable_objects[5].primary_color.set(BLUE);
    clickable_objects[5].current.set(window::width/2-96,window::height/2);
    clickable_objects[5].width=64;
    clickable_objects[5].height=64;
    clickable_objects[5].set_boundaries();
    std::clog<<"object#"<<clickable_objects[5].number<<": "<<clickable_objects[5].name<<" initialized."<<std::endl;
}
