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
#include "draggable_object.h"
#include "physics_object.h"
#include "rts_object.h"
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
public:
    static int total_scenes;
    std::string file_name;
    int number;
    color background_color;
    object* last_object;
    menu* current_menu;
    //maps are used because we need to access the objects by referencing a common identifier (object.number)
    //pointers are used because everything is created in game::initialize() and we just need to reference them
    std::map<int,draggable_object*> draggable_objects;
    std::map<int,physics_object*> physics_objects;
    std::map<int,rts_object*> rts_objects;
    std::map<unsigned char, void (*)()> key_bindings;
    std::map<unsigned char, int*> key_toggles;
    std::map<std::string, void (*)()> special_bindings;
    std::map<std::string, int*> special_toggles;
    std::vector<label*> labels;
    std::vector<checkbox*> checkboxes;
    std::vector<button*> buttons;
    std::vector<menu*> menus;
    std::vector<dropdown_menu*> dropdown_menus;
    void add_object(draggable_object*);//add a draggable object to the scene
    void add_object(physics_object*);//add a physics object to the scene
    void add_object(rts_object*);//add an rts object to the scene
    void add_text(label*);//add text object to the scene
    void add_checkbox(checkbox*);//add checkbox to the scene
    void add_button(button*);//add button to the scene
    void add_menu(menu*);//add menu to the scene
    void add_menu(dropdown_menu*);//add dropdown menu to the scene
    void switch_menu(int index);//make the menu at given index current and hide other menus
    void bind_key(unsigned char key, int* toggle);//associate a key which will toggle a game option on/off
    void bind_key(std::string special_key, int* toggle);//associate a key which will toggle a game option on/off
    void bind_key(unsigned char key, void (*action)());//associate a key with an action
    void bind_key(std::string special_key, void (*action)());//associate a special key with an action
    void show_draggable_objects();//show all draggable objects
    void hide_draggable_objects();//hide all draggable objects
    void show_physics_objects();//show all physics objects
    void hide_physics_objects();//hide all physics objects
    void show_rts_objects();//show all rts objects
    void hide_rts_objects();//hide all rts objects
    void show_text();//show the text
    void hide_text();//hide the text
    void enable_objects();//enable object mouse interaction
    void disable_objects();//disable object mouse interaction
    void show_checkboxes();//show all checkboxes
    void hide_checkboxes();//hide all checkboxes
    void enable_checkboxes();
    void disable_checkboxes();
    void show_buttons();//show all buttons
    void hide_buttons();//hide all buttons
    void enable_buttons();
    void disable_buttons();
    void show_menus();//show all menus
    void hide_menus();//hide all menus
    void enable_menus();//enable all menus
    void disable_menus();//disable all menus
    void show_all();//show all objects and ui elements
    void hide_all();//hide all objects and ui elements
    void enable_all();//enable all ui elements
    void disable_all();//disable all ui elements
    void render();//render all objects and ui elements
    void update();//update all objects and ui elements
    void load();//load all objects
    void save();//save data to file
    void sync();//update clock-based items
    void clear();//delete all objects and ui elements
    scene();
};

#endif // SCENE_H
