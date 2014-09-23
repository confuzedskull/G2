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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "window.h"
#include "game.h"
#include "ui.h"

int main(int argc, char **argv)
{
    std::clog<<"entering main...\n";
    /* initialize random seed: */
    srand (time(NULL));
    //initialize objects
    std::clog<<"initializing objects...\n";
    game::init_objects();
    // initialize GLUT and create window
    std::clog<<"initializing GLUT...\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE || GLUT_RGB);
    std::clog<<"creating window...\n";
    glutInitWindowPosition(window::position_x,window::position_y);
    std::clog<<"window position: "<< window::position_x<< ","<< window::position_y<<std::endl;
    glutInitWindowSize(window::width,window::height);
    std::clog<<"window size: "<<window::width<<"X"<< window::height<<std::endl;
    glutCreateWindow("2D World");
    window::initialize();
    glutReshapeFunc(window::change_size);
    glutIdleFunc(window::update_scene); //use this for animations
    glutKeyboardFunc(ui::key_pressed); // Tell GLUT to use the method "keyPressed" for key presses
    glutKeyboardUpFunc(ui::key_up); // Tell GLUT to use the method "keyUp" for key releases
    glutMouseFunc(ui::mouse_click);
    glutMotionFunc(ui::mouse_drag);
    glutDisplayFunc(window::render_scene);
    std::clog<<"rendering...\n";
    glutMainLoop();
}
