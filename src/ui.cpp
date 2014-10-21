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

#include "ui.h"
#include "window.h"
#include "game.h"
#include "controls.h"
#include "cursor.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

//initialize variables
std::vector<button*> ui::buttons;
std::vector<menu*>ui::menus;
std::vector<text_object*> ui::text_objects;
int ui::margin = 10;

void ui::init_text()
{
    text_object* object_info = new text_object();
    object_info->visible=false;
    object_info->spacing=20;
    object_info->set_position(margin,window::height-20);
    text_objects.push_back(object_info);

    text_object* game_info = new text_object();
    game_info->visible=false;
    game_info->spacing=20;
    game_info->set_position(window::width-(margin+150),window::height-20);
    text_objects.push_back(game_info);
}

void ui::init_buttons()
{
//Main Menu Buttons
    button* play_button = new button();//create a button pointer and initialize it
    play_button->set_label("Play");
    play_button->action=game::play;//function is assigned without '()' at the end
    buttons.push_back(play_button);//add button to container

    button* quit_button = new button();//create a button pointer and initialize it
    quit_button->set_label("Quit");
    quit_button->action=game::quit;//function is assigned without '()' at the end
    buttons.push_back(quit_button);//add button to container
//Pause Menu Buttons
    button* resume_button = new button();//create a button pointer and initialize it
    resume_button->set_label("Resume");
    resume_button->action=game::resume;//function is assigned without '()' at the end
    buttons.push_back(resume_button);//add button to container

    button* main_menu_button = new button();//create a button pointer and initialize it
    main_menu_button->set_label("Main Menu");
    main_menu_button->action=game::return_warning;//function is assigned without '()' at the end
    buttons.push_back(main_menu_button);//add button to container
//Warning Menu Buttons
    button* confirm_return_button = new button();//create a button pointer and initialize it
    confirm_return_button->set_label("Yes");
    confirm_return_button->action=game::return_menu;//function is assigned without '()' at the end
    buttons.push_back(confirm_return_button);//add button to container

    button* cancel_return_button = new button();
    cancel_return_button->set_label("No");
    cancel_return_button->action=game::pause;
    buttons.push_back(cancel_return_button);

//Game Buttons
    button* create_po_button = new button();//"po" stands for "physics object"
    create_po_button->set_position(window::width*0.9,window::height*0.8);//put the button on the right side, 4/5ths of the way up
    create_po_button->set_label("new physics object");
    create_po_button->action=game::add_physics_object;//function is assigned without '()' at the end
    buttons.push_back(create_po_button);//add button to container

    button* create_do_button = new button();//"do" stands for "draggable object"
    create_do_button->set_position(window::width*0.9,window::height*0.6);//put the button on the right side, 3/5ths of the way up
    create_do_button->set_label("new draggable object");
    create_do_button->action=game::add_draggable_object;//function is assigned without '()' at the end
    buttons.push_back(create_do_button);//add button to container

    button* create_rtso_button = new button();//"rtso" stands for "real-time strategy object"
    create_rtso_button->set_position(window::width*0.9,window::height*0.4);//put the button on the right side, 2/5ths of the way up
    create_rtso_button->set_label("new rts object");
    create_rtso_button->action=game::add_rts_object;//function is assigned without '()' at the end
    buttons.push_back(create_rtso_button);//add button to container

    button* delete_object_button = new button();//create a button pointer and initialize it
    delete_object_button->set_position(window::width*0.9,window::height*0.2);//put the button on the right side, 1/5th of the way up
    delete_object_button->set_label("delete object");
    delete_object_button->action=game::delete_selected;//function is assigned without '()' at the end
    buttons.push_back(delete_object_button);//add button to container

    button* menu_button = new button();//create a button pointer and initialize it
    menu_button->set_position(window::center.x,window::height-20);//put the button at the top middle, just below the top
    menu_button->set_label("Menu");
    menu_button->action=game::pause;//function is assigned without '()' at the end
    buttons.push_back(menu_button);//add button to container
}

void ui::init_menus()
{
    menu* main_menu = new menu();
    main_menu->set_title("Main Menu");
    main_menu->items.push_back(buttons[0]);
    main_menu->items.push_back(buttons[1]);
    main_menu->format();
    menus.push_back(main_menu);

    menu* pause_menu = new menu();
    pause_menu->set_title("Pause Menu");
    pause_menu->visible=false;
    pause_menu->items.push_back(buttons[2]);
    pause_menu->items.push_back(buttons[3]);
    pause_menu->format();
    menus.push_back(pause_menu);

    menu* warning_menu = new menu();
    warning_menu->set_title("Warning");
    warning_menu->set_subtitle("Are you sure you want to leave?");
    warning_menu->visible=false;
    warning_menu->layout=HORIZONTAL;
    warning_menu->items.push_back(buttons[4]);
    warning_menu->items.push_back(buttons[5]);
    warning_menu->format();
    menus.push_back(warning_menu);

}

