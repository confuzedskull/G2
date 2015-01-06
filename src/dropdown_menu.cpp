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

#include "dropdown_menu.h"
#include "cursor.h"
#include "ui.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::string ui::dropdown_menu::default_texture = "";
std::string ui::dropdown_menu::default_mask = "";
std::string ui::dropdown_menu::default_clicksound = "";
std::string ui::dropdown_menu::default_hoversound = "";
std::string ui::dropdown_menu::default_layout = "vertical";
color ui::dropdown_menu::default_fillcolor = ui::default_fillcolor;
color ui::dropdown_menu::default_bordercolor = ui::default_bordercolor;

std::string ui::dropdown_menu::get_type()
{
    return "dropdown menu";
}

void ui::dropdown_menu::mouse_function()
{
    if(visible)
    {
        hover_function();
        if(left_clicked()||item_chosen)
        {
            if(expanded)
            {
                if(state_toggle)
                    expand();
                state_toggle=false;
            }
            else
            {
                if(!state_toggle)
                    collapse();
                state_toggle=true;
            }
        }
        else
            expanded=state_toggle;
    }
}

void ui::dropdown_menu::expand()
{
    for(auto i:items)
        i->show();//show the buttons
}

void ui::dropdown_menu::collapse()
{
    set_dimensions(width,items.front()->get_height());//shrink to button size
    for(auto i:items)
        i->hide();//hide the buttons
}

void ui::dropdown_menu::render()
{
    menu::render();
    button::render();
}

void ui::dropdown_menu::update()
{
    item_chosen=false;
    for(unsigned i=0;i<items.size();i++)
    {
        if(items[i]->selected)
        {
            current_item=items[i];
            if(i==items.size()-1)
                next_item=items[0];
            else
                next_item=items[i+1];
            if(i==0)
                previous_item=items[items.size()];
            else
                previous_item=items[i-1];
        }
        if(items[i]->left_clicked())
            item_chosen=true;
        items[i]->click_detection=click_detection&&expanded;
        items[i]->visible=visible&&expanded;//if menu is visible, items are visible
        items[i]->muted=muted;
        items[i]->update();
    }
    mouse_function();
}

void ui::dropdown_menu::load()
{
    std::clog<<file_name;
    std::ifstream object_file(file_name);//access file by name
    if(object_file.bad())//make sure the file is there
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //load basic object properties
    object_file>>position.x>>position.y;
    object_file>>rotation;
    object_file>>width>>height;
    object_file>>fill_color.r>>fill_color.g>>fill_color.b;
    object_file>>marker_color.r>>marker_color.g>>marker_color.b;
    object_file>>border_color.r>>border_color.g>>border_color.b;
    object_file>>filled;
    object_file>>bordered;
    object_file>>textured;
    object_file>>masked;
    object_file>>visible;
    object_file>>selected;
    object_file>>muted;
    object_file>>texture;
    object_file>>mask;
    //load interactive object properties
    object_file>>click_detection;
    object_file>>drag_detection;
    object_file>>hover_detection;
    object_file>>highlight_detection;
    object_file>>click_sound;
    object_file>>hover_sound;
    //load menu properties
    object_file>>spacing;
    object_file>>menu::margin;
    object_file>>layout;
    //load label
    object_file>>text.text;
    object_file>>text.allignment;
    object_file>>text.spacing;
    object_file>>text.font_size;
    object_file>>text.font_width>>text.font_height;
    object_file>>text.font_color.r>>text.font_color.g>>text.font_color.b;
    //load the list of files
    std::string filename;
    while(std::getline(object_file,filename))
    {
        std::string extension=filename.substr(filename.length()-3,filename.length());//get the file extension
        //identify file types
        if(extension=="btn")//file is a button
        {
            filename="./data/buttons/"+filename;
            ui::button* b = new ui::button();
            b->file_name=filename.c_str();
            b->load();
            add_item(b);
            filename.clear();
        }
        if(extension=="cbx")//file is a checkbox
        {
            filename="./data/buttons/"+filename;
            ui::checkbox* c = new ui::checkbox();
            c->file_name=filename.c_str();
            c->load();
            add_item(c);
            filename.clear();
        }
        if(extension=="ddm")//file is a dropdown menu
        {
            filename="./data/menus/"+filename;
            ui::dropdown_menu* d = new ui::dropdown_menu();
            d->file_name=filename.c_str();
            d->load();
            add_item(d);
            filename.clear();
        }
    }
    object_file.close();
    std::clog<<"object#"<<number<<"(dropdown menu)"<<" loaded.\n";
}

void ui::dropdown_menu::save()
{
    std::stringstream filename;
    filename<<"./data/menus/object#"<<number<<".ddm";
    std::ofstream object_file(filename.str());
    if(object_file.bad())
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //save basic object properties
    object_file<<position.x<<' '<<position.y<<std::endl;
    object_file<<rotation<<std::endl;
    object_file<<width<<' '<<height<<std::endl;
    object_file<<fill_color.str()<<std::endl;
    object_file<<marker_color.str()<<std::endl;
    object_file<<border_color.str()<<std::endl;
    object_file<<filled<<std::endl;
    object_file<<bordered<<std::endl;
    object_file<<textured<<std::endl;
    object_file<<masked<<std::endl;
    object_file<<visible<<std::endl;
    object_file<<selected<<std::endl;
    object_file<<muted<<std::endl;
    object_file<<texture<<std::endl;
    object_file<<mask<<std::endl;
    //save interactive object properties
    object_file<<click_detection<<std::endl;
    object_file<<drag_detection<<std::endl;
    object_file<<hover_detection<<std::endl;
    object_file<<click_sound<<std::endl;
    object_file<<hover_sound<<std::endl;
    //save menu properties
    object_file<<spacing<<std::endl;
    object_file<<menu::margin<<std::endl;
    object_file<<layout<<std::endl;
    //save label
    object_file<<text.text<<std::endl;
    object_file<<text.allignment<<std::endl;
    object_file<<text.spacing<<std::endl;
    object_file<<text.font_size<<std::endl;
    object_file<<text.font_width<<' '<<text.font_height<<std::endl;
    object_file<<text.font_color.str()<<std::endl;
    //save items
    for(auto i:items)
    {
        object_file.open(filename.str(),std::fstream::app);//the file is already open so we need to append
        if(i->get_type()=="button")
        {
            object_file<<"object#"<<i->get_number()<<".btn\n";
            object_file.close();//need to close scene file before opening another file
            i->save();
        }
        if(i->get_type()=="checkbox")
        {
            object_file<<"object#"<<i->get_number()<<".cbx\n";
            object_file.close();//need to close scene file before opening another file
            i->save();
        }
        if(i->get_type()=="dropdown menu")
        {
            object_file<<"object#"<<i->get_number()<<".ddm\n";
            object_file.close();//need to close scene file before opening another file
            i->save();
        }
    }
    object_file.close();
    std::clog<<"object#"<<number<<"(dropdown menu)"<<" saved.\n";
}

ui::dropdown_menu::dropdown_menu()
{
	title.hide();
    subtitle.hide();
    text.allign(CENTER);
    set_label("default value");
    set_layout(default_layout);
    spacing=0;
    menu::margin=0;
    state_toggle=false;
    expanded=false;
    fill_color=default_fillcolor;
    border_color=default_bordercolor;
    set_texture(default_texture);
    set_mask(default_mask);
    set_clicksound(default_clicksound);
    set_hoversound(default_hoversound);
	std::clog<<"object#"<<number<<"(dropdown menu)"<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
