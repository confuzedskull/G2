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
scene* game::current_scene = new scene();
std::vector<scene*> game::scenes;

//This checks which objects are touching and what they should do when that occurs
//NOTE: This function uses C++11 "for" loops
void game::collision_detection()
{
    for(auto a:current_scene->rts_objects)//iterate through rts objects comparing
    {
        for(auto b:current_scene->rts_objects)//iterate through rts objects being compared
        {
            if(a.first!=b.first && a.second->is_close(*b.second))//check objects colliding with other objects
            {
                a.second->identify_touched(*b.second);
                a.second->repel(*b.second);
            }
        }
    }
    for(auto a:current_scene->physics_objects)//iterate through physics objects comparing
    {
        for(auto b:current_scene->physics_objects)//iterate through physics objects being compared
        {
            if(a.first!=b.first && a.second->is_close(*b.second))//check objects colliding with other objects
            {
                a.second->identify_touched(*b.second);
                a.second->repel(*b.second);
                a.second->calc_momentum(*b.second);
            }
        }
    }
    for(auto a:current_scene->draggable_objects)//iterate through draggable objects comparing
    {
        for(auto b:current_scene->draggable_objects)//iterate through draggable objects being compared
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
    do1->set_position(window::center.x,window::center.y);//set position window center
    do1->primary_color.set("black");
    std::clog<<"initialized draggable objects\n";
    //initialize the rts objects
    rts_object* rtso1 = new rts_object();
    rtso1->name="yellow square";
    rtso1->set_position(window::center.x+96,window::center.y);//set position right of window center
    rtso1->primary_color.set("yellow");

    rts_object* rtso2 = new rts_object();
    rtso2->name="green square";
    rtso2->set_position(window::center.x,window::center.y-96);//set position below window center
    rtso2->primary_color.set("green");

    rts_object* rtso3 = new rts_object();
    rtso3->name="red square";
    rtso3->set_position(window::center.x,window::center.y+96);//set position above window center
    rtso3->primary_color.set("red");

    rts_object* rtso4 = new rts_object();
    rtso4->name="blue square";
    rtso4->set_position(window::center.x-96,window::center.y);//set position left of window center
    rtso4->primary_color.set("blue");
    std::clog<<"initialized rts objects\n";
//Initialize Text
    //Information Overlay Text
    text_object* object_info = new text_object();//create a pointer and initialize it
    object_info->spacing=20;
    object_info->set_position(ui::margin,window::height-20);
    object_info->hide();//we don't want to see this right away

    text_object* game_info = new text_object();//create a pointer and initialize it
    game_info->spacing=20;
    game_info->set_position(window::width-(ui::margin+150),window::height-20);
    game_info->hide();//we don't want to see this right away

    std::clog<<"initialized text\n";
//Initialize Buttons
    std::clog<<"initializing user interface...\n";
    //Main Menu Buttons
    button* play_button = new button();//create a button pointer and initialize it
    play_button->set_label("Play");
    play_button->action=game::play;//function is assigned without '()' at the end

    button* quit_button = new button();//create a button pointer and initialize it
    quit_button->set_label("Quit");
    quit_button->action=warn_quit;//function is assigned without '()' at the end
    //Quit Menu Buttons
    button* confirm_quit = new button();
    confirm_quit->set_label("Yes");
    confirm_quit->action=game::quit;

    button* cancel_quit = new button();
    cancel_quit->set_label("No");
    cancel_quit->action=game::return_menu;
    //Pause Menu Buttons
    button* resume_button = new button();//create a button pointer and initialize it
    resume_button->set_label("Resume");
    resume_button->action=resume;//function is assigned without '()' at the end

    button* main_menu_button = new button();//create a button pointer and initialize it
    main_menu_button->set_label("Main Menu");
    main_menu_button->action=warn_return;//function is assigned without '()' at the end
    //Warning Menu Buttons
    button* confirm_return_button = new button();//create a button pointer and initialize it
    confirm_return_button->set_label("Yes");
    confirm_return_button->action=return_menu;//function is assigned without '()' at the end

    button* cancel_return_button = new button();//create a button pointer and initialize it
    cancel_return_button->set_label("No");
    cancel_return_button->action=pause;//function is assigned without '()' at the end
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
    menu* main_menu = new menu();//create a pointer and initialize it
    main_menu->set_title("Main Menu");
    main_menu->add_item(play_button);
    main_menu->add_item(quit_button);
    main_menu->format();//make sure everything is neat and tidy

    menu* quit_menu = new menu();//create a pointer and initialize it
    quit_menu->set_title("Warning");
    quit_menu->set_subtitle("Are you sure you want to quit?");
    quit_menu->add_item(confirm_quit);
    quit_menu->add_item(cancel_quit);
    quit_menu->set_layout("horizontal");
    quit_menu->format();
    quit_menu->hide();//we don't want to see this right away

    menu* pause_menu = new menu();//create a pointer and initialize it
    pause_menu->set_title("Pause Menu");
    pause_menu->add_item(resume_button);
    pause_menu->add_item(main_menu_button);
    pause_menu->format();//make sure everything is neat and tidy
    pause_menu->hide();//we don't want to see this right away

    menu* leave_menu = new menu();//create a pointer and initialize it
    leave_menu->set_title("Warning");
    leave_menu->set_subtitle("If you leave, your progress will be lost.");
    leave_menu->set_layout("horizontal");
    leave_menu->add_item(confirm_return_button);
    leave_menu->add_item(cancel_return_button);
    leave_menu->format();//make sure everything is neat and tidy
    leave_menu->hide();//we don't want to see this right away
    std::clog<<"initialized menus\n";
//Initialize Scenes
    std::clog<<"initializing scenes...\n";
    scene* home_screen = new scene();//create a pointer and initialize it
    home_screen->add_menu(main_menu);
    home_screen->add_menu(quit_menu);
    home_screen->current_menu=main_menu;
    home_screen->bind_special("up",controls::previous_item);//bind the "up" arrow key
    home_screen->bind_special("down",controls::next_item);//bind the "down" arrow key
    home_screen->bind_special("left",controls::previous_item);//bind the "left" arrow key
    home_screen->bind_special("right",controls::next_item);//bind the "right" arrow key
    home_screen->bind_key('\r',controls::choose_item);//bind the "return" key
    home_screen->bind_key(27,warn_quit);//open warning when esc is pressed
    scenes.push_back(home_screen);//add to scenes
    current_scene=home_screen;//start the game with this screen

    scene* game_screen = new scene();//create a pointer and initialize it
    game_screen->background_color.set("white");
    game_screen->add_draggable_object(do1);
    game_screen->add_physics_object(po1);
    game_screen->add_physics_object(po2);
    game_screen->add_physics_object(po3);
    game_screen->add_physics_object(po4);
    game_screen->add_rts_object(rtso1);
    game_screen->add_rts_object(rtso2);
    game_screen->add_rts_object(rtso3);
    game_screen->add_rts_object(rtso4);
    game_screen->add_text(object_info);
    game_screen->add_text(game_info);
    game_screen->add_button(create_po_button);
    game_screen->add_button(create_do_button);
    game_screen->add_button(create_rtso_button);
    game_screen->add_button(delete_object_button);
    game_screen->add_button(menu_button);
    game_screen->add_menu(pause_menu);
    game_screen->add_menu(leave_menu);
    game_screen->bind_key('w',controls::move_forward);
    game_screen->bind_key('a',controls::move_left);
    game_screen->bind_key('s',controls::move_back);
    game_screen->bind_key('d',controls::move_right);
    game_screen->bind_key('q',controls::turn_left);
    game_screen->bind_key('e',controls::turn_right);
    game_screen->bind_key('i',ui::show_text,ui::hide_text);
    game_screen->bind_key('\r',controls::choose_item);//bind the "return" key
    game_screen->bind_special("up",controls::previous_item);//bind the "up" arrow key
    game_screen->bind_special("down",controls::next_item);//bind the "down" arrow key
    game_screen->bind_special("left",controls::previous_item);//bind the "left" arrow key
    game_screen->bind_special("right",controls::next_item);//bind the "right" arrow key
    game_screen->bind_key(127,delete_selected);//bind the "delete" key
    game_screen->bind_key(27,pause);//bind the "esc" key
    scenes.push_back(game_screen);//add to scenes
}

void game::add_draggable_object()
{
    draggable_object* new_do = new draggable_object();
    current_scene->draggable_objects.insert(std::pair<int,draggable_object*>(object::total_objects,new_do));//add object to current scene
}

void game::add_physics_object()
{
    physics_object* new_po = new physics_object();
    current_scene->physics_objects.insert(std::pair<int,physics_object*>(object::total_objects,new_po));//add object to current scene
}

void game::add_rts_object()
{
    rts_object* new_rtso = new rts_object();
    current_scene->rts_objects.insert(std::pair<int,rts_object*>(object::total_objects,new_rtso));//add object to current scene
}

void game::delete_selected()
{
    current_scene->draggable_objects.erase(cursor::selected_object);
    current_scene->physics_objects.erase(cursor::selected_object);
    current_scene->rts_objects.erase(cursor::selected_object);
    std::clog<<"object#"<<cursor::left_clicked_object->get_number()<<": "<<cursor::left_clicked_object->name<<'('<<cursor::left_clicked_object->get_type()<<')'<<" deleted."<<std::endl;
}

void game::play()
{
    current_scene=scenes[1];//open game screen
    std::clog<<"started game."<<std::endl;
}

void game::pause()
{
    paused=true;
    scenes[1]->menus[0]->show();//show the pause menu
    scenes[1]->current_menu=scenes[1]->menus[0];
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

void game::warn_quit()
{
    cursor::reset();
    scenes[0]->menus[1]->show();//show the warning prompt
    scenes[0]->current_menu=scenes[0]->menus[1];
}

void game::warn_return()
{
    cursor::reset();
    scenes[1]->menus[0]->hide();//hide the pause menu
    scenes[1]->menus[1]->show();//show the warning prompt
    scenes[1]->current_menu=scenes[1]->menus[1];
}

void game::return_menu()
{
    cursor::reset();
    scenes[0]->menus[1]->hide();//hide the quit menu
    scenes[0]->current_menu=scenes[0]->menus[0];
    current_scene=scenes[0];//open home screen
    std::clog<<"returned to menu."<<std::endl;
}

void game::quit()
{
    std::clog<<"quitting...\n";
    exit(0);
}