void ui::update_text()
{
    if(controls::toggle_overlay)
    {
        text_object* object_info = game::scenes[1]->text_objects[0];
        unsigned index = cursor::selected_object;
        using namespace std;
        object_info->clear();
        object_info->add_line("selected object: #"+to_string(cursor::left_clicked_object->get_number())+", "+cursor::left_clicked_object->name);
        object_info->add_line("type: "+cursor::left_clicked_object->get_type());
        object_info->add_line("dimensions: "+to_string(cursor::left_clicked_object->get_width())+'X'+to_string(cursor::left_clicked_object->get_height()));
        object_info->add_line("rotation: "+to_string(cursor::left_clicked_object->get_rotation()));
        object_info->add_line("current position: "+to_string(cursor::left_clicked_object->get_position().x)+", "+to_string(cursor::left_clicked_object->get_position().y));
        if(cursor::left_clicked_object->get_type()=="physics object")//display the following if a physics object is selected
        {
            object_info->add_line("resting position: "+to_string(game::physics_objects[index]->rest.x)+", "+to_string(game::physics_objects[index]->rest.y));
            object_info->add_line("mass: "+to_string(game::physics_objects[index]->mass));
            object_info->add_line("speed: "+to_string(game::physics_objects[index]->speed));
            object_info->add_line("time moving: "+to_string(game::physics_objects[index]->delta_time[0])+", "+to_string(game::physics_objects[index]->delta_time[1]));
            object_info->add_line("initial velocity: "+to_string(game::physics_objects[index]->velocity[0].x)+", "+to_string(game::physics_objects[index]->velocity[0].y));
            object_info->add_line("final velocity: "+to_string(game::physics_objects[index]->velocity[1].x)+", "+to_string(game::physics_objects[index]->velocity[1].y));
            object_info->add_line("time accelerating: "+to_string(game::physics_objects[index]->delta_time[2])+", "+to_string(game::physics_objects[index]->delta_time[3]));
            object_info->add_line("acceleration: "+to_string(game::physics_objects[index]->acceleration.x)+", "+to_string(game::physics_objects[index]->acceleration.y));
            object_info->add_line("momentum: "+to_string(game::physics_objects[index]->momentum.x)+", "+to_string(game::physics_objects[index]->momentum.y));
            object_info->add_line("force: "+to_string(game::physics_objects[index]->force.x)+", "+to_string(game::physics_objects[index]->force.y));
            object_info->add_line("object touching side L:"+to_string(game::physics_objects[index]->touching[0])+"R:"+to_string(game::physics_objects[index]->touching[1])
                                                        +"T:"+to_string(game::physics_objects[index]->touching[2])+"B:"+to_string(game::physics_objects[index]->touching[3]));
        }
        if(cursor::left_clicked_object->get_type()=="draggable object")//display the following if a draggable object is selected
        {
            object_info->add_line("object touching side"+to_string(game::draggable_objects[index]->touching[0])+to_string(game::draggable_objects[index]->touching[1])
                                   +to_string(game::draggable_objects[index]->touching[2])+to_string(game::draggable_objects[index]->touching[3]));
        }
        if(cursor::left_clicked_object->get_type()=="rts object")//display the following if a RTS object is selected
        {
            object_info->add_line("speed: "+to_string(game::rts_objects[index]->speed));
            object_info->add_line("rally point: "+to_string(game::rts_objects[index]->rally->x)+", "+to_string(game::rts_objects[index]->rally->y));
            object_info->add_line("object touching side L:"+to_string(game::rts_objects[index]->touching[0])+"R:"+to_string(game::rts_objects[index]->touching[1])
                                                         +"T:"+to_string(game::rts_objects[index]->touching[2])+"B:"+to_string(game::rts_objects[index]->touching[3]));
        }

        text_object* game_info = game::scenes[1]->text_objects[1];
        game_info->clear();
        game_info->add_line("game time: "+to_string(game::time));
        game_info->add_line("mouse move: "+to_string(cursor::passive.x)+", "+to_string(cursor::passive.y));
        game_info->add_line("mouse click: "+to_string(cursor::left_down.x)+", "+to_string(cursor::left_down.y));
        game_info->add_line("mouse drag: "+to_string(cursor::left_drag.x)+", "+to_string(cursor::left_drag.y));
    }
}
