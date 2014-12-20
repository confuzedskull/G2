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

#ifndef GAME_H
#define GAME_H
#include "scene.h"
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>

//stores important functions and variables related to the game
namespace game
{
    extern double time;//stores the current game time in seconds
    extern clock_t time_started;//start time
    extern double time_elapsed;//time since start
    extern int state;//whether the game is active or not
    extern scene* current_scene;
    extern scene* main_scene;
    extern scene* play_scene;
    extern std::vector<scene*> scenes;
    typedef std::map<std::string,int*> setting;//a setting stores a variable which can be retrieved by a tag
    extern std::map<std::string,setting> settings;
    typedef std::map<std::string, std::map<int,void (*)()> > condition;
    extern std::map<std::string, condition> conditions;
    void add_setting(std::string section, std::string property, int value);//creates a new variable containing the given value and associates it with a property
    void add_setting(std::string section, std::string property, int* variable);//associates a property with a variable
    void add_condition(std::string section, std::string property, int value, void (*action)());//specifies what action should be performed when a property has a specific value
    void initialize();//initialize the objects
    void load_settings();
    void save_settings();
    void collision_detection();//handles object collision
    void switch_menu(int index);
    void show_foreground();
    void hide_foreground();
    void show_middleground();
    void hide_middleground();
    void show_background();
    void hide_background();
    void show_draggable_objects();//show all draggable objects in play scene
    void hide_draggable_objects();//hide all draggable objects in play scene
    void show_physics_objects();//show all physics objects in play scene
    void hide_physics_objects();//hide all physics objects in play scene
    void show_rts_objects();//show all rts objects in play scene
    void hide_rts_objects();//hide all rts objects in play scene
    void show_textures();//show all textures
    void hide_textures();//hide all textures
    void mute_all();//mute all sounds
    void unmute_all();//unmute all sounds
    void add_draggable_object();//add a draggable object to the play scene
    void add_physics_object();//add a physics object to the play scene
    void add_rts_object();//add an rts object to the play scene
    void create_object();//creates an object of the previously created type
    void delete_selected();//remove the selected object from the game
    void play();//open play scene
    void pause();//pause the game
    void resume();//unpause the game
    void return_menu();//open main menu
    void warn_quit();
    void quit();//close the program
    void update();//update variables
    void load();//loads the game
    void save();//saves the game
    void sync();//update clock-based events
};
const int PAUSED=0;
const int PLAYING=1;
const int LOADING=2;
const int SAVING=3;
#endif // GAME_H
