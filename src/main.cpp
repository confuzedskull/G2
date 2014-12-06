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
#include "game.h"
#include "controls.h"
#include "audio.h"
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
#include <iostream>

int main(int argc, char **argv)
{
    audio::load();
    std::clog<<"initializing...\n";
    game::initialize();
    game::load_settings();
    // initialize GLUT and create window
    std::clog<<"initializing GLUT...\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE || GLUT_RGB);
    std::clog<<"initializing window...\n";
    glutInitWindowPosition(window::position.x,window::position.y);
    glutInitWindowSize(window::width,window::height);
    glutCreateWindow("2DWorld");
    window::initialize();
    glutReshapeFunc(window::change_size);
    glutIdleFunc(window::update);
    std::clog<<"initializing keyboard...\n";
    glutKeyboardFunc(controls::key_pressed);
    glutKeyboardUpFunc(controls::key_released);
    glutSpecialFunc(controls::special_keys);
    std::clog<<"initializing mouse...\n";
    glutMouseFunc(controls::mouse_click);
    glutPassiveMotionFunc(controls::mouse_move);
    glutMotionFunc(controls::mouse_drag);
    std::clog<<"rendering...\n";
    glutDisplayFunc(window::render);
    glutMainLoop();
}
