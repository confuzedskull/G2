/*  This file is a part of G2 - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano
    G2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    G2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with the rest of G2.  If not, see <http://www.gnu.org/licenses/>.*/

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

void game::add_bso()
{
    current_scene->add_object(new basic_object());
}

void game::add_cpo()
{
    current_scene->add_object(new complex_object());
}

void game::add_mbo()
{
    current_scene->add_object(new mobile_object());
}

void game::add_smo()
{
    current_scene->add_object(new smart_object());
}

void game::add_iao()
{
    current_scene->add_object(new interactive_object());
}

void game::add_avo()
{
    current_scene->add_object(new advanced_object());
}

void game::add_label()
{
    current_scene->add_label(new ui::label());
}

void game::add_button()
{
    current_scene->add_button(new ui::button());
}

void game::add_checkbox()
{
    current_scene->add_checkbox(new ui::checkbox());
}

void game::add_menu()
{
    current_scene->add_menu(new ui::menu());
}

void game::add_dropdown()
{
    current_scene->add_dropdown(new ui::dropdown_menu());
}


void game::add_scene(scene* scn)
{
    scenes.push_back(scn);
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
    for(auto a:current_scene->advanced_objects)//iterate through rts objects comparing
    {
        for(auto b:current_scene->advanced_objects)//iterate through rts objects being compared
        {
            if(a->get_number()!=b->get_number() && a->within_range(*b))//make sure compared objects are different and close to each other
            {
                a->identify_touched(*b);
                a->repel(*b);
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
        std::clog<<"game paused.\n";
    }
}

void game::resume()
{
    state=PLAYING;
    cursor::highlighting_enabled=true;
    controls::switch_menu(0);
    controls::hide_menu(0);
    std::clog<<"game resumed.\n";
}

void game::load()
{
    std::clog<<"loading game...\n";
    state=LOADING;
    time=0.0;
    time_elapsed=0.0;
    std::ifstream game_file("./data/game.dat");
    std::string filename;
    while(std::getline(game_file,filename))
    {
        filename="./data/scenes/"+filename;
        scene* s = new scene();
        s->file_name=filename;
        s->load();
        scenes.push_back(s);
        filename.clear();
    }
    game_file.close();
    play_scene->load();
    std::clog<<"game loaded.\n";
    play();
}

void game::save()
{
    std::clog<<"saving game...\n";
    state=SAVING;
    std::ofstream game_file("./data/game.dat");
    for(auto s:scenes)
    {
        game_file.open("./data/game.dat",std::fstream::app);//the file is already open so we need to append
        game_file<<s->file_name<<std::endl;
        game_file.close();
        s->save();
    }
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
}

void game::quit()
{
    save_settings();
    std::clog<<"quitting...\n";
    audio::close();
    exit(0);
}
