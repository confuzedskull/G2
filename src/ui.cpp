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
#include <string.h>
#include <stdio.h>

//initialize variables
std::vector<button*> ui::buttons;
std::vector<menu*>ui::menus;
std::vector<char*> ui::info_overlay(20,new char[30]);//create 20 lines of 30 character length
float ui::margin = 10.0f;
float ui::spacing = 20.0f;

void ui::glutPrint(float x, float y, void* font, char* text, color c)
{
    if(!text || !strlen(text))
        return;
    glColor4f(c.r,c.g,c.b,c.a);
    glRasterPos2f(x,y);
    while(*text)
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
}

void ui::glutPrint(float x, float y, void* font, char* text)
{
    glutPrint(x, y, font, text, BLACK);
}

void ui::glutPrint(float x, float y, char* text)
{
    glutPrint(x, y, GLUT_BITMAP_HELVETICA_12, text);
}

void ui::print_overlay()
{
    unsigned index = cursor::selected_object;//number of the currently selected object
    unsigned line = 0;//used for spacing each line

    sprintf(info_overlay[line],"selected object: #%d - %s", cursor::left_clicked_object->get_number(), cursor::left_clicked_object->name);
    glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

    sprintf(info_overlay[line],"type: %s", cursor::left_clicked_object->get_type());
    glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

    sprintf(info_overlay[line],"dimensions: %.2fX%.2f", cursor::left_clicked_object->get_width(),cursor::left_clicked_object->get_height());
    glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

    sprintf(info_overlay[line],"rotation: %.2f", cursor::left_clicked_object->get_rotation());
    glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

    sprintf(info_overlay[line],"current position: %.2f,%.2f", cursor::left_clicked_object->get_position().x,cursor::left_clicked_object->get_position().y);
    glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

    if(strcmp(cursor::left_clicked_object->get_type(),"physics object")==0)//display the following if a physics object is selected
    {
        sprintf(info_overlay[line],"resting position: %.2f, %.2f",game::physics_objects[index]->rest.x,game::physics_objects[index]->rest.y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"mass: %.2f",game::physics_objects[index]->mass);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"speed: %.2f",game::physics_objects[index]->speed);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"time moving: %.2f,%.2f",game::physics_objects[index]->delta_time[0],game::physics_objects[index]->delta_time[1]);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"initial velocity: %.2f,%.2f",game::physics_objects[index]->velocity[0].x,game::physics_objects[index]->velocity[0].y);
        glutPrint (margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"final velocity: %.2f,%.2f",game::physics_objects[index]->velocity[1].x,game::physics_objects[index]->velocity[1].y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"time accelerating: %.2f %.2f",game::physics_objects[index]->delta_time[2],game::physics_objects[index]->delta_time[3]);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"acceleration: %.2f %.2f",game::physics_objects[index]->acceleration.x,game::physics_objects[index]->acceleration.y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"momentum: %.2f %.2f",game::physics_objects[index]->momentum.x,game::physics_objects[index]->momentum.y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"force: %.2f %.2f",game::physics_objects[index]->force.x,game::physics_objects[index]->force.y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"object touching side L:%d R:%d T:%d B:%d",game::physics_objects[index]->touching[0], game::physics_objects[index]->touching[1], game::physics_objects[index]->touching[2],game::physics_objects[index]->touching[3]);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);
    }
    if(strcmp(cursor::left_clicked_object->get_type(),"draggable object")==0)//display the following if a draggable object is selected
    {
        sprintf(info_overlay[line],"object touching side L:%d R:%d T:%d B:%d",game::draggable_objects[index]->touching[0], game::draggable_objects[index]->touching[1],game::draggable_objects[index]->touching[2],game::draggable_objects[index]->touching[3]);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);
    }
    if(strcmp(cursor::left_clicked_object->get_type(),"rts object")==0)//display the following if a RTS object is selected
    {
        sprintf(info_overlay[line],"speed: %.2f",game::rts_objects[index]->speed);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"rally point: %.2f, %.2f",game::rts_objects[index]->rally->x,game::rts_objects[index]->rally->y);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);

        sprintf(info_overlay[line],"object touching side L:%d R:%d T:%d B:%d",game::rts_objects[index]->touching[0], game::rts_objects[index]->touching[1], game::rts_objects[index]->touching[2],game::rts_objects[index]->touching[3]);
        glutPrint(margin,window::height-(line*spacing), info_overlay[line++]);
    }
    sprintf(info_overlay[line],"game time: %.2fs",game::time);
    glutPrint(window::width-(margin+150),window::height-(spacing*1), info_overlay[line++]);

    sprintf(info_overlay[line],"mouse move: %.2f,%.2f",cursor::passive.x,cursor::passive.y);
    glutPrint(window::width-(margin+150),window::height-(spacing*2), info_overlay[line++]);

    sprintf(info_overlay[line],"mouse click: %.2f,%.2f",cursor::left_down.x,cursor::left_down.y);
    glutPrint(window::width-(margin+150),window::height-(spacing*3), info_overlay[line++]);

    sprintf(info_overlay[line],"mouse drag: %.2f,%.2f",cursor::left_drag.x,cursor::left_drag.y);
    glutPrint(window::width-(margin+150),window::height-(spacing*4), info_overlay[line++]);
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
