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
int window::width=1360;
int window::height=720;
point2i window::center=point2i(width/2,height/2);
point2i window::position=point2i(0,0);
double window::refresh_rate=0.0166f;//refresh window at 1/60th of a second (for 60FPS)

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

void window::render()
{
    glClear(GL_COLOR_BUFFER_BIT);// Clear Color Buffers
    game::current_scene->render();
    cursor::selection_box();
    glFlush();
}

void window::update()
{
    ui::update_text();
    game::update();//update game
    cursor::calc_boundaries();//calculate the size of the selection box
    controls::check_clicked();//check if objects are clicked
    //This condition makes sure events occur at the set refresh rate
    if(isgreaterequal(game::time_elapsed,window::refresh_rate))//time elapsed is >= refresh rate
    {
        controls::key_operations();//keyboard controls
        game::sync();//update clock-based events in game
        glutPostRedisplay();//update the scene
    }
}
