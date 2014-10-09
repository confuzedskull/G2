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
#include "controls.h"
#include "ui.h"
#include "cursor.h"
#include "button.h"
#include <math.h>
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

//initialize the variables
int window::width=640;
int window::height=360;
int window::position_x=0;
int window::position_y=0;
double window::refresh_rate=0.0166f;

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
//NOTE: rts_objects are rendered ontop of eachother according to the order in which they are rendered
//BOTTOM
    //render the rts objects
    for(unsigned i=0; i<game::rts_objects.size(); i++)
    game::rts_objects[i]->render();
    //render the selection box
    cursor::selection_box();
    //render the draggable objects
    for(unsigned i=0; i<game::draggable_objects.size(); i++)
    game::draggable_objects[i]->render();
    //render the projectiles
    for(unsigned i=0; i<game::projectiles.size(); i++)
    game::projectiles[i].render();
    //render the physics objects
    for(unsigned i=0; i<game::physics_objects.size(); i++)
    game::physics_objects[i]->render();
    //render buttons
    for(unsigned i=0; i<game::buttons.size(); i++)
    game::buttons[i]->render();
//TOP
    if(controls::toggle_overlay)
    ui::print_overlay();
    glFlush();
}

void window::update_scene()
{
    cursor::calc_boundaries();//calculate the size of the selection box
    game::time_elapsed = ((float)clock()-game::time_started)/CLOCKS_PER_SEC;//update the start time
    //update physics objects
    for(unsigned i=0; i<game::physics_objects.size(); i++)
    game::physics_objects[i]->update();
    //update rts objects
    for(unsigned i=0; i<game::rts_objects.size(); i++)
    game::rts_objects[i]->update();
    //update draggable objects
    for(unsigned i=0; i<game::draggable_objects.size(); i++)
    game::draggable_objects[i]->update();
    //update buttons
    for(unsigned i=0; i<game::buttons.size(); i++)
    game::buttons[i]->update();
    //apply collision effects
    game::collision_detection();
    //check if objects are clicked
    controls::check_clicked();
    //This function acts like timer so that events occur at the set refresh rate
    if(isgreaterequal(game::time_elapsed,window::refresh_rate))//time elapsed is >= refresh rate
    {
        game::time_started=clock();//reset the start time
        game::time+=window::refresh_rate;//increment the game clock
        controls::key_operations();//keyboard controls
        //move rts objects
        for(unsigned i=0; i<game::rts_objects.size(); i++)
        game::rts_objects[i]->perform_actions()||game::rts_objects[i]->move_to_point(*game::rts_objects[i]->rally,2.00f);
        //move physics objects
        for(unsigned i=0; i<game::physics_objects.size(); i++)
        game::physics_objects[i]->perform_actions();
        //move projectiles
        for(unsigned i=0; i<game::projectiles.size(); i++)
        {
            game::projectiles[i].update();//update the position
            game::physics_objects[i]->inertia();
        }
        glutPostRedisplay();//update the scene
    }
}
