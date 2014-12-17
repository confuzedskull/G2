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
#include "audio.h"
#include "ui.h"
#include "graphics.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>

//initialize variables
clock_t game::time_started;
double game::time = 0.0f;
double game::time_elapsed = 0.0f;
int  game::state=2;
scene* game::current_scene = new scene();
scene* game::main_scene = new scene();
scene* game::play_scene = new scene();
std::vector<scene*> game::scenes;
std::map<std::string, game::setting> game::settings;
std::map<std::string, game::condition> game::conditions;

//All the elements of the game are initialized here
void game::initialize()
{
//Initialize Settings
    add_setting("window","width",&window::width);
    add_setting("window","height",&window::height);
    add_setting("window","position_x",&window::position.x);
    add_setting("window","position_y",&window::position.y);
    add_setting("window","refresh_rate",&window::refresh_rate);
    add_setting("ui","overlay_margin",&ui::overlay_margin);
    add_setting("game","show_info_overlay",0);
    add_setting("game","show_draggable_objects",1);
    add_setting("game","show_physics_objects",1);
    add_setting("game","show_rts_objects",1);
    add_setting("draggable_object","default_x",&draggable_object::default_position.x);
    add_setting("draggable_object","default_y",&draggable_object::default_position.y);
    add_setting("draggable_object","default_width",&draggable_object::default_width);
    add_setting("draggable_object","default_height",&draggable_object::default_height);
    add_setting("physics_object","default_x",&physics_object::default_position.x);
    add_setting("physics_object","default_y",&physics_object::default_position.y);
    add_setting("physics_object","default_width",&physics_object::default_width);
    add_setting("physics_object","default_height",&physics_object::default_height);
    add_setting("rts_object","default_x",&rts_object::default_position.x);
    add_setting("rts_object","default_y",&rts_object::default_position.y);
    add_setting("rts_object","default_width",&rts_object::default_width);
    add_setting("rts_object","default_height",&rts_object::default_height);
//Initialize Conditions
    add_condition("game","show_info_overlay",1,ui::show_text);
    add_condition("game","show_info_overlay",0,ui::hide_text);
    add_condition("game","show_draggable_objects",1,show_draggable_objects);
    add_condition("game","show_draggable_objects",0,hide_draggable_objects);
    add_condition("game","show_physics_objects",1,show_physics_objects);
    add_condition("game","show_physics_objects",0,hide_physics_objects);
    add_condition("game","show_rts_objects",1,show_rts_objects);
    add_condition("game","show_rts_objects",0,hide_rts_objects);
//Initialize Sound Effects
    audio::add_sound("clack.wav");
    audio::add_sound("pop.wav");
    audio::add_sound("trash.wav");
    audio::add_sound("click.wav");
    audio::add_sound("swipe.wav");
//Initialize Objects
    std::clog<<"initializing objects...\n";
    //initialize the physics objects
    physics_object* po1 = new physics_object();
    po1->set_position(window::center.x-48,window::center.y+48);//set position forward left of window center
    po1->rest();//make sure the resting point matches the new position
    po1->cue_action("wait",50);
    po1->cue_action("move right",10);
    po1->cue_action("wait",100);
    po1->cue_action("move back",10);
    po1->cue_action("wait",100);
    po1->cue_action("move left",10);
    po1->cue_action("wait",100);
    po1->cue_action("move forward",10);
    po1->cue_action("wait",100);
    po1->cue_action("turn left",30);
    po1->cue_action("wait",50);
    po1->cue_action("turn right",30);

    physics_object* po2 = new physics_object();
    po2->set_position(window::center.x+48,window::center.y+48);//set position forward right of window center
    po2->rest();//make sure the resting point matches the new position
    po2->cue_action("wait",50);
    po2->cue_action("move back",10);
    po2->cue_action("wait",100);
    po2->cue_action("move left",10);
    po2->cue_action("wait",100);
    po2->cue_action("move forward",10);
    po2->cue_action("wait",100);
    po2->cue_action("move right",10);
    po2->cue_action("wait",100);
    po2->cue_action("turn left",30);
    po2->cue_action("wait",50);
    po2->cue_action("turn right",30);

    physics_object* po3 = new physics_object();
    po3->set_position(window::center.x+48,window::center.y-48);//set position backward right of window center
    po3->rest();//make sure the resting point matches the new position
    po3->cue_action("wait",50);
    po3->cue_action("move left",10);
    po3->cue_action("wait",100);
    po3->cue_action("move forward",10);
    po3->cue_action("wait",100);
    po3->cue_action("move right",10);
    po3->cue_action("wait",100);
    po3->cue_action("move back",10);
    po3->cue_action("wait",100);
    po3->cue_action("turn left",30);
    po3->cue_action("wait",50);
    po3->cue_action("turn right",30);

    physics_object* po4 = new physics_object();
    po4->set_position(window::center.x-48,window::center.y-48);//set position backward left of window center
    po4->rest();//make sure the resting point matches the new position
    po4->cue_action("wait",50);
    po4->cue_action("move forward",10);
    po4->cue_action("wait",100);
    po4->cue_action("move right",10);
    po4->cue_action("wait",100);
    po4->cue_action("move back",10);
    po4->cue_action("wait",100);
    po4->cue_action("move left",10);
    po4->cue_action("wait",100);
    po4->cue_action("turn left",30);
    po4->cue_action("wait",50);
    po4->cue_action("turn right",30);
    std::clog<<"initialized physics objects\n";
    //initialize the draggable objects
    draggable_object* do1 = new draggable_object();
    do1->set_position(window::center.x,window::center.y);//set position window center

    std::clog<<"initialized draggable objects\n";
    //initialize the rts objects
    rts_object* rtso1 = new rts_object();
    rtso1->set_position(window::center.x+96,window::center.y);//set position right of window center
    rtso1->fill_color.set("yellow");

    rts_object* rtso2 = new rts_object();
    rtso2->set_position(window::center.x,window::center.y-96);//set position below window center
    rtso2->fill_color.set("green");

    rts_object* rtso3 = new rts_object();
    rtso3->set_position(window::center.x,window::center.y+96);//set position above window center
    rtso3->fill_color.set("red");

    rts_object* rtso4 = new rts_object();
    rtso4->set_position(window::center.x-96,window::center.y);//set position left of window center
    rtso4->fill_color.set("blue");
    std::clog<<"initialized rts objects\n";
//Initialize Text
    //Information Overlay Text
    label* object_info = new label();
    object_info->spacing=20;
    object_info->set_position(ui::overlay_margin,window::height-20);
    object_info->hide();//we don't want to see this right away

    label* game_info = new label();
    game_info->spacing=20;
    game_info->set_position(window::width-(ui::overlay_margin+200),window::height-20);
    game_info->hide();//we don't want to see this right away

    std::clog<<"initialized text\n";
    std::clog<<"initializing user interface...\n";
//Initialize Checkboxes
    checkbox* show_dos_checkbox = new checkbox();
    show_dos_checkbox->set_position(window::width*0.9,window::height*0.4);
    show_dos_checkbox->set_label("show draggable objects");
    show_dos_checkbox->bind_option(settings["game"]["show_draggable_objects"]);

    checkbox* show_pos_checkbox = new checkbox();
    show_pos_checkbox->set_position(window::width*0.9,window::height*0.35);
    show_pos_checkbox->set_label("show physics objects");
    show_pos_checkbox->bind_option(settings["game"]["show_physics_objects"]);

    checkbox* show_rtsos_checkbox = new checkbox();
    show_rtsos_checkbox->set_position(window::width*0.9,window::height*0.3);
    show_rtsos_checkbox->set_label("show rts objects");
    show_rtsos_checkbox->bind_option(settings["game"]["show_rts_objects"]);

    std::clog<<"initialized checkboxes\n";
//Initialize Buttons
    //Main Menu Buttons
    button* play_button = new button();
    play_button->set_label("Play");
    play_button->set_action(play);

    button* load_button = new button();
    load_button->set_label("Load");
    load_button->set_action(load);

    button* quit_button = new button();
    quit_button->set_label("Quit");
    quit_button->set_action(switch_menu,1);
    //Quit Menu Buttons
    button* confirm_quit = new button();
    confirm_quit->set_label("Yes");
    confirm_quit->set_action(quit);

    button* cancel_quit = new button();
    cancel_quit->set_label("No");
    cancel_quit->set_action(switch_menu,0);
    //Pause Menu Buttons
    button* resume_button = new button();
    resume_button->set_label("Resume");
    resume_button->set_action(resume);

    button* save_button = new button();
    save_button->set_label("Save");
    save_button->set_action(save);

    button* main_menu_button = new button();
    main_menu_button->set_label("Main Menu");
    main_menu_button->set_action(switch_menu,1);
    //Warning Menu Buttons
    button* confirm_return_button = new button();
    confirm_return_button->set_label("Yes");
    confirm_return_button->set_action(return_menu);

    button* cancel_return_button = new button();
    cancel_return_button->set_label("No");
    cancel_return_button->set_action(switch_menu,0);
    //Game Buttons
    button* create_po_button = new button();//"po" stands for "physics object"
    create_po_button->set_label("physics object");
    create_po_button->set_action(add_physics_object);

    button* create_do_button = new button();//"do" stands for "draggable object"
    create_do_button->set_label("draggable object");
    create_do_button->set_action(add_draggable_object);

    button* create_rtso_button = new button();//"rtso" stands for "real-time strategy object"
    create_rtso_button->set_label("rts object");
    create_rtso_button->set_action(add_rts_object);

    button* create_object_button = new button();
    create_object_button->set_position(window::width*0.9,window::height*0.1);//put the button on the right side, 1/5th of the way up
    create_object_button->set_label("create object");
    create_object_button->set_action(create_object);

    button* delete_object_button = new button();
    delete_object_button->set_position(window::width*0.9,window::height*0.05);//put the button on the right side, 1/5th of the way up
    delete_object_button->set_label("delete object");
    delete_object_button->set_action(delete_selected);

    button* menu_button = new button();
    menu_button->set_position(window::center.x,window::height-20);//put the button at the top middle, just below the top
    menu_button->set_label("Menu");
    menu_button->set_action(pause);
    std::clog<<"initialized buttons\n";
//Initialize Menus
    dropdown_menu* creation_menu = new dropdown_menu();
    creation_menu->set_title("create new...");
    creation_menu->set_position(window::width*0.9,window::height*0.25);
    creation_menu->add_item(create_do_button);
    creation_menu->add_item(create_po_button);
    creation_menu->add_item(create_rtso_button);

    menu* main_menu = new menu();
    main_menu->set_title("Main Menu");
    main_menu->add_item(play_button);
    main_menu->add_item(load_button);
    main_menu->add_item(quit_button);
    main_menu->format();

    menu* quit_menu = new menu();
    quit_menu->set_title("Warning");
    quit_menu->set_subtitle("Are you sure you want to quit?");
    quit_menu->add_item(confirm_quit);
    quit_menu->add_item(cancel_quit);
    quit_menu->set_layout("horizontal");
    quit_menu->format();
    quit_menu->hide();//we don't want to see this right away

    menu* pause_menu = new menu();
    pause_menu->set_title("Pause Menu");
    pause_menu->add_item(resume_button);
    pause_menu->add_item(save_button);
    pause_menu->add_item(main_menu_button);
    pause_menu->format();
    pause_menu->hide();//we don't want to see this right away

    menu* leave_menu = new menu();
    leave_menu->set_title("Warning");
    leave_menu->set_subtitle("Are you sure you want to leave?");
    leave_menu->set_layout("horizontal");
    leave_menu->add_item(confirm_return_button);
    leave_menu->add_item(cancel_return_button);
    leave_menu->format();
    leave_menu->hide();//we don't want to see this right away
    std::clog<<"initialized menus\n";
//Initialize Scenes
    std::clog<<"initializing scenes...\n";
    scene* home_screen = new scene();
    home_screen->add_menu(main_menu);
    home_screen->add_menu(quit_menu);
    home_screen->current_menu=main_menu;
    home_screen->bind_key("up",controls::previous_item);
    home_screen->bind_key("down",controls::next_item);
    home_screen->bind_key("left",controls::previous_item);
    home_screen->bind_key("right",controls::next_item);
    home_screen->bind_key('\r',controls::choose_item);
    home_screen->bind_key(27,warn_quit);//27 is the 'esc' key
    scenes.push_back(home_screen);//add to scenes
    main_scene=home_screen;//make this the main scene
    current_scene=home_screen;//start the game with this screen

    scene* game_screen = new scene();
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
    game_screen->add_checkbox(show_dos_checkbox);
    game_screen->add_checkbox(show_pos_checkbox);
    game_screen->add_checkbox(show_rtsos_checkbox);
    game_screen->add_button(delete_object_button);
    game_screen->add_button(create_object_button);
    game_screen->add_button(menu_button);
    game_screen->add_menu(pause_menu);
    game_screen->add_menu(leave_menu);
    game_screen->add_menu(creation_menu);
    game_screen->bind_key('w',controls::move_forward);
    game_screen->bind_key('a',controls::move_left);
    game_screen->bind_key('s',controls::move_back);
    game_screen->bind_key('d',controls::move_right);
    game_screen->bind_key('q',controls::turn_left);
    game_screen->bind_key('e',controls::turn_right);
    game_screen->bind_key('i',settings["game"]["show_info_overlay"]);
    game_screen->bind_key('\r',controls::choose_item);
    game_screen->bind_key("up",controls::previous_item);
    game_screen->bind_key("down",controls::next_item);
    game_screen->bind_key("left",controls::previous_item);
    game_screen->bind_key("right",controls::next_item);
    game_screen->bind_key("insert",game::create_object);
    game_screen->bind_key(127,delete_selected);//127 is the delete key
    game_screen->bind_key(27, pause);//27 is the 'esc' key
    play_scene=game_screen;
    scenes.push_back(game_screen);//add to scenes
}

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
                if(a.second->collided)
                    audio::play("clack.wav");
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
                if(a.second->collided)
                    audio::play("clack.wav");
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
                if(a.second->collided)
                    audio::play("clack.wav");
            }
        }
    }
}

