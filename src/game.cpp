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
#include "controls.h"
#include "cursor.h"
#include "object.h"
#include "ui.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>

//initialize variables
clock_t game::time_started;
float game::time = 0.0f;
double game::time_elapsed = 0.0f;
bool game::paused=false;
std::vector<scene*> game::scenes;

//This checks which objects are touching and what they should do when that occurs
//NOTE: This function uses C++11 "for" loops
void game::collision_detection()
{
    for(auto a:scenes[window::current_scene]->rts_objects)//iterate through rts objects comparing
    {
        for(auto b:scenes[window::current_scene]->rts_objects)//iterate through rts objects being compared
        {
            if(a.first!=b.first && a.second->is_close(*b.second))//check objects colliding with other objects
            {
                a.second->identify_touched(*b.second);
                a.second->repel(*b.second);
            }
        }
    }
    for(auto a:scenes[window::current_scene]->physics_objects)//iterate through physics objects comparing
    {
        for(auto b:scenes[window::current_scene]->physics_objects)//iterate through physics objects being compared
        {
            if(a.first!=b.first && a.second->is_close(*b.second))//check objects colliding with other objects
            {
                a.second->identify_touched(*b.second);
                a.second->repel(*b.second);
                a.second->calc_momentum(*b.second);
            }
        }
    }
    for(auto a:scenes[window::current_scene]->draggable_objects)//iterate through draggable objects comparing
    {
        for(auto b:scenes[window::current_scene]->draggable_objects)//iterate through draggable objects being compared
        {
            if(a.first!=b.first && a.second->is_close(*b.second))//check objects colliding with other objects
            {
                a.second->identify_touched(*b.second);
                a.second->repel(*b.second);
            }
        }
    }
}

