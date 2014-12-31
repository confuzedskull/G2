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
    game::add_setting("label","default_font_size",&ui::label::default_font_size);
    game::add_setting("label","default_spacing",&ui::label::default_spacing);
    game::add_setting("menu","default_margin",&ui::menu::default_margin);
    game::add_setting("menu","default_spacing",&ui::menu::default_spacing);
    game::add_setting("button","default_width",&ui::button::default_width);
    game::add_setting("button","default_height",&ui::button::default_height);
    game::add_setting("button","default_margin",&ui::button::default_margin);
    game::add_setting("button","default_spacing",&ui::button::default_margin);
    game::add_setting("checkbox","default_width",&ui::checkbox::default_width);
    game::add_setting("checkbox","default_height",&ui::checkbox::default_height);
    game::add_setting("checkbox","default_margin",&ui::checkbox::default_margin);
    game::add_setting("model","default_x",&model::default_position.x);
    game::add_setting("model","default_y",&model::default_position.y);
    game::add_setting("model","default_width",&model::default_width);
    game::add_setting("model","default_height",&model::default_height);
    game::add_setting("game","show_info_overlay",0);
    game::add_setting("game","show_models",1);
    game::add_setting("game","show_foreground",1);
    game::add_setting("game","show_middleground",0);
    game::add_setting("game","show_background",1);
    game::add_setting("game","show_textures",1);
    game::add_setting("game","mute_all",0);
//Initialize rules
    game::add_rule("game","show_models",1,controls::show_models);
    game::add_rule("game","show_models",0,controls::hide_models);
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
//Initialize Models
    model::default_width=64;
    model::default_height=64;
    model::enable_dragging=true;
    model::default_texture="companioncube.bmp";
    model::default_mask="companioncube-mask.bmp";

    model* dro1 = new model();
    dro1->set_position(window::center.x,window::center.y);

    model::default_width=32;
    model::default_height=32;
    model::enable_physics=true;
    model::enable_dragging=false;
    model::enable_keyboard_controls=true;
    model::default_texture="angrybird.bmp";
    model::default_mask="angrybird-mask.bmp";
    model::default_click_sound="angrybird-aheheha.wav";
    model::default_collision_sound="angrybird-ow.wav";

    model* po1 = new model();
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

    model* po2 = new model();
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

    model* po3 = new model();
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

    model* po4 = new model();
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

    model::default_width=64;
    model::default_height=64;
    model::enable_physics=false;
    model::enable_rts_controls=true;
    model::enable_keyboard_controls=false;
    model::default_texture="SC2siegetank.bmp";
    model::default_mask="SC2siegetank-mask.bmp";
    model::default_movement_sound="low_clack.wav";
    model::default_click_sound="siegetank-yessir.wav";
    model::default_collision_sound="siegetank-move_it.wav";

    model* rtso1 = new model();
    rtso1->set_position(window::center.x+96,window::center.y);//set position right of window center
    rtso1->fill_color.set("yellow");

    model* rtso2 = new model();
    rtso2->set_position(window::center.x,window::center.y-96);//set position below window center
    rtso2->fill_color.set("green");

    model* rtso3 = new model();
    rtso3->set_position(window::center.x,window::center.y+96);//set position above window center
    rtso3->fill_color.set("red");

    model* rtso4 = new model();
    rtso4->set_position(window::center.x-96,window::center.y);//set position left of window center
    rtso4->fill_color.set("blue");
//Initialize Text
    //Information Overlay Text
    ui::label* object_info = new ui::label();
    object_info->set_spacing(20);
    object_info->set_position(50,window::height-20);

    ui::label* game_info = new ui::label();
    game_info->set_spacing(20);
    game_info->set_position(window::width-200,window::height-20);
//Initialize Checkboxes
    ui::checkbox::default_click_sound="click.wav";
    ui::checkbox::default_hover_sound="swipe.wav";
    ui::checkbox* mute_all_checkbox = new ui::checkbox();
    mute_all_checkbox->text.set_text("mute all");
    mute_all_checkbox->bind_option(game::settings["game"]["mute_all"]);

    ui::checkbox* show_textures_checkbox = new ui::checkbox();
    show_textures_checkbox->text.set_text("show textures");
    show_textures_checkbox->bind_option(game::settings["game"]["show_textures"]);

    ui::checkbox* show_foreground_checkbox = new ui::checkbox();
    show_foreground_checkbox->text.set_text("show foreground");
    show_foreground_checkbox->bind_option(game::settings["game"]["show_foreground"]);

    ui::checkbox* show_middleground_checkbox = new ui::checkbox();
    show_middleground_checkbox->set_label("show middleground");
    show_middleground_checkbox->bind_option(game::settings["game"]["show_middleground"]);

    ui::checkbox* show_background_checkbox = new ui::checkbox();
    show_background_checkbox->set_label("show background");
    show_background_checkbox->bind_option(game::settings["game"]["show_background"]);

    ui::checkbox* show_models_checkbox = new ui::checkbox();
    show_models_checkbox->set_label("show models");
    show_models_checkbox->bind_option(game::settings["game"]["show_models"]);