void game::switch_menu(int index)
{
    current_scene->switch_menu(index);
}

void game::add_setting(std::string section, std::string property, int value)
{
    //check if the setting already exists
    if(settings.find(section)!=settings.end() && settings[section].find(property)!=settings[section].end())
        *settings[section][property]=value;//assign setting given value
    else
    {
        int* variable = new int(value);//create a new variable to associate with this value
        settings[section][property]=variable;//add variable to settings
    }
}

void game::add_setting(std::string section, std::string property, int* variable)
{
    settings[section][property]=variable;
}

void game::add_condition(std::string section, std::string property, int value, void (*action)())
{
    conditions[section][property][value]=action;
}

void game::load_settings()
{
    state=LOADING;
    std::clog<<"loading settings...\n";
    std::ifstream config_file("./data/settings.ini");
    while(config_file.good())
    {
        std::string file_line;
        char first_char=config_file.peek();//check the first character
        if(first_char=='[')//section is detected
        {
            config_file>>file_line;
            std::string section=file_line.substr(1,file_line.length()-2);//the section name is between the brackets
            do
            {
                //load settings
                std::string property;
                char separator;
                int value;
                config_file>>property>>separator>>value;
                add_setting(section,property,value);
                std::clog<<"setting: "<<section<<"::"<<property<<':'<<value<<" loaded."<<std::endl;
                config_file.get();//eat the newline character
                first_char=config_file.peek();//check the first character
            }
            while(first_char!='[' && first_char>0);//as long as new section is not detected
        }
    }
    config_file.close();
    std::clog<<"settings loaded.\n";
}

