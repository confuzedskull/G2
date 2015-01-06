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

#ifndef SCENE_H
#define SCENE_H
#include "menu.h"
#include "checkbox.h"
#include "dropdown_menu.h"
#include "advanced_object.h"
#include <map>
#include <vector>

class scene
{
private:
    int number;
    std::string music;
    std::string ambience;
    bool music_started;
    bool ambience_started;
public:
    static int total_scenes;
    std::string file_name;
    basic_object* current_object;
    basic_object* previous_object;
    advanced_object* player;
    ui::menu* current_menu;
    std::map<unsigned char, void (*)()> key_bindings;
    std::map<unsigned char, int*> key_toggles;
    std::map<std::string, void (*)()> special_bindings;
    std::map<std::string, int*> special_toggles;
    std::vector<basic_object*> basic_objects;
    std::vector<complex_object*> complex_objects;
    std::vector<mobile_object*> mobile_objects;
    std::vector<smart_object*> smart_objects;
    std::vector<physical_object*> physical_objects;
    std::vector<interactive_object*> interactive_objects;
    std::vector<advanced_object*> advanced_objects;
    std::vector<ui::label*> labels;
    std::vector<ui::checkbox*> checkboxes;
    std::vector<ui::button*> buttons;
    std::vector<ui::menu*> menus;
    std::vector<ui::dropdown_menu*> dropdown_menus;
    void remove_object(basic_object* bso);//remove basic object from the scene
    void remove_object(complex_object* cpo);//remove complex object from the scene
    void remove_object(mobile_object* mbo);//remove movable object from the scene
    void remove_object(smart_object* smo);//remove smart object from the scene
    void remove_object(physical_object* pso);//remove physics object from the scene
    void remove_object(interactive_object* iao);//remove interactive object from the scene
    void remove_object(advanced_object* avo);//remove advanced_object from the scene
    void add_object(basic_object* bso);//add basic object to the scene
    void add_object(complex_object* cpo);//add complex object to the scene
    void add_object(mobile_object* mbo);//add movable object to the scene
    void add_object(smart_object* smo);//add smart object to the scene
    void add_object(physical_object* pso);//add physics object to the scene
    void add_object(interactive_object* iao);//add interactive object to the scene
    void add_object(advanced_object* avo);//add advanced object to the scene
    void add_label(ui::label* lbl);//add label to the scene
    void add_checkbox(ui::checkbox* cbx);//add checkbox to the scene
    void add_button(ui::button* btn);//add button to the scene
    void add_menu(ui::menu* mnu);//add menu to the scene
    void add_dropdown(ui::dropdown_menu* ddm);//add dropdown menu to the scene
    void switch_menu(int index);//make the menu at given index current and hide other menus
    void switch_menu(ui::menu* mnu);//make given menu current and hide other menus
    void bind_key(unsigned char key, int* toggle);//associate a key which will toggle a game option on/off
    void bind_key(std::string special_key, int* toggle);//associate a key which will toggle a game option on/off
    void bind_key(unsigned char key, void (*action)());//associate a key with an action
    void bind_key(std::string special_key, void (*action)());//associate a special key with an action
    void set_music(std::string filename);
    void set_ambience(std::string filename);
    void render();//render all objects and ui elements
    void update();//update all objects and ui elements
    void sync();//update clock-based items
    void load();//load all objects
    void save();//save data to file
    void clear();//delete all objects and ui elements
    scene();
};

#endif // SCENE_H
