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

#include "menu.h"
#include "window.h"
#include "cursor.h"
#include "ui.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>

int ui::menu::default_spacing = 10;
int ui::menu::default_margin = 20;
std::string ui::menu::default_layout = "vertical";
std::string ui::menu::default_texture = "";
std::string ui::menu::default_mask = "";
color ui::menu::default_fillcolor = ui::default_fillcolor;
color ui::menu::default_bordercolor = ui::default_bordercolor;

std::string ui::menu::get_type()
{
    return "menu";
}

void ui::menu::format()
{
    int total_width=0;//width of buttons and the spaces between
    int total_height=0;//height of buttons and spaces between
    int widest;//width of the widest item
    if(title.get_width()>subtitle.get_width())
        widest=title.get_width();
    else
        widest=subtitle.get_width();
    if(get_type()=="dropdown menu" && widest<width)
        widest=width;
    //arrange the items
    for(unsigned i=0;i<items.size();i++)//use regular 'for' loop because 'i' is used as number
    {
        if(items[i]->combined_width()>widest)
            widest=items[i]->combined_width();
        if(layout=="vertical")
        {
            if(items[i]->get_type()=="checkbox")
                items[i]->set_position(xmax-margin-items[i]->get_width(),ymax-margin-title.get_height()-total_height);
            else
                items[i]->set_position(position.x,ymax-margin-title.get_height()-items[i]->get_height()-total_height);
        }
        if(layout=="horizontal")
        {
            if(subtitle.visible)
                items[i]->set_position(xmin+margin+total_width,ymax-margin-title.get_height()-spacing-subtitle.get_height()-spacing-(items[0]->get_height()/2));
            else
                items[i]->set_position(xmin+margin+total_width,ymax-margin-title.get_height()-spacing-(items[0]->get_height()/2));
            total_width+=spacing;
        }
        items[i]->text.set_position(items[i]->get_x(),items[i]->get_y());
        total_width+=items[i]->combined_width();
        total_height+=(items[i]->get_height()+spacing);
    }
    //resize the menu
    if(layout=="vertical")
    {
        if(title.visible)
        {
            if(subtitle.visible)
                set_dimensions(widest+(margin*2),total_height+title.get_height()+subtitle.get_height()+spacing+(margin*2));
            else
                set_dimensions(widest+(margin*2),total_height+title.get_height()+spacing+(margin*2));
        }
        else
            set_dimensions(widest+(margin*2),total_height+(margin*2));
    }
    if(layout=="horizontal")
    {
        if(title.visible)
        {
            if(subtitle.visible)
                set_dimensions(total_width+(margin*2),items[0]->get_height()+title.get_height()+spacing+subtitle.get_height()+spacing+(margin*2));
            else
                set_dimensions(total_width+(margin*2),items[0]->get_height()+title.get_height()+spacing+(margin*2));
        }
        else
            set_dimensions(total_width+(margin*2),items[0]->get_height()+(margin*2));
    }
    title.set_position(position.x,ymax-margin-(title.get_height()/2));
    subtitle.set_position(position.x,ymax-margin-title.get_height()-spacing-(subtitle.get_height()/2));
}

void ui::menu::set_title(std::string txt)
{
    title.set_text(txt);
    format();
}

void ui::menu::set_subtitle(std::string txt)
{
    subtitle.set_text(txt);
    subtitle.show();
    format();
}

void ui::menu::set_layout(std::string l)
{
    if(l=="vertical" || l=="horizontal")
        layout=l;
    else
        std::cerr<<"invalid layout.\n";
}


void ui::menu::add_item(button* item)
{
    items.push_back(item);
    format();
}

void ui::menu::add_item(std::string text, void (*action)())
{
    button* item = new button();
    item->set_label(text);
    item->set_action(action);
    add_item(item);
    format();
}

void ui::menu::render()
{
    if(visible)
    {
        render_shape();
        render_border();
        for(auto i:items)
            i->render();
        subtitle.render();
        title.render();
    }
}

void ui::menu::update()
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
        items[i]->visible=visible;//if menu is visible, items are visible
        items[i]->muted=muted;
        items[i]->update();
    }
}

void ui::menu::load()
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
    //load menu properties
    object_file>>spacing;
    object_file>>margin;
    object_file>>layout;
    //load title
    object_file>>title.text;
    object_file>>title.allignment;
    object_file>>title.spacing;
    object_file>>title.font_size;
    object_file>>title.font_width>>title.font_height;
    object_file>>title.font_color.r>>title.font_color.g>>title.font_color.b;
    //load subtitle
    object_file>>subtitle.text;
    object_file>>subtitle.allignment;
    object_file>>subtitle.spacing;
    object_file>>subtitle.font_size;
    object_file>>subtitle.font_width>>subtitle.font_height;
    object_file>>subtitle.font_color.r>>subtitle.font_color.g>>subtitle.font_color.b;
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
    std::clog<<"object#"<<number<<"(menu)"<<" loaded.\n";
}

void ui::menu::save()
{
    std::stringstream filename;
    filename<<"./data/menus/object#"<<number<<".mnu";
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
    //save menu properties
    object_file<<spacing<<std::endl;
    object_file<<margin<<std::endl;
    object_file<<layout<<std::endl;
    //save title
    object_file<<title.text<<std::endl;
    object_file<<title.allignment<<std::endl;
    object_file<<title.spacing<<std::endl;
    object_file<<title.font_size<<std::endl;
    object_file<<title.font_width<<' '<<title.font_height<<std::endl;
    object_file<<title.font_color.str()<<std::endl;
    //save subtitle
    object_file<<subtitle.text<<std::endl;
    object_file<<subtitle.allignment<<std::endl;
    object_file<<subtitle.spacing<<std::endl;
    object_file<<subtitle.font_size<<std::endl;
    object_file<<subtitle.font_width<<' '<<subtitle.font_height<<std::endl;
    object_file<<subtitle.font_color.str()<<std::endl;
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
    std::clog<<"object#"<<number<<"(menu)"<<" saved.\n";
}

ui::menu::menu()
{
    set_position(window::center.x,window::center.y);
    fill_color=default_fillcolor;
    border_color=default_bordercolor;
    set_texture(default_texture);
    set_mask(default_mask);
    set_title("menu");
    title.set_font("helvetica",18);
    subtitle.set_font("helvetica",12);
    subtitle.hide();
    layout=default_layout;
    spacing=default_spacing;
    margin=default_margin;
    bordered=true;
    std::clog<<"object#"<<number<<"(menu)"<<" created.\n";
}