void game::save_settings()
{
    std::clog<<"saving settings...\n";
    std::ofstream config_file("./data/settings.ini");
    for(auto sect:settings)//iterate through sections
    {
        config_file<<'['<<sect.first<<']'<<std::endl;//add section header
        for(auto sett:sect.second)//iterate through settings
            config_file<<sett.first<<" = "<<*sett.second<<std::endl;//add property and value
    }
    config_file.close();
    std::clog<<"settings saved.\n";
}

void game::show_draggable_objects()
{
    play_scene->show_draggable_objects();
}

void game::hide_draggable_objects()
{
    play_scene->hide_draggable_objects();
}

void game::show_physics_objects()
{
    play_scene->show_physics_objects();
}

void game::hide_physics_objects()
{
    play_scene->hide_physics_objects();
}

void game::show_rts_objects()
{
    play_scene->show_rts_objects();
}

void game::hide_rts_objects()
{
    play_scene->hide_rts_objects();
}

void game::add_draggable_object()
{
    audio::play("pop.wav");
    draggable_object* new_do = new draggable_object();
    play_scene->add_object(new_do);
}

void game::add_physics_object()
{
    audio::play("pop.wav");
    physics_object* new_po = new physics_object();
    play_scene->add_object(new_po);
}

void game::add_rts_object()
{
    audio::play("pop.wav");
    rts_object* new_rtso = new rts_object();
    play_scene->add_object(new_rtso);
}

