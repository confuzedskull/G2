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

#include "scene.h"
#include "game.h"
#include "cursor.h"
#include "window.h"
#include "audio.h"
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
#include <sstream>

int scene::total_scenes=0;

void scene::remove_object(basic_object* bso)
{
    int object_number = bso->get_number();
    int index;
    for(unsigned i=0;i<basic_objects.size();i++)
    {
        if(basic_objects[i]->get_number()==object_number)
        {
            index=i;
            break;
        }
    }
    if(index==0)
        basic_objects.erase(basic_objects.begin());
    else
        basic_objects.erase(basic_objects.begin()+(index-1));
    delete bso;
}

void scene::remove_object(complex_object* cpo)
{
    int object_number = cpo->get_number();
    int index;
    for(unsigned i=0;i<complex_objects.size();i++)
    {
        if(complex_objects[i]->get_number()==object_number)
        {
            index=i;
            break;
        }
    }
    if(index==0)
        complex_objects.erase(complex_objects.begin());
    else
        complex_objects.erase(complex_objects.begin()+(index-1));
    delete cpo;
}

void scene::remove_object(mobile_object* mbo)
{
    int object_number = mbo->get_number();
    int index;
    for(unsigned i=0;i<mobile_objects.size();i++)
    {
        if(mobile_objects[i]->get_number()==object_number)
        {
            index=i;
            break;
        }
    }
    if(index==0)
        mobile_objects.erase(mobile_objects.begin());
    else
        mobile_objects.erase(mobile_objects.begin()+(index-1));
    delete mbo;
}

void scene::remove_object(smart_object* smo)
{
    int object_number = smo->get_number();
    int index;
    for(unsigned i=0;i<mobile_objects.size();i++)
    {
        if(smart_objects[i]->get_number()==object_number)
        {
            index=i;
            break;
        }
    }
    if(index==0)
        smart_objects.erase(smart_objects.begin());
    else
        smart_objects.erase(smart_objects.begin()+(index-1));
    delete smo;
}

void scene::remove_object(physical_object* pso)
{
    int object_number = pso->get_number();
    int index;
    for(unsigned i=0;i<physical_objects.size();i++)
    {
        if(physical_objects[i]->get_number()==object_number)
        {
            index=i;
            break;
        }
    }
    if(index==0)
        physical_objects.erase(physical_objects.begin());
    else
        physical_objects.erase(physical_objects.begin()+(index-1));
    delete pso;
}

void scene::remove_object(advanced_object* avo)
{
    int object_number = avo->get_number();
    int index;
    for(unsigned i=0;i<advanced_objects.size();i++)
    {
        if(advanced_objects[i]->get_number()==object_number)
        {
            index=i;
            break;
        }
    }
    if(index==0)
        advanced_objects.erase(advanced_objects.begin());
    else
        advanced_objects.erase(advanced_objects.begin()+(index-1));
    delete avo;
}

void scene::remove_object(interactive_object* iao)
{
    if(iao->get_type()=="interactive object")
        remove_object((advanced_object*)iao);
    int object_number = iao->get_number();
    int index;
    for(unsigned i=0;i<interactive_objects.size();i++)
    {
        if(interactive_objects[i]->get_number()==object_number)
        {
            index=i;
            break;
        }
    }
    if(index==0)
        interactive_objects.erase(interactive_objects.begin());
    else
        interactive_objects.erase(interactive_objects.begin()+(index-1));
    delete iao;
}

void scene::add_object(basic_object* bso)
{
    previous_object=bso;
    basic_objects.push_back(bso);
}

void scene::add_object(complex_object* cpo)
{
    previous_object=cpo;
    complex_objects.push_back(cpo);
}

void scene::add_object(mobile_object* mbo)
{
    previous_object=mbo;
    mobile_objects.push_back(mbo);
}

void scene::add_object(smart_object* smo)
{
    previous_object=smo;
    smart_objects.push_back(smo);
}

void scene::add_object(physical_object* pso)
{
    previous_object=pso;
    physical_objects.push_back(pso);
}

void scene::add_object(interactive_object* iao)
{
    previous_object=iao;
    interactive_objects.push_back(iao);
}

void scene::add_object(advanced_object* avo)
{
    previous_object=avo;
    advanced_objects.push_back(avo);//add advanced_objects to scene
}

void scene::add_label(ui::label* lbl)
{
    previous_object=lbl;
    labels.push_back(lbl);
}

void scene::add_checkbox(ui::checkbox* cbx)
{
    previous_object=cbx;
    checkboxes.push_back(cbx);
}

void scene::add_button(ui::button* btn)
{
    previous_object=btn;
    buttons.push_back(btn);
}

void scene::add_menu(ui::menu* mnu)
{
    previous_object=mnu;
    menus.push_back(mnu);
}

