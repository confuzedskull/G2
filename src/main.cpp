/*  G2 Editor
    This is an editor designed for the G2 Engine
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
    window::title="G2 Editor";
//Initialize Settings
    game::add_setting("window","width",&window::width);
    game::add_setting("window","height",&window::height);
    game::add_setting("window","position_x",&window::position.x);
    game::add_setting("window","position_y",&window::position.y);
    game::add_setting("window","refresh_rate",&window::refresh_rate);
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
    audio::add_sound("angrybirds_theme.wav");
//Initialize Textures
    graphics::add_image("confuzedskull.bmp");
    graphics::add_image("angrybird.bmp");
    graphics::add_image("angrybird-mask.bmp");
    graphics::add_image("companioncube.bmp");
    graphics::add_image("companioncube-mask.bmp");
    graphics::add_image("SC2siegetank.bmp");
    graphics::add_image("SC2siegetank-mask.bmp");
//Initialize Objects
    basic_object* home_screen_background = new basic_object();
    home_screen_background->set_dimensions(window::width,window::height);
    home_screen_background->fill_color.set(0.25,0.25,0.25);//dark gray

    basic_object* play_screen_background = new basic_object();
    play_screen_background->set_dimensions(window::width,window::height);
    play_screen_background->fill_color.set(BLACK);

    advanced_object* dro1 = new advanced_object();
    dro1->set_position(window::center.x,window::center.y);
    dro1->set_dimensions(64,64);
    dro1->drag_detection=true;
    dro1->set_texture("companioncube.bmp");
    dro1->set_mask("companioncube-mask.bmp");
    //set the default values for physics objects
    advanced_object::default_width=32;
    advanced_object::default_height=32;
    advanced_object::enable_physics=true;
    advanced_object::enable_dragging=false;
    advanced_object::enable_keyboardcontrols=true;
    advanced_object::default_texture="angrybird.bmp";
    advanced_object::default_mask="angrybird-mask.bmp";
    advanced_object::default_clicksound="angrybird-aheheha.wav";
    advanced_object::default_collisionsound="angrybird-ow.wav";

    advanced_object* po1 = new advanced_object();
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

    advanced_object* po2 = new advanced_object();
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

    advanced_object* po3 = new advanced_object();
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

    advanced_object* po4 = new advanced_object();
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
    //set the default values for rts objects
    advanced_object::default_width=64;
    advanced_object::default_height=64;
    advanced_object::enable_physics=false;
    advanced_object::enable_rtscontrols=true;
    advanced_object::enable_keyboardcontrols=false;
    advanced_object::default_texture="SC2siegetank.bmp";
    advanced_object::default_mask="SC2siegetank-mask.bmp";
    advanced_object::default_movementsound="low_clack.wav";
    advanced_object::default_clicksound="siegetank-yessir.wav";
    advanced_object::default_collisionsound="siegetank-move_it.wav";

    advanced_object* rtso1 = new advanced_object();
    rtso1->set_position(window::center.x+96,window::center.y);//set position right of window center
    rtso1->fill_color.set("yellow");

    advanced_object* rtso2 = new advanced_object();
    rtso2->set_position(window::center.x,window::center.y-96);//set position below window center
    rtso2->fill_color.set("green");

    advanced_object* rtso3 = new advanced_object();
    rtso3->set_position(window::center.x,window::center.y+96);//set position above window center
    rtso3->fill_color.set("red");

    advanced_object* rtso4 = new advanced_object();
    rtso4->set_position(window::center.x-96,window::center.y);//set position left of window center
    rtso4->fill_color.set("blue");
//Initialize Text
    ui::label* object_info = new ui::label();
    object_info->set_spacing(20);
    object_info->set_position(50,window::height-20);

    ui::label* game_info = new ui::label();
    game_info->set_spacing(20);
    game_info->set_position(window::width-200,window::height-20);
//Initialize Checkboxes
    ui::checkbox::default_clicksound="click.wav";
    ui::checkbox::default_hoversound="swipe.wav";
//Initialize Buttons
    //set some default values
    ui::button::default_clicksound="click.wav";
    ui::button::default_hoversound="swipe.wav";
    //Main Menu Buttons
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

    ui::button* settings_button = new ui::button();
    settings_button->set_label("Settings");
    settings_button->set_action(controls::switch_menu,1);
    //Settings Menu Buttons
    ui::button* leave_settings_button = new ui::button();
    leave_settings_button->set_label("Back");
    leave_settings_button->set_action(controls::switch_menu,0);

    ui::button* music_muted_button = new ui::button();
    music_muted_button->set_label("muted");
    music_muted_button->set_action(audio::set_volume,"angrybirds_theme.wav",0);

    ui::button* music_low_button = new ui::button();
    music_low_button->set_label("low");
    music_low_button->set_action(audio::set_volume,"angrybirds_theme.wav",25);

    ui::button* music_medium_button = new ui::button();
    music_medium_button->set_label("medium");
    music_medium_button->set_action(audio::set_volume,"angrybirds_theme.wav",50);

    ui::button* music_high_button = new ui::button();
    music_high_button->set_label("high");
    music_high_button->set_action(audio::set_volume,"angrybirds_theme.wav",75);

    ui::button* ambience_muted_button = new ui::button();
    ambience_muted_button->set_label("muted");
    ambience_muted_button->set_action(audio::set_volume,"angrybirds_theme.wav",0);

    ui::button* ambience_low_button = new ui::button();
    ambience_low_button->set_label("low");
    ambience_low_button->set_action(audio::set_volume,"angrybirds_theme.wav",25);

    ui::button*ambience_medium_button = new ui::button();
    ambience_medium_button->set_label("medium");
    ambience_medium_button->set_action(audio::set_volume,"angrybirds_theme.wav",50);

    ui::button* ambience_high_button = new ui::button();
    ambience_high_button->set_label("high");
    ambience_high_button->set_action(audio::set_volume,"angrybirds_theme.wav",75);

    ui::button* sfx_muted_button = new ui::button();
    sfx_muted_button->set_label("muted");
    sfx_muted_button->set_action(audio::set_volume,"angrybirds_theme.wav",0);

    ui::button* sfx_low_button = new ui::button();
    sfx_low_button->set_label("low");
    sfx_low_button->set_action(audio::set_volume,"angrybirds_theme.wav",25);

    ui::button*sfx_medium_button = new ui::button();
    sfx_medium_button->set_label("medium");
    sfx_medium_button->set_action(audio::set_volume,"angrybirds_theme.wav",50);

    ui::button* sfx_high_button = new ui::button();
    sfx_high_button->set_label("high");
    sfx_high_button->set_action(audio::set_volume,"angrybirds_theme.wav",75);
    //Play Scene Buttons
    ui::button* pause_button = new ui::button();
    pause_button->set_position(window::center.x,window::height-20);//put the button at the top middle, just below the top
    pause_button->set_label("Pause");
    pause_button->set_action(game::pause);

    ui::button* delete_object_button = new ui::button();
    delete_object_button->set_position(window::width*0.9,window::height*0.05);//put the button on the right side, 1/5th of the way up
    delete_object_button->set_label("delete object");
    delete_object_button->set_clicksound("trash.wav");
//Initialize Menus
    ui::dropdown_menu* music_volume_menu = new ui::dropdown_menu();
    music_volume_menu->set_label("Music Volume");
    music_volume_menu->add_item(music_muted_button);
    music_volume_menu->add_item(music_low_button);
    music_volume_menu->add_item(music_medium_button);
    music_volume_menu->add_item(music_high_button);

    ui::dropdown_menu* ambience_volume_menu = new ui::dropdown_menu();
    ambience_volume_menu->set_label("Ambience Volume");
    ambience_volume_menu->add_item(ambience_muted_button);
    ambience_volume_menu->add_item(ambience_low_button);
    ambience_volume_menu->add_item(ambience_medium_button);
    ambience_volume_menu->add_item(ambience_high_button);

    ui::dropdown_menu* sfx_volume_menu = new ui::dropdown_menu();
    sfx_volume_menu->set_label("SFX Volume");
    sfx_volume_menu->add_item(sfx_muted_button);
    sfx_volume_menu->add_item(sfx_low_button);
    sfx_volume_menu->add_item(sfx_medium_button);
    sfx_volume_menu->add_item(sfx_high_button);

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
    settings_menu->set_layout("horizontal");
    settings_menu->add_item(music_volume_menu);
    settings_menu->add_item(ambience_volume_menu);
    settings_menu->add_item(sfx_volume_menu);
    settings_menu->add_item(leave_settings_button);
    settings_menu->hide();//we don't want to see this right away

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

    ui::dropdown_menu* creation_menu = new ui::dropdown_menu();
    creation_menu->set_position(window::width*0.9,window::height*0.5);
    creation_menu->set_label("create object...");
    creation_menu->add_item("basic object",game::add_bso);
    creation_menu->add_item("complex object",game::add_cpo);
    creation_menu->add_item("mobile object",game::add_mbo);
    creation_menu->add_item("smart object",game::add_smo);
    creation_menu->add_item("interactive object",game::add_iao);
    creation_menu->add_item("advanced object",game::add_avo);
    creation_menu->add_item("label",game::add_label);
    creation_menu->add_item("button",game::add_button);
    creation_menu->add_item("checkbox",game::add_checkbox);
    creation_menu->add_item("menu",game::add_menu);
    creation_menu->add_item("dropdown",game::add_dropdown);

    interactive_object::enable_dragging=true;
//Initialize Scenes
    scene* home_screen = new scene();
    home_screen->add_object(home_screen_background);
    home_screen->add_menu(main_menu);
    home_screen->add_menu(settings_menu);
    home_screen->add_menu(quit_menu);
    home_screen->current_menu=main_menu;
    home_screen->bind_key("up",controls::previous_item);
    home_screen->bind_key("down",controls::next_item);
    home_screen->bind_key("left",controls::previous_item);
    home_screen->bind_key("right",controls::next_item);
    home_screen->bind_key('\r',controls::choose_item);
    game::add_scene(home_screen);
    game::main_scene=home_screen;//make this the main scene
    game::current_scene=home_screen;//start with this scene

    scene* game_screen = new scene();
    game_screen->set_music("angrybirds_theme.wav");
    game_screen->add_object(play_screen_background);
    game_screen->add_object(dro1);
    game_screen->add_object(po1);
    game_screen->add_object(po2);
    game_screen->add_object(po3);
    game_screen->add_object(po4);
    game_screen->add_object(rtso1);
    game_screen->add_object(rtso2);
    game_screen->add_object(rtso3);
    game_screen->add_object(rtso4);
    game_screen->add_label(object_info);
    game_screen->add_label(game_info);
    game_screen->add_button(delete_object_button);
    game_screen->add_button(pause_button);
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
    game_screen->bind_key(27, game::pause);//27 is the 'esc' key
    game::play_scene=game_screen;
    game::add_scene(game_screen);
    game::initialize();//start the game
}
