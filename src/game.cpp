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
#include <cstdlib>
#include <iostream>
#include <ctime>

//initialize variables
int  game::state=2;
double game::time = 0.0;
double game::time_elapsed = 0.0;
clock_t game::time_started;
scene* game::current_scene = new scene();
scene* game::main_scene = new scene();
scene* game::play_scene = new scene();
std::vector<scene*> game::scenes;
std::map<std::string, game::setting> game::settings;
std::map<std::string, game::rule> game::rules;

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

void game::add_rule(std::string section, std::string property, int value, void (*action)())
{
    rules[section][property][value]=action;
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

//This checks which objects are touching and what they should do when that occurs
//NOTE: This function uses C++11 "for" loops
void game::collision_detection()
{
    for(auto a:current_scene->rts_objects)//iterate through rts objects comparing
    {
        for(auto b:current_scene->rts_objects)//iterate through rts objects being compared
        {
            if(a.first!=b.first && a.second->within_range(*b.second))//make sure compared objects are different and close to each other
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
            if(a.first!=b.first && a.second->within_range(*b.second))//make sure compared objects are different and close to each other
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
            if(a.first!=b.first && a.second->within_range(*b.second))//make sure compared objects are different and close to each other
            {
                a.second->identify_touched(*b.second);
                a.second->repel(*b.second);
            }
        }
    }
}

void game::initialize()
{
    std::clog<<"initializing game...\n";
    game::load_settings();
    std::clog<<"initializing GLUT...\n";
    glutInitDisplayMode(GLUT_SINGLE || GLUT_RGB);
    std::clog<<"initializing window...\n";
    glutInitWindowPosition(window::position.x,window::position.y);
    glutInitWindowSize(window::width,window::height);
    glutCreateWindow(window::title.c_str());
    window::initialize();
    glutReshapeFunc(window::change_size);
    glutIdleFunc(window::update);
    std::clog<<"initializing keyboard...\n";
    glutKeyboardFunc(controls::key_pressed);
    glutKeyboardUpFunc(controls::key_released);
    glutSpecialFunc(controls::special_keys);
    std::clog<<"initializing mouse...\n";
    glutMouseFunc(controls::mouse_click);
    glutPassiveMotionFunc(controls::mouse_move);
    glutMotionFunc(controls::mouse_drag);
    std::clog<<"loading resources...\n";
    audio::initialize();
    audio::load_all();
    graphics::load_all();
    std::clog<<"rendering...\n";
    glutDisplayFunc(window::render);
    glutMainLoop();
}

void game::play()
{
    if(state!=PLAYING)
    {
        state=PLAYING;
        cursor::reset();
        cursor::highlighting_enabled=true;
        play_scene->enable_all();
        play_scene->hide_menus();
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
        controls::switch_menu(0);
        play_scene->disable_objects();
        play_scene->disable_buttons();
        play_scene->disable_checkboxes();
        play_scene->disable_dropdown_menus();
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
            if(rules.find(sect.first)!=rules.end())//section exists
            {
                if(rules[sect.first].find(sett.first)!=rules[sect.first].end())//matching rule exists
                {
                    for(auto val:rules[sect.first][sett.first])//iterate through the rules
                    {
                        if(*sett.second == val.first)//setting value matches rule value
                            val.second();//perform associated action
                    }
                }
            }
        }
    }
}

void game::quit()
{
    save_settings();
    std::clog<<"quitting...\n";
    audio::close();
    exit(0);
}