void scene::add_dropdown(ui::dropdown_menu* ddm)
{
    previous_object=ddm;
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
        cursor::reset();
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
    cursor::reset();
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
    else
        std::cerr<<"invalid key.\n";
}

void scene::set_music(std::string filename)
{
    if(audio::sounds.find(filename)!=audio::sounds.end())
        music=filename;
    else
        std::cerr<<filename<<" not found.\n";
}

void scene::set_ambience(std::string filename)
{
    if(audio::sounds.find(filename)!=audio::sounds.end())
        ambience=filename;
    else
        std::cerr<<filename<<" not found.\n";
}

//NOTE: This function uses C++11 "for" loops
void scene::render()
{
    for(auto b:basic_objects)
        b->render();
    for(auto c:complex_objects)
        c->render();
    for(auto m:mobile_objects)
        m->render();
    for(auto s:smart_objects)
        s->render();
    for(auto p:physical_objects)
        p->render();
    for(auto a:advanced_objects)
        a->render();
    for(auto i:interactive_objects)
        i->update();
    for(auto b:buttons)
        b->render();
    for(auto c:checkboxes)
        c->render();
    for(auto dm:dropdown_menus)
        dm->render();
    for(auto t:labels)
        t->render();
    for(auto m:menus)
        m->render();
}

//NOTE: This function uses C++11 "for" loops
void scene::update()
{
    if(!music_started)
    {
        audio::loop(music);
        music_started=true;
    }
    if(!ambience_started)
    {
        audio::loop(ambience);
        ambience_started=true;
    }
    if(cursor::left_clicked_object->get_type()=="advanced object")
        player=(advanced_object*)cursor::left_clicked_object;
    for(auto b:basic_objects)
        b->update();
    for(auto c:complex_objects)
        c->update();
    for(auto m:mobile_objects)
        m->update();
    for(auto s:smart_objects)
        s->update();
    for(auto p:physical_objects)
        p->update();
    for(auto a:advanced_objects)
        a->update();
    for(auto i:interactive_objects)
        i->update();
    for(auto l:labels)
        l->update();
    for(auto b:buttons)
        b->update();
    for(auto c:checkboxes)
        c->update();
    for(auto m:menus)
        m->update();
    for(auto dm:dropdown_menus)
        dm->update();
}

void scene::sync()
{
    for(auto b:basic_objects)
        b->sync();
    for(auto c:complex_objects)
        c->sync();
    for(auto m:mobile_objects)
        m->sync();
    for(auto s:smart_objects)
        s->sync();
    for(auto p:physical_objects)
        p->sync();
    for(auto a:advanced_objects)
        a->sync();
    for(auto i:interactive_objects)
        i->sync();
    for(auto l:labels)
        l->sync();
    for(auto b:buttons)
        b->sync();
    for(auto c:checkboxes)
        c->sync();
    for(auto m:menus)
        m->sync();
    for(auto dm:dropdown_menus)
        dm->sync();
}

