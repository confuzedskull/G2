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
std::map<int,draggable_object*> game::draggable_objects;
std::map<int,physics_object*> game::physics_objects;
std::map<int,rts_object*> game::rts_objects;
//std::vector<projectile> game::projectiles;
std::vector<button*> game::buttons;

void game::init_objects()
{
//initialize the buttons
    button* button1 = new button();
    button1->set_position(window::width*0.9,window::height*0.8);
    button1->set_label("new physics object");
    button1->action=physics_object::add_to_game;//function is assigned without '()' at the end
    buttons.push_back(button1);//add button to container

    button* button2 = new button();
    button2->set_position(window::width*0.9,window::height*0.6);
    button2->set_label("new draggable object");
    button2->action=draggable_object::add_to_game;//function is assigned without '()' at the end
    buttons.push_back(button2);//add button to container

    button* button3 = new button();
    button3->set_position(window::width*0.9,window::height*0.4);
    button3->set_label("new rts object");
    button3->action=rts_object::add_to_game;//function is assigned without '()' at the end
    buttons.push_back(button3);//add button to container

    button* button4 = new button();
    button4->set_position(window::width*0.9,window::height*0.2);
    button4->set_label("delete object");
    button4->action=cursor::delete_selected;//function is assigned without '()' at the end
    buttons.push_back(button4);//add button to container

    object::total_objects=0;//reset the object count so it doesn't include the buttons

//initialize the physics objects
    physics_object* po1 = new physics_object();
    po1->name="small square 1";
    po1->set_position(window::width/2-48,window::height/2+48);//set position forward left of window center
    po1->add_action(2,12);//move right 96 units(take into account momentum)
    po1->add_action(4,12);//move down 96 units(take into account momentum)
    po1->add_action(1,12);//move left 96 units(take into account momentum)
    po1->add_action(3,12);//move up 96 units(take into account momentum)
    po1->add_action(5,15);//turn left 90 degrees(take into account momentum)
    po1->add_action(6,15);//turn right 90 degrees(take into account momentum)
    std::clog<<"object#"<<po1->get_number()<<": "<<po1->name<<" initialized."<<std::endl;
    physics_objects.insert(std::pair<int,physics_object*>(po1->get_number(),po1));//add object to container

    physics_object* po2 = new physics_object();
    po2->name="small square 2";
    po2->set_position(window::width/2+48,window::height/2+48);//set position forward right of window center
    po2->add_action(4,12);//move down 96 units(take into account momentum)
    po2->add_action(1,12);//move left 96 units(take into account momentum)
    po2->add_action(3,12);//move up 96 units(take into account momentum)
    po2->add_action(2,12);//move right 96 units(take into account momentum)
    po2->add_action(5,15);//turn left 90 degrees(take into account momentum)
    po2->add_action(6,15);//turn right 90 degrees(take into account momentum)
    std::clog<<"object#"<<po2->get_number()<<": "<<po2->name<<" initialized."<<std::endl;
    physics_objects.insert(std::pair<int,physics_object*>(po2->get_number(),po2));//add object to container

    physics_object* po3 = new physics_object();
    po3->name="small square 3";
    po3->set_position(window::width/2+48,window::height/2-48);//set position backward right of window center
    po3->add_action(1,12);//move left 96 units(take into account momentum)
    po3->add_action(3,12);//move up 96 units(take into account momentum)
    po3->add_action(2,12);//move right 96 units(take into account momentum)
    po3->add_action(4,12);//move down 96 units(take into account momentum)
    po3->add_action(5,15);//turn left 90 degrees(take into account momentum)
    po3->add_action(6,15);//turn right 90 degrees(take into account momentum)
    std::clog<<"object#"<<po3->get_number()<<": "<<po3->name<<" initialized."<<std::endl;
    physics_objects.insert(std::pair<int,physics_object*>(po3->get_number(),po3));//add object to container

    physics_object* po4 = new physics_object();
    po4->name="small square 4";
    po4->set_position(window::width/2-48,window::height/2-48);//set position backward left of window center
    po4->add_action(3,12);//move up 96 units(take into account momentum)
    po4->add_action(2,12);//move right 96 units(take into account momentum)
    po4->add_action(4,12);//move down 96 units(take into account momentum)
    po4->add_action(1,12);//move left 96 units(take into account momentum)
    po4->add_action(5,15);//turn left 90 degrees(take into account momentum)
    po4->add_action(6,15);//turn right 90 degrees(take into account momentum)
    std::clog<<"object#"<<po4->get_number()<<": "<<po4->name<<" initialized."<<std::endl;
    physics_objects.insert(std::pair<int,physics_object*>(po4->get_number(),po4));//add object to container
//initialize the draggable objects
    draggable_object* do1 = new draggable_object();
    do1->name="black square";
    do1->set_position(window::width/2,window::height/2);//set position window center
    do1->primary_color=BLACK;//set the color like this so that it isn't marked as changed
    std::clog<<"object#"<<do1->get_number()<<": "<<do1->name<<" initialized."<<std::endl;
    draggable_objects.insert(std::pair<int,draggable_object*>(do1->get_number(),do1));//add object to container
//initialize the rts objects
    rts_object* rtso1 = new rts_object();
    rtso1->name="yellow square";
    rtso1->set_position(window::width/2+96,window::height/2);//set position right of window center
    rtso1->primary_color=YELLOW;//set the color like this so that it isn't marked as changed
    std::clog<<"object#"<<rtso1->get_number()<<": "<<rtso1->name<<" initialized."<<std::endl;
    rts_objects.insert(std::pair<int,rts_object*>(rtso1->get_number(),rtso1));//add object to container

    rts_object* rtso2 = new rts_object();
    rtso2->name="green square";
    rtso2->set_position(window::width/2,window::height/2-96);//set position below window center
    rtso2->primary_color=GREEN;//set the color like this so that it isn't marked as changed
    std::clog<<"object#"<<rtso2->get_number()<<": "<<rtso2->name<<" initialized."<<std::endl;
    rts_objects.insert(std::pair<int,rts_object*>(rtso2->get_number(),rtso2));//add object to container

    rts_object* rtso3 = new rts_object();
    rtso3->name="red square";
    rtso3->set_position(window::width/2,window::height/2+96);//set position above window center
    rtso3->primary_color=RED;//set the color like this so that it isn't marked as changed
    std::clog<<"object#"<<rtso3->get_number()<<": "<<rtso3->name<<" initialized."<<std::endl;
    rts_objects.insert(std::pair<int,rts_object*>(rtso3->get_number(),rtso3));//add object to container

    rts_object* rtso4 = new rts_object();
    rtso4->name="blue square";
    rtso4->set_position(window::width/2-96,window::height/2);//set position left of window center
    rtso4->primary_color=BLUE;//set the color like this so that it isn't marked as changed
    std::clog<<"object#"<<rtso4->get_number()<<": "<<rtso4->name<<" initialized."<<std::endl;
    rts_objects.insert(std::pair<int,rts_object*>(rtso4->get_number(),rtso4));//add object to container

//create a projectile for each physics object
    //projectiles.assign(physics_objects.size(),projectile());
//unhighlight the RTS objects
    cursor::highlighted_objects.assign(rts_objects.size(),false);
}

