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

#include "scene.h"
#include "game.h"
#include "cursor.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <iostream>

int scene::total_scenes=0;

void scene::add_object(draggable_object* new_do)
{
    last_object=new_do;
    draggable_objects[new_do->get_number()]=new_do;//add object to scene
}

void scene::add_object(physics_object* new_po)
{
    last_object=new_po;
    physics_objects[new_po->get_number()]=new_po;//add object to scene
}

void scene::add_object(rts_object* new_rtso)
{
    last_object=new_rtso;
    rts_objects[new_rtso->get_number()]=new_rtso;//add object to scene
}

void scene::add_text(label* t)
{
    labels.push_back(t);
}

void scene::add_checkbox(checkbox* c)
{
    checkboxes.push_back(c);
}

void scene::add_button(button* b)
{
    buttons.push_back(b);
}

void scene::add_menu(menu* m)
{
    menus.push_back(m);
}

void scene::add_menu(dropdown_menu* dm)
{
    dropdown_menus.push_back(dm);
}

void scene::switch_menu(int index)
{
    for(int i=0;i<menus.size();i++)
    {
        if(i!=index)
            menus[i]->hide();
    }
    menus[index]->show();
    current_menu=menus[index];
}

void scene::bind_key(unsigned char key, int* toggle)
{
    key_toggles[key]=toggle;
}

void scene::bind_key(std::string special_key, int* toggle)
{
    special_toggles[special_key]=toggle;
}

void scene::bind_key(unsigned char key, void (*action)())
{
    key_bindings[key]=action;
}

void scene::bind_key(std::string special_key, void (*action)())
{
    special_bindings[special_key]=action;
}

void scene::show_draggable_objects()
{
    for(auto d:draggable_objects)
        d.second->show();
}

void scene::hide_draggable_objects()
{
    for(auto d:draggable_objects)
        d.second->hide();
}

void scene::show_physics_objects()
{
    for(auto p:physics_objects)
        p.second->show();
}

void scene::hide_physics_objects()
{
    for(auto p:physics_objects)
        p.second->hide();
}

void scene::show_rts_objects()
{
    for(auto r:rts_objects)
        r.second->show();
}

void scene::hide_rts_objects()
{
    for(auto r:rts_objects)
        r.second->hide();
}

void scene::enable_objects()
{
    for(auto p:physics_objects)
        p.second->enable();
    for(auto d:draggable_objects)
        d.second->enable();
    for(auto r:rts_objects)
        r.second->enable();
}

void scene::disable_objects()
{
    for(auto p:physics_objects)
        p.second->disable();
    for(auto d:draggable_objects)
        d.second->disable();
    for(auto r:rts_objects)
        r.second->disable();
}

void scene::show_text()
{
    for(auto t:labels)//C++11 "for" loop
        t->show();
}

void scene::hide_text()
{
    for(auto t:labels)//C++11 "for" loop
        t->hide();
}

void scene::show_checkboxes()
{
    for(auto c:checkboxes)
        c->show();
}

void scene::hide_checkboxes()
{
    for(auto c:checkboxes)
        c->hide();
}

void scene::enable_checkboxes()
{
    for(auto c:checkboxes)
        c->enable();
}

void scene::disable_checkboxes()
{
    for(auto c:checkboxes)
        c->disable();
}

void scene::show_buttons()
{
    for(auto b:buttons)//C++11 "for" loop
        b->show();
}

void scene::hide_buttons()
{
    for(auto b:buttons)//C++11 "for" loop
        b->hide();
}

void scene::enable_buttons()
{
    for(auto b:buttons)//C++11 "for" loop
        b->enable();
}

void scene::disable_buttons()
{
    for(auto b:buttons)//C++11 "for" loop
        b->disable();
}

void scene::show_menus()
{
    for(auto m:menus)//C++11 "for" loop
        m->show();
    for(auto dm:dropdown_menus)//C++11 "for" loop
        dm->show();
}

void scene::hide_menus()
{
    for(auto m:menus)//C++11 "for" loop
        m->hide();
    for(auto dm:dropdown_menus)//C++11 "for" loop
        dm->hide();
}

void scene::enable_menus()
{
    for(auto dm:dropdown_menus)//C++11 "for" loop
        dm->enable();
}

void scene::disable_menus()
{
    for(auto dm:dropdown_menus)//C++11 "for" loop
        dm->disable();
}

void scene::show_all()
{
    show_draggable_objects();
    show_physics_objects();
    show_rts_objects();
    show_text();
    show_buttons();
    show_checkboxes();
    show_menus();
}

