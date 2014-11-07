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
std::map<std::string, int> game::settings;
std::map<std::string, std::map<int,void (*)()> > game::conditions;

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
//Initialize Settings
    add_setting("show draggable objects",1);
    add_setting("show physics objects",1);
    add_setting("show rts objects",1);

//Initialize Conditions
    add_condition("show draggable objects",1,show_draggable_objects);
    add_condition("show draggable objects",0,hide_draggable_objects);
    add_condition("show physics objects",1,show_physics_objects);
    add_condition("show physics objects",0,hide_physics_objects);
    add_condition("show rts objects",1,show_rts_objects);
    add_condition("show rts objects",0,hide_rts_objects);

//Initialize Objects
    std::clog<<"initializing objects...\n";
    //initialize the physics objects
    physics_object* po1 = new physics_object();//create a pointer and initialize it
    po1->set_position(window::width/2-48,window::height/2+48);//set position forward left of window center
    po1->cue_action(2,12);//move right 12 units (remember there's momentum so a little goes a long way)
    po1->cue_action(4,12);//move down 12 units (remember there's momentum so a little goes a long way)
    po1->cue_action(1,12);//move left 12 units (remember there's momentum so a little goes a long way)
    po1->cue_action(3,12);//move up 12 units (remember there's momentum so a little goes a long way)
    po1->cue_action(5,15);//turn left 15 degrees (remember there's momentum so a little goes a long way)
    po1->cue_action(6,15);//turn right 15 degrees (remember there's momentum so a little goes a long way)

    physics_object* po2 = new physics_object();//create a pointer and initialize it
    po2->set_position(window::width/2+48,window::height/2+48);//set position forward right of window center
    po2->cue_action(4,12);//move down 12 units (remember there's momentum so a little goes a long way)
    po2->cue_action(1,12);//move left 12 units (remember there's momentum so a little goes a long way)
    po2->cue_action(3,12);//move up 12 units (remember there's momentum so a little goes a long way)
    po2->cue_action(2,12);//move right 12 units (remember there's momentum so a little goes a long way)
    po2->cue_action(5,15);//turn left 15 degrees (remember there's momentum so a little goes a long way)
    po2->cue_action(6,15);//turn right 15 degrees (remember there's momentum so a little goes a long way)

    physics_object* po3 = new physics_object();//create a pointer and initialize it
    po3->set_position(window::width/2+48,window::height/2-48);//set position backward right of window center
    po3->cue_action(1,12);//move left 12 units (remember there's momentum so a little goes a long way)
    po3->cue_action(3,12);//move up 12 units (remember there's momentum so a little goes a long way)
    po3->cue_action(2,12);//move right 12 units (remember there's momentum so a little goes a long way)
    po3->cue_action(4,12);//move down 12 units (remember there's momentum so a little goes a long way)
    po3->cue_action(5,15);//turn left 15 degrees (remember there's momentum so a little goes a long way)
    po3->cue_action(6,15);//turn right 15 degrees (remember there's momentum so a little goes a long way)

    physics_object* po4 = new physics_object();//create a pointer and initialize it
    po4->set_position(window::width/2-48,window::height/2-48);//set position backward left of window center
    po4->cue_action(3,12);//move up 12 units (remember there's momentum so a little goes a long way)
    po4->cue_action(2,12);//move right 12 units (remember there's momentum so a little goes a long way)
    po4->cue_action(4,12);//move down 12 units (remember there's momentum so a little goes a long way)
    po4->cue_action(1,12);//move left 12 units (remember there's momentum so a little goes a long way)
    po4->cue_action(5,15);//turn left 15 degrees (remember there's momentum so a little goes a long way)
    po4->cue_action(6,15);//turn right 15 degrees (remember there's momentum so a little goes a long way)
    std::clog<<"initialized physics objects\n";
    //initialize the draggable objects
    draggable_object* do1 = new draggable_object();//create a pointer and initialize it
    do1->set_position(window::center.x,window::center.y);//set position window center
    do1->fill_color.set("black");
    std::clog<<"initialized draggable objects\n";
    //initialize the rts objects
    rts_object* rtso1 = new rts_object();//create a pointer and initialize it
    rtso1->set_position(window::center.x+96,window::center.y);//set position right of window center
    rtso1->fill_color.set("yellow");

    rts_object* rtso2 = new rts_object();//create a pointer and initialize it
    rtso2->set_position(window::center.x,window::center.y-96);//set position below window center
    rtso2->fill_color.set("green");

    rts_object* rtso3 = new rts_object();//create a pointer and initialize it
    rtso3->set_position(window::center.x,window::center.y+96);//set position above window center
    rtso3->fill_color.set("red");

    rts_object* rtso4 = new rts_object();//create a pointer and initialize it
    rtso4->set_position(window::center.x-96,window::center.y);//set position left of window center
    rtso4->fill_color.set("blue");
    std::clog<<"initialized rts objects\n";
