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
std::vector<draggable_object*> game::draggable_objects;
std::vector<physics_object*> game::physics_objects;
std::vector<rts_object*> game::rts_objects;
std::vector<projectile> game::projectiles;

void game::collision_detection()
{
    for(unsigned a=0; a<game::rts_objects.size(); a++)
    {
        for(unsigned b=0; b<game::rts_objects.size(); b++)
        {
            if(a!=b && rts_objects[a]->is_close(*rts_objects[b]))//check objects colliding with other objects
            {
                rts_objects[a]->identify_touched(*rts_objects[b]);
                rts_objects[a]->repel(*rts_objects[b]);
            }
        }
    }
    for(unsigned a=0; a<game::physics_objects.size(); a++)
    {
        for(unsigned b=0; b<game::physics_objects.size(); b++)
        {
            if(a!=b && physics_objects[a]->is_close(*physics_objects[b]))//check objects colliding with other objects
            {
                physics_objects[a]->identify_touched(*physics_objects[b]);
                physics_objects[a]->repel(*physics_objects[b]);
            }
            if(a!=b && physics_objects[a]->is_close(projectiles[b]))//check objects colliding with projectiles
            {
                rts_objects[a]->identify_touched(projectiles[b]);
            }
            if(a!=b && projectiles[a].is_close(*physics_objects[b]))//check projectiles colliding with objects
            projectiles[a].reset();
        }
    }
    for(unsigned a=0; a<game::draggable_objects.size(); a++)
    {
        for(unsigned b=0; b<game::draggable_objects.size(); b++)
        {
            if(a!=b && draggable_objects[a]->is_close(*draggable_objects[b]))//check objects colliding with other objects
            {
                draggable_objects[a]->identify_touched(*draggable_objects[b]);
                draggable_objects[a]->repel(*draggable_objects[b]);
            }
        }
    }
}

void game::init_objects()
{
    object::total_objects=0;//reset the object count

//initialize the physics objects
    physics_object* po1 = new physics_object();
    po1->name="small square";
    po1->current.set(window::width/2-48,window::height/2+48);
    po1->width=32;
    po1->height=32;
    po1->primary_color=GRAY;
    po1->add_action(2,12);//move right 96 units(take into account momentum)
    po1->add_action(4,12);//move down 96 units(take into account momentum)
    po1->add_action(1,12);//move left 96 units(take into account momentum)
    po1->add_action(3,12);//move up 96 units(take into account momentum)
    po1->add_action(5,15);//turn left 90 degrees(take into account momentum)
    po1->add_action(6,15);//turn right 90 degrees(take into account momentum)
    std::clog<<"object#"<<po1->number<<": "<<po1->name<<" initialized."<<std::endl;
    physics_objects.push_back(po1);//add the object to the object container
//initialize the draggable objects
    draggable_object* do1 = new draggable_object();
    do1->name="black square";
    do1->current.set(window::width/2,window::height/2);
    do1->primary_color=BLACK;
    std::clog<<"object#"<<do1->number<<": "<<do1->name<<" initialized."<<std::endl;
    draggable_objects.push_back(do1);
//initialize the rts objects
    rts_object* rtso1 = new rts_object();
    rtso1->name="yellow square";
    rtso1->current.set(window::width/2+96,window::height/2);
    rtso1->primary_color=YELLOW;
    std::clog<<"object#"<<rtso1->number<<": "<<rtso1->name<<" initialized."<<std::endl;
    rts_objects.push_back(rtso1);//add the object to the object container

    rts_object* rtso2 = new rts_object();
    rtso2->name="green square";
    rtso2->current.set(window::width/2,window::height/2-96);
    rtso2->primary_color=GREEN;
    std::clog<<"object#"<<rtso2->number<<": "<<rtso2->name<<" initialized."<<std::endl;
    rts_objects.push_back(rtso2);//add the object to the object container

    rts_object* rtso3 = new rts_object();
    rtso3->name="red square";
    rtso3->current.set(window::width/2,window::height/2+96);
    rtso3->primary_color=RED;
    std::clog<<"object#"<<rtso3->number<<": "<<rtso3->name<<" initialized."<<std::endl;
    rts_objects.push_back(rtso3);//add the object to the object container

    rts_object* rtso4 = new rts_object();
    rtso4->name="blue square";
    rtso4->current.set(window::width/2-96,window::height/2);
    rtso4->primary_color=BLUE;
    std::clog<<"object#"<<rtso4->number<<": "<<rtso4->name<<" initialized."<<std::endl;
    rts_objects.push_back(rtso4);//add the object to the object container
//create a projectile for each physics object
    projectiles.assign(physics_objects.size(),projectile());
//unhighlight everything
    cursor::highlighted_objects.assign(rts_objects.size(),false);
}
