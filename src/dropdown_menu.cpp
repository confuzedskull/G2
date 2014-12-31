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

#include "dropdown_menu.h"
#include "cursor.h"
#include "ui.h"
#include <iostream>

std::string ui::dropdown_menu::default_texture = "";
std::string ui::dropdown_menu::default_mask = "";
std::string ui::dropdown_menu::default_click_sound = "";
std::string ui::dropdown_menu::default_hover_sound = "";
std::string ui::dropdown_menu::default_layout = "vertical";
color ui::dropdown_menu::default_fill_color = ui::default_fill_color;
color ui::dropdown_menu::default_border_color = ui::default_border_color;

std::string ui::dropdown_menu::get_type()
{
    return "dropdown menu";
}

void ui::dropdown_menu::add_item(button* item)
{
    item->bordered=false;
    item->text.allign(CENTER);
	items.push_back(item);
    menu::format();//match menu width to the width of the widest item
    //make all the items the same size
    for(auto i:items)
        i->set_dimensions(width,items.back()->get_height());
    set_dimensions(width,items.front()->get_height());//match menu height to item height
}

void ui::dropdown_menu::mouse_function()
{
    if(visible && enabled)
    {
        hover_function();
        if(left_clicked()||item_clicked()!=-1)
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
    {
        i->show();//show the buttons
        i->enable();
    }
}

void ui::dropdown_menu::collapse()
{
    set_dimensions(width,items.front()->get_height());//shrink to button size
    for(auto i:items)
    {
        i->hide();//hide the buttons
        i->disable();
    }
}

void ui::dropdown_menu::render()
{
    menu::render();
    button::render();
}

void ui::dropdown_menu::update()
{
    for(auto i:items)
    {
        if(!expanded && visible)
            i->visible=true;
        else
            i->visible=false;
        i->muted=muted;
        i->enabled=enabled;
        i->update();
    }
    mouse_function();
}

ui::dropdown_menu::dropdown_menu()
{
	title.hide();
    subtitle.hide();
    text.allign(CENTER);
    set_label("choose one:");
    set_layout(default_layout);
    spacing=0;
    menu::margin=0;
    state_toggle=false;
    expanded=false;
    fill_color=default_fill_color;
    border_color=default_border_color;
    set_texture(default_texture);
    set_mask(default_mask);
    set_click_sound(default_click_sound);
    set_hover_sound(default_hover_sound);
	std::clog<<"object#"<<number<<"(dropdown menu)"<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}
