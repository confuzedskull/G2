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
#include "window.h"
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

void scene::add_model(model* mdl)
{
    last_object=mdl;
    models[mdl->get_number()]=mdl;//add models to scene
}

void scene::add_label(ui::label* lbl)
{

    labels.push_back(lbl);
}

void scene::add_checkbox(ui::checkbox* cbx)
{
    checkboxes.push_back(cbx);
}

void scene::add_button(ui::button* btn)
{
    buttons.push_back(btn);
}

void scene::add_menu(ui::menu* mnu)
{
    menus.push_back(mnu);
}

void scene::add_menu(ui::dropdown_menu* ddm)
{
    dropdown_menus.push_back(ddm);
}

void scene::switch_menu(int index)
{
    if(index>=0 && index<menus.size())
    {
        for(int i=0;i<menus.size();i++)
        {
            if(i!=index)
            menus[i]->hide();
        }
        menus[index]->show();
        current_menu=menus[index];
    }
    else
    {
        std::cerr<<"menu index out of bounds.\n";
        return;
    }
}

void scene::switch_menu(ui::menu* mnu)
{
    for(auto m:menus)
    {
        if(m->get_number()!=mnu->get_number())
            m->hide();
    }
    mnu->show();
    current_menu=mnu;
}

void scene::bind_key(unsigned char key, int* toggle)
{
    key_toggles[key]=toggle;
}

void scene::bind_key(std::string special_key, int* toggle)
{
    std::string comparison = "F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,up,down,left,right,page up,page down,home,end,insert";
    if(comparison.find(special_key))
        special_toggles[special_key]=toggle;
}

void scene::bind_key(unsigned char key, void (*action)())
{
    key_bindings[key]=action;
}

void scene::bind_key(std::string special_key, void (*action)())
{
    std::string comparison = "F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,up,down,left,right,page up,page down,home,end,insert";
    if(comparison.find(special_key))
    special_bindings[special_key]=action;
}

void scene::show_models()
{
    for(auto m:models)
        m.second->show();
}

void scene::hide_models()
{
    for(auto m:models)
        m.second->hide();
}

void scene::enable_models()
{
    for(auto m:models)
        m.second->enable();
}

void scene::disable_models()
{
    for(auto m:models)
        m.second->disable();
}

void scene::mute_models()
{
    for(auto m:models)
        m.second->mute();
}

void scene::unmute_models()
{
    for(auto m:models)
        m.second->unmute();
}

void scene::show_labels()
{
    for(auto t:labels)//C++11 "for" loop
        t->show();
}

void scene::hide_labels()
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

void scene::mute_checkboxes()
{
    for(auto c:checkboxes)
        c->mute();
}