//Initialize Text
    //Information Overlay Text
    label* object_info = new label();//create a pointer and initialize it
    object_info->spacing=20;
    object_info->set_position(ui::margin,window::height-20);
    object_info->hide();//we don't want to see this right away

    label* game_info = new label();//create a pointer and initialize it
    game_info->spacing=20;
    game_info->set_position(window::width-(ui::margin+200),window::height-20);
    game_info->hide();//we don't want to see this right away

    std::clog<<"initialized text\n";
    std::clog<<"initializing user interface...\n";
//Initialize Checkboxes
    checkbox* show_dos = new checkbox();
    show_dos->set_position(window::width*0.9,window::height*0.4);
    show_dos->set_label("show draggable objects");
    show_dos->bind_option(&settings["show draggable objects"]);

    checkbox* show_pos = new checkbox();
    show_pos->set_position(window::width*0.9,window::height*0.35);
    show_pos->set_label("show physics objects");
    show_pos->bind_option(&settings["show physics objects"]);

    checkbox* show_rtsos = new checkbox();
    show_rtsos->set_position(window::width*0.9,window::height*0.3);
    show_rtsos->set_label("show rts objects");
    show_rtsos->bind_option(&settings["show rts objects"]);
    std::clog<<"initialized checkboxes\n";
//Initialize Buttons
    //Main Menu Buttons
    button* play_button = new button();//create a button pointer and initialize it
    play_button->set_label("Play");
    play_button->action=game::play;//function is assigned without '()' at the end

    button* quit_button = new button();//create a button pointer and initialize it
    quit_button->set_label("Quit");
    quit_button->action=warn_quit;//function is assigned without '()' at the end
    //Quit Menu Buttons
    button* confirm_quit = new button();//create a pointer and initialize it
    confirm_quit->set_label("Yes");
    confirm_quit->action=game::quit;

    button* cancel_quit = new button();//create a pointer and initialize it
    cancel_quit->set_label("No");
    cancel_quit->action=game::return_menu;
    //Pause Menu Buttons
    button* resume_button = new button();//create a button pointer and initialize it
    resume_button->set_label("Resume");
    resume_button->action=resume;//function is assigned without '()' at the end

    button* save_button = new button();//create a button pointer and initialize it
    save_button->set_label("Save");
    save_button->action=save;//function is assigned without '()' at the end

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
    create_po_button->set_label("physics object");
    create_po_button->action=add_physics_object;//function is assigned without '()' at the end

    button* create_do_button = new button();//"do" stands for "draggable object"
    create_do_button->set_label("draggable object");
    create_do_button->action=add_draggable_object;//function is assigned without '()' at the end

    button* create_rtso_button = new button();//"rtso" stands for "real-time strategy object"
    create_rtso_button->set_label("rts object");
    create_rtso_button->action=add_rts_object;//function is assigned without '()' at the end

    button* create_object_button = new button();//create a button pointer and initialize it
    create_object_button->set_position(window::width*0.9,window::height*0.1);//put the button on the right side, 1/5th of the way up
    create_object_button->set_label("create object");
    create_object_button->action=create_object;//function is assigned without '()' at the end

    button* delete_object_button = new button();//create a button pointer and initialize it
    delete_object_button->set_position(window::width*0.9,window::height*0.05);//put the button on the right side, 1/5th of the way up
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
    pause_menu->add_item(save_button);
    pause_menu->add_item(main_menu_button);
    pause_menu->format();//make sure everything is neat and tidy
    pause_menu->hide();//we don't want to see this right away

    menu* leave_menu = new menu();//create a pointer and initialize it
    leave_menu->set_title("Warning");
    leave_menu->set_subtitle("Are you sure you want to leave?");
    leave_menu->set_layout("horizontal");
    leave_menu->add_item(confirm_return_button);
    leave_menu->add_item(cancel_return_button);
    leave_menu->format();//make sure everything is neat and tidy
    leave_menu->hide();//we don't want to see this right away

    dropdown_menu* creation_menu = new dropdown_menu();//create a pointer and initialize it
    creation_menu->set_title("create new...");
    creation_menu->set_position(window::width*0.9,window::height*0.25);
    creation_menu->add_item(create_do_button);
    creation_menu->add_item(create_po_button);
    creation_menu->add_item(create_rtso_button);
    std::clog<<"initialized menus\n";