void game::create_object()
{
    audio::play("pop.wav");
    if(play_scene->last_object->get_type()=="draggable object")
        play_scene->add_object(new draggable_object());
    if(play_scene->last_object->get_type()=="physics object")
        play_scene->add_object(new physics_object());
    if(play_scene->last_object->get_type()=="rts object")
        play_scene->add_object(new rts_object());
}

void game::delete_selected()
{
    audio::play("trash.wav");
    for(auto so:cursor::selected_objects)
    {
        if(play_scene->draggable_objects.find(so.first)!=play_scene->draggable_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<"(draggable object)"<<" deleted."<<std::endl;
            delete play_scene->draggable_objects[so.first];
            play_scene->draggable_objects.erase(so.first);
        }
        if(play_scene->physics_objects.find(so.first)!=play_scene->physics_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<"(physics object)"<<" deleted."<<std::endl;
            delete play_scene->physics_objects[so.first];
            play_scene->physics_objects.erase(so.first);
        }
        if(play_scene->rts_objects.find(so.first)!=play_scene->rts_objects.end())
        {
            std::clog<<"object#"<<so.second->get_number()<<"(rts object)"<<" deleted."<<std::endl;
            delete play_scene->rts_objects[so.first];
            play_scene->rts_objects.erase(so.first);
        }
    }
    cursor::selected_objects.clear();
}

