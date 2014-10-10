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

//initialize variables
clock_t game::time_started;
float game::time = 0.0f;
double game::time_elapsed = 0.0f;
std::vector<draggable_object*> game::draggable_objects;
std::vector<physics_object*> game::physics_objects;
std::vector<rts_object*> game::rts_objects;
std::vector<projectile> game::projectiles;
std::vector<button*> game::buttons;

//This checks which objects are touching and what they should do when that occurs
void game::collision_detection()
{
    for(unsigned a=0; a<game::rts_objects.size(); a++)//iterate through rts objects comparing
    {
        for(unsigned b=0; b<game::rts_objects.size(); b++)//iterate through rts objects being compared
        {
            if(a!=b && rts_objects[a]->is_close(*rts_objects[b]))//check objects colliding with other objects
            {
                rts_objects[a]->identify_touched(*rts_objects[b]);
                rts_objects[a]->repel(*rts_objects[b]);
            }
        }
    }
    for(unsigned a=0; a<game::physics_objects.size(); a++)//iterate through physics objects comparing
    {
        for(unsigned b=0; b<game::physics_objects.size(); b++)//iterate through physics objects being compared
        {
            if(a!=b && physics_objects[a]->is_close(*physics_objects[b]))//check objects colliding with other objects
            {
                physics_objects[a]->identify_touched(*physics_objects[b]);
                physics_objects[a]->repel(*physics_objects[b]);
                physics_objects[a]->calc_momentum(*physics_objects[b]);
            }
            if(a!=b && physics_objects[a]->is_close(projectiles[b]))//check objects colliding with projectiles
            {
                physics_objects[a]->identify_touched(projectiles[b]);
            }
            if(a!=b && projectiles[b].is_close(*physics_objects[a]))//check projectiles colliding with objects
            projectiles[b].reset();
        }
    }
    for(unsigned a=0; a<game::draggable_objects.size(); a++)//iterate through draggable objects comparing
    {
        for(unsigned b=0; b<game::draggable_objects.size(); b++)//iterate through draggable objects being compared
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
//initialize the buttons
    button* button1 = new button();
    button1->set_position(window::width*0.25,window::height*0.05);
    button1->set_label("new physics object");
    button1->action=physics_object::add_to_game;
    buttons.push_back(button1);

    button* button2 = new button();
    button2->set_position(window::width*0.5,window::height*0.05);
    button2->set_label("new draggable object");
    button2->action=draggable_object::add_to_game;
    buttons.push_back(button2);

    button* button3 = new button();
    button3->set_position(window::width*0.75,window::height*0.05);
    button3->set_label("new rts object");
    button3->action=rts_object::add_to_game;
    buttons.push_back(button3);

    object::total_objects=0;//reset the object count so it doesn't include the buttons

//initialize the physics objects
    physics_object* po1 = new physics_object();
    po1->name="small square";
    po1->set_position(window::width/2-48,window::height/2+48);//set position forward left of window center
    po1->set_dimensions(32,32);
    po1->primary_color=GRAY;
    po1->add_action(2,12);//move right 96 units(take into account momentum)
    po1->add_action(4,12);//move down 96 units(take into account momentum)
    po1->add_action(1,12);//move left 96 units(take into account momentum)
    po1->add_action(3,12);//move up 96 units(take into account momentum)
    po1->add_action(5,15);//turn left 90 degrees(take into account momentum)
    po1->add_action(6,15);//turn right 90 degrees(take into account momentum)
    std::clog<<"object#"<<po1->get_number()<<": "<<po1->name<<" initialized."<<std::endl;
    physics_objects.push_back(po1);//add the object to the object container

    physics_object* po2 = new physics_object();
    po2->name="small square 2";
    po2->set_position(window::width/2+48,window::height/2+48);//set position forward right of window center
    po2->set_dimensions(32,32);
    po2->primary_color=GRAY;
    po2->add_action(4,12);//move down 96 units(take into account momentum)
    po2->add_action(1,12);//move left 96 units(take into account momentum)
    po2->add_action(3,12);//move up 96 units(take into account momentum)
    po2->add_action(2,12);//move right 96 units(take into account momentum)
    po2->add_action(5,15);//turn left 90 degrees(take into account momentum)
    po2->add_action(6,15);//turn right 90 degrees(take into account momentum)
    std::clog<<"object#"<<po2->get_number()<<": "<<po2->name<<" initialized."<<std::endl;
    physics_objects.push_back(po2);//add the object to the object container

    physics_object* po3 = new physics_object();
    po3->name="small square 3";
    po3->set_position(window::width/2+48,window::height/2-48);//set position backward right of window center
    po3->set_dimensions(32,32);
    po3->primary_color=GRAY;
    po3->add_action(1,12);//move left 96 units(take into account momentum)
    po3->add_action(3,12);//move up 96 units(take into account momentum)
    po3->add_action(2,12);//move right 96 units(take into account momentum)
    po3->add_action(4,12);//move down 96 units(take into account momentum)
    po3->add_action(5,15);//turn left 90 degrees(take into account momentum)
    po3->add_action(6,15);//turn right 90 degrees(take into account momentum)
    std::clog<<"object#"<<po3->get_number()<<": "<<po3->name<<" initialized."<<std::endl;
    physics_objects.push_back(po3);//add the object to the object container

    physics_object* po4 = new physics_object();
    po4->name="small square 4";
    po4->set_position(window::width/2-48,window::height/2-48);//set position backward left of window center
    po4->set_dimensions(32,32);
    po4->primary_color=GRAY;
    po4->add_action(3,12);//move up 96 units(take into account momentum)
    po4->add_action(2,12);//move right 96 units(take into account momentum)
    po4->add_action(4,12);//move down 96 units(take into account momentum)
    po4->add_action(1,12);//move left 96 units(take into account momentum)
    po4->add_action(5,15);//turn left 90 degrees(take into account momentum)
    po4->add_action(6,15);//turn right 90 degrees(take into account momentum)
    std::clog<<"object#"<<po4->get_number()<<": "<<po4->name<<" initialized."<<std::endl;
    physics_objects.push_back(po4);//add the object to the object container
//initialize the draggable objects
    draggable_object* do1 = new draggable_object();
    do1->name="black square";
    do1->set_position(window::width/2,window::height/2);//set position window center
    do1->primary_color=BLACK;
    std::clog<<"object#"<<do1->get_number()<<": "<<do1->name<<" initialized."<<std::endl;
    draggable_objects.push_back(do1);
//initialize the rts objects
    rts_object* rtso1 = new rts_object();
    rtso1->name="yellow square";
    rtso1->set_position(window::width/2+96,window::height/2);//set position right of window center
    rtso1->primary_color=YELLOW;
    std::clog<<"object#"<<rtso1->get_number()<<": "<<rtso1->name<<" initialized."<<std::endl;
    rts_objects.push_back(rtso1);//add the object to the object container

    rts_object* rtso2 = new rts_object();
    rtso2->name="green square";
    rtso2->set_position(window::width/2,window::height/2-96);//set position below window center
    rtso2->primary_color=GREEN;
    std::clog<<"object#"<<rtso2->get_number()<<": "<<rtso2->name<<" initialized."<<std::endl;
    rts_objects.push_back(rtso2);//add the object to the object container

    rts_object* rtso3 = new rts_object();
    rtso3->name="red square";
    rtso3->set_position(window::width/2,window::height/2+96);//set position above window center
    rtso3->primary_color=RED;
    std::clog<<"object#"<<rtso3->get_number()<<": "<<rtso3->name<<" initialized."<<std::endl;
    rts_objects.push_back(rtso3);//add the object to the object container

    rts_object* rtso4 = new rts_object();
    rtso4->name="blue square";
    rtso4->set_position(window::width/2-96,window::height/2);//set position left of window center
    rtso4->primary_color=BLUE;
    std::clog<<"object#"<<rtso4->get_number()<<": "<<rtso4->name<<" initialized."<<std::endl;
    rts_objects.push_back(rtso4);//add the object to the object container
//create a projectile for each physics object
    projectiles.assign(physics_objects.size(),projectile());
//unhighlight everything
    cursor::highlighted_objects.assign(rts_objects.size(),false);
}