void scene::load()
{
    std::clog<<"loading scene...\n";
    float fparam1,fparam2;//temporary buffers to store floats and use them as parameters for a setter
    int iparam1,iparam2;//temporary buffers to store ints and use them as parameters for a setter
    std::string sparam1;//temporary buffer to store a string and use it as a parameter for a setter
    std::string filename;
    //clear everything before loading
    clear();
    //access scene file
    std::ifstream scene_file(file_name.c_str());
    if(scene_file.bad())
        return;
    scene_file.precision(3);
    scene_file.setf(std::ios::fixed);
    scene_file>>music;
    scene_file>>ambience;
    scene_file.get();
    //load the list of files
    while(std::getline(scene_file,filename))
    {
        std::string extension=filename.substr(filename.length()-3,filename.length());//get the file extension
        //identify file types
        if(extension=="bso")//file is a basic object
        {
            filename="./data/objects/"+filename;
            basic_object* b = new basic_object();
            b->file_name=filename.c_str();
            b->load();
            add_object(b);
            filename.clear();
        }
        if(extension=="cpo")//file is a complex object
        {
            filename="./data/objects/"+filename;
            complex_object* c = new complex_object();
            c->file_name=filename.c_str();
            c->load();
            add_object(c);
            filename.clear();
        }
        if(extension=="mbo")//file is a movable object
        {
            filename="./data/objects/"+filename;
            mobile_object* m = new mobile_object();
            m->file_name=filename.c_str();
            m->load();
            add_object(m);
            filename.clear();
        }
        if(extension=="smo")//file is a smart object
        {
            filename="./data/objects/"+filename;
            smart_object* t = new smart_object();
            t->file_name=filename.c_str();
            t->load();
            add_object(t);
            filename.clear();
        }
        if(extension=="pso")//file is a physics object
        {
            filename="./data/objects/"+filename;
            physical_object* p = new physical_object();
            p->file_name=filename.c_str();
            p->load();
            add_object(p);
            filename.clear();
        }
        if(extension=="avo")//file is an advanced object
        {
            filename="./data/objects/"+filename;
            advanced_object* a = new advanced_object();
            a->file_name=filename.c_str();
            a->load();
            add_object(a);
            filename.clear();
        }
        if(extension=="iao")//file is a interactive object
        {
            filename="./data/objects/"+filename;
            interactive_object* c = new interactive_object();
            c->file_name=filename.c_str();
            c->load();
            add_object(c);
            filename.clear();
        }
        if(extension=="lbl")//file is a label
        {
            filename="./data/labels/"+filename;
            ui::label* l = new ui::label();
            l->file_name=filename.c_str();
            l->load();
            add_label(l);
            filename.clear();
        }
        if(extension=="btn")//file is a button
        {
            filename="./data/buttons/"+filename;
            ui::button* b = new ui::button();
            b->file_name=filename.c_str();
            b->load();
            add_button(b);
            filename.clear();
        }
        if(extension=="cbx")//file is a checkbox
        {
            filename="./data/buttons/"+filename;
            ui::checkbox* c = new ui::checkbox();
            c->file_name=filename.c_str();
            c->load();
            add_checkbox(c);
            filename.clear();
        }
        if(extension=="mnu")//file is a menu
        {
            filename="./data/menus/"+filename;
            ui::menu* m = new ui::menu();
            m->file_name=filename.c_str();
            m->load();
            add_menu(m);
            filename.clear();
        }
        if(extension=="ddm")//file is a dropdown menu
        {
            filename="./data/menus/"+filename;
            ui::dropdown_menu* d = new ui::dropdown_menu();
            d->file_name=filename.c_str();
            d->load();
            add_dropdown(d);
            filename.clear();
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
    scene_file<<music<<std::endl;
    scene_file<<ambience<<std::endl;
    std::clog<<"saving objects...\n";
    for(auto b:basic_objects)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<b->get_number()<<".bso\n";
        scene_file.close();//need to close scene file before opening another file
        b->save();
    }
    for(auto c:complex_objects)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<c->get_number()<<".cpo\n";
        scene_file.close();//need to close scene file before opening another file
        c->save();
    }
    for(auto m:mobile_objects)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<m->get_number()<<".mbo\n";
        scene_file.close();//need to close scene file before opening another file
        m->save();
    }
    for(auto s:smart_objects)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<s->get_number()<<".smo\n";
        scene_file.close();//need to close scene file before opening another file
        s->save();
    }
    for(auto p:physical_objects)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<p->get_number()<<".pso\n";
        scene_file.close();//need to close scene file before opening another file
        p->save();
    }
    for(auto a:advanced_objects)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<a->get_number()<<".avo\n";
        scene_file.close();//need to close scene file before opening another file
        a->save();
    }
    for(auto i:interactive_objects)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<i->get_number()<<".iao\n";
        scene_file.close();//need to close scene file before opening another file
        i->save();
    }
    std::clog<<"saving labels...\n";
    for(auto l:labels)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<l->get_number()<<".lbl\n";
        scene_file.close();//need to close scene file before opening another file
        l->save();
    }
    std::clog<<"saving buttons...\n";
    for(auto b:buttons)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<b->get_number()<<".btn\n";
        scene_file.close();//need to close scene file before opening another file
        b->save();
    }
    for(auto c:checkboxes)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<c->get_number()<<".cbx\n";
        scene_file.close();//need to close scene file before opening another file
        c->save();
    }
    std::clog<<"saving menus...\n";
    for(auto m:menus)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<m->get_number()<<".mnu\n";
        scene_file.close();//need to close scene file before opening another file
        m->save();
    }
    for(auto d:dropdown_menus)
    {
        scene_file.open(file_name.c_str(),std::fstream::app);//the file is already open so we need to append
        scene_file<<"object#"<<d->get_number()<<".ddm\n";
        scene_file.close();//need to close scene file before opening another file
        d->save();
    }
    scene_file.close();
    std::clog<<"scene#"<<number<<" saved.\n";
}

void scene::clear()
{
    basic_objects.clear();
    complex_objects.clear();
    mobile_objects.clear();
    smart_objects.clear();
    physical_objects.clear();
    advanced_objects.clear();
    interactive_objects.clear();
    labels.clear();
    buttons.clear();
    checkboxes.clear();
    menus.clear();
    dropdown_menus.clear();
}

scene::scene()
{
    number=total_scenes++;
    std::stringstream fn;
    fn<<"./data/scenes/scene#"<<number<<".scn";//generate the file name
    file_name=fn.str();
    music_started=false;
    ambience_started=false;
}