void scene::hide_all()
{
    hide_draggable_objects();
    hide_physics_objects();
    hide_rts_objects();
    hide_text();
    hide_buttons();
    hide_checkboxes();
    hide_menus();
}

void scene::enable_all()
{
    enable_objects();
    enable_checkboxes();
    enable_buttons();
    enable_menus();
}

void scene::disable_all()
{
    disable_objects();
    disable_checkboxes();
    disable_buttons();
    disable_menus();
}

//NOTE: This function uses C++11 "for" loops
void scene::render()
{
    glClearColor(background_color.r, background_color.g, background_color.b, 0.5);//background
    //render the rts objects
    for(auto r:rts_objects)
        r.second->render();
    //render the draggable objects
    for(auto d:draggable_objects)
        d.second->render();
    //render the physics objects
    for(auto p:physics_objects)
        p.second->render();
    //render checkboxes
    for(auto c:checkboxes)
        c->render();
    //render buttons
    for(auto b:buttons)
        b->render();
    //render menus
    for(auto m:menus)
        m->render();
    for(auto dm:dropdown_menus)
        dm->render();
    //render text
    for(auto t:labels)
        t->render();
}

//NOTE: This function uses C++11 "for" loops
void scene::update()
{
    //update physics objects
    for(auto p:physics_objects)
        p.second->update();
    //update rts objects
    for(auto r:rts_objects)
        r.second->update();
    //update draggable objects
    for(auto d:draggable_objects)
        d.second->update();
    //update menus
    for(auto m:menus)
        m->update();
    for(auto dm:dropdown_menus)
        dm->update();
    //update checkboxes
    for(auto c:checkboxes)
        c->update();
    //update buttons
    for(auto b:buttons)
        b->update();
}

void scene::load()
{
    std::clog<<"loading scene...\n";
    std::string filename;
    //clear all objects before loading
    draggable_objects.clear();
    physics_objects.clear();
    rts_objects.clear();
    //access scene file
    std::ifstream scene_file(file_name.c_str());
    if(scene_file.bad())
        return;
    //load the list of files
    while(std::getline(scene_file,filename))
    {
        std::string extension=filename.substr(filename.length()-3,filename.length());//get the file extension
        filename="./data/objects/"+filename;
        //identify file type
        if(extension=="dro")//file is a draggable object
        {
            draggable_object* d = new draggable_object();
            d->file_name=filename.c_str();
            d->load();
            add_object(d);
        }
        if(extension=="pso")//file is a physics object
        {
            physics_object* p = new physics_object();
            p->file_name=filename.c_str();
            p->load();
            add_object(p);
        }
        if(extension=="rso")//file is a real-time strategy object
        {
            rts_object* r = new rts_object();
            r->file_name=filename.c_str();
            r->load();
            add_object(r);
        }
    }
    scene_file.close();
    std::clog<<"scene#"<<number<<" loaded.\n";
}

void scene::save()
{
    std::clog<<"saving scene...\n";
    std::ofstream scene_file(file_name.c_str());//open the file
    std::clog<<"saving objects...\n";
    //save draggable objects
    for(auto d:draggable_objects)
    {
        scene_file<<"object#"<<d.first<<".dro\n";
        scene_file.close();
        d.second->save();
    }
    //save physics objects
    for(auto p:physics_objects)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<p.first<<".pso\n";
        scene_file.close();
        p.second->save();
    }
    //save rts objects
    for(auto r:rts_objects)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<r.first<<".rso\n";
        scene_file.close();
        r.second->save();
    }
    scene_file.close();
    std::clog<<"scene#"<<number<<" saved.\n";
}

void scene::sync()
{
    //move draggable objects
    for(auto d:draggable_objects)//C++11 "for" loop
        d.second->sync();
    //move rts objects
    for(auto r:rts_objects)//C++11 "for" loop
        r.second->sync();
    //move physics objects
    for(auto p:physics_objects)//C++11 "for" loop
        p.second->sync();
}

void scene::clear()
{
    physics_objects.clear();
    draggable_objects.clear();
    rts_objects.clear();
    labels.clear();
    buttons.clear();
    menus.clear();
    dropdown_menus.clear();
    key_bindings.clear();
}

scene::scene()
{
    number=total_scenes++;
    std::stringstream fn;
    fn<<"./data/scenes/scene#"<<number<<".scn";//generate the file name
    file_name=fn.str();
    background_color.set(0.25,0.25,0.25);//set the color to dark gray
}
