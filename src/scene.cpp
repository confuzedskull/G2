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

void scene::add_object(draggable_object* new_do)
{
    last_object=new_do;
    draggable_objects.insert(std::pair<int,draggable_object*>(new_do->get_number(),new_do));//add object to scene
}

void scene::add_object(physics_object* new_po)
{
    last_object=new_po;
    physics_objects.insert(std::pair<int,physics_object*>(new_po->get_number(),new_po));//add object to scene
}

void scene::add_object(rts_object* new_rtso)
{
    last_object=new_rtso;
    rts_objects.insert(std::pair<int,rts_object*>(new_rtso->get_number(),new_rtso));//add object to scene
}

void scene::add_text(text_object* t)
{
    text_objects.push_back(t);
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

void scene::bind_key(unsigned char key, std::string condition, void (*action)())
{
    if(condition=="hold")
        key_bindings.insert(std::pair<unsigned char, void (*)()>(key,action));
    if(condition=="press")
    {
        key_bindings.insert(std::pair<unsigned char, void (*)()>(key,action));
        key_toggles.insert(std::pair<unsigned char, void (*)()>(key,action));
    }
}

void scene::bind_key(unsigned char key, void (*actionA)(), void (*actionB)())
{
    key_bindings.insert(std::pair<unsigned char, void (*)()>(key,actionA));
    key_toggles.insert(std::pair<unsigned char, void (*)()>(key,actionB));//bind actionB to the shift form of the key
}

void scene::bind_key(std::string special_key, std::string condition, void (*action)())
{
    if(condition=="hold")
        special_bindings.insert(std::pair<std::string, void (*)()>(special_key,action));
    if(condition=="press")
    {
        special_bindings.insert(std::pair<std::string, void (*)()>(special_key,action));
        special_toggles.insert(std::pair<std::string, void (*)()>(special_key,action));
    }
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

void scene::show_text()
{
    for(auto t:text_objects)//C++11 "for" loop
        t->show();
}

void scene::hide_text()
{
    for(auto t:text_objects)//C++11 "for" loop
        t->hide();
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

void scene::show_all()
{
    //show physics objects
    for(auto p:physics_objects)
        p.second->show();
    //show rts objects
    for(auto r:rts_objects)
        r.second->show();
    //show draggable objects
    for(auto d:draggable_objects)
        d.second->show();
    //show text
    for(auto t:text_objects)
        t->show();
    //show menus
    for(auto m:menus)
        m->show();
    for(auto dm:dropdown_menus)
        dm->show();
    //show buttons
    for(auto b:buttons)
        b->show();
}

void scene::hide_all()
{
    //hide physics objects
    for(auto p:physics_objects)
        p.second->hide();
    //hide rts objects
    for(auto r:rts_objects)
        r.second->hide();
    //hide draggable objects
    for(auto d:draggable_objects)
        d.second->hide();
    //hide text
    for(auto t:text_objects)
        t->hide();
    //hide menus
    for(auto m:menus)
        m->hide();
    for(auto dm:dropdown_menus)
        dm->hide();
    //hide buttons
    for(auto b:buttons)
        b->hide();
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
    //render text
    for(auto t:text_objects)
        t->render();
    //render menus
    for(auto m:menus)
        m->render();
    for(auto dm:dropdown_menus)
        dm->render();
    //render buttons
    for(auto b:buttons)
        b->render();
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
    //update buttons
    for(auto b:buttons)
        b->update();
}

void scene::sync()
{
    if(!game::paused)
    {
        //move rts objects
        for(auto r:rts_objects)//C++11 "for" loop
            r.second->perform_actions()||r.second->move_to_point(*r.second->rally);
        //move physics objects
        for(auto p:physics_objects)//C++11 "for" loop
        {
            p.second->perform_actions();
            p.second->inertia();
        }
    }
}

void scene::clear()
{
    physics_objects.clear();
    draggable_objects.clear();
    rts_objects.clear();
    text_objects.clear();
    buttons.clear();
    menus.clear();
    dropdown_menus.clear();
    key_bindings.clear();
}

scene::scene()
{
    background_color.set(0.25,0.25,0.25);//set the color to dark gray
}