//Initialize Buttons
    //Main Menu Buttons
    ui::button::default_click_sound="click.wav";
    ui::button::default_hover_sound="swipe.wav";
    ui::button* play_button = new ui::button();
    play_button->set_label("Play");
    play_button->set_action(game::play);

    ui::button* load_button = new ui::button();
    load_button->set_label("Load");
    load_button->set_action(game::load);

    ui::button* quit_button = new ui::button();
    quit_button->set_label("Quit");
    quit_button->set_action(controls::switch_menu,2);
    //Quit Menu Buttons
    ui::button* confirm_quit = new ui::button();
    confirm_quit->set_label("Yes");
    confirm_quit->set_action(game::quit);

    ui::button* cancel_quit = new ui::button();
    cancel_quit->set_label("No");
    cancel_quit->set_action(controls::switch_menu,0);
    //Pause Menu Buttons
    ui::button* resume_button = new ui::button();
    resume_button->set_label("Resume");
    resume_button->set_action(game::resume);

    ui::button* save_button = new ui::button();
    save_button->set_label("Save");
    save_button->set_action(game::save);

    ui::button* main_menu_button = new ui::button();
    main_menu_button->set_label("Main Menu");
    main_menu_button->set_action(controls::switch_menu,2);
    //Warning Menu Buttons
    ui::button* confirm_return_button = new ui::button();
    confirm_return_button->set_label("Yes");
    confirm_return_button->set_action(controls::switch_scene,0);

    ui::button* cancel_return_button = new ui::button();
    cancel_return_button->set_label("No");
    cancel_return_button->set_action(controls::switch_menu,0);
    //Game Buttons
    ui::button* create_model_button = new ui::button();
    create_model_button->set_label("model");
    create_model_button->set_action(controls::add_model);
    create_model_button->set_click_sound("pop.wav");

    ui::button* create_object_button = new ui::button();
    create_object_button->set_position(window::width*0.9,window::height*0.1);//put the button on the right side, 1/5th of the way up
    create_object_button->set_label("create object");
    create_object_button->set_action(controls::create_object);
    create_object_button->set_click_sound("pop.wav");

    ui::button* delete_object_button = new ui::button();
    delete_object_button->set_position(window::width*0.9,window::height*0.05);//put the button on the right side, 1/5th of the way up
    delete_object_button->set_label("delete object");
    delete_object_button->set_action(controls::delete_selected);
    delete_object_button->set_click_sound("trash.wav");

    ui::button* menu_button = new ui::button();
    menu_button->set_position(window::center.x,window::height-20);//put the button at the top middle, just below the top
    menu_button->set_label("Pause");
    menu_button->set_action(game::pause);

    ui::button* settings_button = new ui::button();
    settings_button->set_label("Settings");
    settings_button->set_action(controls::switch_menu,1);

    ui::button* leave_settings_button = new ui::button();
    leave_settings_button->set_label("Back");
    leave_settings_button->set_action(controls::switch_menu,0);
//Initialize Menus
    ui::dropdown_menu* creation_menu = new ui::dropdown_menu();
    creation_menu->set_position(window::width*0.9,window::height*0.25);
    creation_menu->set_label("create new...");
    creation_menu->add_item(create_model_button);

    ui::menu* main_menu = new ui::menu();
    main_menu->set_title("Main Menu");
    main_menu->add_item(play_button);
    main_menu->add_item(load_button);
    main_menu->add_item(settings_button);
    main_menu->add_item(quit_button);

    ui::menu* quit_menu = new ui::menu();
    quit_menu->set_title("Warning");
    quit_menu->set_subtitle("Are you sure you want to quit?");
    quit_menu->set_layout("horizontal");
    quit_menu->add_item(confirm_quit);
    quit_menu->add_item(cancel_quit);
    quit_menu->hide();//we don't want to see this right away

    ui::menu* settings_menu = new ui::menu();
    settings_menu->set_title("Settings");
    settings_menu->add_item(mute_all_checkbox);
    settings_menu->add_item(show_textures_checkbox);
    settings_menu->add_item(show_foreground_checkbox);
    settings_menu->add_item(show_middleground_checkbox);
    settings_menu->add_item(show_background_checkbox);
    settings_menu->add_item(show_models_checkbox);
    settings_menu->add_item(leave_settings_button);
    settings_menu->hide();

    ui::menu* pause_menu = new ui::menu();
    pause_menu->set_title("Paused");
    pause_menu->add_item(resume_button);
    pause_menu->add_item(save_button);
    pause_menu->add_item(settings_button);
    pause_menu->add_item(main_menu_button);
    pause_menu->hide();//we don't want to see this right away

    ui::menu* leave_menu = new ui::menu();
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
    game_screen->add_model(dro1);
    game_screen->add_model(po1);
    game_screen->add_model(po2);
    game_screen->add_model(po3);
    game_screen->add_model(po4);
    game_screen->add_model(rtso1);
    game_screen->add_model(rtso2);
    game_screen->add_model(rtso3);
    game_screen->add_model(rtso4);
    game_screen->add_label(object_info);
    game_screen->add_label(game_info);
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