void game::initialize()
{
//Initialize Objects
    std::clog<<"initializing objects...\n";
    object::total_objects=0;//reset the object count
    //initialize the physics objects
    physics_object* po1 = new physics_object();
    po1->name="small square 1";
    po1->set_position(window::width/2-48,window::height/2+48);//set position forward left of window center
    po1->cue_action(2,12);//move right 96 units(take into account momentum)
    po1->cue_action(4,12);//move down 96 units(take into account momentum)
    po1->cue_action(1,12);//move left 96 units(take into account momentum)
    po1->cue_action(3,12);//move up 96 units(take into account momentum)
    po1->cue_action(5,15);//turn left 90 degrees(take into account momentum)
    po1->cue_action(6,15);//turn right 90 degrees(take into account momentum)

    physics_object* po2 = new physics_object();
    po2->name="small square 2";
    po2->set_position(window::width/2+48,window::height/2+48);//set position forward right of window center
    po2->cue_action(4,12);//move down 96 units(take into account momentum)
    po2->cue_action(1,12);//move left 96 units(take into account momentum)
    po2->cue_action(3,12);//move up 96 units(take into account momentum)
    po2->cue_action(2,12);//move right 96 units(take into account momentum)
    po2->cue_action(5,15);//turn left 90 degrees(take into account momentum)
    po2->cue_action(6,15);//turn right 90 degrees(take into account momentum)

    physics_object* po3 = new physics_object();
    po3->name="small square 3";
    po3->set_position(window::width/2+48,window::height/2-48);//set position backward right of window center
    po3->cue_action(1,12);//move left 96 units(take into account momentum)
    po3->cue_action(3,12);//move up 96 units(take into account momentum)
    po3->cue_action(2,12);//move right 96 units(take into account momentum)
    po3->cue_action(4,12);//move down 96 units(take into account momentum)
    po3->cue_action(5,15);//turn left 90 degrees(take into account momentum)
    po3->cue_action(6,15);//turn right 90 degrees(take into account momentum)

    physics_object* po4 = new physics_object();
    po4->name="small square 4";
    po4->set_position(window::width/2-48,window::height/2-48);//set position backward left of window center
    po4->cue_action(3,12);//move up 96 units(take into account momentum)
    po4->cue_action(2,12);//move right 96 units(take into account momentum)
    po4->cue_action(4,12);//move down 96 units(take into account momentum)
    po4->cue_action(1,12);//move left 96 units(take into account momentum)
    po4->cue_action(5,15);//turn left 90 degrees(take into account momentum)
    po4->cue_action(6,15);//turn right 90 degrees(take into account momentum)
    std::clog<<"initialized physics objects\n";
    //initialize the draggable objects
    draggable_object* do1 = new draggable_object();
    do1->name="black square";
    do1->set_position(window::width/2,window::height/2);//set position window center
    do1->primary_color=BLACK;//set the color like this so that it isn't marked as changed
    std::clog<<"initialized draggable objects\n";
    //initialize the rts objects
    rts_object* rtso1 = new rts_object();
    rtso1->name="yellow square";
    rtso1->set_position(window::width/2+96,window::height/2);//set position right of window center
    rtso1->primary_color=YELLOW;//set the color like this so that it isn't marked as changed

    rts_object* rtso2 = new rts_object();
    rtso2->name="green square";
    rtso2->set_position(window::width/2,window::height/2-96);//set position below window center
    rtso2->primary_color=GREEN;//set the color like this so that it isn't marked as changed

    rts_object* rtso3 = new rts_object();
    rtso3->name="red square";
    rtso3->set_position(window::width/2,window::height/2+96);//set position above window center
    rtso3->primary_color=RED;//set the color like this so that it isn't marked as changed

    rts_object* rtso4 = new rts_object();
    rtso4->name="blue square";
    rtso4->set_position(window::width/2-96,window::height/2);//set position left of window center
    rtso4->primary_color=BLUE;//set the color like this so that it isn't marked as changed
    std::clog<<"initialized rts objects\n";
//Initialize Text
    text_object* object_info = new text_object();
    object_info->hide();
    object_info->spacing=20;
    object_info->set_position(ui::margin,window::height-20);

    text_object* game_info = new text_object();
    game_info->hide();
    game_info->spacing=20;
    game_info->set_position(window::width-(ui::margin+150),window::height-20);
    std::clog<<"initialized text\n";
//Initialize Buttons
    std::clog<<"initializing user interface...\n";
    //Main Menu Buttons
    button* play_button = new button();//create a button pointer and initialize it
    play_button->set_label("Play");
    play_button->action=game::play;//function is assigned without '()' at the end

    button* quit_button = new button();//create a button pointer and initialize it
    quit_button->set_label("Quit");
    quit_button->action=quit;//function is assigned without '()' at the end
    //Pause Menu Buttons
    button* resume_button = new button();//create a button pointer and initialize it
    resume_button->set_label("Resume");
    resume_button->action=resume;//function is assigned without '()' at the end

    button* main_menu_button = new button();//create a button pointer and initialize it
    main_menu_button->set_label("Main Menu");
    main_menu_button->action=return_warning;//function is assigned without '()' at the end
    //Warning Menu Buttons
    button* confirm_return_button = new button();//create a button pointer and initialize it
    confirm_return_button->set_label("Yes");
    confirm_return_button->action=return_menu;//function is assigned without '()' at the end

    button* cancel_return_button = new button();
    cancel_return_button->set_label("No");
    cancel_return_button->action=pause;
    //Game Buttons
    button* create_po_button = new button();//"po" stands for "physics object"
    create_po_button->set_position(window::width*0.9,window::height*0.8);//put the button on the right side, 4/5ths of the way up
    create_po_button->set_label("new physics object");
    create_po_button->action=add_physics_object;//function is assigned without '()' at the end

    button* create_do_button = new button();//"do" stands for "draggable object"
    create_do_button->set_position(window::width*0.9,window::height*0.6);//put the button on the right side, 3/5ths of the way up
    create_do_button->set_label("new draggable object");
    create_do_button->action=add_draggable_object;//function is assigned without '()' at the end

    button* create_rtso_button = new button();//"rtso" stands for "real-time strategy object"
    create_rtso_button->set_position(window::width*0.9,window::height*0.4);//put the button on the right side, 2/5ths of the way up
    create_rtso_button->set_label("new rts object");
    create_rtso_button->action=add_rts_object;//function is assigned without '()' at the end

    button* delete_object_button = new button();//create a button pointer and initialize it
    delete_object_button->set_position(window::width*0.9,window::height*0.2);//put the button on the right side, 1/5th of the way up
    delete_object_button->set_label("delete object");
    delete_object_button->action=delete_selected;//function is assigned without '()' at the end

    button* menu_button = new button();//create a button pointer and initialize it
    menu_button->set_position(window::center.x,window::height-20);//put the button at the top middle, just below the top
    menu_button->set_label("Menu");
    menu_button->action=pause;//function is assigned without '()' at the end
    std::clog<<"initialized buttons\n";
//Initialize Menus
    menu* main_menu = new menu();
    main_menu->set_title("Main Menu");
    main_menu->items.push_back(play_button);
    main_menu->items.push_back(quit_button);
    main_menu->format();

    menu* pause_menu = new menu();
    pause_menu->set_title("Pause Menu");
    pause_menu->hide();
    pause_menu->items.push_back(resume_button);
    pause_menu->items.push_back(main_menu_button);
    pause_menu->format();

    menu* warning_menu = new menu();
    warning_menu->set_title("Warning");
    warning_menu->set_subtitle("Are you sure you want to leave?");
    warning_menu->hide();
    warning_menu->layout=HORIZONTAL;
    warning_menu->items.push_back(confirm_return_button);
    warning_menu->items.push_back(cancel_return_button);
    warning_menu->format();
    std::clog<<"initialized menus\n";
//Initialize Scenes
    std::clog<<"initializing scenes...\n";
    scene* home_screen = new scene();
    home_screen->menus.push_back(main_menu);
    home_screen->bind_key(27,quit);
    scenes.push_back(home_screen);

    scene* game_screen = new scene();
    game_screen->background_color.set(WHITE);
    game_screen->add_draggable_object(do1);
    game_screen->add_physics_object(po1);
    game_screen->add_physics_object(po2);
    game_screen->add_physics_object(po3);
    game_screen->add_physics_object(po4);
    game_screen->add_rts_object(rtso1);
    game_screen->add_rts_object(rtso2);
    game_screen->add_rts_object(rtso3);
    game_screen->add_rts_object(rtso4);
    game_screen->buttons.push_back(create_po_button);
    game_screen->buttons.push_back(create_do_button);
    game_screen->buttons.push_back(create_rtso_button);
    game_screen->buttons.push_back(delete_object_button);
    game_screen->buttons.push_back(menu_button);
    game_screen->menus.push_back(pause_menu);
    game_screen->menus.push_back(warning_menu);
    game_screen->text_objects.push_back(object_info);
    game_screen->text_objects.push_back(game_info);
    game_screen->bind_key('w',controls::move_forward);
    game_screen->bind_key('a',controls::move_left);
    game_screen->bind_key('s',controls::move_back);
    game_screen->bind_key('d',controls::move_right);
    game_screen->bind_key('q',controls::turn_left);
    game_screen->bind_key('e',controls::turn_right);
    scenes.push_back(game_screen);
}

