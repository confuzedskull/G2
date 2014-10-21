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
void scene::render()
{
    glClearColor(background_color.r, background_color.g, background_color.b, 0.5);//background
    //render the rts objects
    for(std::map<int,rts_object*>::iterator i=rts_objects.begin(); i!=rts_objects.end(); ++i)
    i->second->render();
    //render the selection box
    cursor::selection_box();
    //render the draggable objects
    for(std::map<int,draggable_object*>::iterator i=draggable_objects.begin(); i!=draggable_objects.end(); ++i)
    i->second->render();
    //render the physics objects
    for(std::map<int,physics_object*>::iterator i=physics_objects.begin(); i!=physics_objects.end(); ++i)
    i->second->render();
    //render text
    for(unsigned i=0; i<text_objects.size(); i++)
    text_objects[i]->render();
    //render menus
    for(unsigned i=0; i<menus.size(); i++)
    menus[i]->render();
    //render buttons
    for(unsigned i=0; i<buttons.size(); i++)
    buttons[i]->render();
}

void scene::update()
{
    //update physics objects
    for(std::map<int,physics_object*>::iterator i=physics_objects.begin(); i!=physics_objects.end(); ++i)
    i->second->update();
    //update rts objects
    for(std::map<int,rts_object*>::iterator i=rts_objects.begin(); i!=rts_objects.end(); ++i)
    i->second->update();
    //update draggable objects
    for(std::map<int,draggable_object*>::iterator i=draggable_objects.begin(); i!=draggable_objects.end(); ++i)
    i->second->update();
    //update menus
    for(unsigned i=0; i<menus.size(); i++)
    menus[i]->update();
    //update buttons
    for(unsigned i=0; i<buttons.size(); i++)
    buttons[i]->update();
}

scene::scene()
{
    background_color.set(0.25,0.25,0.25);
}
