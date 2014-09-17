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
#include "window.h"
#include "game.h"
#include "ui.h"
#include "cursor.h"
#include "compare.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//initialize the variables
int window::width=640;
int window::height=360;
int window::position_x=100;
int window::position_y=100;
double window::refresh_rate=0.0166d;

//resize the window
void window::change_size(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    // Reset Matrix
    glLoadIdentity();
    glOrtho(0.0,(GLdouble)w,0.0,(GLdouble)h, -1.0,1.0);
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    window::width=w;//set the global window width
    window::height=h;//set the global window height
}

void window::initialize()
{
    glClearColor (1.0, 1.0, 1.0, 1.0);//white background
    glViewport(0, 0, width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)width, 0.0,(GLdouble)height, -1.0, 1.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);//white background
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void window::render_scene()
{
    glClear(GL_COLOR_BUFFER_BIT);// Clear Color Buffers
//render the projectiles
    game::projectiles[0].render();
    game::projectiles[1].render();
    game::projectiles[2].render();
    game::projectiles[3].render();
    game::projectiles[4].render();
    game::projectiles[5].render();
//render the clickable_objects
//NOTE: clickable_objects are rendered ontop of eachother according to the order in which they are rendered
//BOTTOM
    game::clickable_objects[5].render();
    game::clickable_objects[4].render();
    game::clickable_objects[3].render();
    game::clickable_objects[2].render();
    game::clickable_objects[1].render();
    game::clickable_objects[0].render();
//render the selection box
    cursor::selection_box();
//TOP
    if(ui::toggle_text)
    ui::print_text();
    glFlush();
}

void window::update_scene()
{
    ui::key_operations();//keyboard controls
    cursor::set_boundaries();//calculate the size of the selection box
    game::time_elapsed = ((float)clock()-game::time_started)/CLOCKS_PER_SEC;//update the start time
    //calculate the physics for all clickable_objects
    game::clickable_objects[0].physics();
    game::clickable_objects[1].physics();
    game::clickable_objects[2].physics();
    game::clickable_objects[3].physics();
    game::clickable_objects[4].physics();
    game::clickable_objects[5].physics();
    //calculate the physics for all projectiles
    game::projectiles[0].physics();
    game::projectiles[1].physics();
    game::projectiles[2].physics();
    game::projectiles[3].physics();
    game::projectiles[4].physics();
    game::projectiles[5].physics();
    //apply collision effects
    game::collision_detection();
    //check if objects are clicked
    ui::check_clicked();
    //mouse interactivity
    game::clickable_objects[0].mouse_function();
    game::clickable_objects[1].mouse_function();
    game::clickable_objects[2].mouse_function();
    game::clickable_objects[3].mouse_function();
    game::clickable_objects[4].mouse_function();
    game::clickable_objects[5].mouse_function();
    //This function acts like timer so that events occur at the set refresh rate
    if(compare(game::time_elapsed,window::refresh_rate)==1)//time elapsed is > refresh rate
    {
        game::time_started=clock();//reset the start time
        game::time+=window::refresh_rate;//increment the game clock
        //move clickable_objects
        game::clickable_objects[0].perform_actions();//scripted movement
        game::clickable_objects[1].move_to_point(*game::clickable_objects[1].rally);
        game::clickable_objects[2].move_to_point(*game::clickable_objects[2].rally);
        game::clickable_objects[3].move_to_point(*game::clickable_objects[3].rally);
        game::clickable_objects[4].move_to_point(*game::clickable_objects[4].rally);
        game::clickable_objects[5].move_to_point(*game::clickable_objects[5].rally);
        //move game::projectiles
        game::projectiles[0].update();
        game::projectiles[1].update();
        game::projectiles[2].update();
        game::projectiles[3].update();
        game::projectiles[4].update();
        game::projectiles[5].update();
        glutPostRedisplay();//update the scene
    }
}
