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
double game::time_elapsed = 0.0d;
std::vector<clickable_object> game::clickable_objects;
std::vector<projectile> game::projectiles;

void game::collision_detection()
{
    for(unsigned a=0; a<game::clickable_objects.size(); a++)
    {
        for(unsigned b=0; b<game::clickable_objects.size(); b++)
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
    object::total_objects=0;//reset the object count

    //initialize the clickable_objects
    //first object (yes first, because the index starts at 0) from clickable_objects container
    clickable_objects.push_back(clickable_object());
    clickable_objects[0].name="small square";
    clickable_objects[0].primary_color.set(0.5,0.5,0.5);
    clickable_objects[0].current.set(window::width/2-48,window::height/2+48);
    clickable_objects[0].width=32;
    clickable_objects[0].height=32;
    clickable_objects[0].add_action(2,96);//move right 96 units
    clickable_objects[0].add_action(4,96);//move down 96 units
    clickable_objects[0].add_action(1,96);//move left 96 units
    clickable_objects[0].add_action(3,96);//move up 96 units
    clickable_objects[0].add_action(5,90);//turn left 90 degrees
    clickable_objects[0].add_action(6,90);//turn right 90 degrees
    std::clog<<"object#"<<clickable_objects[0].number<<": "<<clickable_objects[0].name<<" initialized."<<std::endl;

    //second object from clickable objects container
    clickable_objects.push_back(clickable_object());
    clickable_objects[1].name="black square";
    clickable_objects[1].primary_color.set(BLACK);
    std::clog<<"object#"<<clickable_objects[1].number<<": "<<clickable_objects[1].name<<" initialized."<<std::endl;

    //third object from clickable_objects container
    clickable_objects.push_back(clickable_object());
    clickable_objects[2].name="yellow square";
    clickable_objects[2].primary_color.set(YELLOW);
    clickable_objects[2].current.set(window::width/2+96,window::height/2);
    std::clog<<"object#"<<clickable_objects[2].number<<": "<<clickable_objects[2].name<<" initialized."<<std::endl;

    //fourth object from clickable_objects container
    clickable_objects.push_back(clickable_object());
    clickable_objects[3].name="green square";
    clickable_objects[3].primary_color.set(GREEN);
    clickable_objects[3].current.set(window::width/2,window::height/2-96);
    std::clog<<"object#"<<clickable_objects[3].number<<": "<<clickable_objects[3].name<<" initialized."<<std::endl;

    //fifth object from clickable_objects container
    clickable_objects.push_back(clickable_object());
    clickable_objects[4].name="red square";
    clickable_objects[4].primary_color.set(RED);
    clickable_objects[4].current.set(window::width/2,window::height/2+96);
    std::clog<<"object#"<<clickable_objects[4].number<<": "<<clickable_objects[4].name<<" initialized."<<std::endl;

    //sixth object from clickable_objects container
    clickable_objects.push_back(clickable_object());
    clickable_objects[5].name="blue square";
    clickable_objects[5].primary_color.set(BLUE);
    clickable_objects[5].current.set(window::width/2-96,window::height/2);
    std::clog<<"object#"<<clickable_objects[5].number<<": "<<clickable_objects[5].name<<" initialized."<<std::endl;

    //create a projectile for each clickable object
    projectiles.assign(6,projectile());

    //unhighlight everything
    cursor::highlighted_objects.assign(6,false);
}
