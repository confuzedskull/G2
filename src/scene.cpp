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

#include "scene.h"
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

//NOTE: This function uses C++11 "for" loops
void scene::render()
{
    glClearColor(background_color.r, background_color.g, background_color.b, 0.5);//background
    //render the rts objects
    for(auto r:rts_objects)
    r.second->render();
    //render the selection box
    cursor::selection_box();
    //render the draggable objects
    for(auto d:draggable_objects)
    d.second->render();
    //render the physics objects
    for(auto p:physics_objects)
    p.second->render();
    //render text
    for(auto t:text_objects)
    t->render();
    //render menus
    for(auto m:menus)
    m->render();
    //render buttons
    for(auto b:buttons)
    b->render();
}

//NOTE: This function uses C++11 "for" loops
void scene::update()
{
    //update physics objects
    for(auto p:physics_objects)
    p.second->update();
    //update rts objects
    for(auto r:rts_objects)
    r.second->update();
    //update draggable objects
    for(auto d:draggable_objects)
    d.second->update();
    //update menus
    for(auto m:menus)
    m->update();
    //update buttons
    for(auto b:buttons)
    b->update();
}

scene::scene()
{
    background_color.set(0.25,0.25,0.25);//set the color to dark gray
}