void game::play()
{
    if(state!=PLAYING)
    {
        state=PLAYING;
        cursor::reset();
        cursor::highlighting_enabled=true;
        time=0.0;//reset the clock
        time_elapsed=0.0;
        play_scene->enable_all();
        play_scene->menus[0]->hide();//hide the pause menu
        play_scene->menus[1]->hide();//hide the warning menu
        play_scene->current_menu=play_scene->dropdown_menus[0];//set the creation menu as current
        current_scene=play_scene;//open game screen
        std::clog<<"game started.\n";
    }
}

void game::pause()
{
    if(state!=PAUSED)
    {
        state=PAUSED;
        cursor::highlighting_enabled=false;
        audio::pause_all();
        switch_menu(0);
        play_scene->disable_all();
        std::clog<<"game paused.\n";
    }
}

void game::resume()
{
    state=PLAYING;
    cursor::highlighting_enabled=true;
    play_scene->enable_all();
    play_scene->menus[0]->hide();//hide pause menu
    play_scene->menus[1]->hide();//hide warning menu
    play_scene->current_menu=play_scene->dropdown_menus[0];//set the creation menu as current
    std::clog<<"game resumed.\n";
}

void game::warn_quit()
{
    switch_menu(1);
}

void game::return_menu()
{
    cursor::reset();
    current_scene->draggable_objects.clear();
    current_scene->physics_objects.clear();
    current_scene->rts_objects.clear();
    main_scene->menus[0]->show();//enable the main menu
    main_scene->menus[1]->hide();//hide the quit menu
    main_scene->current_menu=main_scene->menus[0];//set main menu as current
    current_scene=main_scene;//open home screen
    std::clog<<"returned to menu.\n";
}

void game::quit()
{
    save_settings();
    std::clog<<"quitting...\n";
    audio::close();
    exit(0);
}

void game::update()
{
    if(state!=PAUSED)
    {
        time_elapsed = ((float)clock()-time_started)/CLOCKS_PER_SEC;//update the start time
        collision_detection();//apply collision effects
    }
    current_scene->update();//update scene
    //process settings
    for(auto sect:settings)//iterate through sections
    {
        for(auto sett:sect.second)//iterate through settings
        {
            if(conditions.find(sect.first)!=conditions.end())//section exists
            {
                if(conditions[sect.first].find(sett.first)!=conditions[sect.first].end())//matching condition exists
                {
                    for(auto val:conditions[sect.first][sett.first])//iterate through the conditions
                    {
                        if(*sett.second == val.first)//setting value matches condition value
                            val.second();//perform associated action
                    }
                }
            }
        }
    }
}

void game::load()
{
    std::clog<<"loading game...\n";
    state=LOADING;
    time=0.0;
    time_elapsed=0.0;
    play_scene->load();
    std::clog<<"game loaded.\n";
    play();
}

void game::save()
{
    std::clog<<"saving game...\n";
    state=SAVING;
    play_scene->save();
    std::clog<<"game saved.\n";
}

void game::sync()
{
    if(state!=PAUSED)
    {
        time_started=clock();//reset the start time
        time+=(double)1/window::refresh_rate;//increment the game clock
        play_scene->sync();//update clock-based events
    }
}
