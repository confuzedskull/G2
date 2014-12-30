/*  2DWorld - The Generic 2D Game Engine
    This is a multipurpose 2D game engine created from the ground up using OpenGL and GLUT
    Copyright (C) 2014  James Nakano

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include "window.h"
#include "audio.h"
#include "graphics.h"
#include "controls.h"
#include "game.h"
#include "ui.h"

int main()
{
//Initialize Settings
    game::add_setting("window","width",&window::width);
    game::add_setting("window","height",&window::height);
    game::add_setting("window","position_x",&window::position.x);
    game::add_setting("window","position_y",&window::position.y);
    game::add_setting("window","refresh_rate",&window::refresh_rate);
    game::add_setting("ui","overlay_margin",&ui::overlay_margin);
    game::add_setting("label","default_size",&label::default_size);
    game::add_setting("label","default_spacing",&label::default_spacing);
    game::add_setting("menu","default_margin",&menu::default_margin);
    game::add_setting("menu","default_spacing",&menu::default_spacing);
    game::add_setting("button","default_width",&button::default_width);
    game::add_setting("button","default_height",&button::default_height);
    game::add_setting("button","default_margin",&button::default_margin);
    game::add_setting("button","default_spacing",&button::default_margin);
    game::add_setting("checkbox","default_width",&checkbox::default_width);
    game::add_setting("checkbox","default_height",&checkbox::default_height);
    game::add_setting("checkbox","default_margin",&checkbox::default_margin);
    game::add_setting("draggable_object","default_x",&draggable_object::default_position.x);
    game::add_setting("draggable_object","default_y",&draggable_object::default_position.y);
    game::add_setting("draggable_object","default_width",&draggable_object::default_width);
    game::add_setting("draggable_object","default_height",&draggable_object::default_height);
    game::add_setting("physics_object","default_x",&physics_object::default_position.x);
    game::add_setting("physics_object","default_y",&physics_object::default_position.y);
    game::add_setting("physics_object","default_width",&physics_object::default_width);
    game::add_setting("physics_object","default_height",&physics_object::default_height);
    game::add_setting("rts_object","default_x",&rts_object::default_position.x);
    game::add_setting("rts_object","default_y",&rts_object::default_position.y);
    game::add_setting("rts_object","default_width",&rts_object::default_width);
    game::add_setting("rts_object","default_height",&rts_object::default_height);
    game::add_setting("game","show_info_overlay",0);
    game::add_setting("game","show_draggable_objects",1);
    game::add_setting("game","show_physics_objects",1);
    game::add_setting("game","show_rts_objects",1);
    game::add_setting("game","show_foreground",1);
    game::add_setting("game","show_middleground",0);
    game::add_setting("game","show_background",1);
    game::add_setting("game","show_textures",1);
    game::add_setting("game","mute_all",0);
//Initialize rules
    game::add_rule("game","show_info_overlay",1,ui::show_text);
    game::add_rule("game","show_info_overlay",0,ui::hide_text);
    game::add_rule("game","show_draggable_objects",1,controls::show_draggable_objects);
    game::add_rule("game","show_draggable_objects",0,controls::hide_draggable_objects);
    game::add_rule("game","show_physics_objects",1,controls::show_physics_objects);
    game::add_rule("game","show_physics_objects",0,controls::hide_physics_objects);
    game::add_rule("game","show_rts_objects",1,controls::show_rts_objects);
    game::add_rule("game","show_rts_objects",0,controls::hide_rts_objects);
    game::add_rule("game","show_foreground",1,controls::show_foreground);
    game::add_rule("game","show_foreground",0,controls::hide_foreground);
    game::add_rule("game","show_middleground",1,controls::show_middleground);
    game::add_rule("game","show_middleground",0,controls::hide_middleground);
    game::add_rule("game","show_background",1,controls::show_background);
    game::add_rule("game","show_background",0,controls::hide_background);
    game::add_rule("game","show_textures",1,controls::show_textures);
    game::add_rule("game","show_textures",0,controls::hide_textures);
    game::add_rule("game","mute_all",1,controls::mute_all);
    game::add_rule("game","mute_all",0,controls::unmute_all);
//Initialize Sound Effects
    audio::add_sound("clack.wav");
    audio::add_sound("pop.wav");
    audio::add_sound("trash.wav");
    audio::add_sound("click.wav");
    audio::add_sound("swipe.wav");
    audio::add_sound("angrybird-aheheha.wav");
    audio::add_sound("angrybird-ow.wav");
    audio::add_sound("siegetank-yessir.wav");
    audio::add_sound("siegetank-move_it.wav");
    audio::add_sound("low_clack.wav");
//Initialize Textures
    graphics::add_image("confuzedskull.bmp");
    graphics::add_image("angrybird.bmp");
    graphics::add_image("angrybird-mask.bmp");
    graphics::add_image("companioncube.bmp");
    graphics::add_image("companioncube-mask.bmp");
    graphics::add_image("SC2siegetank.bmp");
    graphics::add_image("SC2siegetank-mask.bmp");
    graphics::add_image("angrybirds_ground.bmp");
    graphics::add_image("angrybirds_ground-mask.bmp");
    graphics::add_image("SC2background.bmp");
    graphics::add_image("portals.bmp");
//Initialize Objects
    //initialize the physics objects
    physics_object::default_texture="angrybird.bmp";
    physics_object::default_mask="angrybird-mask.bmp";
    physics_object::default_click_sound="angrybird-aheheha.wav";
    physics_object::default_collision_sound="angrybird-ow.wav";
    physics_object* po1 = new physics_object();
    po1->set_position(window::center.x-48,window::center.y+48);//set position forward left of window center
    po1->rest();//make sure the resting point matches the new position
    po1->cue_action("wait",50);
    po1->cue_action("move right",10);
    po1->cue_action("wait",100);
    po1->cue_action("move back",10);
    po1->cue_action("wait",100);
    po1->cue_action("move left",10);
    po1->cue_action("wait",100);
    po1->cue_action("move forward",10);
    po1->cue_action("wait",100);
    po1->cue_action("turn left",30);
    po1->cue_action("wait",50);
    po1->cue_action("turn right",30);

    physics_object* po2 = new physics_object();
    po2->set_position(window::center.x+48,window::center.y+48);//set position forward right of window center
    po2->rest();//make sure the resting point matches the new position
    po2->cue_action("wait",50);
    po2->cue_action("move back",10);
    po2->cue_action("wait",100);
    po2->cue_action("move left",10);
    po2->cue_action("wait",100);
    po2->cue_action("move forward",10);
    po2->cue_action("wait",100);
    po2->cue_action("move right",10);
    po2->cue_action("wait",100);
    po2->cue_action("turn left",30);
    po2->cue_action("wait",50);
    po2->cue_action("turn right",30);

    physics_object* po3 = new physics_object();
    po3->set_position(window::center.x+48,window::center.y-48);//set position backward right of window center
    po3->rest();//make sure the resting point matches the new position
    po3->cue_action("wait",50);
    po3->cue_action("move left",10);
    po3->cue_action("wait",100);
    po3->cue_action("move forward",10);
    po3->cue_action("wait",100);
    po3->cue_action("move right",10);
    po3->cue_action("wait",100);
    po3->cue_action("move back",10);
    po3->cue_action("wait",100);
    po3->cue_action("turn left",30);
    po3->cue_action("wait",50);
    po3->cue_action("turn right",30);

    physics_object* po4 = new physics_object();
    po4->set_position(window::center.x-48,window::center.y-48);//set position backward left of window center
    po4->rest();//make sure the resting point matches the new position
    po4->cue_action("wait",50);
    po4->cue_action("move forward",10);
    po4->cue_action("wait",100);
    po4->cue_action("move right",10);
    po4->cue_action("wait",100);
    po4->cue_action("move back",10);
    po4->cue_action("wait",100);
    po4->cue_action("move left",10);
    po4->cue_action("wait",100);
    po4->cue_action("turn left",30);
    po4->cue_action("wait",50);
    po4->cue_action("turn right",30);
    //initialize the draggable objects
    draggable_object::default_texture="companioncube.bmp";
    draggable_object::default_mask="companioncube-mask.bmp";
    draggable_object* do1 = new draggable_object();
    do1->set_position(window::center.x,window::center.y);//set position window center
    //initialize the rts objects
    rts_object::default_texture="SC2siegetank.bmp";
    rts_object::default_mask="SC2siegetank-mask.bmp";
    rts_object::default_click_sound="siegetank-yessir.wav";
    rts_object::default_collision_sound="siegetank-move_it.wav";
    rts_object::default_movement_sound="low_clack.wav";
    rts_object* rtso1 = new rts_object();
    rtso1->set_position(window::center.x+96,window::center.y);//set position right of window center
    rtso1->fill_color.set("yellow");

    rts_object* rtso2 = new rts_object();
    rtso2->set_position(window::center.x,window::center.y-96);//set position below window center
    rtso2->fill_color.set("green");

    rts_object* rtso3 = new rts_object();
    rtso3->set_position(window::center.x,window::center.y+96);//set position above window center
    rtso3->fill_color.set("red");

    rts_object* rtso4 = new rts_object();
    rtso4->set_position(window::center.x-96,window::center.y);//set position left of window center
    rtso4->fill_color.set("blue");
//Initialize Text
    //Information Overlay Text
    label* object_info = new label();
    object_info->set_spacing(20);
    object_info->set_position(ui::overlay_margin,window::height-20);
    object_info->hide();//we don't want to see this right away

    label* game_info = new label();
    game_info->set_spacing(20);
    game_info->set_position(window::width-(ui::overlay_margin+200),window::height-20);
    game_info->hide();//we don't want to see this right away
//Initialize Checkboxes
    checkbox::default_click_sound="click.wav";
    checkbox::default_hover_sound="swipe.wav";
    checkbox* mute_all_checkbox = new checkbox();
    mute_all_checkbox->text.set_text("mute all");
    mute_all_checkbox->bind_option(game::settings["game"]["mute_all"]);

    checkbox* show_textures_checkbox = new checkbox();
    show_textures_checkbox->text.set_text("show textures");
    show_textures_checkbox->bind_option(game::settings["game"]["show_textures"]);

    checkbox* show_foreground_checkbox = new checkbox();
    show_foreground_checkbox->text.set_text("show foreground");
    show_foreground_checkbox->bind_option(game::settings["game"]["show_foreground"]);

    checkbox* show_middleground_checkbox = new checkbox();
    show_middleground_checkbox->set_label("show middleground");
    show_middleground_checkbox->bind_option(game::settings["game"]["show_middleground"]);

    checkbox* show_background_checkbox = new checkbox();
    show_background_checkbox->set_label("show background");
    show_background_checkbox->bind_option(game::settings["game"]["show_background"]);

    checkbox* show_dos_checkbox = new checkbox();
    show_dos_checkbox->set_label("show draggable objects");
    show_dos_checkbox->bind_option(game::settings["game"]["show_draggable_objects"]);

    checkbox* show_pos_checkbox = new checkbox();
    show_pos_checkbox->set_label("show physics objects");
    show_pos_checkbox->bind_option(game::settings["game"]["show_physics_objects"]);

    checkbox* show_rtsos_checkbox = new checkbox();
    show_rtsos_checkbox->set_label("show rts objects");
    show_rtsos_checkbox->bind_option(game::settings["game"]["show_rts_objects"]);
//Initialize Buttons
    //Main Menu Buttons
    button::default_click_sound="click.wav";
    button::default_hover_sound="swipe.wav";
    button* play_button = new button();
    play_button->set_label("Play");
    play_button->set_action(game::play);

    button* load_button = new button();
    load_button->set_label("Load");
    load_button->set_action(game::load);

    button* quit_button = new button();
    quit_button->set_label("Quit");
    quit_button->set_action(controls::switch_menu,2);
    //Quit Menu Buttons
    button* confirm_quit = new button();
    confirm_quit->set_label("Yes");
    confirm_quit->set_action(game::quit);

    button* cancel_quit = new button();
    cancel_quit->set_label("No");
    cancel_quit->set_action(controls::switch_menu,0);
    //Pause Menu Buttons
    button* resume_button = new button();
    resume_button->set_label("Resume");
    resume_button->set_action(game::resume);

    button* save_button = new button();
    save_button->set_label("Save");
    save_button->set_action(game::save);

    button* main_menu_button = new button();
    main_menu_button->set_label("Main Menu");
    main_menu_button->set_action(controls::switch_menu,2);
    //Warning Menu Buttons
    button* confirm_return_button = new button();
    confirm_return_button->set_label("Yes");
    confirm_return_button->set_action(controls::switch_scene,0);

    button* cancel_return_button = new button();
    cancel_return_button->set_label("No");
    cancel_return_button->set_action(controls::switch_menu,0);
    //Game Buttons
    button* create_po_button = new button();//"po" stands for "physics object"
    create_po_button->set_label("physics object");
    create_po_button->set_action(controls::add_physics_object);
    create_po_button->set_click_sound("pop.wav");

    button* create_do_button = new button();//"do" stands for "draggable object"
    create_do_button->set_label("draggable object");
    create_do_button->set_action(controls::add_draggable_object);
    create_do_button->set_click_sound("pop.wav");

    button* create_rtso_button = new button();//"rtso" stands for "real-time strategy object"
    create_rtso_button->set_label("rts object");
    create_rtso_button->set_action(controls::add_rts_object);
    create_rtso_button->set_click_sound("pop.wav");

    button* create_object_button = new button();
    create_object_button->set_position(window::width*0.9,window::height*0.1);//put the button on the right side, 1/5th of the way up
    create_object_button->set_label("create object");
    create_object_button->set_action(controls::create_object);
    create_object_button->set_click_sound("pop.wav");

    button* delete_object_button = new button();
    delete_object_button->set_position(window::width*0.9,window::height*0.05);//put the button on the right side, 1/5th of the way up
    delete_object_button->set_label("delete object");
    delete_object_button->set_action(controls::delete_selected);
    delete_object_button->set_click_sound("trash.wav");

    button* menu_button = new button();
    menu_button->set_position(window::center.x,window::height-20);//put the button at the top middle, just below the top
    menu_button->set_label("Pause");
    menu_button->set_action(game::pause);

    button* settings_button = new button();
    settings_button->set_label("Settings");
    settings_button->set_action(controls::switch_menu,1);

    button* leave_settings_button = new button();
    leave_settings_button->set_label("Back");
    leave_settings_button->set_action(controls::switch_menu,0);
//Initialize Menus
    dropdown_menu* creation_menu = new dropdown_menu();
    creation_menu->set_label("create new...");
    creation_menu->set_position(window::width*0.9,window::height*0.25);
    creation_menu->add_item(create_do_button);
    creation_menu->add_item(create_po_button);
    creation_menu->add_item(create_rtso_button);

    menu* main_menu = new menu();
    main_menu->set_title("Main Menu");
    main_menu->add_item(play_button);
    main_menu->add_item(load_button);
    main_menu->add_item(settings_button);
    main_menu->add_item(quit_button);

    menu* quit_menu = new menu();
    quit_menu->set_title("Warning");
    quit_menu->set_subtitle("Are you sure you want to quit?");
    quit_menu->set_layout("horizontal");
    quit_menu->add_item(confirm_quit);
    quit_menu->add_item(cancel_quit);
    quit_menu->hide();//we don't want to see this right away

    menu* settings_menu = new menu();
    settings_menu->set_title("Settings");
    settings_menu->add_item(mute_all_checkbox);
    settings_menu->add_item(show_textures_checkbox);
    settings_menu->add_item(show_foreground_checkbox);
    settings_menu->add_item(show_middleground_checkbox);
    settings_menu->add_item(show_background_checkbox);
    settings_menu->add_item(show_dos_checkbox);
    settings_menu->add_item(show_pos_checkbox);
    settings_menu->add_item(show_rtsos_checkbox);
    settings_menu->add_item(leave_settings_button);
    settings_menu->hide();

    menu* pause_menu = new menu();
    pause_menu->set_title("Paused");
    pause_menu->add_item(resume_button);
    pause_menu->add_item(save_button);
    pause_menu->add_item(settings_button);
    pause_menu->add_item(main_menu_button);
    pause_menu->hide();//we don't want to see this right away

    menu* leave_menu = new menu();
    leave_menu->set_title("Warning");
    leave_menu->set_subtitle("Are you sure you want to leave?");
    leave_menu->set_layout("horizontal");
    leave_menu->add_item(confirm_return_button);
    leave_menu->add_item(cancel_return_button);
    leave_menu->hide();//we don't want to see this right away
//Initialize Scenes
    scene* home_screen = new scene();
    home_screen->foreground.fill_color.set(0.25,0.25,0.25);
    home_screen->add_menu(main_menu);
    home_screen->add_menu(settings_menu);
    home_screen->add_menu(quit_menu);
    home_screen->current_menu=main_menu;
    home_screen->bind_key("up",controls::previous_item);
    home_screen->bind_key("down",controls::next_item);
    home_screen->bind_key("left",controls::previous_item);
    home_screen->bind_key("right",controls::next_item);
    home_screen->bind_key('\r',controls::choose_item);
    game::scenes.push_back(home_screen);//add to scenes
    game::main_scene=home_screen;//make this the main scene
    game::current_scene=home_screen;//start the game with this screen

    scene* game_screen = new scene();
    game_screen->background.set_dimensions(window::width,window::height);
    game_screen->background.textured=true;
    game_screen->background.set_texture("SC2background.bmp");
    game_screen->middleground.set_dimensions(window::width/4,window::height/3);
    game_screen->middleground.textured=true;
    game_screen->middleground.set_texture("portals.bmp");
    game_screen->foreground.set_position(window::center.x,window::center.y-(window::height/3));
    game_screen->foreground.set_dimensions(window::width,window::height/3);
    game_screen->foreground.textured=true;
    game_screen->foreground.masked=true;
    game_screen->foreground.set_texture("angrybirds_ground.bmp");
    game_screen->foreground.set_mask("angrybirds_ground-mask.bmp");
    game_screen->add_object(do1);
    game_screen->add_object(po1);
    game_screen->add_object(po2);
    game_screen->add_object(po3);
    game_screen->add_object(po4);
    game_screen->add_object(rtso1);
    game_screen->add_object(rtso2);
    game_screen->add_object(rtso3);
    game_screen->add_object(rtso4);
    game_screen->add_text(object_info);
    game_screen->add_text(game_info);
    game_screen->add_button(delete_object_button);
    game_screen->add_button(create_object_button);
    game_screen->add_button(menu_button);
    game_screen->add_menu(pause_menu);
    game_screen->add_menu(settings_menu);
    game_screen->add_menu(leave_menu);
    game_screen->add_menu(creation_menu);
    game_screen->bind_key('w',controls::move_forward);
    game_screen->bind_key('a',controls::move_left);
    game_screen->bind_key('s',controls::move_back);
    game_screen->bind_key('d',controls::move_right);
    game_screen->bind_key('q',controls::turn_left);
    game_screen->bind_key('e',controls::turn_right);
    game_screen->bind_key('i',game::settings["game"]["show_info_overlay"]);
    game_screen->bind_key('\r',controls::choose_item);
    game_screen->bind_key("up",controls::previous_item);
    game_screen->bind_key("down",controls::next_item);
    game_screen->bind_key("left",controls::previous_item);
    game_screen->bind_key("right",controls::next_item);
    game_screen->bind_key("insert",controls::create_object);
    game_screen->bind_key(127,controls::delete_selected);//127 is the delete key
    game_screen->bind_key(27, game::pause);//27 is the 'esc' key
    game::play_scene=game_screen;
    game::scenes.push_back(game_screen);//add to scenes
    game::initialize();//start the game
}