void scene::unmute_checkboxes()
{
    for(auto c:checkboxes)
        c->unmute();
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

void scene::mute_buttons()
{
    for(auto b:buttons)
        b->mute();
}

void scene::unmute_buttons()
{
    for(auto b:buttons)
        b->unmute();
}

void scene::show_menus()
{
    for(auto m:menus)//C++11 "for" loop
        m->show();
}

void scene::hide_menus()
{
    for(auto m:menus)//C++11 "for" loop
        m->hide();
}

void scene::enable_menus()
{
    for(auto m:menus)//C++11 "for" loop
    {
        for(auto i:m->items)
            i->enable();
    }
}

void scene::disable_menus()
{
    for(auto m:menus)//C++11 "for" loop
    {
        for(auto i:m->items)
            i->disable();
    }
}

void scene::mute_menus()
{
    for(auto m:menus)
        m->mute();
}

void scene::unmute_menus()
{
    for(auto m:menus)
        m->unmute();
}

void scene::show_dropdown_menus()
{
    for(auto dm:dropdown_menus)//C++11 "for" loop
        dm->show();
}

void scene::hide_dropdown_menus()
{
    for(auto dm:dropdown_menus)//C++11 "for" loop
        dm->hide();
}

void scene::enable_dropdown_menus()
{
    for(auto dm:dropdown_menus)//C++11 "for" loop
        dm->enable();
}

void scene::disable_dropdown_menus()
{
    for(auto dm:dropdown_menus)//C++11 "for" loop
        dm->disable();
}

void scene::mute_dropdown_menus()
{
    for(auto dm:dropdown_menus)
        dm->mute();
}

void scene::unmute_dropdown_menus()
{
    for(auto dm:dropdown_menus)
        dm->unmute();
}

void scene::show_textures()
{
    background.textured=true;
    background.filled=false;
    middleground.textured=true;
    middleground.filled=false;
    foreground.textured=true;
    foreground.filled=false;
    for(auto m:models)
    {
        m.second->textured=true;
        m.second->filled=false;
    }
}

void scene::hide_textures()
{
    background.textured=false;
    background.filled=true;
    middleground.textured=false;
    middleground.filled=true;
    foreground.textured=false;
    foreground.filled=true;
    for(auto m:models)
    {
        m.second->textured=false;
        m.second->filled=true;
    }
}

void scene::show_all()
{
    background.show();
    middleground.show();
    foreground.show();
    show_models();
    show_labels();
    show_buttons();
    show_checkboxes();
    show_menus();
    show_dropdown_menus();
}

void scene::hide_all()
{
    background.hide();
    middleground.hide();
    foreground.hide();
    hide_models();
    hide_labels();
    hide_buttons();
    hide_checkboxes();
    hide_menus();
    hide_dropdown_menus();
}

void scene::enable_all()
{
    enable_models();
    enable_checkboxes();
    enable_buttons();
    enable_menus();
    enable_dropdown_menus();
}

void scene::disable_all()
{
    disable_models();
    disable_checkboxes();
    disable_buttons();
    disable_menus();
    disable_dropdown_menus();
}

void scene::mute_all()
{
    background.mute();
    middleground.mute();
    foreground.mute();
    mute_models();
    mute_checkboxes();
    mute_buttons();
    mute_menus();
    mute_dropdown_menus();
}

void scene::unmute_all()
{
    background.unmute();
    middleground.unmute();
    foreground.unmute();
    unmute_models();
    unmute_checkboxes();
    unmute_buttons();
    unmute_menus();
    unmute_dropdown_menus();
}

//NOTE: This function uses C++11 "for" loops
void scene::render()
{
    background.render();
    for(auto m:models)
        m.second->render();
    middleground.render();
    foreground.render();
    for(auto c:checkboxes)
        c->render();
    for(auto b:buttons)
        b->render();
    for(auto m:menus)
        m->render();
    for(auto dm:dropdown_menus)
        dm->render();
    for(auto t:labels)
        t->render();
}

//NOTE: This function uses C++11 "for" loops
void scene::update()
{
    background.update();
    middleground.update();
    foreground.update();
    for(auto m:models)
        m.second->update();
    for(auto m:menus)
        m->update();
    for(auto dm:dropdown_menus)
        dm->update();
    for(auto c:checkboxes)
        c->update();
    for(auto b:buttons)
        b->update();
    if(cursor::left_clicked_object->get_type()=="model")
        current_model=models[cursor::left_clicked_object->get_number()];
}

void scene::load()
{
    std::clog<<"loading scene...\n";
    float fparam1,fparam2;//temporary buffers to store floats and use them as parameters for a setter
    int iparam1,iparam2;//temporary buffers to store ints and use them as parameters for a setter
    std::string sparam1;//temporary buffer to store a string and use it as a parameter for a setter
    std::string filename;
    //clear models before loading
    models.clear();
    //access scene file
    std::ifstream scene_file(file_name.c_str());
    if(scene_file.bad())
        return;
    scene_file.precision(3);
    scene_file.setf(std::ios::fixed);
    //load foreground properties
    scene_file>>fparam1>>fparam2;
    foreground.set_position(fparam1,fparam2);
    scene_file>>fparam1;
    foreground.set_rotation(fparam1);
    scene_file>>iparam1>>iparam2;
    foreground.set_dimensions(iparam1,iparam2);
    scene_file>>foreground.fill_color.r>>foreground.fill_color.g>>foreground.fill_color.b;
    scene_file>>foreground.marker_color.r>>foreground.marker_color.g>>foreground.marker_color.b;
    scene_file>>foreground.border_color.r>>foreground.border_color.g>>foreground.border_color.b;
    scene_file>>foreground.filled;
    scene_file>>foreground.bordered;
    scene_file>>foreground.textured;
    scene_file>>foreground.visible;
    scene_file>>foreground.selected;
    scene_file>>foreground.muted;
    scene_file>>sparam1;
    foreground.set_texture(sparam1);
    //load middleground properties
    scene_file>>fparam1>>fparam2;
    middleground.set_position(fparam1,fparam2);
    scene_file>>fparam1;
    middleground.set_rotation(fparam1);
    scene_file>>iparam1>>iparam2;
    middleground.set_dimensions(iparam1,iparam2);
    scene_file>>middleground.fill_color.r>>middleground.fill_color.g>>middleground.fill_color.b;
    scene_file>>middleground.marker_color.r>>middleground.marker_color.g>>middleground.marker_color.b;
    scene_file>>middleground.border_color.r>>middleground.border_color.g>>middleground.border_color.b;
    scene_file>>middleground.filled;
    scene_file>>middleground.bordered;
    scene_file>>middleground.textured;
    scene_file>>middleground.visible;
    scene_file>>middleground.selected;
    scene_file>>middleground.muted;
    scene_file>>sparam1;
    middleground.set_texture(sparam1);
    //load background properties
    scene_file>>fparam1>>fparam2;
    background.set_position(fparam1,fparam2);
    scene_file>>fparam1;
    background.set_rotation(fparam1);
    scene_file>>iparam1>>iparam2;
    background.set_dimensions(iparam1,iparam2);
    scene_file>>background.fill_color.r>>background.fill_color.g>>background.fill_color.b;
    scene_file>>background.marker_color.r>>background.marker_color.g>>background.marker_color.b;
    scene_file>>background.border_color.r>>background.border_color.g>>background.border_color.b;
    scene_file>>background.filled;
    scene_file>>background.bordered;
    scene_file>>background.textured;
    scene_file>>background.visible;
    scene_file>>background.selected;
    scene_file>>background.muted;
    scene_file>>sparam1;
    background.set_texture(sparam1);
    scene_file.get();
    //load the list of files
    while(std::getline(scene_file,filename))
    {
        std::string extension=filename.substr(filename.length()-3,filename.length());//get the file extension
        filename="./data/models/"+filename;
        //identify file type
        if(extension=="mdl")//file is a draggable object
        {
            model* m = new model();
            m->file_name=filename.c_str();
            m->load();
            add_model(m);
        }
    }
    scene_file.close();
    std::clog<<"scene#"<<number<<" loaded.\n";
}

void scene::save()
{
    std::clog<<"saving scene...\n";
    std::ofstream scene_file(file_name.c_str());//open the file
    scene_file.precision(3);
    scene_file.setf(std::ios::fixed);
    //save foreground properties
    scene_file<<foreground.get_x()<<' '<<foreground.get_position().y<<std::endl;
    scene_file<<foreground.get_rotation()<<std::endl;
    scene_file<<foreground.get_width()<<' '<<foreground.get_height()<<std::endl;
    scene_file<<foreground.fill_color.str()<<std::endl;
    scene_file<<foreground.marker_color.str()<<std::endl;
    scene_file<<foreground.border_color.str()<<std::endl;
    scene_file<<foreground.filled<<std::endl;
    scene_file<<foreground.bordered<<std::endl;
    scene_file<<foreground.textured<<std::endl;
    scene_file<<foreground.visible<<std::endl;
    scene_file<<foreground.selected<<std::endl;
    scene_file<<foreground.muted<<std::endl;
    scene_file<<foreground.get_texture()<<std::endl;
    //save middleground properties
    scene_file<<middleground.get_x()<<' '<<middleground.get_position().y<<std::endl;
    scene_file<<middleground.get_rotation()<<std::endl;
    scene_file<<middleground.get_width()<<' '<<middleground.get_height()<<std::endl;
    scene_file<<middleground.fill_color.str()<<std::endl;
    scene_file<<middleground.marker_color.str()<<std::endl;
    scene_file<<middleground.border_color.str()<<std::endl;
    scene_file<<middleground.filled<<std::endl;
    scene_file<<middleground.bordered<<std::endl;
    scene_file<<middleground.textured<<std::endl;
    scene_file<<middleground.visible<<std::endl;
    scene_file<<middleground.selected<<std::endl;
    scene_file<<middleground.muted<<std::endl;
    scene_file<<middleground.get_texture()<<std::endl;
    //save background properties
    scene_file<<background.get_x()<<' '<<background.get_position().y<<std::endl;
    scene_file<<background.get_rotation()<<std::endl;
    scene_file<<background.get_width()<<' '<<background.get_height()<<std::endl;
    scene_file<<background.fill_color.str()<<std::endl;
    scene_file<<background.marker_color.str()<<std::endl;
    scene_file<<background.border_color.str()<<std::endl;
    scene_file<<background.filled<<std::endl;
    scene_file<<background.bordered<<std::endl;
    scene_file<<background.textured<<std::endl;
    scene_file<<background.visible<<std::endl;
    scene_file<<background.selected<<std::endl;
    scene_file<<background.muted<<std::endl;
    scene_file<<background.get_texture()<<std::endl;
    std::clog<<"saving models...\n";
    //save models
    for(auto m:models)
    {
        scene_file<<"object#"<<m.first<<".mdl\n";
        scene_file.close();
        m.second->save();
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
    }
    scene_file.close();
    std::clog<<"scene#"<<number<<" saved.\n";
}

void scene::sync()
{
    background.sync();
    middleground.sync();
    foreground.sync();
    for(auto m:models)//C++11 "for" loop
        m.second->sync();
}

void scene::clear()
{
    models.clear();
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
    background.set_position(window::center.x,window::center.y);
    background.set_dimensions(window::width,window::height);
    background.fill_color.set(BLACK);
    middleground.set_position(window::center.x,window::center.y);
    middleground.set_dimensions(window::width,window::height);
    middleground.fill_color.set(0.25,0.25,0.25);
    foreground.set_position(window::center.x,window::center.y);
    foreground.set_dimensions(window::width,window::height);
    foreground.fill_color.set(GRAY);
}