void game::add_draggable_object()
{
    draggable_object* new_do = new draggable_object();
    scenes[window::current_scene]->draggable_objects.insert(std::pair<int,draggable_object*>(object::total_objects,new_do));//add object to current scene
}

void game::add_physics_object()
{
    physics_object* new_po = new physics_object();
    scenes[window::current_scene]->physics_objects.insert(std::pair<int,physics_object*>(object::total_objects,new_po));//add object to current scene
}

void game::add_rts_object()
{
    rts_object* new_rtso = new rts_object();
    scenes[window::current_scene]->rts_objects.insert(std::pair<int,rts_object*>(object::total_objects,new_rtso));//add object to current scene
}

void game::delete_selected()
{
    scenes[window::current_scene]->draggable_objects.erase(cursor::selected_object);
    scenes[window::current_scene]->physics_objects.erase(cursor::selected_object);
    scenes[window::current_scene]->rts_objects.erase(cursor::selected_object);
    std::clog<<"object#"<<cursor::left_clicked_object->get_number()<<": "<<cursor::left_clicked_object->name<<'('<<cursor::left_clicked_object->get_type()<<')'<<" deleted."<<std::endl;
}

void game::play()
{
    window::current_scene=1;//open game screen
    std::clog<<"started game."<<std::endl;
}

void game::pause()
{
    paused=true;
    scenes[1]->menus[0]->show();//show the pause menu
    scenes[1]->menus[1]->hide();//hide the warning prompt
    scenes[1]->hide_buttons();//disable the buttons
    std::clog<<"paused game."<<std::endl;
}

void game::resume()
{
    paused=false;
    scenes[1]->menus[0]->hide();//hide the pause menu
    scenes[1]->show_buttons();//enable the buttons
    std::clog<<"resumed game."<<std::endl;
}

void game::return_warning()
{
    cursor::reset();
    scenes[1]->menus[0]->hide();//hide the pause menu
    scenes[1]->menus[1]->show();//show the warning prompt
}

void game::return_menu()
{
    cursor::reset();
    window::current_scene=0;//open home screen
    std::clog<<"returned to menu."<<std::endl;
}

void game::quit()
{
    std::clog<<"quitting...\n";
    exit(0);
}
