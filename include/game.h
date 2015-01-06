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

#ifndef GAME_H
#define GAME_H
#include "scene.h"
#include <time.h>
#include <string>
#include <vector>
#include <map>

//stores important functions and variables related to the game
namespace game
{
    typedef std::map<std::string,int*> setting;//a setting stores a variable which can be retrieved by a tag
    extern int state;//whether the game is active or not
    extern double time;//stores the current game time in seconds
    extern double time_elapsed;//time since start
    extern clock_t time_started;//start time
    extern scene* current_scene;
    extern scene* main_scene;
    extern scene* play_scene;
    extern std::vector<scene*> scenes;
    extern std::map<std::string,setting> settings;
    void add_bso();//add a basic object to the play scene
    void add_cpo();//add a complex object to the play scene
    void add_mbo();//add a mobile object to the play scene
    void add_smo();//add a smart object to the play scene
    void add_iao();//add an interactive object to the play scene
    void add_avo();//add an advanced object to the play scene
    void add_label();//add a label to the play scene
    void add_button();//add a button to the play scene
    void add_checkbox();//add a checkbox to the play scene
    void add_menu();//add a menu to the play scene
    void add_dropdown();//add a dropdown menu to the play scene
    void add_scene(scene* scn);
    void add_setting(std::string section, std::string property, int value);//creates a new variable containing the given value and associates it with a property
    void add_setting(std::string section, std::string property, int* variable);//associates a property with a variable
    void load_settings();
    void save_settings();
    void collision_detection();//handles object collision
    void initialize();
    void play();//open play scene
    void pause();//pause the game
    void resume();//unpause the game
    void load();//loads the game
    void save();//saves the game
    void sync();//update clock-based events
    void update();//update variables
    void quit();//close the program
};
const int PAUSED=0;
const int PLAYING=1;
const int LOADING=2;
const int SAVING=3;
#endif // GAME_H