//Initialize Scenes
    std::clog<<"initializing scenes...\n";
    scene* home_screen = new scene();//create a pointer and initialize it
    home_screen->add_menu(main_menu);
    home_screen->add_menu(quit_menu);
    home_screen->current_menu=main_menu;
    home_screen->bind_key("up","hold",controls::previous_item);//select previous item when up arrow is pressed
    home_screen->bind_key("down","hold",controls::next_item);//select next item when down arrow is pressed
    home_screen->bind_key("left","hold",controls::previous_item);//select previous item when left arrow is pressed
    home_screen->bind_key("right","hold",controls::next_item);//select next item when right arrow is pressed
    home_screen->bind_key('\r',"press",controls::choose_item);//choose current item when return key is pressed
    home_screen->bind_key(27,"press",warn_quit);//open warning when escape key is pressed
    scenes.push_back(home_screen);//add to scenes
    current_scene=home_screen;//start the game with this screen

    scene* game_screen = new scene();//create a pointer and initialize it
    game_screen->background_color.set("white");
    game_screen->add_object(do1);
    game_screen->add_object(po1);
    game_screen->add_object(po2);
    game_screen->add_object(po3);
    game_screen->add_object(po4);
    game_screen->add_object(rtso1);
    game_screen->add_object(rtso2);
    game_screen->add_object(rtso3);
    game_screen->add_object(rtso4);
    game_screen->add_text(object_info);
    game_screen->add_text(game_info);
    game_screen->add_checkbox(show_dos);
    game_screen->add_checkbox(show_pos);
    game_screen->add_checkbox(show_rtsos);
    game_screen->add_button(delete_object_button);
    game_screen->add_button(create_object_button);
    game_screen->add_button(menu_button);
    game_screen->add_menu(pause_menu);
    game_screen->add_menu(leave_menu);
    game_screen->add_menu(creation_menu);
    game_screen->bind_key('w',"hold",controls::move_forward);//move selected object forward when 'w' key is held
    game_screen->bind_key('a',"hold",controls::move_left);//move selected object left when 'a' key is held
    game_screen->bind_key('s',"hold",controls::move_back);//move selected object back when 's' key is held
    game_screen->bind_key('d',"hold",controls::move_right);//move selected object right when 'd' key is held
    game_screen->bind_key('q',"hold",controls::turn_left);//turn selected object left when 'q' key is held
    game_screen->bind_key('e',"hold",controls::turn_right);//turn selected object right when 'e' key is held
    game_screen->bind_key('i',ui::show_text,ui::hide_text);//toggles between two actions
    game_screen->bind_key('\r',"press",controls::choose_item);//choose current item when return key is pressed
    game_screen->bind_key("up","hold",controls::previous_item);//select previous item when up arrow is held
    game_screen->bind_key("down","hold",controls::next_item);//select next item when down arrow is held
    game_screen->bind_key("left","hold",controls::previous_item);//select previous item when left arrow is held
    game_screen->bind_key("right","hold",controls::next_item);//select next item when right arrow is held
    game_screen->bind_key("insert","press",game::create_object);//creates an object when insert key is pressed
    game_screen->bind_key(127,"press",delete_selected);//delete selected object when DEL key is pressed
    game_screen->bind_key(27,pause,resume);//open/close pause menu when escape key is pressed
    scenes.push_back(game_screen);//add to scenes
}

void game::add_setting(std::string name, int value)
{
    settings[name]=value;
}

void game::add_condition(std::string name, int value, void (*action)())
{
    conditions[name][value]=action;
}

void game::show_draggable_objects()
{
    current_scene->show_draggable_objects();
}

void game::hide_draggable_objects()
{
    current_scene->hide_draggable_objects();
}

void game::show_physics_objects()
{
    current_scene->show_physics_objects();
}

void game::hide_physics_objects()
{
    current_scene->hide_physics_objects();
}

void game::show_rts_objects()
{
    current_scene->show_rts_objects();
}

void game::hide_rts_objects()
{
    current_scene->hide_rts_objects();
}

void game::add_draggable_object()
{
    draggable_object* new_do = new draggable_object();//create a pointer and initialize it
    current_scene->add_object(new_do);//add object to current scene
}

void game::add_physics_object()
{
    physics_object* new_po = new physics_object();//create a pointer and initialize it
    current_scene->add_object(new_po);//add object to current scene
}