//This checks which objects are touching and what they should do when that occurs
void game::collision_detection()
{
    for(std::map<int,rts_object*>::iterator a=rts_objects.begin(); a!=rts_objects.end(); ++a)//iterate through rts objects comparing
    {
        for(std::map<int,rts_object*>::iterator b=rts_objects.begin(); b!=rts_objects.end(); ++b)//iterate through rts objects being compared
        {
            if(a->first!=b->first && a->second->is_close(*b->second))//check objects colliding with other objects
            {
                a->second->identify_touched(*b->second);
                a->second->repel(*b->second);
            }
        }
    }
    for(std::map<int,physics_object*>::iterator a=physics_objects.begin(); a!=physics_objects.end(); ++a)//iterate through physics objects comparing
    {
        for(std::map<int,physics_object*>::iterator b=physics_objects.begin(); b!=physics_objects.end(); ++b)//iterate through physics objects being compared
        {
            if(a->first!=b->first && a->second->is_close(*b->second))//check objects colliding with other objects
            {
                a->second->identify_touched(*b->second);
                a->second->repel(*b->second);
                a->second->calc_momentum(*b->second);
            }
        }
        /*for(int p=0; p<game::projectiles.size();p++)
        {
            if(a->second->is_close(projectiles[p]))//check objects colliding with projectiles
            {
                a->second->identify_touched(projectiles[p]);
            }
            if(projectiles[p].is_close(*a->second))//check projectiles colliding with objects
            projectiles[p].reset();
        }*/
    }
    for(std::map<int,draggable_object*>::iterator a=draggable_objects.begin(); a!=draggable_objects.end(); ++a)//iterate through draggable objects comparing
    {
        for(std::map<int,draggable_object*>::iterator b=draggable_objects.begin(); b!=draggable_objects.end(); ++b)//iterate through draggable objects being compared
        {
            if(a->first!=b->first && a->second->is_close(*b->second))//check objects colliding with other objects
            {
                a->second->identify_touched(*b->second);
                a->second->repel(*b->second);
            }
        }
    }
}
