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

#ifndef SCENE_H
#define SCENE_H
#include "model.h"
#include "label.h"
#include "checkbox.h"
#include "button.h"
#include "menu.h"
#include "dropdown_menu.h"
#include <map>
#include <vector>
#include <sstream>

class scene
{
private:
    int number;
public:
    static int total_scenes;
    std::string file_name;
    basic_object foreground, middleground, background;
    basic_object* current_object;
    basic_object* last_object;
    ui::menu* current_menu;
    model* current_model;
    std::map<int,model*> models;
    std::map<unsigned char, void (*)()> key_bindings;
    std::map<unsigned char, int*> key_toggles;
    std::map<std::string, void (*)()> special_bindings;
    std::map<std::string, int*> special_toggles;
    std::vector<ui::label*> labels;
    std::vector<ui::checkbox*> checkboxes;
    std::vector<ui::button*> buttons;
    std::vector<ui::menu*> menus;
    std::vector<ui::dropdown_menu*> dropdown_menus;
    void add_model(model* mdl);//add a model to the scene
    void add_label(ui::label* lbl);//add label to the scene
    void add_checkbox(ui::checkbox* cbx);//add checkbox to the scene
    void add_button(ui::button* btn);//add button to the scene
    void add_menu(ui::menu* mnu);//add menu to the scene
    void add_menu(ui::dropdown_menu* ddm);//add dropdown menu to the scene
    void switch_menu(int index);//make the menu at given index current and hide other menus
    void switch_menu(ui::menu* mnu);//make given menu current and hide other menus
    void bind_key(unsigned char key, int* toggle);//associate a key which will toggle a game option on/off
    void bind_key(std::string special_key, int* toggle);//associate a key which will toggle a game option on/off
    void bind_key(unsigned char key, void (*action)());//associate a key with an action
    void bind_key(std::string special_key, void (*action)());//associate a special key with an action
    void show_labels();//show labels
    void hide_labels();//hide labels
    void show_models();//show all objects
    void hide_models();//hide all objects
    void enable_models();//enable object mouse interaction
    void disable_models();//disable object mouse interaction
    void mute_models();//silence model sound
    void unmute_models();//enable model sound
    void show_checkboxes();//show all checkboxes
    void hide_checkboxes();//hide all checkboxes
    void enable_checkboxes();//enable checkbox mouse interaction
    void disable_checkboxes();//disable checkbox mouse interaction
    void mute_checkboxes();//disable checkbox sound
    void unmute_checkboxes();//enable checkbox sound
    void show_buttons();//show all buttons
    void hide_buttons();//hide all buttons
    void enable_buttons();//enable button mouse interaction
    void disable_buttons();//disable button mouse interaction
    void mute_buttons();//disable button sound
    void unmute_buttons();//enable button sound
    void show_menus();//show all menus
    void hide_menus();//hide all menus
    void enable_menus();//enable all menus
    void disable_menus();//disable all menus
    void mute_menus();//mute all menus
    void unmute_menus();//unmute all menus
    void show_dropdown_menus();//show all dropdown menus
    void hide_dropdown_menus();//hide all dropdown menus
    void enable_dropdown_menus();//enable all dropdown menus
    void disable_dropdown_menus();//disable all dropdown menus
    void mute_dropdown_menus();//mute all dropdown menus
    void unmute_dropdown_menus();//unmute all dropdown menus
    void show_textures();//disable object fill colors and enable textures
    void hide_textures();//enable object fill colors and disable textures
    void show_all();//show all objects and ui elements
    void hide_all();//hide all objects and ui elements
    void enable_all();//enable all ui elements
    void disable_all();//disable all ui elements
    void mute_all();//disable all sounds
    void unmute_all();//enable all sounds
    void render();//render all objects and ui elements
    void update();//update all objects and ui elements
    void load();//load all objects
    void save();//save data to file
    void sync();//update clock-based items
    void clear();//delete all objects and ui elements
    scene();
};

#endif // SCENE_H