void game::add_rts_object()
{
    rts_object* new_rtso = new rts_object();//create a pointer and initialize it
    current_scene->add_object(new_rtso);//add object to current scene
}

void game::create_object()
{
    if(current_scene->last_object->get_type()=="draggable object")
        current_scene->add_object(new draggable_object());
    if(current_scene->last_object->get_type()=="physics object")
        current_scene->add_object(new physics_object());
    if(current_scene->last_object->get_type()=="rts object")
        current_scene->add_object(new rts_object());
}

void game::delete_selected()
{
    for(auto so:cursor::selected_objects)
    {
        if(current_scene->draggable_objects.find(so.first)!=current_scene->draggable_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<'('<<so.second->get_type()<<')'<<" deleted."<<std::endl;
            delete current_scene->draggable_objects[so.first];
            current_scene->draggable_objects.erase(so.first);
        }
        if(current_scene->physics_objects.find(so.first)!=current_scene->physics_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<'('<<so.second->get_type()<<')'<<" deleted."<<std::endl;
            delete current_scene->physics_objects[so.first];
            current_scene->physics_objects.erase(so.first);
        }
        if(current_scene->rts_objects.find(so.first)!=current_scene->rts_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<'('<<so.second->get_type()<<')'<<" deleted."<<std::endl;
            delete current_scene->rts_objects[so.first];
            current_scene->rts_objects.erase(so.first);
        }
    }
    cursor::selected_objects.clear();
}

void game::play()
{
    cursor::reset();
    cursor::highlighting_enabled=true;
    paused=false;
    scenes[1]->enable_all();
    scenes[1]->menus[0]->hide();
    scenes[1]->menus[1]->hide();
    scenes[1]->current_menu=scenes[1]->dropdown_menus[0];//set the creation menu as current
    current_scene=scenes[1];//open game screen
    std::clog<<"started game."<<std::endl;
}

void game::pause()
{
    paused=true;
    cursor::highlighting_enabled=false;
    scenes[1]->menus[0]->show();//show the pause menu
    scenes[1]->menus[1]->hide();//hide the warning menu
    scenes[1]->current_menu=scenes[1]->menus[0];//set the pause menu as current
    scenes[1]->disable_all();
    std::clog<<"paused game."<<std::endl;
}

void game::resume()
{
    paused=false;
    cursor::highlighting_enabled=true;
    scenes[1]->enable_all();
    scenes[1]->menus[0]->hide();//hide pause menu
    scenes[1]->menus[1]->hide();//hide warning menu
    scenes[1]->current_menu=scenes[1]->dropdown_menus[0];//set the creation menu as current
    std::clog<<"resumed game."<<std::endl;
}

void game::warn_quit()
{
    scenes[0]->menus[0]->hide();//hide main menu
    scenes[0]->menus[1]->show();//show the quit menu
    scenes[0]->current_menu=scenes[0]->menus[1];//set the warning menu as current
}

void game::warn_return()
{
    scenes[1]->menus[0]->hide();//hide the pause menu
    scenes[1]->menus[1]->show();//show the warning prompt
    scenes[1]->current_menu=scenes[1]->menus[1];//set the warning menu as current
}

void game::return_menu()
{
    cursor::reset();
    scenes[0]->menus[0]->show();//enable the main menu
    scenes[0]->menus[1]->hide();//hide the quit menu
    scenes[0]->current_menu=scenes[0]->menus[0];//set main menu as current
    current_scene=scenes[0];//open home screen
    std::clog<<"returned to menu."<<std::endl;
}

void game::quit()
{
    std::clog<<"quitting...\n";
    exit(0);
}

void game::update()
{
    if(!paused)
    {
        time_elapsed = ((float)clock()-time_started)/CLOCKS_PER_SEC;//update the start time
        collision_detection();//apply collision effects
    }
    current_scene->update();//update scene
    //process settings
    for(auto c:conditions)//iterate through conditions
    {
        for(auto v:c.second)//iterate through the inner map of values and actions
        {
            if(v.first==settings[c.first])//setting value matches the condition
            v.second();//perform associated action

        }
    }
}

void game::save()
{
    std::clog<<"saving game...\n";
    current_scene->save();
    std::fstream settings_file("./data/settings.txt");
    for(auto s:settings)
        settings_file<<s.first<<'='<<s.second<<std::endl;
    settings_file.close();
    std::clog<<"game saved.\n";
}

void game::sync()
{
    if(!paused)
    {
        time_started=clock();//reset the start time
        time+=window::refresh_rate;//increment the game clock
        current_scene->sync();//update clock-based events
    }
}
